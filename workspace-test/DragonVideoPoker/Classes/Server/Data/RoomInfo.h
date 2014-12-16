//
//  RoomInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/25/14.
//
//

#ifndef __DragonVideoPoker__RoomInfo__
#define __DragonVideoPoker__RoomInfo__

#include <string>
#include "cocos2d.h"
#include "ILabelSource.h"

using namespace std;
using namespace cocos2d;

class RoomInfoJackpot : public ILabelSource {
public:
    RoomInfoJackpot() : ILabelSource() {}
    virtual void updateValue(const long long &);
};

class RoomInfo : public CCObject {
public:
    RoomInfo();
    
    void updateChipTypeValueFromString(string* chipType);
    void setJackpot(long long var);
    
    // static memeber
    CC_SYNTHESIZE(long, mIndex, Index);
    CC_SYNTHESIZE(long, mLevelRequired, LevelRequired);
    CC_SYNTHESIZE(string*, mRoomName, RoomName);
    CC_SYNTHESIZE(long, mMinStakes, MinStakes);
    CC_SYNTHESIZE(long, mMaxStakes, MaxStakes);
    CC_SYNTHESIZE(long, mJackpotPercent, JackpotPercent);   // server use only
    CC_SYNTHESIZE(long, mJackpotHand, JackpotHand);
    CC_SYNTHESIZE(long, mJackpotReset, JackpotReset);
    CC_SYNTHESIZE(string*, mJackpotName, JackpotName);
    
    CC_SYNTHESIZE(long, mChip1, Chip1);
    CC_SYNTHESIZE(long, mChip2, Chip2);
    CC_SYNTHESIZE(long, mChip3, Chip3);

    // dynamic memeber
    CC_SYNTHESIZE(long, mNumberOnlinePlayers, NumberOnlinePlayers);
    CC_SYNTHESIZE_READONLY(long long, mJackpot, Jackpot);
    CC_SYNTHESIZE(RoomInfoJackpot*, mRoomInfoJackpot, RoomInfoJackpot);

private:

};


#endif /* defined(__DragonVideoPoker__RoomInfo__) */
