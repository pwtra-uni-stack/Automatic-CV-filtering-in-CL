#ifndef AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
#include "CV.h"
#include <string>
#include <vector>

class FileManager {
private:
    static std::string layGiaTri(std::string text, std::string tuKhoaBatDau, std::string tuKhoaKetThuc);

public:
    static CV parseCVText(std::string raw_text);
    static std::vector<std::string> getCVFiles(const std::string& directory);
    static CV* loadCVFromFile(const std::string& filePath);
    static bool saveAllCVs(const std::string& path, const std::vector<CV*>& cvs);
    static std::string extractTextFromFile(const std::string& filePath); // Hàm tùy chọn trích xuất text thô
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_FILEMANAGER_H
