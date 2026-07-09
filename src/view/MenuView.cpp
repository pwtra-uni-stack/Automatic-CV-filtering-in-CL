#include "MenuView.h"
#include <iostream>

int MenuView::showMainMenu() {
    std::cout << "\n========== CV AUTO SYSTEM ==========\n";
    std::cout << "1. Load data\n";
    std::cout << "2. View all CVs\n";
    std::cout << "3. View CV detail\n";
    std::cout << "4. Filter CVs\n";
    std::cout << "5. Scan CVs (classify)\n";
    std::cout << "6. Delete CVs\n";
    std::cout << "7. Save data\n";
    std::cout << "8. Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;
    return choice;
}

void MenuView::showSubMenu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n--- " << title << " ---\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i+1) << ". " << options[i] << '\n';
    }
    std::cout << "Your choice: ";
}