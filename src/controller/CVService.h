// src/controller/CVService.h
#ifndef CVSERVICE_H
#define CVSERVICE_H

#include <string>
#include <vector>
#include "model/CV.h"
#include "model/CVDatabase.h"
#include "scanner/ScanEngine.h"
#include "ai/IAIClient.h" // Thêm header để làm việc với AI Client

class CVService {
public:
    // =========================================================================
    // 4 BƯỚC MỚI BỔ SUNG VÀO LUỒNG XỬ LÝ CV VỚI AI
    // =========================================================================

    // Bước 1: Kiểm tra tính hợp lệ của tệp (Đuôi .pdf/.docx, dung lượng, sự tồn tại)
    static bool validateFile(const std::string& filePath, std::string& outErrorMessage);

    // Bước 2: Làm sạch và tiền xử lý văn bản thô trích xuất từ CV
    static std::string sanitizeText(const std::string& rawText);

    // Bước 3: Gửi request đến AI Client với cơ chế Retry & Timeout
    static std::string callAIWithRetry(IAIClient& aiClient,
                                       const std::string& prompt,
                                       int maxRetries = 2);

    // Bước 4: Xuất và lưu kết quả đánh giá (Ra file JSON/CSV hoặc ghi chép báo cáo)
    static bool exportScanResult(const std::string& outputPath,
                                 const ScanResult& result);

    // [HÀM ĐIỀU PHỐI TỔNG HỢP] Kết hợp cả 4 bước trên thành luồng quét CV hoàn chỉnh
    static bool processAndScanCV(const std::string& filePath,
                                 IAIClient& aiClient,
                                 ScanResult& outResult);


    // =========================================================================
    // CÁC HÀM HIỆN CÓ TRONG DỰ ÁN CỦA BẠN
    // =========================================================================

    // Load & Save
    static int loadCVsFromDirectory(const std::string& dir, CVDatabase& db);
    static bool saveCVsToFile(const std::string& path, const CVDatabase& db);

    // Filter
    static std::vector<CV*> filterBySkill(const std::vector<CV*>& list, const std::string& keyword);
    static std::vector<CV*> filterByExperience(const std::vector<CV*>& list, int minYears);
    static std::vector<CV*> filterByEducation(const std::vector<CV*>& list, const std::string& degree);

    // Scan
    static ScanResult scanCVs(const std::vector<CV*>& list);

    // Statistics
    static int countQualified(const std::vector<CV*>& list);
    static int countJunk(const std::vector<CV*>& list);
    static int countMismatch(const std::vector<CV*>& list);
    static void printStatistics(const std::vector<CV*>& list);
};

#endif // CVSERVICE_H