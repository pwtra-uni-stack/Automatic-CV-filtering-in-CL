// src/view/OutputView.h
#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <string>
#include <vector>

class CV;

class OutputView {
public:
    static void showMessage(const std::string& msg);
    static void showError(const std::string& error);
    static void showCVList(const std::vector<CV*>& cvs);
    static void showCVDetail(const CV* cv);
    static void showStatistics(int total, int junk, int mismatch, int qualified);
    static void showRawContent(const std::string& content, const std::string& filename);
};

#endif // OUTPUTVIEW_H