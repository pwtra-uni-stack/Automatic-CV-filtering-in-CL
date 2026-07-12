//
// Created by ADMIN on 09/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H
#include <string>
#include <iostream>

class Candidate {
public:
    std::string candidate_id;
    std::string name;
    std::string email;

    //hàm khởi tạo mặc định (ko tham số): Gán các chuỗi về rỗng
    Candidate() {
        candidate_id = " ";
        name = "";
        email = "";
    }

    //Hàm khởi tạo có tham số:đổ nhanh dữ liệu vào các thuộc tính khi tạo đối tượng
    Candidate(std::string id, std::string n, std::string e) {
        candidate_id = id;
        name = n;
        email = e;
    }

    //Hàm in trực tiếp thông tin ứng viên ra màn hình dòng lệnh

    void HienThi() {
        std::cout <<"Candidate [" << candidate_id << ", "<< name << ", "<< email << "]" << std::endl;
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_CANDIDATE_H
