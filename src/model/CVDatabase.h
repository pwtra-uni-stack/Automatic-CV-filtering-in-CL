//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
#include "CV.h"
#include <vector>

class CVDatabase {
public:
    std::vector <CV> list_cv;  //Mãng động vector đóng vai trò là "Kho dữ liệu" lưu trữ toàn bọo các CV

    //Hàm khởi tạo mặc định
    CVDatabase() {}

    //Hàm nạp một đối tượng CV mới vào cuối mảng để thực hiện lưu trữ thông tin
    void addCV(CV cv) {
        list_cv.push_back(cv);  //hàm push_back có sẵn giúp đẩy dữ liệu vào bộ nhớ kho
        std::cout << " -> [Database] Da luu thong tin CV" << cv.cv_id << "vao he thong!\n";
    }
    //Hàm duyệt qua kho dữ liệu từ đầu đến cuối và in toàn bộ danh sách ra màn hình
    void inDanhSach() {
        for (int i = 0; i < list_cv.size(); i++) {
            list_cv[i].HienThi(); //Gọi hàm hiển thị của phần tử CV thứ i
        }
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_CVDATABASE_H
