#include "CVController.h"
#include "model/FileManager.h"
#include "model/SkillFilter.h"
#include "model/ExperienceFilter.h"
#include "model/EducationFilter.h"
#include "scanner/BasicScan.h"
#include "scanner/AdvancedScan.h"
#include "exception/Exception.h"
#include "utils/Logger.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

CVController::CVController() {
    LOG_INFO("CVController initialized");
    // Khởi tạo dữ liệu mẫu (sau này có thể load từ file)
    // Tạm thời để database rỗng, người dùng sẽ load từ menu
}

// -------------------- HÀM RUN CHÍNH (đã bổ sung case 9) --------------------
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
                    OutputView::showMessage("Goodbye!");
                    break;
                case 9: handlePreview(); break;   // Đã thêm case 9
                default:
                    OutputView::showError("Invalid choice!");
            }
        } catch (const InvalidInputException& e) {
            OutputView::showError("Input error: " + std::string(e.what()));
        } catch (const FileException& e) {
            OutputView::showError("File error: " + std::string(e.what()));
        } catch (const std::exception& e) {
            OutputView::showError("System error: " + std::string(e.what()));
        }
    } while (choice != 8);
}

// -------------------- HANDLER LOAD --------------------
void CVController::handleLoad() {
    OutputView::showMessage("Loading CVs from Data/cvs/");

    try {
        auto files = FileManager::getCVFiles("Data/cvs/");
        if (files.empty()) {
            OutputView::showError("No files found in Data/cvs/");
            return;
        }

        int loaded = 0;
        for (const auto& file : files) {
            CV* cv = FileManager::loadCVFromFile(file);
            if (cv) {
                database.addCV(cv);
                loaded++;
                LOG_INFO("Loaded: " + file);
            } else {
                LOG_WARN("Failed to parse: " + file);
            }
        }

        OutputView::showMessage("Loaded " + std::to_string(loaded) + " CVs successfully!");
        LOG_INFO("Loaded " + std::to_string(loaded) + " CVs");
    } catch (const FileException& e) {
        OutputView::showError("File error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        OutputView::showError("Error: " + std::string(e.what()));
    }
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
    auto all = database.getAll();
    if (all.empty()) {
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

// -------------------- HANDLER FILTER (đã sửa SkillFilter) --------------------
void CVController::handleFilter() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showError("No CVs to filter. Load data first.");
        return;
    }

    std::string keyword = InputView::getStringInput("Enter skill keyword (or leave empty): ");
    int minExp = InputView::getIntInput("Enter minimum years of experience: ");
    std::string edu = InputView::getStringInput("Enter required education (BSc/MSc/PhD or leave empty): ");

    std::vector<CVFilter*> filters;
    if (!keyword.empty()) {
        // SỬA: truyền vector<string> thay vì string
        filters.push_back(new SkillFilter({keyword}));
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

    auto result = database.filter(filters);
    OutputView::showCVList(result);
    OutputView::showMessage("Found " + std::to_string(result.size()) + " CV(s) matching criteria.");

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
    LOG_INFO("Starting scan of " + std::to_string(all.size()) + " CVs");

    BasicScan basic;
    AdvancedScan advanced;
    scanEngine.addStrategy(&basic);
    scanEngine.addStrategy(&advanced);

    ScanResult result = scanEngine.scanAll(all);

    OutputView::showStatistics(
        all.size(),
        result.junk.size(),
        result.mismatch.size(),
        result.qualified.size()
    );

    LOG_INFO("Scan complete: " +
             std::to_string(result.junk.size()) + " junk, " +
             std::to_string(result.mismatch.size()) + " mismatch, " +
             std::to_string(result.qualified.size()) + " qualified");
}

// -------------------- HANDLER DELETE --------------------
void CVController::handleDelete() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showError("No CVs to delete.");
        return;
    }

    OutputView::showMessage("Delete options:");
    OutputView::showMessage("1. Delete by ID");
    OutputView::showMessage("2. Delete all junk CVs (run scan first)");
    OutputView::showMessage("3. Delete all mismatch CVs (run scan first)");

    int choice = InputView::getIntInput("Your choice: ");

    switch (choice) {
        case 1: {
            int id = InputView::getIntInput("Enter CV ID to delete: ");
            if (database.getById(id)) {
                if (InputView::getConfirmation("Are you sure?")) {
                    database.removeCV(id);
                    OutputView::showMessage("CV #" + std::to_string(id) + " deleted.");
                    LOG_INFO("Deleted CV #" + std::to_string(id));
                }
            } else {
                OutputView::showError("CV not found.");
            }
            break;
        }
        case 2:
        case 3:
            OutputView::showMessage("Please run Scan first to classify CVs.");
            break;
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

    std::string path = InputView::getStringInput("Enter output file path (default: Data/cv_data.txt): ");
    if (path.empty()) {
        path = "Data/cv_data.txt";
    }

    try {
        if (FileManager::saveAllCVs(path, all)) {
            OutputView::showMessage("Saved " + std::to_string(all.size()) + " CVs to " + path);
            LOG_INFO("Saved " + std::to_string(all.size()) + " CVs to " + path);
        } else {
            OutputView::showError("Failed to save data.");
        }
    } catch (const FileException& e) {
        OutputView::showError("File error: " + std::string(e.what()));
    }
}

// -------------------- HANDLER PREVIEW (duy nhất) --------------------
void CVController::handlePreview() {
    std::string filePath = InputView::getStringInput("Enter file path (e.g., Data/cvs/sample.txt): ");
    if (filePath.empty()) {
        OutputView::showError("No file path provided.");
        return;
    }

    try {
        std::string content = FileManager::extractTextFromFile(filePath);
        if (content.empty()) {
            OutputView::showError("Unable to read file or unsupported format.");
            return;
        }
        OutputView::showRawContent(content, filePath);
    } catch (const FileException& e) {
        OutputView::showError("File error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        OutputView::showError("Error: " + std::string(e.what()));
    }
}