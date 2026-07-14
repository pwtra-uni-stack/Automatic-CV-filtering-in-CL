#include <iostream>
#include <curl/curl.h>
#include "controller/CVController.h"
#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    // 1. Khởi tạo Logger hệ thống
    Logger::getInstance().init("Data/logs.txt", Logger::INFO);
    LOG_INFO("--- STARTING CV AUTO MANAGEMENT SYSTEM ---");

    // 2. Khởi tạo CURL toàn cục (Bắt buộc trước khi gọi các hàm mạng của GeminiClient)
    CURLcode curl_init_status = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (curl_init_status != CURLE_OK) {
        LOG_ERROR("Failed to initialize cURL globally. Exiting program.");
        Logger::getInstance().close();
        return 1;
    }
    LOG_INFO("Global cURL initialized successfully.");

    try {
        // 3. Khởi tạo Controller và chạy vòng lặp Menu chính
        CVController controller;
        controller.run(); // Hàm này nội bộ sẽ gọi menu.showMainMenu()[cite: 1]
    }
    catch (const std::exception& e) {
        LOG_ERROR("Unhandled critical exception in main: " + std::string(e.what()));
    }
    catch (...) {
        LOG_ERROR("Unknown critical error occurred in main.");
    }

    // 4. Giải phóng CURL toàn cục trước khi kết thúc chương trình
    curl_global_cleanup();
    LOG_INFO("Global cURL cleaned up.");
    LOG_INFO("--- SYSTEM SHUTDOWN CLEANLY ---");

    // 5. Đóng file log an toàn
    Logger::getInstance().close();
    return 0;
}