#include "Candidate.h"
#include <iostream>

Candidate::Candidate() {
    candidate_id = "";
    name = "";
    email = "";
    phone = "";
}

Candidate::Candidate(std::string id, std::string name, std::string email, std::string phone) {
    this->candidate_id = id;
    this->name = name;
    this->email = email;
    this->phone = phone;
}

void Candidate::HienThi() {
    std::cout << "Candidate[" << candidate_id << ", " << name << ", " << email;
    if (!phone.empty()) {
        std::cout << ", " << phone;
    }
    std::cout << "]";
}