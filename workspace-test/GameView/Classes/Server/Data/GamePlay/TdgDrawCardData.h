//
//  TdgDrawCardData.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/18/14.
//
//

#ifndef __DragonVideoPoker__TdgDrawCardData__
#define __DragonVideoPoker__TdgDrawCardData__

#include "cocos2d.h"
#include "SmartFox.h"

USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgDrawCardData : public CCObject
{
public:
    virtual bool init();
    CREATE_FUNC(TdgDrawCardData);
    
    void updateData(SFSObject* data);
    
    CC_SYNTHESIZE(vector<int>*, mDrawCards, DrawCards);
    CC_SYNTHESIZE(int, mWonHandType, WonHandType);
    CC_SYNTHESIZE(int, mWonBit, WonBit);
    CC_SYNTHESIZE(long long, mWonValue, WonValue);
    CC_SYNTHESIZE(bool, mIsGotJackpot, IsGotJackpot);
};


#endif /* defined(__DragonVideoPoker__TdgDrawCardData__) */
