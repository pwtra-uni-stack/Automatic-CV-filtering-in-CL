// src/controller/CVService.h
#ifndef CVSERVICE_H
#define CVSERVICE_H

#include <string>
#include <vector>
#include "model/CV.h"
#include "model/CVDatabase.h"
#include "scanner/ScanEngine.h"

class CVService {
public:
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