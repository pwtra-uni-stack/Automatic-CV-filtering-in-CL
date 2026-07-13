#ifndef AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_H

#include "DocumentParser.h"
#include <string> // Cần include thư viện string tại đây

// Kế thừa public từ DocumentParser
class PdfParser : public DocumentParser {
public:
    // Dùng std::string để đồng bộ với lớp cha
    std::string parse(std::string duong_dan_file) override;
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_HRING_IN_CL_PDFPARSER_H