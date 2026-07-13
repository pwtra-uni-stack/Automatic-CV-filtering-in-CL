#include "Candidate.h"
#include <iostream>

Candidate::Candidate() {
    candidate_id = "";
    name = "";
    email = "";
}
Candidate::Candidate(std::string id, std::string name, std::string email) {
    this->candidate_id = id;
    this->name = name;
    this->email = email;
}
void Candidate::HienThi() {
    std::cout << "Candidate[" << candidate_id << ", " << name << ", " << email << "]";
}
