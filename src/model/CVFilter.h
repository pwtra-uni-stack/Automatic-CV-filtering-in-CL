#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H

#include <string>
#include "CV.h"
class CVFilter {
public:
    virtual bool match(CV cv) = 0; // Hàm ảo thuần ảo phục vụ đa hình
    virtual ~CVFilter();
};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H
