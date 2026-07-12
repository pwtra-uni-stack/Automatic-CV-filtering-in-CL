#include "ScanEngine.h"
#include "BasicScan.h"
#include "AdvancedScan.h"

#include <iostream>

ScanEngine::ScanEngine()
{
    basic = new BasicScan();

    advanced = new AdvancedScan();
}

ScanEngine::~ScanEngine()
{
    delete basic;

    delete advanced;
}

void ScanEngine::scan(std::vector<CV>& list)
{
    junk.clear();
    mismatch.clear();
    qualified.clear();

    for (size_t i = 0; i < list.size(); i++)
    {
        CV cv = list[i];

        try
        {
            if (!basic->scan(cv))
            {
                junk.push_back(cv);
            }
            else if (!advanced->scan(cv))
            {
                mismatch.push_back(cv);
            }
            else
            {
                qualified.push_back(cv);
            }
        }
        catch (...)
        {
            std::cout << "Loi khi scan CV "
                      << cv.cv_id
                      << std::endl;
        }
    }
}

void ScanEngine::showStatistic()
{
    std::cout << "\n===== THONG KE =====\n";

    std::cout << "Qualified : "
              << qualified.size()
              << std::endl;

    std::cout << "Mismatch : "
              << mismatch.size()
              << std::endl;

    std::cout << "Junk : "
              << junk.size()
              << std::endl;
}

void ScanEngine::showQualified()
{
    std::cout << "\n===== QUALIFIED =====\n";

    for (size_t i = 0; i < qualified.size(); i++)
    {
        qualified[i].HienThi();
    }
}

void ScanEngine::showMismatch()
{
    std::cout << "\n===== MISMATCH =====\n";

    for (size_t i = 0; i < mismatch.size(); i++)
    {
        mismatch[i].HienThi();
    }
}

void ScanEngine::showJunk()
{
    std::cout << "\n===== JUNK =====\n";

    for (size_t i = 0; i < junk.size(); i++)
    {
        junk[i].HienThi();
    }
}
