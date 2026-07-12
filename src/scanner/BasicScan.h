//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H

class BasicScan : public ScanStrategy{
public:

    bool scan(const CV& cv) override{

        if(cv.candidate.name.empty())
            return false;

        if(cv.candidate.email.empty())
            return false;

        if(cv.skills.empty())
            return false;

        if(cv.raw_text.length()<30)
            return false;

        return true;
    }
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_BASICSCAN_H
