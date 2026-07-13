#include "AdvancedScan.h"

bool AdvancedScan::hasRequiredSkill(const CV& cv)
{
    return !cv.skills.empty();
}

bool AdvancedScan::hasEnoughExperience(const CV& cv)
{
    return cv.experienceYears >= 1;
}

bool AdvancedScan::hasEnoughScore(const CV& cv)
{
    return cv.score >= 60;
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

