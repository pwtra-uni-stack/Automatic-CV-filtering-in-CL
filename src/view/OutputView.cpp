#include "OutputView.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"

void OutputView::showMessage(const std::string& msg) {
    std::cout << GREEN << "✅ " << msg << RESET << std::endl;
}

void OutputView::showError(const std::string& error) {
    std::cout << RED << "❌ Error: " << error << RESET << std::endl;
}

void OutputView::showCVList(const std::vector<CV*>& cvs) {
    if (cvs.empty()) {
        showMessage("No CVs found.");
        return;
    }

    std::cout << "\n" << CYAN << BOLD << "═══════════ CV LIST ═══════════\n" << RESET;
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(15) << "Top Skills"
              << std::setw(10) << "Exp (yrs)"
              << std::setw(8)  << "Score"
              << "\n";
    std::cout << std::setfill('-') << std::setw(60) << "" << std::setfill(' ') << "\n";

    for (const auto* cv : cvs) {
        if (!cv || !cv->candidate) continue;
        std::string skills;
        for (size_t i = 0; i < std::min(cv->skills.size(), size_t(2)); ++i) {
            if (i > 0) skills += ", ";
            skills += cv->skills[i];
        }
        if (cv->skills.size() > 2) skills += ", ...";

        std::cout << std::left
                  << std::setw(6)  << cv->id
                  << std::setw(20) << cv->candidate->name
                  << std::setw(15) << skills
                  << std::setw(10) << cv->experienceYears
                  << std::setw(8)  << cv->score
                  << "\n";
    }
    std::cout << CYAN << "═══════════════════════════════════════════\n" << RESET;
}

void OutputView::showCVDetail(const CV* cv) {
    if (!cv || !cv->candidate) {
        showError("Invalid CV.");
        return;
    }
    std::cout << "\n" << CYAN << BOLD << "════════════ CV DETAIL ════════════\n" << RESET;
    std::cout << "  🆔 ID         : " << cv->id << "\n";
    std::cout << "  👤 Name       : " << cv->candidate->name << "\n";
    std::cout << "  📧 Email      : " << cv->candidate->email << "\n";
    std::cout << "  📞 Phone      : " << cv->candidate->phone << "\n";
    std::cout << "  🛠️  Skills    : ";
    for (size_t i = 0; i < cv->skills.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << cv->skills[i];
    }
    std::cout << "\n";
    std::cout << "  📅 Experience : " << cv->experienceYears << " years\n";
    std::cout << "  🎓 Education  : " << cv->education << "\n";
    std::cout << "  ⭐ Score      : " << cv->score << "\n";
    std::cout << CYAN << "═══════════════════════════════════════════\n" << RESET;
}

void OutputView::showStatistics(int total, int junk, int mismatch, int qualified) {
    std::cout << "\n" << MAGENTA << BOLD << "═════════ CV STATISTICS ══════════\n" << RESET;
    std::cout << "  📦 Total      : " << total << "\n";
    std::cout << "  🗑️  Junk      : " << junk << "\n";
    std::cout << "  ⚠️  Mismatch  : " << mismatch << "\n";
    std::cout << "  ✅ Qualified  : " << qualified << "\n";
    std::cout << MAGENTA << "══════════════════════════════════════\n" << RESET;
}

// NEW: Preview raw content
void OutputView::showRawContent(const std::string& content, const std::string& filename) {
    std::cout << "\n" << CYAN << BOLD << "═══════ FILE CONTENT ═══════\n" << RESET;
    std::cout << "📄 " << filename << "\n";
    std::cout << YELLOW << "─────────────────────────────\n" << RESET;

    std::istringstream stream(content);
    std::string line;
    int lineCount = 0;
    const int MAX_LINES = 30;
    while (std::getline(stream, line) && lineCount < MAX_LINES) {
        std::cout << line << "\n";
        lineCount++;
    }
    if (lineCount == MAX_LINES && stream.peek() != EOF) {
        std::cout << MAGENTA << "... (more lines below)" << RESET << "\n";
    }
    std::cout << CYAN << "═══════════════════════════════════════\n" << RESET;
}