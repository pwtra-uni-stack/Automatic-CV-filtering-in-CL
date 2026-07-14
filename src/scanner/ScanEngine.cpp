#include "ScanEngine.h"

ScanEngine::ScanEngine()
{
}

void ScanEngine::addStrategy(ScanStrategy* strategy)
{
    if (strategy)
        strategies.push_back(strategy);
}

void ScanEngine::clearStrategies()
{
    strategies.clear();
}

ScanResult ScanEngine::scanAll(const std::vector<CV*>& cvs)
{
    ScanResult result;

    // Không có strategy nào → không phân loại được
    if (strategies.empty())
        return result;

    // Giả định: strategy[0] là BasicScan, strategy[1] là AdvancedScan (nếu có)
    // Nhưng để an toàn, ta kiểm tra từng vị trí
    bool hasBasic = strategies.size() >= 1;
    bool hasAdvanced = strategies.size() >= 2;

    for (CV* cv : cvs)
    {
        if (cv == nullptr)
            continue;

        bool basicPass = true;
        bool advancedPass = true;   // mặc định đạt nếu không có advanced

        // Áp dụng Basic (nếu có)
        if (hasBasic)
            basicPass = strategies[0]->scan(*cv);

        // Nếu basic thất bại → junk
        if (!basicPass)
        {
            result.junk.push_back(cv);
            continue;
        }

        // Áp dụng Advanced (nếu có)
        if (hasAdvanced)
            advancedPass = strategies[1]->scan(*cv);

        // Nếu vượt qua cả basic và (nếu có) advanced → qualified
        if (advancedPass)
            result.qualified.push_back(cv);
        else
            result.mismatch.push_back(cv);
    }

    return result;
}