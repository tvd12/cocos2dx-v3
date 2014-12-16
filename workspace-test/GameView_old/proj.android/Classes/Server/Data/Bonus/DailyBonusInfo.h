//
//  DailyBonusInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#ifndef __DragonVideoPoker__DailyBonusInfo__
#define __DragonVideoPoker__DailyBonusInfo__

#include "cocos2d.h"

USING_NS_CC;

class DailyBonusInfo : public CCObject
{
public:
    
    ~DailyBonusInfo();
    virtual bool init();
    
    CREATE_FUNC(DailyBonusInfo);
    
    void resetDailyBonusInfo();
    void simulateDailyBonus();
    
    // days info
    CC_SYNTHESIZE(long *, mDayBonusList, DayBonusList);
    CC_SYNTHESIZE(long, mDaysPlay, DaysPlay);
    CC_SYNTHESIZE(long, mDaysBonus, DaysBonus);
    
    // vip bonus
    CC_SYNTHESIZE(long, mVipBonus, VipBonus);
    CC_SYNTHESIZE(long, mVipStatus, VipStatus);
    
    // level bonus
    CC_SYNTHESIZE(long, mLevelBonus, LevelBonus);
    CC_SYNTHESIZE(long, mLevel, Level);
    CC_SYNTHESIZE(long, mBonusPerLevel, BonusPerLevel);
    
    // friends bonus
    CC_SYNTHESIZE(long, mFriendsBonus, FriendsBonus);
    CC_SYNTHESIZE(long, mFriendsNumber, FriendsNumber);
    CC_SYNTHESIZE(long, mBonusPerFriend, BonusPerFriend);
    
    // total bonus
    CC_SYNTHESIZE(long, mTotalBonus, TotalBonus);
    
    std::string getVipTypeText();

private:
        std::string mVipTypeText;
};

#endif /* defined(__DragonVideoPoker__DailyBonusInfo__) */
