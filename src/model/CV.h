#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CV_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CV_H

#include "Candidate.h"
#include <vector>
#include <string>

class CV {
public:
    std::string id;
    Candidate* candidate;
    std::vector<std::string> skills;
    int experienceYears;
    std::string education;
    std::string raw_text;
    int score;

    CV();
    CV(std::string id, Candidate* cand, std::vector<std::string> sk,
       int exp, std::string edu, std::string raw = "", int score = 0);

    ~CV();

    void HienThi();
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_CV_H