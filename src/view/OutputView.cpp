#include "OutputView.h"
#include <iostream>
#include <iomanip>

void OutputView::showMessage(const std::string& msg) {
    std::cout << msg << std::endl;
}

void OutputView::showError(const std::string& error) {
    std::cerr << "[ERROR] " << error << std::endl;
}

void OutputView::showCVList(const std::vector<CV*>& cvs) {
    if (cvs.empty()) {
        std::cout << "No CVs found.\n";
        return;
    }
    std::cout << "\n=== CV List (" << cvs.size() << " items) ===\n";
    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(15) << "Skills" 
              << std::setw(10) << "Exp" 
              << "Score\n";
    std::cout << "--------------------------------------------------\n";
    for (const auto* cv : cvs) {
        if (cv && cv->candidate) {
            std::string skillStr;
            for (size_t i = 0; i < cv->skills.size() && i < 3; ++i) {
                if (i > 0) skillStr += ", ";
                skillStr += cv->skills[i];
            }
            if (cv->skills.size() > 3) skillStr += "...";
            
            std::cout << std::left << std::setw(6) << cv->id
                      << std::setw(20) << cv->candidate->name
                      << std::setw(15) << skillStr
                      << std::setw(10) << cv->experienceYears
                      << cv->score << '\n';
        }
    }
}

void OutputView::showCVDetail(const CV* cv) {
    if (!cv || !cv->candidate) {
        showError("CV is null or invalid.");
        return;
    }
    std::cout << "\n========== CV DETAIL ==========\n";
    std::cout << "ID           : " << cv->id << '\n';
    std::cout << "Name         : " << cv->candidate->name << '\n';
    std::cout << "Email        : " << cv->candidate->email << '\n';
    std::cout << "Phone        : " << cv->candidate->phone << '\n';
    std::cout << "Skills       : ";
    for (const auto& skill : cv->skills) {
        std::cout << skill << " ";
    }
    std::cout << '\n';
    std::cout << "Experience   : " << cv->experienceYears << " years\n";
    std::cout << "Education    : " << cv->education << '\n';
    std::cout << "Score        : " << cv->score << '\n';
    std::cout << "===============================\n";
}

void OutputView::showStatistics(int total, int junk, int mismatch, int qualified) {
    std::cout << "\n========== STATISTICS ==========\n";
    std::cout << "Total CVs      : " << total << '\n';
    std::cout << "Junk (trash)   : " << junk << '\n';
    std::cout << "Mismatch       : " << mismatch << '\n';
    std::cout << "Qualified      : " << qualified << '\n';
    std::cout << "================================\n";
}