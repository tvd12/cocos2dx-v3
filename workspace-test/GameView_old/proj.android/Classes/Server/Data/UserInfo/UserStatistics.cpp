//
//  UserStatistics.cpp
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 6/4/14.
//
//

#include "UserStatistics.h"
#include "GameParams.h"
#include "TextUtils.h"

bool UserStatistics::init()
{
    mHandsPlayed = 0;
    mHandsWon = 0;
    mBiggestWin = 0;
    mBestHand = new vector<int>(5);
    for (int i = 0; i < 5; i++) {
        mBestHand->at(i) = -1;
    }
    return true;
}

const char* UserStatistics::getHandsPlayedString()
{
    CCString *str = CCString::createWithFormat("%s", CURRENCY_LONG(mHandsPlayed));
    return str->getCString();
}

const char* UserStatistics::getHandsWonString()
{
    CCString *str = CCString::createWithFormat("%s", CURRENCY_LONG(mHandsWon));
    return str->getCString();
}

const char* UserStatistics::getHandsWonRatioString()
{
    float wonRatio;
    if (mHandsPlayed < 1) {
        wonRatio = 0;
    }
    else {
        wonRatio = float(mHandsWon) / float(mHandsPlayed) * 100.0f;
    }
    CCString *str = CCString::createWithFormat("%0.2f%%", wonRatio);
    return str->getCString();
}

const char* UserStatistics::getBiggestWinString()
{
    CCString *str = CCString::createWithFormat("%s", CURRENCY_LONG(mBiggestWin));
    return str->getCString();
}
