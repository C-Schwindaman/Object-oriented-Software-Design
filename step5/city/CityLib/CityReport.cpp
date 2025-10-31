/**
 * @file CityReport.cpp
 *
 * @author Anik Momtaz
 * @author Charles B. Owen
 */

#include "pch.h"
#include "CityReport.h"

/**
 * Constructor
 * @param city City this report is for. 
*/
CityReport::CityReport(City* city) : mCity(city)
{
    // Create and initialize a random number generator
    std::random_device rd;
    mRandom = std::mt19937(rd());
}

/**
 * Add a new city report
 * @param report ReportHolder to add
*/
void CityReport::Add(std::shared_ptr<MemberReport> report)
{
    // Create a ReportHolder object to hold the new report
    // and add the report to it
    auto reportHolder = std::make_shared<ReportHolder>();
    reportHolder->mReport = report;

    std::uniform_int_distribution<int> pick(0, NumContainers-1);
    int newContainer = pick(mRandom);
    int newLocation = (int)mContainers[newContainer].size();
    mContainers[newContainer].push_back(reportHolder);

    if(mFirstContainer < 0)
    {
        // The collection is empty, so the first and last
        // record will be the new location
        mFirstContainer = newContainer;
        mFirstLocation = newLocation;

    }
    else
    {
        auto last = mContainers[mLastContainer][mLastLocation];
        last->mNextContainer = newContainer;
        last->mNextLocation = newLocation;
    }

    // The newly added value is the new last location
    mLastContainer = newContainer;
    mLastLocation = newLocation;
}



