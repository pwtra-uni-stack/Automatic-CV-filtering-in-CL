#include "AdvancedScan.h"

int AdvancedScan::calculateScore(const CV& cv)
{
    int score = 0;

    score += static_cast<int>(cv.skills.size()) * 10;
    score += cv.experience_years * 5;

    if (cv.education == "Bachelor")
        score += 20;
    else if (cv.education == "Master")
        score += 30;
    else if (cv.education == "PhD")
        score += 40;

    return score;
}

bool AdvancedScan::scan(const CV& cv)
{
    return calculateScore(cv) >= 60;
}
