//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H

#include "model/CV.h"

class ScanStrateg {
public:
    virtual bool scan(const CV& cv) = 0;
    virtual ~ScanStrategy() = default;
};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H
