#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H

#include <string>
#include "CV.h"

class CVFilter {
public:
    virtual bool match(CV cv) = 0;
    virtual ~CVFilter() = default;
};

#endif