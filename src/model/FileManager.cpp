#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// Các parser giả lập (giữ nguyên để minh hoạ)
class DocxParser { public: std::string extractText(std::string p) { return "[Nội dung Docx thực tế]"; } };
class PdfParser  { public: std::string extractText(std::string p) { return "[Nội dung Pdf thực tế]"; } };

// ----- Hàm trích xuất giá trị theo cặp từ khoá -----
std::string FileManager::layGiaTri(std::string text, std::string tuKhoaBatDau, std::string tuKhoaKetThuc) {
    size_t viTriDau = text.find(tuKhoaBatDau);
    if (viTriDau == std::string::npos) return "";
    viTriDau += tuKhoaBatDau.length();

    size_t viTriCuoi = text.find(tuKhoaKetThuc, viTriDau);
    if (viTriCuoi == std::string::npos) {
        return text.substr(viTriDau);
    }
    return text.substr(viTriDau, viTriCuoi - viTriDau);
}

// ----- Phân tích text -> đối tượng CV (trả về con trỏ động) -----
CV* FileManager::parseCVText(const std::string& raw_text) {
    // Lấy các trường từ text
    std::string id      = layGiaTri(raw_text, "ID: ", "\n");
    std::string name    = layGiaTri(raw_text, "Ten: ", "\n");
    std::string email   = layGiaTri(raw_text, "Email: ", "\n");
    std::string skills_raw = layGiaTri(raw_text, "Ky nang: ", "\n");
    std::string exp_raw = layGiaTri(raw_text, "Kinh nghiem: ", "\n");
    std::string edu     = layGiaTri(raw_text, "Hoc van: ", "\n");

    // --- CHUẨN HÓA ID: LUÔN CÓ TIỀN TỐ "CV_" ---
    if (id.empty()) {
        id = "CV_0"; // fallback an toàn
    } else if (id.compare(0, 3, "CV_") != 0) {
        id = "CV_" + id;
    }

    // Tách kỹ năng
    std::vector<std::string> skills;
    std::stringstream ss(skills_raw);
    std::string token;
    while (std::getline(ss, token, ',')) {
        while (!token.empty() && token[0] == ' ') token.erase(0, 1);
        while (!token.empty() && token[token.length() - 1] == ' ') token.erase(token.length() - 1, 1);
        if (!token.empty()) skills.push_back(token);
    }

    // Đọc số năm kinh nghiệm
    int exp_years = 0;
    if (!exp_raw.empty()) {
        std::stringstream chuyenDoi(exp_raw);
        chuyenDoi >> exp_years;
    }

    // Tạo đối tượng Candidate động (sẽ được CV quản lý)
    Candidate* cand = new Candidate("CAND_" + id, name, email);

    // Tạo CV động và trả về
    return new CV(id, cand, skills, exp_years, edu, raw_text, 0);
}

// ----- Lấy danh sách file trong thư mục -----
std::vector<std::string> FileManager::getCVFiles(const std::string& directory) {
    std::vector<std::string> files;
    if (!fs::exists(directory) || !fs::is_directory(directory)) return files;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

// ----- Trích xuất nội dung thô từ file (hỗ trợ .txt, .docx, .pdf) -----
std::string FileManager::extractTextFromFile(const std::string& filePath) {
    fs::path p(filePath);
    std::string ext = p.extension().string();

    if (ext == ".txt") {
        std::ifstream file(filePath);
        if (!file.is_open()) return "";
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    else if (ext == ".docx") {
        DocxParser parser;
        return parser.extractText(filePath);
    }
    else if (ext == ".pdf") {
        PdfParser parser;
        return parser.extractText(filePath);
    }
    return "";
}

// ----- Load một CV từ file, trả về con trỏ -----
CV* FileManager::loadCVFromFile(const std::string& filePath) {
    std::string text = extractTextFromFile(filePath);
    if (text.empty()) return nullptr;
    return parseCVText(text);   // parseCVText đã trả về CV* mới
}

// ----- Lưu danh sách CV vào file văn bản -----
bool FileManager::saveAllCVs(const std::string& path, const std::vector<CV*>& cvs) {
    std::ofstream file(path);
    if (!file.is_open()) return false;

    for (size_t i = 0; i < cvs.size(); i++) {
        if (cvs[i] == nullptr) continue;
        file << "=========================\n";
        file << "ID: " << cvs[i]->id << "\n";
        file << "Ten: " << cvs[i]->candidate->name << "\n";
        file << "Email: " << cvs[i]->candidate->email << "\n";
        file << "Experience: " << cvs[i]->experienceYears << "\n";
        file << "Education: " << cvs[i]->education << "\n";
    }
    file.close();
    return true;
}