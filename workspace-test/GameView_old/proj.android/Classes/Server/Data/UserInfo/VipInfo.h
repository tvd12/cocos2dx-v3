//
//  VipInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#ifndef __DragonVideoPoker__VipInfo__
#define __DragonVideoPoker__VipInfo__

#include "cocos2d.h"

// vip type define
typedef enum VIP_TYPE
{
    kVIPNormal              = 0,
    kVIPBronze              = 1,
    kVIPSilver              = 2,
    kVIPGold                = 3,
    kVIPPlatinum            = 4,
    kVIPDiamond             = 5,
} Vip_Type;


USING_NS_CC;

class VipInfo: public CCObject
{
public:
    
    VipInfo();
    
    static VipInfo * create();
    
    void reset();
    void updateInfo(long type, long percentMore, long pointMax, long upgradeBonus);
    
    const char* getVipText();
    const char* getVipCardText();
    const char* getNextVipCardText();
    
    const char* getProgressText();
    const char* getDescriptionText1();
    const char* getDescriptionText2();
    const char* getVipPointRequireText();
    const char* getMultiplyText();
    
    CC_SYNTHESIZE(long, mType, Type);
    CC_SYNTHESIZE(float, mMultiply, Multiply);
    CC_SYNTHESIZE(float, mProgressPercent, ProgressPercent);
    CC_SYNTHESIZE(long, mPointMax, PointMax);
    CC_SYNTHESIZE(long, mPointToLevelUp, PointToLevelUp);
    CC_SYNTHESIZE(long, mUpgradeBonus, UpgradeBonus);
    CC_SYNTHESIZE(long, mTotalPointToLevel, TotalPointToLevel);
};


#endif /* defined(__DragonVideoPoker__VipInfo__) */
