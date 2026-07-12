//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
#define AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
#include "ScanStrategy.h"

class AdvancedScan : public ScanStrategy{

public:

    int calculateScore(const CV& cv){

        int score=0;

        score+=cv.skills.size()*10;

        score+=cv.experience_years*5;

        if(cv.education=="Bachelor")
            score+=20;

        else if(cv.education=="Master")
            score+=30;

        else if(cv.education=="PhD")
            score+=40;

        return score;
    }

    bool scan(const CV& cv) override{

        int score=calculateScore(cv);

        return score>=60;
    }

};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_ADVANCEDSCAN_H
