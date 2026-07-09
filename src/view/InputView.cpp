#include "InputView.h"
#include <iostream>
#include <limits>

std::string InputView::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin >> std::ws, input); // bỏ qua khoảng trắng đầu
    return input;
}

int InputView::getIntInput(const std::string& prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cerr << "Invalid input! Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << prompt;
    }
    return value;
}

bool InputView::getConfirmation(const std::string& prompt) {
    std::cout << prompt << " (y/n): ";
    char c;
    std::cin >> c;
    return (c == 'y' || c == 'Y');
}