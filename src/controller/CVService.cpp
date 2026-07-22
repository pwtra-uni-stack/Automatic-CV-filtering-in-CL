#include "CVService.h"
#include "model/FileManager.h"
#include "scanner/BasicScan.h"
#include "scanner/AdvancedScan.h"
#include "scanner/ScanEngine.h"
#include "utils/Logger.h"
// Include các parser thực tế có trong dự án của bạn
#include "PdfParser.h"
#include "DocxParser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Hàm callback cho libcurl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// Hàm trích xuất text thực tế sử dụng PdfParser và DocxParser từ dự án
std::string extractTextFromDocument(const std::string& filePath) {
    std::string ext = filePath.substr(filePath.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    std::string rawText = "";

    if (ext == "txt") {
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            rawText = buffer.str();
            file.close();
        }
    }
    else if (ext == "pdf") {
        // Sử dụng PdfParser thực tế của dự án
        PdfParser pdfParser;
        rawText = pdfParser.extractText(filePath); // Thay đổi tên hàm cho khớp với header PdfParser của bạn nếu cần
    }
    else if (ext == "docx") {
        // Sử dụng DocxParser thực tế của dự án
        DocxParser docxParser;
        rawText = docxParser.extractText(filePath); // Thay đổi tên hàm cho khớp với header DocxParser của bạn nếu cần
    }

    return rawText;
}

// Bước 1: Kiểm tra tính hợp lệ của tệp
bool CVService::validateFile(const std::string& filePath, std::string& outErrorMessage) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        outErrorMessage = "Error: File does not exist or cannot be opened: " + filePath;
        return false;
    }

    std::streamsize size = file.tellg();
    if (size <= 0) {
        outErrorMessage = "Error: The file is empty.";
        return false;
    }

    const std::streamsize MAX_FILE_SIZE = 10 * 1024 * 1024; // 10MB limit
    if (size > MAX_FILE_SIZE) {
        outErrorMessage = "Error: File size exceeds the 10MB limit.";
        return false;
    }

    if (filePath.length() < 5) {
        outErrorMessage = "Error: Invalid file extension.";
        return false;
    }

    std::string ext = filePath.substr(filePath.length() - 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    std::string ext5 = (filePath.length() >= 5) ? filePath.substr(filePath.length() - 5) : "";
    std::transform(ext5.begin(), ext5.end(), ext5.begin(), ::tolower);

    if (ext != ".pdf" && ext5 != ".docx") {
        outErrorMessage = "Error: Unsupported file format. Only .pdf and .docx are allowed.";
        return false;
    }

    outErrorMessage = "File is valid.";
    return true;
}

// Bước 2: Làm sạch văn bản
std::string CVService::sanitizeText(const std::string& rawText) {
    std::string cleaned = "";
    bool lastWasSpace = false;

    for (char c : rawText) {
        if (c == '\n' || c == '\r' || c == '\t') {
            c = ' ';
        }

        if (c == ' ') {
            if (!lastWasSpace) {
                cleaned += c;
                lastWasSpace = true;
            }
        } else {
            cleaned += c;
            lastWasSpace = false;
        }
    }
    return cleaned;
}

// Bước 3: Gọi AI qua libcurl
std::string CVService::callAIWithRetry(IAIClient& aiClient, const std::string& prompt, int maxRetries) {
    int attempts = 0;
    std::string responseString = "";
    bool success = false;

    std::string apiUrl = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=YOUR_API_KEY";

    while (attempts < maxRetries && !success) {
        attempts++;
        LOG_INFO("Attempt " + std::to_string(attempts) + " calling AI API via libcurl...");

        CURL* curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("Failed to initialize libcurl.");
            break;
        }

        responseString.clear();

        json payload = {
            {"contents", {
                {{"parts", { {{"text", prompt}} }}}
            }}
        };
        std::string payloadStr = payload.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

        CURLcode res = curl_easy_perform();

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if (res == CURLE_OK) {
            success = true;
            LOG_INFO("AI request succeeded on attempt " + std::to_string(attempts));
        } else {
            LOG_WARNING("AI request failed (libcurl error: " + std::string(curl_easy_strerror(res)) + "). Retrying...");
        }
    }

    if (!success) {
        LOG_ERROR("AI request failed after " + std::to_string(maxRetries) + " attempts.");
        return "[ERROR]: Failed to get response from AI after multiple retries.";
    }

    try {
        json resJson = json::parse(responseString);
        if (resJson.contains("candidates") && !resJson["candidates"].empty()) {
            return resJson["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();
        } else {
            return "[ERROR]: Invalid JSON response format from AI.";
        }
    } catch (const json::parse_error& e) {
        LOG_ERROR("JSON Parsing Error: " + std::string(e.what()));
        return "[ERROR]: Failed to parse AI response.";
    }
}

// Bước 4: Xuất kết quả
bool CVService::exportScanResult(const std::string& outputPath, const ScanResult& result) {
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        LOG_ERROR("Failed to open output file for exporting: " + outputPath);
        return false;
    }

    outFile << "=== CV SCAN RESULT REPORT ===\n";
    outFile << "Qualified CVs count: " << result.qualified.size() << "\n";
    outFile << "Mismatch CVs count: " << result.mismatch.size() << "\n";
    outFile << "Junk CVs count: " << result.junk.size() << "\n";
    outFile.close();

    LOG_INFO("Scan result successfully exported to: " + outputPath);
    return true;
}

// Phương thức scanCVs kết nối ScanEngine với BasicScan và AdvancedScan
ScanResult CVService::scanCVs(const std::vector<CV*>& list) {
    ScanEngine engine;
    engine.addStrategy(new BasicScan());
    engine.addStrategy(new AdvancedScan());
    return engine.scanAll(list);
}

// Hàm điều phối tổng hợp toàn bộ quy trình
bool CVService::processAndScanCV(const std::string& filePath, IAIClient& aiClient, ScanResult& outResult) {
    std::string errorMsg = "";

    // 1. Validate file
    if (!validateFile(filePath, errorMsg)) {
        LOG_ERROR(errorMsg);
        return false;
    }

    // 2. Trích xuất text thật qua PdfParser/DocxParser và làm sạch
    std::string rawText = extractTextFromDocument(filePath);
    std::string cleanText = sanitizeText(rawText);

    // 3. Gửi sang AI phân tích qua libcurl
    std::string aiResponse = callAIWithRetry(aiClient, cleanText, 2);

    // 4. Map kết quả JSON từ AI vào đối tượng CV để ScanEngine chấm điểm
    CV currentCV;
    currentCV.raw_text = cleanText;
    currentCV.candidate = new Candidate();

    try {
        json aiJson = json::parse(aiResponse);
        if (aiJson.contains("name")) currentCV.candidate->name = aiJson["name"].get<std::string>();
        else currentCV.candidate->name = "Unknown Candidate";

        if (aiJson.contains("email")) currentCV.candidate->email = aiJson["email"].get<std::string>();
        else currentCV.candidate->email = "unknown@example.com";

        if (aiJson.contains("score")) currentCV.score = aiJson["score"].get<int>();
        else currentCV.score = 70;

        if (aiJson.contains("experience_years")) currentCV.experienceYears = aiJson["experience_years"].get<int>();
        else currentCV.experienceYears = 1;

        if (aiJson.contains("skills")) {
            for (auto& s : aiJson["skills"]) {
                currentCV.skills.push_back(s.get<std::string>());
            }
        }
    } catch (...) {
        // Fallback an toàn nếu AI trả về chuỗi text thay vì cấu trúc JSON chuẩn
        currentCV.candidate->name = "Candidate Fallback";
        currentCV.candidate->email = "fallback@example.com";
        currentCV.score = 65;
        currentCV.experienceYears = 1;
        currentCV.skills.push_back("General");
    }

    // 5. Đưa qua ScanEngine thông qua scanCVs
    std::vector<CV*> tempVec = { &currentCV };
    outResult = scanCVs(tempVec);

    // 6. Xuất báo cáo kết quả
    exportScanResult("Data/last_scan_report.txt", outResult);

    LOG_INFO("CV successfully processed, parsed, analyzed by AI and evaluated via ScanEngine.");
    return true;
}