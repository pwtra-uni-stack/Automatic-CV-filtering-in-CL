#include "DocxParser.h"
#include <string>
#include <fstream>
#include <iostream>

std::string DocxParser::parse(std::string duong_dan_file) {
    std::ifstream file(duong_dan_file);
    if (!file.is_open()) {
        std::cout << "Loi: Khong mo duoc file CV tai: " << duong_dan_file << std::endl;
        return "";
    }
    std::string noi_dung_tong = "";
    std::string dong_chu;
    while (std::getline(file, dong_chu)) {
        noi_dung_tong += dong_chu + "\n";
    }
    file.close();
    return noi_dung_tong;
}