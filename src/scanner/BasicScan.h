#ifndef AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H

#include <string>            
#include "ScanStrategy.h"

class BasicScan : public ScanStrategy
{
private:
    bool isValidEmail(const std::string& email);

public:
    bool scan(const CV& cv) override;
};

#endif