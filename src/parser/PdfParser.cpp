//
// Created by admin on 12/07/2026.
//
#include "PdfParser.h"
#include "../exception/FileException.h"
#include <fstream>
#include <iostream>

std::string PdfParser::parse(std::string duong_dan_file) {
    std::ifstream file(duong_dan_file);
    if (file.is_open() == false) {
        throw FileException("Khong the mo file CV dạng PDF tai: " + duong_dan_file);
    }

    std::string noi_dung_tong = "";
    std::string dong_chu;

    while (std::getline(file, dong_chu)) {
        noi_dung_tong += dong_chu + "\n";
    }

    file.close();
    return noi_dung_tong;
}
