//
//  VipInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#include "VipInfo.h"
#include "GameParams.h"
#include "TextUtils.h"
#include "TdgServer.h"
#include "UserInfo.h"


VipInfo::VipInfo()
{
    reset();
}

VipInfo* VipInfo::create()
{
    VipInfo* vipInfo = new VipInfo();
    return vipInfo;
}

void VipInfo::reset()
{
    mType = kVIPNormal;
    mMultiply = 0;
    mPointMax = 0;
}

void VipInfo::updateInfo(long type, long percentMore, long pointMax, long upgradeBonus)
{
    this->setType(type);
    this->setMultiply((float)percentMore / 100.0f);
    this->setPointMax(pointMax);
    this->setUpgradeBonus(upgradeBonus);
}

const char* VipInfo::getVipText()
{
    const char * ret = "";
    switch (mType) {
        case kVIPBronze:
            ret = "BRONZE";
            break;
            
        case kVIPSilver:
            ret = "SILVER";
            break;
            
        case kVIPGold:
            ret = "GOLD";
            break;
            
        case kVIPPlatinum:
            ret = "PLATINUM";
            break;
            
        case kVIPDiamond:
            ret = "DIAMOND";
            break;
            
        default:
            break;
    }
    
    return ret;
}

const char * VipInfo::getVipCardText()
{
    const char * ret = "";
    switch (mType) {
        case kVIPBronze:
            ret = "BRONZE CARD";
            break;
            
        case kVIPSilver:
            ret = "SILVER CARD";
            break;
            
        case kVIPGold:
            ret = "GOLD CARD";
            break;
            
        case kVIPPlatinum:
            ret = "PLATINUM CARD";
            break;
            
        case kVIPDiamond:
            ret = "DIAMOND CARD";
            break;
            
        default:
            break;
    }
    
    return ret;
}

const char* VipInfo::getNextVipCardText()
{
    const char * ret = "";
    switch (mType) {
        case kVIPNormal:
            ret = "BRONZE CARD";
            break;
            
        case kVIPBronze:
            ret = "SILVER CARD";
            break;
            
        case kVIPSilver:
            ret = "GOLD CARD";
            break;
            
        case kVIPGold:
            ret = "PLATINUM CARD";
            break;
            
        case kVIPPlatinum:
            ret = "DIAMOND CARD";
            break;
            
        case kVIPDiamond:
            ret = "DIAMOND CARD";
            break;
            
        default:
            break;
    }
    
    return ret;
}

const char* VipInfo::getProgressText()
{
    long vipPoint = USERINFO()->getVipPoint();
    CCString* text;
    if (mType == kVIPNormal) {
        text = CCString::create("");
        mProgressPercent = 0;
    }
    else if (mType == kVIPDiamond) {
        text = CCString::create("DIAMOND");
        mProgressPercent = 100.0f;
    }
    else {
        text = CCString::createWithFormat("%ld/%ld", vipPoint, mPointToLevelUp);
        mProgressPercent = ((float)vipPoint / (float)mPointToLevelUp)*100.0f;
    }
    return text->getCString();
}

const char* VipInfo::getDescriptionText1()
{
    long vipPoint = USERINFO()->getVipPoint();
    CCString* text;
    if (mType == kVIPNormal) {
        text = CCString::create("Make a purchase to join VIP CLUB");
    }
    else if (mType == kVIPDiamond) {
        text = CCString::create("Perfect! You're the Maximum VIP!");
    }
    else {
        long needMorePoint = mPointToLevelUp - vipPoint;
        text = CCString::createWithFormat("%s more points to %s",
                                          CURRENCY_LONG(needMorePoint),
                                          getNextVipCardText());
    }
    
    return text->getCString();
}

const char* VipInfo::getDescriptionText2()
{
    CCString* text;
    if (mType == kVIPNormal) {
        text = CCString::create("");
    }
    else {
        text = CCString::createWithFormat("%s all in-app purchase!",
                                          getMultiplyText());
    }
    
    return text->getCString();
}

const char* VipInfo::getVipPointRequireText()
{
    CCString *str = CCString::createWithFormat("%s", CURRENCY_LONG(mTotalPointToLevel));
    return str->getCString();
}

const char* VipInfo::getMultiplyText()
{
    CCString* text = CCString::createWithFormat("x%s",
                                                TEXT().TextFromFloatNumber(mMultiply));

    return text->getCString();
}

