// src/controller/CVController.h
#ifndef CVCONTROLLER_H
#define CVCONTROLLER_H

#include "model/CVDatabase.h"
#include "view/MenuView.h"
#include "view/InputView.h"
#include "view/OutputView.h"
#include "scanner/ScanEngine.h"
#include "controller/CVService.h"
#include "ai/IAIClient.h"
#include <memory>

class CVController {
private:
    CVDatabase database;
    MenuView menu;
    ScanEngine scanEngine;

    // Khai báo thêm Service và AI Client
    CVService cvService;
    std::shared_ptr<IAIClient> aiClientInstance;

public:
    CVController();
    void run();
    void handleLoad();
    void handleViewAll();
    void handleViewDetail();
    void handleFilter();
    void handleScan();
    void handleDelete();
    void handleSave();
    void handlePreview();

    // Thêm hàm xử lý đánh giá AI đa hình (Gemini / Ollama)
    void handleAIEvaluation(CV* cv);
    void handleAIEvaluation();
    // Constructor nhận vào AI Client (Áp dụng Dependency Injection)
    explicit CVController(IAIClient* client);
    ~CVController() = default;

    // Hàm hiển thị menu điều hướng chính của ứng dụng
    void showMenu();

    // Hàm xử lý chức năng quét CV khi người dùng chọn trên menu
    void onScanCVMenuSelected();
};

#endif // CVCONTROLLER_H
