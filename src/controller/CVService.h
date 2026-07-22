#ifndef CVSERVICE_H
#define CVSERVICE_H

#include <string>
#include <vector>
#include "model/CV.h"
#include "model/CVDatabase.h"
#include "scanner/ScanEngine.h"
#include "ai/IAIClient.h"

class CVService {
public:
    // 4 bước xử lý AI & luồng chính
    static bool validateFile(const std::string& filePath, std::string& outErrorMessage);
    static std::string sanitizeText(const std::string& rawText);
    static std::string callAIWithRetry(IAIClient& aiClient, const std::string& prompt, int maxRetries = 2);
    static bool exportScanResult(const std::string& outputPath, const ScanResult& result);
    static bool processAndScanCV(const std::string& filePath, IAIClient& aiClient, ScanResult& outResult);

    // Các hàm nghiệp vụ hiện có
    static int loadCVsFromDirectory(const std::string& dir, CVDatabase& db);
    static bool saveCVsToFile(const std::string& path, const CVDatabase& db);

    static std::vector<CV*> filterBySkill(const std::vector<CV*>& list, const std::string& keyword);
    static std::vector<CV*> filterByExperience(const std::vector<CV*>& list, int minYears);
    static std::vector<CV*> filterByEducation(const std::vector<CV*>& list, const std::string& degree);

    // [ĐÃ HIỆN THỰC] Phương thức quét danh sách CV dùng ScanEngine
    static ScanResult scanCVs(const std::vector<CV*>& list);

    static int countQualified(const std::vector<CV*>& list);
    static int countJunk(const std::vector<CV*>& list);
    static int countMismatch(const std::vector<CV*>& list);
    static void printStatistics(const std::vector<CV*>& list);
};

#endif // CVSERVICE_H