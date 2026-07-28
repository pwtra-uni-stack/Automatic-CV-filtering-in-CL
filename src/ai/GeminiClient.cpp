#include "GeminiClient.h"
#include <nlohmann/json.hpp>
#include "utils/Logger.h"

using json = nlohmann::json;

GeminiClient::GeminiClient(const std::string& key) : apiKey(key) {}

std::string GeminiClient::phânTíchCV(const std::string& rawText, const std::string& prompt) {
    if (apiKey.empty()) {
        LOG_ERROR("Gemini API Key is empty!");
        return "{}";
    }

    LOG_INFO("Processing CV analysis (Mock Mode without cURL)...");

    // Tạo dữ liệu JSON giả lập trả về cho CVService chấm điểm
    json mockResult = {
        {"name", "Nguyen Van A"},
        {"email", "nguyenvana@example.com"},
        {"score", 85},
        {"experience_years", 3},
        {"skills", {"C++", "Python", "CMake"}}
    };

    return mockResult.dump();
}

// Nếu file GeminiClient.h có định nghĩa hàm danhGiaCV
std::string GeminiClient::danhGiaCV(std::string noiDungCV, std::string yeuCauJob) {
    return phânTíchCV(noiDungCV, yeuCauJob);
}
