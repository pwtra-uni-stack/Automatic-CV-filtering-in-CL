//
// Created by admin on 10/07/2026.
//

#ifndef LTHDT_UTILS_H
#define LTHDT_UTILS_H
#include <string>
#include <vector>

class Utils {
public:
    static std::string trim(std::string str);
    static std::vector<std::string> split(std::string str, char text_chia);
};
#endif