#include "BasicScan.h"

bool BasicScan::isValidEmail(const std::string& email)
{
    return email.find('@') != std::string::npos;
}

bool BasicScan::scan(const CV& cv)
{
    if (cv.candidate.name.empty())
        return false;

    if (!isValidEmail(cv.candidate.email))
        return false;

    if (cv.skills.empty())
        return false;

    if (cv.experience_years < 0)
        return false;

    if (cv.raw_text.length() < 30)
        return false;

    return true;
}
