//
//  HourlyBonusInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#include "HourlyBonusInfo.h"
#include <time.h>


HourlyBonusInfo::HourlyBonusInfo()
{
    resetHourlyBonusInfo();
}

void HourlyBonusInfo::resetHourlyBonusInfo()
{
    mBonusMax           = 4000;
    mCurrentBonus       = 0;
    mChipsPerSecond     = 0.5;
    mLastBonusTime      = 0;
    mLastBonus          = 0;
    mLastClaimed        = 0;
}

long HourlyBonusInfo::getCurrentUnixTime()
{
    time_t current = time(NULL);
    return current;
}

void HourlyBonusInfo::updateLastBonusTime()
{
    mLastBonusTime = getCurrentUnixTime();
}

void HourlyBonusInfo::updateCurrentBonus()
{
    long currentTime = getCurrentUnixTime();
    
    // get number of second from last server updated
    long seconds = currentTime - mLastBonusTime;
    mCurrentBonus = mLastBonus + (long)(seconds * mChipsPerSecond);
    if (mCurrentBonus > mBonusMax) {
        mCurrentBonus = mBonusMax;
    }
}
