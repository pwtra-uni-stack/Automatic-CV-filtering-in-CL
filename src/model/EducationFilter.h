#ifndef AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
#include "CVFilter.h"
#include <string>

class EducationFilter : public CVFilter {
public:
    std::string required_edu;
    EducationFilter(std::string edu);
    bool match(CV cv) override;
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_EDUCATIONFILTER_H
