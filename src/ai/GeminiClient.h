#ifndef CV_AUTO_GEMINICLIENT_H
#define CV_AUTO_GEMINICLIENT_H

#include <string>

class GeminiClient {
private:
    std::string apiKey;
    // Hàm hỗ trợ libcurl ghi dữ liệu nhận được từ API vào chuỗi string
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

public:
    GeminiClient(const std::string& key);
    // Hàm gửi nội dung CV và Prompt tới Gemini, trả về phản hồi dạng văn bản
    std::string phânTíchCV(const std::string& rawText, const std::string& prompt);
};


#endif //CV_AUTO_GEMINICLIENT_H
