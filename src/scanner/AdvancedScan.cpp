#include "AdvancedScan.h"

bool AdvancedScan::hasRequiredSkill(const CV& cv)
{
    return !cv.skills.empty();
}

bool AdvancedScan::hasEnoughExperience(const CV& cv)
{
    return cv.experience_years >= 1;
}

bool AdvancedScan::hasEnoughScore(const CV& cv)
{
    return cv.skills.size() >= 60;
}

bool AdvancedScan::scan(const CV& cv)
{
    if (!hasRequiredSkill(cv))
        return false;

    if (!hasEnoughExperience(cv))
        return false;

    if (!hasEnoughScore(cv))
        return false;

    return true;
}

