#include "PdfParser.h"
#include "../exception/FileException.h"
#include <cstdlib>    // cho std::system
#include <fstream>    // cho std::ifstream
#include <sstream>    // cho std::stringstream
#include <string>

std::string PdfParser::parse(std::string duong_dan_file) {
    std::string file_tam = duong_dan_file + ".txt";

    std::string lenh = "pdftotext \"" + duong_dan_file + "\" \"" + file_tam + "\"";
    int trang_thai = std::system(lenh.c_str());

    if (trang_thai != 0) {
        throw FileException("Lệnh pdftotext thất bại. Hãy kiểm tra pdftotext đã được cài đặt chưa: " + duong_dan_file);
    }

    std::ifstream file(file_tam);
    if (!file.is_open()) {
        throw FileException("Không thể mở file sau khi parse PDF: " + duong_dan_file);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::remove(file_tam.c_str());

    return buffer.str();
}
