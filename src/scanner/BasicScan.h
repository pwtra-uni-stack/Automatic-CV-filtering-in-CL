//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H

#include "ScanStrategy.h"
#include <string>

class BasicScan : public ScanStrategy
{
private:
    bool isValidEmail(const std::string& email);

public:
    bool scan(const CV& cv) override;
};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H
