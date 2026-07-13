//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H

#include <vector>
#include "../model/CVDatabase.h"
#include "BasicScan.h"
#include "AdvancedScan.h"

class ScanEngine {
private:
    BasicScan basicScan;
    AdvancedScan advancedScan;

    std::vector<CV*> junkList;
    std::vector<CV*> mismatchList;
    std::vector<CV*> qualifiedList;

public:
    ScanEngine();

    void scan(CVDatabase& database);

    const std::vector<CV*>& getJunk() const;
    const std::vector<CV*>& getMismatch() const;
    const std::vector<CV*>& getQualified() const;

    void clear();
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
