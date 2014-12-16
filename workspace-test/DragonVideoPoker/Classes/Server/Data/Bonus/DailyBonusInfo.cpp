//
//  DailyBonusInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#include "DailyBonusInfo.h"

bool DailyBonusInfo::init()
{
    resetDailyBonusInfo();
    return true;
}

DailyBonusInfo::~DailyBonusInfo()
{
    if (mDayBonusList != NULL) {
        delete mDayBonusList;
    }
}

void DailyBonusInfo::resetDailyBonusInfo()
{
    mDaysPlay            = 0;
    mDaysBonus           = 0;
    mVipBonus            = 0;
    mVipStatus           = 0;
    mLevel               = 0;
    mLevelBonus          = 0;
    mFriendsBonus        = 0;
    mFriendsNumber       = 0;
    mTotalBonus          = 0;
    
    mDayBonusList        = new long[10];
}

void DailyBonusInfo::simulateDailyBonus()
{
    mDaysBonus              = 1000;
    mDaysPlay               = 2;
    
    mVipBonus               = 1000;
    mVipStatus              = 2;
    
    mLevelBonus             = 2000;
    mLevel                  = 20;
    mBonusPerLevel          = 100;
    
    mFriendsBonus           = 10000;
    mFriendsNumber          = 10;
    mBonusPerFriend         = 100;
    
    mTotalBonus             = mDaysBonus + mVipBonus + mLevelBonus + mFriendsBonus;
    
    mDayBonusList[0]        = 200;
    mDayBonusList[1]        = 500;
    mDayBonusList[2]        = 1000;
    mDayBonusList[3]        = 2000;
}

std::string DailyBonusInfo::getVipTypeText() {
    std::string result = "Bronze";
    switch (mVipStatus) {
        case 2:
            result = "Silver";
            break;
        case 3:
            result = "Gold";
            break;
        case 4:
            result = "Platinum";
            break;
        case 5:
            result = "Diamond";
            break;
            
        default:
            break;
            
    }
    result += " VIP Member";
    if(mVipStatus == 0) {
        result = "Non-VIP Member";
    }
    
    return result;
}
