//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H

#include "ScanStrategy.h"

class AdvancedScan :public ScanStrategy{
private:
    bool hasRequiredSkill(const CV& cv);
    bool hasEnoughExperience(const CV& cv);
    bool hasEnoughScore(const CV& cv);

public:
    bool scan(const CV& cv) override;
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
