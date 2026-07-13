#include "CV.h"
CV::CV() {
    cv_id = " ";
    experience_years = 0;
    education = "";
    raw_text = "";
}
CV::CV(std::string id, Candidate cand, std::vector < std::string > sk,
    int exp, std::string edu, std::string raw) {
    cv_id = id;
    candidate = cand;
    skills = sk;
    experience_years = exp;
    education = edu;
    raw_text = raw;
}
void CV::HienThi() {
    std::cout << "CV ID: " << cv_id << " | ";
    candidate.HienThi();
    std::cout << " | Experience: " << experience_years <<
        " years | Education: " << education << "| skills: ";
    for (size_t i = 0; i < skills.size(); i++) {
        std::cout << skills[i] << "  ";
    }
    std::cout << std::endl;
}
