//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_H
#include "DocumentParser.h"

class PdfParser : public DocumentParser {
public:
    std::string parse(std::string duong_dan_file) override;
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_PDFPARSER_H
