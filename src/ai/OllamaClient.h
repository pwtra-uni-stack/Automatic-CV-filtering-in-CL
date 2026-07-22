//
// Created by khánh linh on 22/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_OLLAMACLIENT_H
#define AUTOMATIC_CV_FILTERING_IN_CL_OLLAMACLIENT_H
#include <string>

#include "IAIClient.h"

class OllamaClient : public IAIClient {
private:
    std::string url;
    std::string model;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

public:
    OllamaClient(std::string modelName = "qwen2.5:7b");
    std::string guiCauHoi(std::string prompt);
    std::string danhGiaCV(std::string noiDungCV, std::string yeuCauJob) override;
};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_OLLAMACLIENT_H
