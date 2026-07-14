#include "CV.h"
#include <iostream>

CV::CV() {
    id = "";
    candidate = nullptr;
    experienceYears = 0;
    education = "";
    raw_text = "";
    score = 0;
}

CV::CV(std::string id, Candidate* cand, std::vector<std::string> sk,
       int exp, std::string edu, std::string raw, int score) {
    this->id = id;
    this->candidate = cand;
    this->skills = sk;
    this->experienceYears = exp;
    this->education = edu;
    this->raw_text = raw;
    this->score = score;
}

CV::~CV() {
    if (candidate != nullptr) {
        delete candidate; // Giải phóng vùng nhớ của Candidate khi CV bị huỷ
        candidate = nullptr;
    }
}

void CV::HienThi() {
    std::cout << "CV ID: " << id << " | ";
    if (candidate != nullptr) {
        candidate->HienThi();
    } else {
        std::cout << "No Candidate Info";
    }
    std::cout << " | Experience: " << experienceYears
              << " years | Education: " << education
              << " | Score: " << score
              << " | Skills: ";
    for (size_t i = 0; i < skills.size(); i++) {
        std::cout << skills[i] << (i == skills.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}