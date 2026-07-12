//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H
#include "CVFilter.h"
#include <vector>
#include <string>

class SkillFilter : public CVFilter {
public:
    std::vector <std::string> required_skills; //Danh sách các từ khóa kỹ năng bắt buộc cần tìm kiếm để lọc

    //Hàm khởi tạo nhận vào mãng kỹ năng tiêu chuẩn yêu cầu tuyển dụng
    SkillFilter(std::vector <std::string> sk) {
        required_skills = sk;
    }

    //Ghi đè lại hàm match của lớp cha để thực hiện kiểm tra kỹ năng
    bool match(CV cv) override {
        //duyệt qua từng kỹ năng bắt buộc trong bộ lọc tuyển dụng
        for (int i = 0; i < required_skills.size(); i++) {
            bool TimThay = false;
            // Quét danh sách kỹ năng ứng viên ghi trong Cv xem có khớp không
            for (int j = 0; j < required_skills.size(); j++) {
                if (cv.skills[j] == required_skills[i]) {
                    TimThay = true;
                    break;
                }
            }
            if (TimThay == false) return false; //chỉ cần thiếu 1 kỹ năng yêu cầu bắt buộc là loại luôn
        }
        return true;
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_SKILLFILTER_H
