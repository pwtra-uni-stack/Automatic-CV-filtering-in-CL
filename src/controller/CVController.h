// src/controller/CVController.h
#ifndef CVCONTROLLER_H
#define CVCONTROLLER_H

#include "model/CVDatabase.h"
#include "view/MenuView.h"
#include "view/InputView.h"
#include "view/OutputView.h"
#include "scanner/ScanEngine.h"

class CVController:public CVView {
private:
    CVDatabase database;
    MenuView menu;
    ScanEngine scanEngine;

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
};

#endif // CVCONTROLLER_H