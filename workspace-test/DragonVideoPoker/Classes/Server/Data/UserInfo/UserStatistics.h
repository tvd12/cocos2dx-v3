//
//  UserStatistics.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 6/4/14.
//
//

#ifndef __DragonVideoPoker__UserStatistics__
#define __DragonVideoPoker__UserStatistics__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class UserStatistics : public CCObject {
public:
    virtual bool init();
    CREATE_FUNC(UserStatistics);
    
    const char* getHandsPlayedString();
    const char* getHandsWonString();
    const char* getHandsWonRatioString();
    const char* getBiggestWinString();
    
    CC_SYNTHESIZE(long , mHandsPlayed, HandsPlayed);
    CC_SYNTHESIZE(long, mHandsWon, HandsWon);
    CC_SYNTHESIZE(long long, mBiggestWin, BiggestWin);
    CC_SYNTHESIZE(vector<int>*, mBestHand, BestHand);
};


#endif /* defined(__DragonVideoPoker__UserStatistics__) */
