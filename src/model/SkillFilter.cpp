#include "SkillFilter.h"
#include "CV.h"

SkillFilter::SkillFilter(std::vector<std::string> sk) {
    required_skills = sk;
}

bool SkillFilter::match(CV cv) {
    // Với mỗi từ khóa yêu cầu
    for (const std::string& keyword : required_skills) {
        bool found = false;
        // Duyệt qua tất cả kỹ năng của CV
        for (const std::string& skill : cv.skills) {
            // Tìm kiếm chuỗi con (không phân biệt hoa/thường nếu cần)
            if (skill.find(keyword) != std::string::npos) {
                found = true;
                break;
            }
        }
        // Nếu thiếu bất kỳ từ khóa nào -> không khớp
        if (!found) return false;
    }
    return true;
}