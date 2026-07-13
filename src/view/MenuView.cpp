// src/view/MenuView.cpp
#include "MenuView.h"
#include <iostream>
#include <iomanip>

// ANSI color codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"

int MenuView::showMainMenu() {
    std::cout << "\n" << CYAN << BOLD
              << "╔══════════════════════════════════════════╗\n"
              << "║        CV_AUTO – CV MANAGEMENT SYSTEM   ║\n"
              << "╚══════════════════════════════════════════╝\n"
              << RESET;
    std::cout << YELLOW
              << "  1. 📂 Load data\n"
              << "  2. 📋 View all CVs\n"
              << "  3. 🔍 View CV detail\n"
              << "  4. 🔎 Filter CVs\n"
              << "  5. 🧹 Scan & classify CVs\n"
              << "  6. 🗑️  Delete CVs\n"
              << "  7. 💾 Save data\n"
              << "  8. 🚪 Exit\n"
              << "  9. 👁️  Preview file content\n"
              << RESET;
    std::cout << GREEN << "─────────────────────────────────────────\n" << RESET;
    std::cout << "➜ Enter your choice: ";
    int choice;
    std::cin >> choice;
    return choice;
}

void MenuView::showSubMenu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n" << CYAN << BOLD << "─── " << title << " ───\n" << RESET;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "  " << (i+1) << ". " << options[i] << "\n";
    }
    std::cout << GREEN << "➜ Your choice: " << RESET;
}