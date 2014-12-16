//
//  TdgDonCardData.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/12/14.
//
//

#ifndef __DragonVideoPoker__TdgDonCardData__
#define __DragonVideoPoker__TdgDonCardData__

#include "cocos2d.h"
#include "SmartFox.h"

USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgDonCardData : public CCObject
{
public:
    virtual bool init();
    CREATE_FUNC(TdgDonCardData);
    
    void updateData(SFSObject* data);
    
    CC_SYNTHESIZE(vector<int>*, mDonCards, DonCards);
    CC_SYNTHESIZE(long long, mWonChips, WonChips);
    CC_SYNTHESIZE(int, mHoldPosition, HoldPosition);
};

#endif /* defined(__DragonVideoPoker__TdgDonCardData__) */
