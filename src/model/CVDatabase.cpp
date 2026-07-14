#include "CVDatabase.h"
#include <iostream>
#include <algorithm>

CVDatabase::CVDatabase() {}

CVDatabase::~CVDatabase() {
    // Giải phóng toàn bộ vùng nhớ của các CV được lưu trong Database
    for (CV* cv : list_cv) {
        if (cv != nullptr) {
            delete cv;
        }
    }
    list_cv.clear();
}

void CVDatabase::addCV(CV* cv) {
    if (cv != nullptr) {
        list_cv.push_back(cv);
    }
}

void CVDatabase::removeCV(int id) {
    std::string idStr = "CV_" + std::to_string(id); // Hoặc điều chỉnh quy tắc chuyển ID phù hợp
    auto it = std::remove_if(list_cv.begin(), list_cv.end(), [&idStr](CV* cv) {
        if (cv != nullptr && (cv->id == idStr || cv->id == std::to_string(id))) {
            delete cv; // Giải phóng vùng nhớ trước khi xóa khỏi vector
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

CV* CVDatabase::getById(int id) {
    std::string targetId1 = "CV_" + std::to_string(id);
    std::string targetId2 = std::to_string(id);

    for (CV* cv : list_cv) {
        if (cv != nullptr && (cv->id == targetId1 || cv->id == targetId2)) {
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
                break; // Chỉ cần một bộ lọc không khớp thì bỏ qua CV này
            }
        }

        if (passAll) {
            results.push_back(cv);
        }
    }
    return results;
}