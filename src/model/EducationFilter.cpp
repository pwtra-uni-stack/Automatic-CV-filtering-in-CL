#include "EducationFilter.h"
EducationFilter::EducationFilter(std::string edu) {
    required_edu = edu;
}

bool EducationFilter::match(const CV& cv) {
    return cv.education == required_edu;
}
