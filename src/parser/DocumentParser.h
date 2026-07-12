//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_DOCUMENTPARSER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_DOCUMENTPARSER_H
#include <string>
class DocumentParser {
public:
    virtual ~DocumentParser() {}

    virtual std::string parse(std::string duong_dan_file) = 0;
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_DOCUMENTPARSER_H
