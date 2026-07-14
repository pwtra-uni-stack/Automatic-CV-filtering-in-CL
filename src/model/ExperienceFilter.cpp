#include "ExperienceFilter.h"
ExperienceFilter::ExperienceFilter(int years) {
    min_years = years;
}
bool ExperienceFilter::match(CV cv) {
    return cv.experienceYears >= min_years;
}
