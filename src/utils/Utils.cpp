#include "Utils.h"
#include <sstream>

std::string Utils::trim(std::string str) {
    size_t dau = str.find_first_not_of(" \t\r\n");
    if (dau == std::string::npos) return "";

    size_t cuoi = str.find_last_not_of(" \t\r\n");
    return str.substr(dau, (cuoi - dau + 1));
}

std::vector<std::string> Utils::split(std::string str, char text_chia) {
    std::vector<std::string> cac_tu;
    std::string tu;
    std::stringstream ss(str);

    while (std::getline(ss, tu, text_chia)) {
        cac_tu.push_back(trim(tu));
    }
    return cac_tu;
}
