//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H

#include "ScanStrategy.h"

class AdvancedScan : public ScanStrategy
{
public:
    bool scan(const CV& cv) override;

private:
    int calculateScore(const CV& cv);
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
