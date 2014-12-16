//
//  HourlyBonusInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#ifndef __DragonVideoPoker__HourlyBonusInfo__
#define __DragonVideoPoker__HourlyBonusInfo__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class HourlyBonusInfo : public CCObject {
public:
    HourlyBonusInfo();
    void resetHourlyBonusInfo();
    void updateLastBonusTime();
    void updateCurrentBonus();
    
    CC_SYNTHESIZE(long, mBonusMax, BonusMax);
    CC_SYNTHESIZE(long, mCurrentBonus, CurrentBonus);
    CC_SYNTHESIZE(float, mChipsPerSecond, ChipsPerSecond);
    
    CC_SYNTHESIZE(long, mLastBonusTime, LastBonusTime);
    CC_SYNTHESIZE(long, mLastBonus, LastBonus);
    CC_SYNTHESIZE(long, mLastClaimed, LastClaimed);

private:
    long getCurrentUnixTime();
    
};

#endif /* defined(__DragonVideoPoker__HourlyBonusInfo__) */
