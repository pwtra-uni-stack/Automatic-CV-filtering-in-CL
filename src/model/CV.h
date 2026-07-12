//
// Created by ADMIN on 09/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CV_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CV_H
#include "Candidate.h"
#include <vector>
#include <string>

class CV {
public:
    std::string cv_id;             // Biến lưu mã số định danh của hồ sơ CV
    Candidate candidate;      // Đối tượng Candidate sở hữu cấu trúc CV này
    std::vector<std::string> skills;    // Mảng động chứa danh sách kỹ năng của ứng viên
    int experience_years;     // Biến lưu số năm kinh nghiệm làm việc
    std::string education;         // Biến lưu trình độ học vấn
    std::string raw_text;          // Biến lưu chuỗi văn bản thô ban đầu đọc từ file CV

    // --- BỔ SUNG DÒNG NÀY: Hàm khởi tạo mặc định không tham số để sửa lỗi biên dịch ---
    CV() {
        cv_id = "";
        experience_years = 0;
        education = "";
        raw_text = "";
    }

    // Hàm khởi tạo nhận vào đầy đủ thông tin (giữ nguyên của bạn)
    CV(std::string id, Candidate cand, std::vector<std::string> sk, int exp, std::string edu, std::string raw = "") {
        cv_id = id;
        candidate = cand;
        skills = sk;
        experience_years = exp;
        education = edu;
        raw_text = raw;
    }

    // Hàm hiển thị chi tiết nội dung CV (giữ nguyên của bạn)
    void HienThi() {
        std::cout << "CV ID: " << cv_id << " | ";
        candidate.HienThi();
        std::cout << " | Kinh nghiem: " << experience_years << " nam | Hoc van: " << education << " | Ky nang: ";
        for (size_t i = 0; i < skills.size(); i++) {
            std::cout << skills[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_CV_H
