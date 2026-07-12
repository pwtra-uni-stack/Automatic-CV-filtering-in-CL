// src/controller/CVController.cpp
#include "CVController.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <filesystem>

// Model
#include "model/CV.h"
#include "model/CVDatabase.h"
#include "model/CVFilter.h"
#include "model/SkillFilter.h"
#include "model/ExperienceFilter.h"
#include "model/EducationFilter.h"
#include "model/FileManager.h"

// Scanner
#include "scanner/ScanEngine.h"
#include "scanner/BasicScan.h"
#include "scanner/AdvancedScan.h"

// Exception
#include "exception/Exception.h"

// Utils
#include "utils/Utils.h"

// View (đã được include qua header)

// -------------------- CONSTRUCTOR --------------------
CVController::CVController() {
    // Khởi tạo dữ liệu mặc định (có thể load từ file nếu muốn)
    std::cout << "CVController initialized.\n";
}

// -------------------- VÒNG LẶP CHÍNH --------------------
void CVController::run() {
    int choice;
    do {
        try {
            choice = menu.showMainMenu();
            switch (choice) {
                case 1: handleLoad(); break;
                case 2: handleViewAll(); break;
                case 3: handleViewDetail(); break;
                case 4: handleFilter(); break;
                case 5: handleScan(); break;
                case 6: handleDelete(); break;
                case 7: handleSave(); break;
                case 8:
                    OutputView::showMessage("Goodbye! Thanks for using CV_Auto.");
                    break;
                default:
                    OutputView::showError("Invalid choice. Please try again.");
            }
        } catch (const std::exception& e) {
            OutputView::showError(std::string("System error: ") + e.what());
        }
    } while (choice != 8);
}

// -------------------- HANDLER LOAD --------------------
void CVController::handleLoad() {
    OutputView::showMessage("Loading CVs from default directory: data/cvs/");

    // 1. Lấy danh sách file trong thư mục
    std::string dir = "data/cvs/";
    std::vector<std::string> files = FileManager::getCVFiles(dir);

    if (files.empty()) {
        OutputView::showError("No files found in " + dir);
        return;
    }

    // 2. Duyệt từng file và load
    int loadedCount = 0;
    for (const auto& file : files) {
        try {
            // Thử load CV từ file
            CV* cv = FileManager::loadCVFromFile(file);
            if (cv) {
                database.addCV(cv);
                loadedCount++;
                // OutputView::showMessage("Loaded: " + file);
            } else {
                OutputView::showError("Failed to parse CV from: " + file);
            }
        } catch (const FileException& e) {
            OutputView::showError(std::string("File error: ") + e.what());
        } catch (const std::exception& e) {
            OutputView::showError(std::string("Unexpected error while loading ") + file + ": " + e.what());
        }
    }

    OutputView::showMessage("Successfully loaded " + std::to_string(loadedCount) + " CV(s).");
}

// -------------------- HANDLER VIEW ALL --------------------
void CVController::handleViewAll() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showMessage("No CVs in database. Please load data first.");
        return;
    }
    OutputView::showCVList(all);
}

// -------------------- HANDLER VIEW DETAIL --------------------
void CVController::handleViewDetail() {
    if (database.getAll().empty()) {
        OutputView::showError("No CVs available. Load data first.");
        return;
    }

    int id = InputView::getIntInput("Enter CV ID: ");
    CV* cv = database.getById(id);
    if (cv) {
        OutputView::showCVDetail(cv);
    } else {
        OutputView::showError("CV with ID " + std::to_string(id) + " not found.");
    }
}

// -------------------- HANDLER FILTER --------------------
void CVController::handleFilter() {
    if (database.getAll().empty()) {
        OutputView::showError("No CVs to filter. Load data first.");
        return;
    }

    // 1. Nhập tiêu chí lọc
    std::string keyword = InputView::getStringInput("Enter skill keyword (or leave empty): ");
    int minExp = InputView::getIntInput("Enter minimum years of experience: ");
    std::string edu = InputView::getStringInput("Enter required education (BSc/MSc/PhD or leave empty): ");

    // 2. Tạo danh sách filter
    std::vector<CVFilter*> filters;

    if (!keyword.empty()) {
        filters.push_back(new SkillFilter(keyword));
    }
    if (minExp > 0) {
        filters.push_back(new ExperienceFilter(minExp));
    }
    if (!edu.empty()) {
        filters.push_back(new EducationFilter(edu));
    }

    if (filters.empty()) {
        OutputView::showMessage("No filters applied. Showing all CVs.");
        handleViewAll();
        return;
    }

    // 3. Áp dụng filter
    auto result = database.filter(filters);

    // 4. Hiển thị kết quả
    OutputView::showCVList(result);
    OutputView::showMessage("Found " + std::to_string(result.size()) + " CV(s) matching criteria.");

    // 5. Dọn dẹp bộ nhớ filter
    for (auto* f : filters) {
        delete f;
    }
}

// -------------------- HANDLER SCAN --------------------
void CVController::handleScan() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showError("No CVs to scan. Load data first.");
        return;
    }

    OutputView::showMessage("Scanning and classifying CVs...");

    // 1. Tạo các strategy
    BasicScan basicScan;
    AdvancedScan advancedScan;

    // 2. Thêm vào ScanEngine
    scanEngine.addStrategy(&basicScan);
    scanEngine.addStrategy(&advancedScan);

    // 3. Thực hiện quét
    ScanResult result = scanEngine.scanAll(all);

    // 4. Lưu các CV đã phân loại vào thư mục tương ứng (nếu có thể)
    //    Để đơn giản, ta chỉ hiển thị thống kê
    OutputView::showStatistics(
        static_cast<int>(all.size()),
        static_cast<int>(result.junk.size()),
        static_cast<int>(result.mismatch.size()),
        static_cast<int>(result.qualified.size())
    );

    // (Có thể gọi FileManager::copyFile để sao chép file gốc vào thư mục tương ứng)
    // Nhưng hiện tại chưa biết đường dẫn file gốc, nên tạm bỏ qua
}

// -------------------- HANDLER DELETE --------------------
void CVController::handleDelete() {
    if (database.getAll().empty()) {
        OutputView::showError("No CVs to delete.");
        return;
    }

    // Hỏi loại xóa
    std::cout << "Delete options:\n";
    std::cout << "1. Delete by ID\n";
    std::cout << "2. Delete all junk CVs\n";
    std::cout << "3. Delete all mismatch CVs\n";
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            int id = InputView::getIntInput("Enter CV ID to delete: ");
            CV* cv = database.getById(id);
            if (!cv) {
                OutputView::showError("CV not found.");
                return;
            }
            bool confirm = InputView::getConfirmation("Are you sure you want to delete CV #" + std::to_string(id) + "?");
            if (confirm) {
                database.removeCV(id);
                OutputView::showMessage("CV #" + std::to_string(id) + " deleted.");
            } else {
                OutputView::showMessage("Delete cancelled.");
            }
            break;
        }
        case 2: {
            // Xóa tất cả CV rác (cần quét trước)
            OutputView::showMessage("Please run Scan first to classify CVs.");
            break;
        }
        case 3: {
            OutputView::showMessage("Please run Scan first to classify CVs.");
            break;
        }
        default:
            OutputView::showError("Invalid option.");
    }
}

// -------------------- HANDLER SAVE --------------------
void CVController::handleSave() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showError("No data to save.");
        return;
    }

    std::string path = InputView::getStringInput("Enter output file path (default: data/cv_data.txt): ");
    if (path.empty()) {
        path = "data/cv_data.txt";
    }

    try {
        bool success = FileManager::saveAllCVs(path, all);
        if (success) {
            OutputView::showMessage("Saved " + std::to_string(all.size()) + " CVs to " + path);
        } else {
            OutputView::showError("Failed to save data.");
        }
    } catch (const FileException& e) {
        OutputView::showError(std::string("File error: ") + e.what());
    }
}