//
// Created by ADMIN on 22/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_AIFACTORY_H
#define AUTOMATIC_CV_FILTERING_IN_CL_AIFACTORY_H
#include "IAIClient.h"
#include "GeminiClient.h"
#include "OllamaClient.h"
#include <memory>
#include <string>

class AIFactory {
public:
    enum Provider {
        GEMINI,
        OLLAMA
    };

    static std::unique_ptr<IAIClient> createClient(Provider type) {
        if (type == GEMINI) {
            return std::make_unique<GeminiClient>();
        } else {
            return std::make_unique<OllamaClient>("qwen2.5:7b");
        }
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_AIFACTORY_H
