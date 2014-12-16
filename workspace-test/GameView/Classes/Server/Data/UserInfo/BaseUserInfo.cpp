//
//  BaseUserInfo.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#include "BaseUserInfo.h"
BaseUserInfo::BaseUserInfo() :
firstName(NULL),
lastName(NULL),
fullname(NULL),
profileID(NULL),
hometown(NULL),
presentLocation(NULL),
userPhotoPath(NULL),
location(NULL)
{
    reset();
}

void BaseUserInfo::reset()
{
    // fb data
    if (fullname != NULL) {
        delete fullname;
    }
    fullname        = NULL;
    
    if (firstName != NULL) {
        delete firstName;
    }
    firstName       = NULL;
    
    if (lastName != NULL) {
        delete lastName;
    }
    lastName        = NULL;
    
    if (profileID != NULL) {
        delete profileID;
    }
    profileID       = NULL;
    
    if (hometown != NULL) {
        delete hometown;
    }
    hometown        = NULL;
    
    if (presentLocation != NULL) {
        delete presentLocation;
    }
    presentLocation = NULL;
    
    if (userPhotoPath != NULL) {
        delete userPhotoPath;
    }
    userPhotoPath   = NULL;
    
    if (location != NULL) {
        delete location;
    }
    location        = NULL;
    
    gender          = 0;
    
    // currency
    totalChips      = 0;
    
    // level up
    level           = 0;
    
    // other
    userID          = 0;
    isFBAccount     = false;
    userAvatarType  = 0;
}

BaseUserInfo:: ~BaseUserInfo()
{
    if (fullname != NULL) {
        delete fullname;
    }
    if (firstName != NULL) {
        delete firstName;
    }
    if (lastName != NULL) {
        delete lastName;
    }
    if (profileID != NULL) {
        delete profileID;
    }
    if (hometown != NULL) {
        delete hometown;
    }
    if (presentLocation != NULL) {
        delete presentLocation;
    }
    if (userPhotoPath != NULL) {
        delete userPhotoPath;
    }
    if (location != NULL) {
        delete location;
    }
}

BaseUserInfo* BaseUserInfo::create()
{
    BaseUserInfo* user = new BaseUserInfo();
    //    if (user)
    //    {
    //        user->autorelease();
    //    }
    //    else
    //    {
    //        CC_SAFE_DELETE(user);
    //        return NULL;
    //    }
    
    return user;
}

const char* BaseUserInfo::getFirstName()
{
    if (firstName == NULL) {
        return "";
    }
    return firstName->c_str();
}

const char* BaseUserInfo::getLastName()
{
    if (lastName == NULL) {
        return "";
    }
    return lastName->c_str();
}

const char* BaseUserInfo::getProfileID()
{
    if (profileID == NULL) {
        return "";
    }
    return profileID->c_str();
}

const char* BaseUserInfo::getHomeTown()
{
    if (hometown == NULL) {
        return "";
    }
    return hometown->c_str();
}

const char* BaseUserInfo::getPresentLocation()
{
    if (presentLocation == NULL) {
        return "";
    }
    return presentLocation->c_str();
}

const char* BaseUserInfo::getLocation()
{
    if (location == NULL) {
        return "";
    }
    return location->c_str();
}

const char* BaseUserInfo::getFullName()
{
    if (fullname == NULL)
    {
        // Full name is not available. So join first name and last name and return it.
        if (firstName == NULL) {
            fullname = new string("");
        }
        else {
            fullname = new string(*firstName);
            if (lastName != NULL) {
                fullname->append(" ").append(*lastName);
            }
        }
    }
    
    return fullname->c_str();
}

void BaseUserInfo::resetFullName()
{
    if (fullname != NULL) {
        delete fullname;
    }
    
    fullname = NULL;
}

void BaseUserInfo::setUserPhotoPath(const char * photoPath)
{
    string str = string(photoPath);
    this->userPhotoPath = new string(photoPath);
}

const char* BaseUserInfo::getPhotoPath()
{
    if (userPhotoPath == NULL)
    {
        // Friends are not available
        return NULL;
    }
    else {
        return userPhotoPath->c_str();
    }
}

void BaseUserInfo::setFirstName(const char* str)
{
    firstName = new string(str);
}

void BaseUserInfo::setLastName(const char* str)
{
    lastName = new string(str);
}

void BaseUserInfo::setProfileID(const char* str)
{
    profileID = new string(str);
}

void BaseUserInfo::setHomeTown(const char* str)
{
    hometown = new string(str);
}

void BaseUserInfo::setPresentLocation(const char* str)
{
    presentLocation = new string(str);
}

void BaseUserInfo::setLocation(const char *  str)
{
    location = new string(str);
}

void BaseUserInfo::detectFBAccount()
{
    if (profileID->find("_") != string::npos) {
        isFBAccount = false;
    }
    else {
        isFBAccount = true;
    }
}
