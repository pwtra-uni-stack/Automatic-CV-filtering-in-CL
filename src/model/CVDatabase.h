#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H

#include "CV.h"
#include "CVFilter.h"
#include <vector>
#include <string>

class CVDatabase {
private:
    std::vector<CV*> list_cv; // Đổi thành danh sách con trỏ để quản lý đồng bộ

public:
    CVDatabase();
    ~CVDatabase(); // Destructor giải phóng toàn bộ CV* khi kết thúc chương trình

    void addCV(CV* cv); // Nhận con trỏ CV*
    void removeCV(int id); // Sửa tham số ID thành int để khớp logic menu xóa trong CVController
    void inDanhSach();
    std::vector<CV*> getAll(); // Trả về danh sách con trỏ
    CV* getById(int id); // Đổi kiểu ID thành int khớp với menu điều khiển của bạn

    // Chấp nhận vector bộ lọc đa hình (hoạt động theo cơ chế And-Filter)
    std::vector<CV*> filter(const std::vector<CVFilter*>& filters);
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H