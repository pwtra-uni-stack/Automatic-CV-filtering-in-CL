#include "SkillFilter.h"
#include "CV.h"

SkillFilter::SkillFilter(std::vector<std::string> sk) {
    required_skills = sk;
}
bool SkillFilter::match(CV cv) {
    for (size_t i = 0; i < required_skills.size(); i++) {
        bool timThay = false;
        for (size_t j = 0; j < cv.skills.size(); j++) {
            if (cv.skills[j] == required_skills[i]) {
                timThay = true;
                break;
            }
        }
        if (!timThay) return false;
    }
    return true;
}
