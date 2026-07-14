
#include "GeminiClient.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "utils/Logger.h"

using json = nlohmann::json;

GeminiClient::GeminiClient(const std::string& key) : apiKey(key) {}

size_t GeminiClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GeminiClient::phânTíchCV(const std::string& rawText, const std::string& prompt) {
    if (apiKey.empty()) {
        LOG_ERROR("Gemini API Key is empty!");[cite: 36];
        return "{}";
    }

    CURL* curl = curl_easy_init();
    std::string responseString;

    if (curl) {
        // Endpoint chính thức của phiên bản Gemini 1.5 Flash (phù hợp cho việc xử lý text nhanh)
        std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + apiKey;

        // Tạo cấu trúc JSON Payload theo đúng quy định của Google API
        json payload = {
            {"contents", {
                {{"parts", {
                    {{"text", prompt + "\n\nNội dung CV:\n" + rawText}}
                }}}
            }}
        };
        std::string jsonStr = payload.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        // Thực hiện cuộc gọi mạng
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            LOG_ERROR("CURL Request failed: " + std::string(curl_easy_strerror(res)));[cite: 36];
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return responseString;
}