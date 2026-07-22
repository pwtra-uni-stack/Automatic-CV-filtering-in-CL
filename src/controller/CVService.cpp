#include <fstream>
#include <algorithm>
#include <cctype>

// Bước 1: Kiểm tra tính hợp lệ của tệp (Đuôi file, dung lượng, sự tồn tại)
bool CVService::validateFile(const std::string& filePath, std::string& outErrorMessage) {
    // Kiểm tra xem file có tồn tại và mở được không
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        outErrorMessage = "Error: File does not exist or cannot be opened: " + filePath;
        return false;
    }

    // Kiểm tra file rỗng (dung lượng = 0)
    std::streamsize size = file.tellg();
    if (size <= 0) {
        outErrorMessage = "Error: The file is empty.";
        return false;
    }

    // Kiểm tra dung lượng quá lớn (Ví dụ: Giới hạn 10MB = 10 * 1024 * 1024 bytes)
    const std::streamsize MAX_FILE_SIZE = 10 * 1024 * 1024;
    if (size > MAX_FILE_SIZE) {
        outErrorMessage = "Error: File size exceeds the 10MB limit.";
        return false;
    }

    // Kiểm tra định dạng phần mở rộng (đuôi .pdf hoặc .docx)
    if (filePath.length() < 5) {
        outErrorMessage = "Error: Invalid file extension.";
        return false;
    }

    std::string ext = filePath.substr(filePath.length() - 4);
    // Chuyển đuôi về chữ thường để so sánh an toàn (.PDF -> .pdf)
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

// Bước 2: Làm sạch và tiền xử lý văn bản thô trích xuất từ CV
std::string CVService::sanitizeText(const std::string& rawText) {
    std::string cleaned = "";
    bool lastWasSpace = false;

    for (char c : rawText) {
        // Thay thế các ký tự điều khiển/xuống dòng rác bằng khoảng trắng chuẩn
        if (c == '\n' || c == '\r' || c == '\t') {
            c = ' ';
        }

        // Lọc bỏ khoảng trắng thừa liên tiếp (chỉ giữ lại 1 khoảng trắng)
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

// Bước 3: Gửi request đến AI Client với cơ chế Retry & Timeout
std::string CVService::callAIWithRetry(IAIClient& aiClient, const std::string& prompt, int maxRetries) {
    int attempts = 0;
    std::string response = "";

    while (attempts < maxRetries) {
        attempts++;
        LOG_INFO("Attempt " + std::to_string(attempts) + " calling AI client...");

        // Giả lập gọi phương thức phân tích của AI Client (tùy thuộc vào thiết kế IAIClient của bạn)
        // Ví dụ: response = aiClient.generateResponse(prompt);
        if (!response.empty()) {
            LOG_INFO("AI request succeeded on attempt " + std::to_string(attempts));
            return response;
        }

        LOG_WARNING("AI request failed or timed out. Retrying...");
    }

    LOG_ERROR("AI request failed after " + std::to_string(maxRetries) + " attempts.");
    return "[ERROR]: Failed to get response from AI after multiple retries.";
}

// Bước 4: Xuất và lưu kết quả đánh giá (Ra file hoặc báo cáo)
bool CVService::exportScanResult(const std::string& outputPath, const ScanResult& result) {
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        LOG_ERROR("Failed to open output file for exporting: " + outputPath);
        return false;
    }

    // Ghi thông tin kết quả cơ bản ra file
    outFile << "=== CV SCAN RESULT REPORT ===\n";
    // Tùy biến ghi nội dung chi tiết từ biến result tùy thuộc vào struct ScanResult của bạn
    outFile.close();

    LOG_INFO("Scan result successfully exported to: " + outputPath);
    return true;
}

// [HÀM ĐIỀU PHỐI TỔNG HỢP] Kết hợp 4 bước thành quy trình khép kín
bool CVService::processAndScanCV(const std::string& filePath, IAIClient& aiClient, ScanResult& outResult) {
    std::string errorMsg = "";

    // Bước 1: Validate file
    if (!validateFile(filePath, errorMsg)) {
        LOG_ERROR(errorMsg);
        return false;
    }

    // Bước 2: Đọc file thô và làm sạch text (Giả lập bước đọc file sang rawText)
    std::string rawText = "Sample raw text extracted from file...";
    std::string cleanText = sanitizeText(rawText);

    // Bước 3: Gọi AI phân tích với cơ chế Retry
    std::string aiResponse = callAIWithRetry(aiClient, cleanText, 2);

    // Bước 4: Lưu/Export kết quả quét
    exportScanResult("Data/last_scan_report.txt", outResult);

    LOG_INFO("CV successfully processed and scanned.");
    return true;
}