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
#include "ai/GeminiClient.h"
#include "utils/EnvLoader.h"
#include <nlohmann/json.hpp>


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

void handleAICVProcessing(CV* cv) {
    // 1. Đọc API Key
    std::string apiKey = EnvLoader::getEnv("GEMINI_API_KEY");[cite: 45];
    GeminiClient client(apiKey);

    // 2. Viết định hướng Prompt ép AI trả về đúng cấu trúc JSON mong muốn
    std::string prompt = "Bạn là một chuyên gia tuyển dụng phần mềm. Hãy phân tích CV sau và trả về "
                         "kết quả duy nhất dưới định dạng JSON có cấu trúc như sau, không kèm markdown:\n"
                         "{\n"
                         "  \"score\": <số nguyên từ 0-100>,\n"
                         "  \"skills\": [\"kỹ năng 1\", \"kỹ năng 2\"]\n"
                         "}";

    // 3. Gọi API Gemini
    std::string rawJsonResponse = client.phânTíchCV(cv->raw_text, prompt);

    try {
        // 4. Bóc tách JSON kết quả trả về bằng nlohmann/json
        auto parsedJson = nlohmann::json::parse(rawJsonResponse);

        // Lưu ý: Cấu trúc trả về của Gemini API nằm bọc trong candidates[0].content.parts[0].text
        std::string aiTextResponse = parsedJson["candidates"][0]["content"]["parts"][0]["text"];

        // Khử nhiễu nếu AI vô tình bọc thẻ ```json ... ```
        auto aiData = nlohmann::json::parse(aiTextResponse);

        // 5. Cập nhật trực tiếp vào đối tượng CV của bạn[cite: 14]
        cv->score = aiData["score"].get<int>();[cite: 14];
        cv->skills = aiData["skills"].get<std::vector<std::string>>();[cite : 14];

        LOG_INFO("CV #" + cv->id + " successfully processed by Gemini AI.");[cite: 1, 36];
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to parse Gemini AI response: " + std::string(e.what()));[cite: 36];
    }
}
// -------------------- HANDLER AI EVALUATION (Tích hợp Gemini & Ollama) --------------------
#include "ai/AIFactory.h"

void CVController::handleAIEvaluation() {
    auto all = database.getAll();
    if (all.empty()) {
        OutputView::showError("No CVs available. Load data first.");
        return;
    }

    // 1. Chọn CV cần đánh giá thông qua ID
    int id = InputView::getIntInput("Enter CV ID to evaluate with AI: ");
    CV* cv = database.getById(id);
    if (!cv) {
        OutputView::showError("CV with ID " + std::to_string(id) + " not found.");
        return;
    }

    // 2. Cho phép người dùng lựa chọn nhà cung cấp AI
    OutputView::showMessage("\n=== SELECT AI PROVIDER ===");
    OutputView::showMessage("1. Google Gemini (Cloud AI)");
    OutputView::showMessage("2. Ollama (Local AI - Qwen/Llama)");
    int choice = InputView::getIntInput("Your choice (1 or 2): ");

    // 3. Khởi tạo client thông qua AIFactory (Áp dụng Polymorphism / Strategy Pattern)
    std::unique_ptr<IAIClient> aiClient;
    if (choice == 1) {
        aiClient = AIFactory::createClient(AIFactory::GEMINI);
        LOG_INFO("Selected Gemini AI client for evaluation.");
    } else {
        aiClient = AIFactory::createClient(AIFactory::OLLAMA);
        LOG_INFO("Selected Ollama AI client for evaluation.");
    }

    // 4. Nhập Yêu cầu công việc (Job Description) từ người dùng
    std::string jobDesc = InputView::getStringInput("Enter Job Description (JD): ");
    if (jobDesc.empty()) {
        OutputView::showError("Job Description cannot be empty.");
        return;
    }

    OutputView::showMessage("\n[Processing] AI is evaluating the CV, please wait...");
    LOG_INFO("Sending CV #" + std::to_string(id) + " content to AI provider.");

    try {
        // 5. Gọi hàm đa hình danhGiaCV đã được đồng bộ chuẩn giao diện IAIClient
        std::string evaluationResult = aiClient->danhGiaCV(cv->raw_text, jobDesc);

        // 6. Hiển thị kết quả ra màn hình giao diện View
        OutputView::showMessage("\n================ AI EVALUATION RESULT ================");
        std::cout << evaluationResult << "\n";
        OutputView::showMessage("======================================================");

        LOG_INFO("AI evaluation completed successfully for CV #" + std::to_string(id));
    } catch (const std::exception& e) {
        OutputView::showError("AI Evaluation error: " + std::string(e.what()));
        LOG_ERROR("AI evaluation failed: " + std::string(e.what()));
    }
}