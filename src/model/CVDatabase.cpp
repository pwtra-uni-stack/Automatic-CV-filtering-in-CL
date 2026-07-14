#include "CVDatabase.h"
#include <iostream>
#include <algorithm>

CVDatabase::CVDatabase() {}

CVDatabase::~CVDatabase() {
    // Giải phóng toàn bộ CV
    for (CV* cv : list_cv) {
        delete cv;
    }
    list_cv.clear();
}

void CVDatabase::addCV(CV* cv) {
    if (cv != nullptr) {
        list_cv.push_back(cv);
    }
}

// ----- Xóa CV theo ID (chỉ so sánh với định dạng "CV_X") -----
void CVDatabase::removeCV(int id) {
    std::string targetId = "CV_" + std::to_string(id);
    auto it = std::remove_if(list_cv.begin(), list_cv.end(), [&targetId](CV* cv) {
        if (cv != nullptr && cv->id == targetId) {
            delete cv;
            return true;
        }
        return false;
    });
    list_cv.erase(it, list_cv.end());
}

void CVDatabase::inDanhSach() {
    for (CV* cv : list_cv) {
        if (cv != nullptr) {
            cv->HienThi();
        }
    }
}

std::vector<CV*> CVDatabase::getAll() {
    return list_cv;
}

// ----- Lấy CV theo ID (chỉ so sánh với định dạng "CV_X") -----
CV* CVDatabase::getById(int id) {
    std::string targetId = "CV_" + std::to_string(id);
    for (CV* cv : list_cv) {
        if (cv != nullptr && cv->id == targetId) {
            return cv;
        }
    }
    return nullptr;
}

std::vector<CV*> CVDatabase::filter(const std::vector<CVFilter*>& filters) {
    std::vector<CV*> results;
    for (CV* cv : list_cv) {
        if (cv == nullptr) continue;
        bool passAll = true;
        for (CVFilter* filter : filters) {
            if (filter != nullptr && !filter->match(*cv)) {
                passAll = false;
                break;
            }
        }
        if (passAll) {
            results.push_back(cv);
        }
    }
    return results;
}