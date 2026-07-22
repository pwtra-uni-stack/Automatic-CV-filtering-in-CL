#include "OllamaClient.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

// Constructor bình thường
OllamaClient::OllamaClient(std::string modelName) {
    url = "http://localhost:11434/api/generate";
    model = modelName;
}

size_t OllamaClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}//hi

std::string OllamaClient::guiCauHoi(std::string prompt) {
    CURL* curl = curl_easy_init();
    std::string responseString = "";

    if (curl) {
        json j = {
            {"model", model},
            {"prompt", prompt},
            {"stream", false}
        };

        std::string jsonText = j.dump();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonText.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if (res == CURLE_OK) {
            try {
                auto resJson = json::parse(responseString);
                return resJson["response"].get<std::string>();
            } catch (...) {
                return "Loi: Khong the parse JSON tra ve!";
            }
        }
    }
    return "Loi: Khong ket noi duoc toi Ollama!";
}

std::string OllamaClient::danhGiaCV(std::string noiDungCV, std::string yeuCauJob) {
    std::string prompt = "Ban la chuyen gia tuyen dung. Hay phan tich CV va so sanh voi Yeu cau cong viec (JD).\n\n"
                         "=== YEU CAU CONG VIEC ===\n" + yeuCauJob + "\n\n"
                         "=== NOI DUNG CV ===\n" + noiDungCV + "\n\n"
                         "Dua ra danh gia ngan gon bao gom:\n"
                         "1. Diem phu hop (thang diem 100)\n"
                         "2. Ky nang dat yeu cau\n"
                         "3. Ky nang con thieu\n"
                         "4. Nhan xet chung.";

    return guiCauHoi(prompt);
}