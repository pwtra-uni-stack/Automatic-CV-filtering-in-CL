// src/controller/CVService.cpp
#include "CVService.h"
#include "model/FileManager.h"
#include "scanner/BasicScan.h"
#include "scanner/AdvancedScan.h"
#include "utils/Logger.h"
#include <iostream>

class CV;
class CVDatabase;

int CVService::loadCVsFromDirectory(const std::string& dir, CVDatabase& db) {
    LOG_INFO("Loading CVs from: " + dir);
    auto files = FileManager::getCVFiles(dir);
    int count = 0;
    for (const auto& file : files) {
        CV* cv = FileManager::loadCVFromFile(file);
        if (cv) {
            db.addCV(cv);
            count++;
        }
    }
    LOG_INFO("Loaded " + std::to_string(count) + " CVs");
    return count;
}

bool CVService::saveCVsToFile(const std::string& path, const CVDatabase& db) {
    LOG_INFO("Saving CVs to: " + path);
    return FileManager::saveAllCVs(path, db.getAll());
}

std::vector<CV*> CVService::filterBySkill(const std::vector<CV*>& list, const std::string& keyword) {
    std::vector<CV*> result;
    for (auto* cv : list) {
        for (const auto& skill : cv->skills) {
            if (skill.find(keyword) != std::string::npos) {
                result.push_back(cv);
                break;
            }
        }
    }
    return result;
}

std::vector<CV*> CVService::filterByExperience(const std::vector<CV*>& list, int minYears) {
    std::vector<CV*> result;
    for (auto* cv : list) {
        if (cv->experienceYears >= minYears) {
            result.push_back(cv);
        }
    }
    return result;
}

std::vector<CV*> CVService::filterByEducation(const std::vector<CV*>& list, const std::string& degree) {
    std::vector<CV*> result;
    for (auto* cv : list) {
        if (cv->education.find(degree) != std::string::npos) {
            result.push_back(cv);
        }
    }
    return result;
}

ScanResult CVService::scanCVs(const std::vector<CV*>& list) {
    LOG_INFO("Scanning " + std::to_string(list.size()) + " CVs");
    ScanEngine engine;
    BasicScan basic;
    AdvancedScan advanced;
    engine.addStrategy(&basic);
    engine.addStrategy(&advanced);
    return engine.scanAll(list);
}

int CVService::countQualified(const std::vector<CV*>& list) {
    int count = 0;
    for (auto* cv : list) {
        if (cv->score >= 60) count++;
    }
    return count;
}

int CVService::countJunk(const std::vector<CV*>& list) {
    int count = 0;
    for (auto* cv : list) {
        if (cv->skills.empty() || cv->candidate->name.empty()) count++;
    }
    return count;
}

int CVService::countMismatch(const std::vector<CV*>& list) {
    int total = list.size();
    int junk = countJunk(list);
    int qualified = countQualified(list);
    return total - junk - qualified;
}

void CVService::printStatistics(const std::vector<CV*>& list) {
    int total = list.size();
    int junk = countJunk(list);
    int mismatch = countMismatch(list);
    int qualified = countQualified(list);
    std::cout << "\n========== STATISTICS ==========\n";
    std::cout << "Total CVs      : " << total << '\n';
    std::cout << "Junk (trash)   : " << junk << '\n';
    std::cout << "Mismatch       : " << mismatch << '\n';
    std::cout << "Qualified      : " << qualified << '\n';
    std::cout << "================================\n";
}