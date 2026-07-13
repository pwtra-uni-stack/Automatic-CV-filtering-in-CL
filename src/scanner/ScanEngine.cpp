#include "ScanEngine.h"

ScanEngine::ScanEngine()
{
}

void ScanEngine::addStrategy(ScanStrategy* strategy)
{
    strategies.push_back(strategy);
}

void ScanEngine::clearStrategies()
{
    strategies.clear();
}

ScanResult ScanEngine::scanAll(const std::vector<CV*>& cvs)
{
    ScanResult result;

    for (CV* cv : cvs)
    {
        if (cv == nullptr)
            continue;

        bool basicPass = true;
        bool advancedPass = true;

        if (strategies.size() >= 1)
            basicPass = strategies[0]->scan(*cv);

        if (!basicPass)
        {
            result.junk.push_back(cv);
            continue;
        }

        if (strategies.size() >= 2)
            advancedPass = strategies[1]->scan(*cv);

        if (advancedPass)
        {
            result.qualified.push_back(cv);
        }
        else
        {
            result.mismatch.push_back(cv);
        }
    }

    return result;
}
