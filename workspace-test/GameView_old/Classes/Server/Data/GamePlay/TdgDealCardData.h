//
//  TdgDealCardData.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/18/14.
//
//

#ifndef __DragonVideoPoker__TdgDealCardData__
#define __DragonVideoPoker__TdgDealCardData__

#include "cocos2d.h"
#include "SmartFox.h"

USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgDealCardData : public CCObject
{
public:
    virtual bool init();
    CREATE_FUNC(TdgDealCardData);

    void updateData(SFSObject* data);
    
    CC_SYNTHESIZE(vector<int>*, mDealCards, DealCards);
    CC_SYNTHESIZE(int, mHintBits, HintBits);
};

#endif /* defined(__DragonVideoPoker__TdgDealCardData__) */
