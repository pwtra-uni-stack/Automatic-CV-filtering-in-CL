//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
#include "CVFilter.h"
#include <string>

class EducationFilter : public CVFilter {
public:
    std::string required_edu;

    //Hàm khởi tạo gán tiêu chuẩn trình độ học vấn cần lọc
    EducationFilter(std::string edu) {
        required_edu = edu;
    }

    //Ghi đè lại hàm match để so sánh chuỗi trình độ học vấn
    bool match(CV cv) override {
        return cv.education == required_edu;
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
