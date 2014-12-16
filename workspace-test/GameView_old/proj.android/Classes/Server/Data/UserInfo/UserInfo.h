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

USING_NS_CC;
using namespace std;

class UserInfo: public BaseUserInfo
{
public:
    
    UserInfo();
    virtual ~UserInfo();
    
    static UserInfo* create();
    virtual void reset();
    
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
    CC_SYNTHESIZE(long long, totalBetChips, TotalBetChips);
    CC_SYNTHESIZE(long long, totalWonChips, TotalWonChips);
    CC_SYNTHESIZE(bool, mIsGotJackpot, IsGotJackpot);
    
    // vip info
    CC_SYNTHESIZE(long, mVipType, VipType);
    CC_SYNTHESIZE(long, mVipPoint, VipPoint);
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
