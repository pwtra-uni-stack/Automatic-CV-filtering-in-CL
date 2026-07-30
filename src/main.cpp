#include <iostream>
#include "controller/CVController.h"
#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    // 1. Khởi tạo Logger hệ thống
    Logger::getInstance().init("Data/logs.txt", Logger::INFO);
    LOG_INFO("--- STARTING CV AUTO MANAGEMENT SYSTEM ---");

    try {
        // 2. Khởi tạo Controller và chạy vòng lặp Menu chính
        CVController controller;
        controller.run();
    }
    catch (const std::exception& e) {
        LOG_ERROR("Unhandled critical exception in main: " + std::string(e.what()));
    }
    catch (...) {
        LOG_ERROR("Unknown critical error occurred in main.");
    }

    LOG_INFO("--- SYSTEM SHUTDOWN CLEANLY ---");

    // 3. Đóng file log an toàn
    Logger::getInstance().close();
    return 0;
}
