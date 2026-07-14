#ifndef AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
#include "CVFilter.h"
#include <vector>
#include <string>  

class ExperienceFilter : public CVFilter {
public:
    int min_years;
    ExperienceFilter(int years);
    bool match(CV cv) override;
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_EXPERIENCEFILTER_H
