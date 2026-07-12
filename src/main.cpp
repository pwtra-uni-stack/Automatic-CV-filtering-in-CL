#include "controller/CVController.h"
#include <iostream>
#include <exception>

int main() {
    try {
        CVController controller;
        controller.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}