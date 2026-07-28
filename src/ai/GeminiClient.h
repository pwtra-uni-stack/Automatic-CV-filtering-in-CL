#ifndef CV_AUTO_GEMINICLIENT_H
#define CV_AUTO_GEMINICLIENT_H

#include <string>
#include "IAIClient.h"

class GeminiClient : public IAIClient {
private:
    std::string apiKey;

public:
    // Constructor nhận key
    explicit GeminiClient(const std::string& key = "");

    // Hàm phân tích CV
    std::string phânTíchCV(const std::string& rawText, const std::string& prompt);

    // Hàm đánh giá CV (kế thừa hoặc gọi lại phânTíchCV)
    std::string danhGiaCV(std::string noiDungCV, std::string yeuCauJob) override;
};

#endif //CV_AUTO_GEMINICLIENT_H
