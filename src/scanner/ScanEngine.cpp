#include "ScanEngine.h"
#include <iostream>

ScanEngine::ScanEngine()
{
}

void ScanEngine::clear()
{
    junkList.clear();
    mismatchList.clear();
    qualifiedList.clear();
}

void ScanEngine::scan(CVDatabase& database)
{
    clear();

    for (CV* cv : database.list_cv)
    {
        if (cv == nullptr)
            continue;

        if (!basicScan.scan(*cv))
        {
            junkList.push_back(cv);
        }
        else if (!advancedScan.scan(*cv))
        {
            mismatchList.push_back(cv);
        }
        else
        {
            qualifiedList.push_back(cv);
        }
    }
}

const std::vector<CV*>& ScanEngine::getJunk() const
{
    return junkList;
}

const std::vector<CV*>& ScanEngine::getMismatch() const
{
    return mismatchList;
}

const std::vector<CV*>& ScanEngine::getQualified() const
{
    return qualifiedList;
}
