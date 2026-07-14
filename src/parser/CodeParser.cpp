#include "CodeParser.h"
#include <string>
#include <sstream>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

std::string CodeParser::quétThưMụcCode(std::string duong_dan_thu_muc) {
    if (!fs::exists(duong_dan_thu_muc) || !fs::is_directory(duong_dan_thu_muc)) {
        return "[Lỗi] Thư mục mã nguồn không tồn tại!";
    }

    std::stringstream chuoi_code_tong_hop;

    // Sửa: khai báo đúng kiểu std::set<std::string>
    std::set<std::string> duoi_file_hop_le = {".py", ".cpp", ".h", ".java", ".js", ".ts"};
    std::set<std::string> thu_muc_bo_qua = {".venv", "node_modules", ".git", "build", "__pycache__"};

    for (const auto& entry : fs::recursive_directory_iterator(duong_dan_thu_muc)) {
        auto path = entry.path();
        bool la_thu_muc_rac = false;
        for (const auto& part : path) {
            if (thu_muc_bo_qua.count(part.string())) {
                la_thu_muc_rac = true;
                break;
            }
        }
        if (la_thu_muc_rac) continue;

        if (fs::is_regular_file(entry) && duoi_file_hop_le.count(path.extension().string())) {
            std::ifstream file(path);
            if (file.is_open()) {
                std::string path_tuong_doi = fs::relative(path, duong_dan_thu_muc).string();
                chuoi_code_tong_hop << "=== FILE: " << path_tuong_doi << " ===\n";
                chuoi_code_tong_hop << file.rdbuf();
                chuoi_code_tong_hop << "\n\n";
                file.close();
            }
        }
    }
    return chuoi_code_tong_hop.str();
}