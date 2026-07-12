//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
#include "CVFilter.h"

class ExperienceFilter : public CVFilter {
public:
    int min_years;

    //Hàm khởi tạo gán định mức năm kinh nghiệm cần lọc
    ExperienceFilter(int years) {
        min_years = years;
    }

    //Ghi đè lại hàm match để thực hiện so sanh số năm kinh nghiệm
    bool match(CV cv) override {
        // nếu số năm kinh nghiệm của ứng viên lớn hơn hoặc bằng định mức yêu cầu thì đạt
        return cv.experience_years >= min_years;
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
