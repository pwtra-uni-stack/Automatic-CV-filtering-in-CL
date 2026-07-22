#ifndef CV_AUTO_GEMINICLIENT_H
#define CV_AUTO_GEMINICLIENT_H

#include <string>

#include "IAIClient.h"

class GeminiClient : public IAIClient {
private:
    std::string apiKey;
    std::string modelName;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);

public:
    GeminiClient();
    std::str


#endif //CV_AUTO_GEMINICLIENT_H
