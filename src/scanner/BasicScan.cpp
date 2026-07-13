#include "BasicScan.h"

bool BasicScan::scan(const CV& cv)
{
    if (cv.candidate.name.empty())
        return false;

    if (cv.candidate.email.empty())
        return false;

    if (cv.skills.empty())
        return false;

    if (cv.raw_text.length() < 30)
        return false;

    return true;
}
