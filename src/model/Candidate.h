#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H

#include <string>

class Candidate {
public:
    std::string candidate_id;
    std::string name;
    std::string email;
    std::string phone;
    Candidate();
    Candidate(std::string id, std::string name, std::string email, std::string phone = "");
    void HienThi();
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H
