#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CV_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CV_H
#include "Candidate.h"
#include <vector>
#include <string>

class CV {
    std::string cv_id;
    Candidate candidate;
    std::vector < std::string > skills;
    int experience_years;
    std::string education;
    std::string raw_text;

    CV();
    CV(std::string id, Candidate cand, std::vector < std::string > sk,
        int exp, std::string edu, std::string raw = "");
    void HienThi();
};


#endif //AUTOMATIC_CV_FILTERING_IN_CL_CV_H
