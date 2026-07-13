// src/view/InputView.cpp
#include "InputView.h"
#include <iostream>
#include <limits>
#include <algorithm>

std::string InputView::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin >> std::ws, input);
    // Trim whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);
    return input;
}

int InputView::getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[31m❌ Please enter a valid integer.\033[0m\n";
        }
    }
    return value;
}

bool InputView::getConfirmation(const std::string& prompt) {
    std::cout << prompt << " (y/n): ";
    char c;
    std::cin >> c;
    return (c == 'y' || c == 'Y');
}