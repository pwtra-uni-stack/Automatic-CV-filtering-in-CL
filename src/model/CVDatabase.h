#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
#include "CV.h"
#include "CVFilter.h"
#include <vector>
#include <string>

class CVDatabase {
public:
    std::vector<CV> list_cv;
    CVDatabase();
    void addCV(CV cv);
    void inDanhSach();
    std::vector<CV> getAll();
    CV getById(std::string id);
    std::vector<CV> filter(CVFilter* criterion);
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
