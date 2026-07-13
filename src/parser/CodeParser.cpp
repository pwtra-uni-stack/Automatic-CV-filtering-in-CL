#include "CodeParser.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;

std::string CodeParser::quétThưMụcCode(std::string duong_dan_thu_muc) {
    if (!fs::exists(duong_dan_thu_muc) || !fs::is_directory(duong_dan_thu_muc)) {
        return "[Lỗi] Thư mục mã nguồn không tồn tại!";
    }

    std::stringstream chuoi_code_tong_hop;
    
    // Định nghĩa các đuôi file code được phép đọc
    std::set<std::string> duoi_file_hop_le = {".py", ".cpp", ".h", ".java", ".js", ".ts"};
    // Bỏ qua các thư mục rác/thư viện cài thêm để tránh AI bị quá tải dữ liệu
    std::set<std::string> thu_muc_bo_qua = {".venv", "node_modules", ".git", "build", "__pycache__"};

    // Duyệt đệ quy (vào cả các thư mục con sâu nhất)
    for (const auto& entry : fs::recursive_directory_iterator(duong_dan_thu_muc)) {
        auto path = entry.path();

        // Kiểm tra nếu đường dẫn đi qua thư mục rác thì bỏ qua
        bool la_thu_muc_rac = false;
        for (const auto& part : path) {
            if (thu_muc_bo_qua.count(part.string())) {
                la_thu_muc_rac = true;
                break;
            }
        }
        if (la_thu_muc_rac) continue;

        // Nếu phát hiện đúng file code hợp lệ
        if (fs::is_regular_file(entry) && duoi_file_hop_le.count(path.extension().string())) {
            std::ifstream file(path);
            if (file.is_open()) {
                // Lấy đường dẫn tương đối để gắn nhãn file cho AI dễ hiểu cấu trúc dự án
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