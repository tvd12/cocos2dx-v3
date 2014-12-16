//
//  Leaderboard.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 7/28/14.
//
//

#ifndef __DragonVideoPoker__Leaderboard__
#define __DragonVideoPoker__Leaderboard__

#include <iostream>
#include <string>
#include <vector>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class UserInfo;

class Leaderboard : public CCObject {
public:
    Leaderboard();
    
    static Leaderboard* create();
    
    CC_SYNTHESIZE(string, mUserChipRank, UserChipRank);
    void setUserInfos(const vector<UserInfo*> &userInfos);
    inline vector<UserInfo*> getUserInfos() { return mUserInfos; }
    inline vector<UserInfo*> *getUserInfosPtr() {return &mUserInfos; }
protected:
    vector<UserInfo*> mUserInfos;
};

#endif /* defined(__DragonVideoPoker__Leaderboard__) */
