#include "EducationFilter.h"
EducationFilter::EducationFilter(std::string edu) {
    required_edu = edu;
}

bool EducationFilter::match(CV cv) {
    return cv.education == required_edu;
}
