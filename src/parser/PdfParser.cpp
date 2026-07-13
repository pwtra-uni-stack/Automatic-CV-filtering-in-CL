#include "PdfParser.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

std::string PdfParser::parse(std::string duong_dan_file) {
    std::string file_tam = duong_dan_file + ".txt";

    std::string lenh = "pdftotext \"" + duong_dan_file + "\" \"" + file_tam + "\"";
    int trang_thai = std::system(lenh.c_str());

    std::ifstream file(file_tam);
    if (!file.is_open()) {
        return "[Lỗi] Không thể trích xuất văn bản từ file PDF: " + duong_dan_file;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::remove(file_tam.c_str());

    return buffer.str();
}
