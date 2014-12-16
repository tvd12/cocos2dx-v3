//
//  UserInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#include "UserInfo.h"
#include "EziSocialDefinition.h"


void UserInfoTotalChips::updateValue(const long long &pValue) {
    ILabelSource::updateValue(pValue);
}

void UserInfoBetChips::updateValue(const long long &pValue) {
    ILabelSource::updateValue(pValue);
}

void UserInfoTotalWonChips::updateValue(const long long &pValue) {
    ILabelSource::updateValue(pValue);
}

UserInfo::UserInfo()
{
    reset();
    mUserInfoTotalChips = new UserInfoTotalChips();
    mUserInfoBetChips = new UserInfoBetChips();
    mUserInfoTotalWonChips = new UserInfoTotalWonChips();
}

void UserInfo::reset()
{
    BaseUserInfo::reset();
    
    // fb data
    username        = NULL;
    accessToken     = NULL;
    emailID         = NULL;
    userFriends     = NULL;
    
    // level up
    experience      = 0;
    mVipType        = 0;
    mVipPoint       = 0;
    playerType      = 0;
    mIsGotJackpot   = false;
}

UserInfo:: ~UserInfo()
{
    if (username != NULL) {
        delete username;
    }
    if (accessToken != NULL) {
        delete accessToken;
    }
    if (emailID != NULL) {
        delete emailID;
    }
    if (userFriends != NULL) {
        delete userFriends;
    }
}

UserInfo* UserInfo::create()
{
    UserInfo* fbUser = new UserInfo();
    //    if (fbUser)
    //    {
    //        fbUser->autorelease();
    //    }
    //    else
    //    {
    //        CC_SAFE_DELETE(fbUser);
    //        return NULL;
    //    }
    
    return fbUser;
}

void UserInfo::saveFBData(const char* key, const char * dataValue)
{
    CCLOG("dataValue = %s - key = %s", dataValue, key);

    if (strcmp(key, KEY_FB_USER_NAME) == 0)
    {
        this->username = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_ACCESS_TOKEN) == 0)
    {
        this->accessToken = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_EMAIL) == 0)
    {
        this->emailID = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_FIRST_NAME) == 0)
    {
        this->firstName = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_GENDER) == 0)
    {
        if (strcmp(dataValue, "male") == 0) {
            this->gender = 0;
        }
        else {
            this->gender = 1;
        }
    }
    else if (strcmp(key, KEY_FB_USER_HOMETOWN) == 0)
    {
        CCLOG("hometown = %s", dataValue);
        this->hometown = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_LAST_NAME) == 0)
    {
        this->lastName = new std::string(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_PROFILE_ID) == 0)
    {
        this->setProfileID(dataValue);
    }
    else if (strcmp(key, KEY_FB_USER_PRESENT_LOCATION) == 0)
    {
        CCLOG("presentLocation = %s", dataValue);
        this->presentLocation = new std::string(dataValue);
    }
    else
    {
        CCLOG("Unrecognized Key while saving the user data.");
    }
}

const char* UserInfo::getUserName()
{
    return username->c_str();
}

const char* UserInfo::getAccessToken()
{
    return accessToken->c_str();
}

const char* UserInfo::getEmailID()
{
    return emailID->c_str();
}

const char* UserInfo::getUserFriends()
{
    if (userFriends == NULL) {
        // Friends are not available
        return NULL;
    }
    else {
        return userFriends->c_str();
    }
}

void UserInfo::saveUserFriends(const char *friends)
{
    userFriends = new std::string(friends);
}

void UserInfo::importFBUser(EziFacebookUser *fbUser)
{
    this->saveFBData(KEY_FB_USER_NAME, fbUser->getUserName());
    this->saveFBData(KEY_FB_USER_FIRST_NAME, fbUser->getFirstName());
    this->saveFBData(KEY_FB_USER_LAST_NAME, fbUser->getLastName());
    this->saveFBData(KEY_FB_USER_PROFILE_ID, fbUser->getProfileID());
    this->saveFBData(KEY_FB_USER_HOMETOWN, fbUser->getHomeTown());
    this->saveFBData(KEY_FB_USER_PRESENT_LOCATION, fbUser->getPresentLocation());
    this->saveFBData(KEY_FB_USER_ACCESS_TOKEN, fbUser->getAccessToken());
    this->saveFBData(KEY_FB_USER_EMAIL, fbUser->getEmailID());
    this->saveFBData(KEY_FB_USER_GENDER, fbUser->getGender());
    if (fbUser->getPhotoPath() != NULL) {
        this->setUserPhotoPath(fbUser->getPhotoPath());
    }
}

void UserInfo::setTotalChips(long long var) {
    totalChips = var;
    mUserInfoTotalChips->updateValue(var);
}

void UserInfo::setTotalBetChips(long long var) {
    totalBetChips = var;
    mUserInfoBetChips->updateValue(var);
}

void UserInfo::setTotalWonChips(long long var) {
    totalWonChips = var;
    mUserInfoTotalWonChips->updateValue(var);
}

