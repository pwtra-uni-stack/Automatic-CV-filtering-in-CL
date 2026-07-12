//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H

#include <vector>
#include "../model/CV.h"
#include "BasicScan.h"
#include "AdvancedScan.h"

class ScanEngine{

private:

    BasicScan basic;
    AdvancedScan advanced;

public:

    std::vector<CV> junk;

    std::vector<CV> mismatch;

    std::vector<CV> qualified;

    void scan(std::vector<CV>& list){

        junk.clear();
        mismatch.clear();
        qualified.clear();

        for(auto &cv:list){

            if(!basic.scan(cv)){

                junk.push_back(cv);
            }

            else if(!advanced.scan(cv)){

                mismatch.push_back(cv);
            }

            else{

                qualified.push_back(cv);
            }
        }
    }

    void showStatistic(){

        std::cout<<"===== THONG KE =====\n";

        std::cout<<"Junk: "<<junk.size()<<std::endl;

        std::cout<<"Mismatch: "<<mismatch.size()<<std::endl;

        std::cout<<"Qualified: "<<qualified.size()<<std::endl;
    }

};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_SCANENGINE_H
