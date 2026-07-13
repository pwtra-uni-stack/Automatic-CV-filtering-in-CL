//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H

#include <vector>

#include "../model/CV.h"
#include "ScanStrategy.h"

struct ScanResult
{
    std::vector<CV*> junk;
    std::vector<CV*> mismatch;
    std::vector<CV*> qualified;
};

class ScanEngine
{
private:
    std::vector<ScanStrategy*> strategies;

public:
    ScanEngine();

    void addStrategy(ScanStrategy* strategy);

    void clearStrategies();

    ScanResult scanAll(const std::vector<CV*>& cvs);
};



#endif //AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
