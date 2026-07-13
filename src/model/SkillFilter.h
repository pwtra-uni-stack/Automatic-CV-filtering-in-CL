#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H
#include "CVFilter.h"
#include <vector>
#include <string>

class SkillFilter : public CVFilter {
public:
    std::vector<std::string> required_skills;

    SkillFilter(std::vector<std::string> sk);
    bool match(CV cv) override;
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H

