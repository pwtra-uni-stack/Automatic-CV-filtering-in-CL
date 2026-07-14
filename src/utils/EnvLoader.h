//
// Created by ADMIN on 14/07/2026.
//

#ifndef CV_AUTO_ENVLOADER_H
#define CV_AUTO_ENVLOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include "Utils.h" // Tận dụng hàm trim của bạn để làm sạch dữ liệu

class EnvLoader {
public:
    static std::string getEnv(const std::string& key, const std::string& filepath = ".env") {
        std::ifstream file(filepath);
        if (!file.is_open()) return "";

        std::string line;
        while (std::getline(file, line)) {
            // Bỏ qua dòng trống hoặc dòng comment
            if (line.empty() || line[0] == '#') continue;

            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string currentKey = Utils::trim(line.substr(0, delimiterPos));
                if (currentKey == key) {
                    return Utils::trim(line.substr(delimiterPos + 1));
                }
            }
        }
        return "";
    }
};


#endif //CV_AUTO_ENVLOADER_H
