//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_OUTPUTVIEW_H
#define AUTOMATIC_CV_FILTERING_IN_CL_OUTPUTVIEW_H
#pragma once
#include <string>
#include <vector>

class CV; // forward declaration để tránh include CV.h

class OutputView {
public:
    static void showMessage(const std::string& msg);
    static void showError(const std::string& error);
    static void showCVList(const std::vector<CV*>& cvs);
    static void showCVDetail(const CV* cv);
    static void showStatistics(int total, int junk, int mismatch, int qualified);
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_OUTPUTVIEW_H
