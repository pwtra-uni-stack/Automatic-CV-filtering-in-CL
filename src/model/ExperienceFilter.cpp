#include "ExperienceFilter.h"
ExperienceFilter::ExperienceFilter(int years) {
    min_years = years;
}
bool ExperienceFilter::match(CV cv) {
    return cv.experience_years >= min_years;
}
