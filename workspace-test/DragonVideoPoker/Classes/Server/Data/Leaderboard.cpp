//
//  Leaderboard.cpp
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 7/28/14.
//
//

#include "Leaderboard.h"
#include "UserInfo.h"

Leaderboard::Leaderboard() :
mUserChipRank("1000+"),
mUserInfos(vector<UserInfo*>(20))
{
    
}

Leaderboard* Leaderboard::create() {
    Leaderboard* obj = new Leaderboard();
    
    return obj;
}

void Leaderboard::setUserInfos(const vector<UserInfo*> &userInfos) {
    if(mUserInfos.size()) {
        for(int i = 0 ; i < mUserInfos.size() ; i++) {
            if(mUserInfos[i] != NULL) {
                mUserInfos[i]->release();
            }
        }
    }
    
    mUserInfos = userInfos;
}