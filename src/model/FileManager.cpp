#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

class DocxParser { public: std::string extractText(std::string p) { return "[Nội dung Docx thực tế]"; } };
class PdfParser { public: std::string extractText(std::string p) { return "[Nội dung Pdf thực tế]"; } };

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

CV FileManager::parseCVText(std::string raw_text) {
    std::string cv_id = layGiaTri(raw_text, "ID: ", "\n");
    std::string name = layGiaTri(raw_text, "Ten: ", "\n");
    std::string email = layGiaTri(raw_text, "Email: ", "\n");
    std::string skills_raw = layGiaTri(raw_text, "Ky nang: ", "\n");
    std::string exp_raw = layGiaTri(raw_text, "Kinh nghiem: ", "\n");
    std::string edu = layGiaTri(raw_text, "Hoc van: ", "\n");

    std::vector<std::string> skills;
    std::stringstream ss(skills_raw);
    std::string token;
    while (std::getline(ss, token, ',')) {
        while (!token.empty() && token[0] == ' ') token.erase(0, 1);
        while (!token.empty() && token[token.length() - 1] == ' ') token.erase(token.length() - 1, 1);
        skills.push_back(token);
    }

    int exp_years = 0;
    if (!exp_raw.empty()) {
        std::stringstream chuyenDoi(exp_raw);
        chuyenDoi >> exp_years;
    }

    Candidate cand("CAND_" + cv_id, name, email);
    return CV(cv_id, cand, skills, exp_years, edu, raw_text);
}

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

CV* FileManager::loadCVFromFile(const std::string& filePath) {
    std::string text = extractTextFromFile(filePath);
    if (text.empty()) return nullptr;
    CV cv = parseCVText(text);
    return new CV(cv.cv_id, cv.candidate, cv.skills, cv.experience_years, cv.education, text);
}
bool FileManager::saveAllCVs(const std::string& path, const std::vector<CV*>& cvs) {
    std::ofstream file(path);
    if (!file.is_open()) return false;

    for (size_t i = 0; i < cvs.size(); i++) {
        if (cvs[i] == nullptr) continue;
        file << "=========================\n";
        file << "ID: " << cvs[i]->cv_id << "\n";
        file << "Ten: " << cvs[i]->candidate.name << "\n";
        file << "Email: " << cvs[i]->candidate.email << "\n";
        file << "Experience: " << cvs[i]->experience_years << "\n";
        file << "Education: " << cvs[i]->education << "\n";
    }
    file.close();
    return true;
}
