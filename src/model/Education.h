#ifndef AUTOMATIC_CV_FILTERING_IN_CL_EDUCATION_H
#define AUTOMATIC_CV_FILTERING_IN_CL_EDUCATION_H
#include "CVFilter.h"
#include <string>

class EducationFilter : public CVFilter {
public:
    std::string required_edu;
    EducationFilter(std::string edu);
    bool match(const CV& cv) override;
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_EDUCATION_H
