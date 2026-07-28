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

public:
    explicit OllamaClient(std::string modelName = "llama2");

    std::string guiCauHoi(std::string prompt);

    // Khai báo khớp chính xác với IAIClient:
    std::string danhGiaCV(std::string noiDungCV, std::string yeuCauJob) override;
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_OLLAMACLIENT_H
