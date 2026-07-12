//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
#include "CV.h"
#include <string>
#include <sstream>
#include <vector>

class FileManager {
private:
    // Hàm phụ trợ độc bản dùng để tìm kiếm và cắt chuỗi text nằm ở giữa 2 từ khóa mốc định vị
    static std::string layGiaTri(std::string text, std::string TuKhoaBatDau, std::string TuKhoaKetThuc) {
        size_t viTriDau = text.find(TuKhoaBatDau);
        if (viTriDau == std::string::npos) return ""; // Không tìm thấy từ khóa mốc bắt đầu
        viTriDau += TuKhoaBatDau.length(); // Di chuyển con trỏ qua độ dài từ khóa

        size_t viTriCuoi = text.find(TuKhoaKetThuc, viTriDau);
        if (viTriCuoi == std::string::npos) {
            return text.substr(viTriDau); // Nếu không tìm thấy mốc kết thúc, cắt lấy toàn bộ phần còn lại
        }
        return text.substr(viTriDau, viTriCuoi - viTriDau); // Trả về chuỗi cắt được ở giữa
    }

public:
    // Hàm xử lý bóc tách văn bản thô trực tiếp trong file .h
    static CV parseCVText(std::string raw_text) {
        // Tiến hành bóc tách chuỗi thô dựa trên các nhãn nhắm sẵn
        std::string cv_id = layGiaTri(raw_text, "ID: ", "\n");
        std::string name = layGiaTri(raw_text, "Ten: ", "\n");
        std::string email = layGiaTri(raw_text, "Email: ", "\n");
        std::string skills_raw = layGiaTri(raw_text, "Ky nang: ", "\n");
        std::string exp_raw = layGiaTri(raw_text, "Kinh nghiem: ", "\n");
        std::string edu = layGiaTri(raw_text, "Hoc van: ", "\n");

        // Tiến hành xử lý cắt chuỗi kỹ năng phân tách bằng dấu phẩy
        std::vector<std::string> skills;
        std::stringstream ss(skills_raw);
        std::string token;
        while (getline(ss, token, ',')) {
            // SỬA TẠI ĐÂY: Dùng cách truyền thống thay cho .front() để tránh lỗi trình biên dịch cũ
            while (!token.empty() && token[0] == ' ') {
                token.erase(0, 1);
            }
            // SỬA TẠI ĐÂY: Dùng cách truyền thống thay cho .back() để tránh lỗi trình biên dịch cũ
            while (!token.empty() && token[token.length() - 1] == ' ') {
                token.erase(token.length() - 1, 1);
            }
            skills.push_back(token); // Đẩy kỹ năng sạch vào danh sách mảng động
        }

        // Chuyển đổi định dạng số năm kinh nghiệm từ dạng văn bản string sang kiểu số nguyên int
        int exp_years = 0;
        if (!exp_raw.empty()) {
            std::stringstream chuyenDoi(exp_raw);
            chuyenDoi >> exp_years; // Dùng stringstream để ép kiểu an toàn tuyệt đối trên mọi phiên bản C++
        }

        // Tạo lập đối tượng chủ sở hữu hồ sơ (Candidate)
        Candidate cand("CAND_" + cv_id, name, email);

        // Khởi tạo thực thể đối tượng CV hoàn chỉnh từ các dữ liệu vừa parse được và trả về kết quả
        return CV(cv_id, cand, skills, exp_years, edu, raw_text);
    }
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
