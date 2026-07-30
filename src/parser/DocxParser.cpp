#include "DocxParser.h"
#include "../exception/FileException.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

std::string DocxParser::parse(std::string duong_dan_file) {
    // .docx là file ZIP chứa XML — không thể đọc trực tiếp bằng ifstream
    // Dùng tool 'docx2txt' (tương tự pdftotext) để convert sang plain text
    std::string file_tam = duong_dan_file + ".txt";

    std::string lenh = "docx2txt \"" + duong_dan_file + "\" \"" + file_tam + "\"";
    int trang_thai = std::system(lenh.c_str());

    if (trang_thai != 0) {
        throw FileException("Lệnh docx2txt thất bại. Hãy kiểm tra docx2txt đã được cài đặt chưa: " + duong_dan_file);
    }

    std::ifstream file(file_tam);
    if (!file.is_open()) {
        throw FileException("Không thể mở file sau khi parse DOCX: " + duong_dan_file);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::remove(file_tam.c_str());

    return buffer.str();
}