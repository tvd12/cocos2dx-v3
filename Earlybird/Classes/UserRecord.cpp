//
//  UserRecord.cpp
//  Earlybird
//
//  Created by Dung Ta Van on 1/12/15.
//
//

#include "UserRecord.h"

UserRecord::UserRecord() :
mTheBestScore(0) {
    init();
}

bool UserRecord::init() {
    
    mTheBestScore = UserDefault::getInstance()
    ->getIntegerForKey("best_score", 0);
    
    return true;
}

UserRecord* UserRecord::getInstance() {
    static UserRecord sInstance;
    
    return &sInstance;
}

void UserRecord::saveTheBestScore(int score) {
    mTheBestScore = score;
    UserDefault::getInstance()->setIntegerForKey("best_score", score);
}

int UserRecord::getTheBestScore() {
    return mTheBestScore;
}

UserRecord::~UserRecord() {
    
}

