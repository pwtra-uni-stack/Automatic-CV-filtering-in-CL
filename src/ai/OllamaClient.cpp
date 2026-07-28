#include "OllamaClient.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

// Constructor
OllamaClient::OllamaClient(std::string modelName) {
    url = "http://localhost:11434/api/generate";
    model = modelName;
}

// Hàm gửi câu hỏi (Mock Mode - Bỏ cURL)
std::string OllamaClient::guiCauHoi(std::string prompt) {
    json mockResult = {
        {"response", "Mock Ollama response for prompt: " + prompt}
    };

    return mockResult.dump();
}

// Hàm đánh giá CV
std::string OllamaClient::danhGiaCV(std::string noiDungCV, std::string yeuCauJob) {
    std::string prompt = "Ban la chuyen gia tuyen dung. Hay phan tich CV va so sanh voi Yeu cau cong viec (JD).\n\n"
                         "=== YEU CAU CONG VIEC ===\n" + yeuCauJob + "\n\n"
                         "=== NOI DUNG CV ===\n" + noiDungCV + "\n\n"
                         "Dua ra danh gia ngan gon.";

    return guiCauHoi(prompt);
}
