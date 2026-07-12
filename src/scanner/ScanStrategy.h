//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H

class ScanStrategy {
public:
    virtual bool scan(const CV& cv)=0;
    virtual ~ScanStrategy(){}
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_SCANSTRATEGY_H
