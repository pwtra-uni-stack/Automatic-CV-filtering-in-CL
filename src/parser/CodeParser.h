#include <string>
#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CODEPARSER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CODEPARSER_H
class CodeParser {
public:
    // Hàm quét qua thư mục và gộp tất cả nội dung các file code lại thành 1 chuỗi lớn
    std::string quétThưMụcCode(std::string duong_dan_thu_muc);
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_CODEPARSER_H
