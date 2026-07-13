#include "CVDatabase.h"
#include <iostream>

CVDatabase::CVDatabase() {}

void CVDatabase::addCV(CV cv) {
    list_cv.push_back(cv);
}
void CVDatabase::inDanhSach() {
    for (size_t i = 0; i < list_cv.size(); i++) {
        list_cv[i].HienThi();
    }
}
std::vector<CV> CVDatabase::getAll() {
    return list_cv;
}

CV CVDatabase::getById(std::string id) {
    for (size_t i = 0; i < list_cv.size(); i++) {
        if (list_cv[i].cv_id == id) {
            return list_cv[i];
        }
    }
    return CV();
}

std::vector<CV> CVDatabase::filter(CVFilter* criterion) {
    std::vector<CV> results;
    if (criterion == nullptr) return results;

    for (size_t i = 0; i < list_cv.size(); i++) {
        if (criterion->match(list_cv[i])) {
            results.push_back(list_cv[i]);
        }
    }
    return results;
}
