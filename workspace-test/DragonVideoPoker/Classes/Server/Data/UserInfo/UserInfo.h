//
//  UserInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#ifndef __DragonVideoPoker__UserInfo__
#define __DragonVideoPoker__UserInfo__

#include "cocos2d.h"
#include "BaseUserInfo.h"
#include "EziFacebookUser.h"
#include "GameParams.h"
#include "ILabelSource.h"

USING_NS_CC;
using namespace std;

class UserInfoTotalChips: public ILabelSource  {
public:
    virtual void updateValue(const long long &);
};

class UserInfoBetChips: public ILabelSource {
public:
    virtual void updateValue(const long long &);
};

class UserInfoTotalWonChips : public ILabelSource {
public:
    virtual void updateValue(const long long &);
};

class UserInfo: public BaseUserInfo
{
public:
    
    UserInfo();
    virtual ~UserInfo();
    
    static UserInfo* create();
    virtual void reset();
    virtual void setTotalChips(long long var);
    virtual void setTotalBetChips(long long var);
    virtual void setTotalWonChips(long long var);
    
    void importFBUser(EziFacebookUser *fbUser);
    void saveUserFriends(const char *friends);
    
    const char*  getUserName();
    const char*  getAccessToken();
    const char*  getEmailID();
    const char*  getUserFriends();
    
    // levelup system
    CC_SYNTHESIZE(long long, experience, Experience);
    CC_SYNTHESIZE(long long, experienceMax, ExperienceMax);
    
    // player type info
    CC_SYNTHESIZE(long, playerType, PlayerType);        // client only

    // on game play
    CC_SYNTHESIZE_READONLY(long long, totalChips, TotalChips);
    CC_SYNTHESIZE_READONLY(long long, totalBetChips, TotalBetChips);
    CC_SYNTHESIZE_READONLY(long long, totalWonChips, TotalWonChips);
    
    CC_SYNTHESIZE(bool, mIsGotJackpot, IsGotJackpot);
    
    // vip info
    CC_SYNTHESIZE(long, mVipType, VipType);
    CC_SYNTHESIZE(long, mVipPoint, VipPoint);
    
    // user chip rank
    CC_SYNTHESIZE(string *, mChipRank, ChipRank);
    
    //
    CC_SYNTHESIZE(UserInfoTotalChips*, mUserInfoTotalChips, UserInfoTotalChips);
    CC_SYNTHESIZE(UserInfoBetChips*, mUserInfoBetChips, UserInfoBetChips);
    CC_SYNTHESIZE(UserInfoTotalWonChips*, mUserInfoTotalWonChips, UserInfoTotalWonChips);
    
    inline const string getChipsString() { return CURRENCY_LONG(totalChips); }

    string getVipTypeText();

private:
    void saveFBData(const char* key, const char * dataValue);
    
    // fb info
    string *username;           // fb only
    string *accessToken;        // fb only
    string *emailID;
    string *userFriends;
};

#endif /* defined(__DragonVideoPoker__UserInfo__) */
