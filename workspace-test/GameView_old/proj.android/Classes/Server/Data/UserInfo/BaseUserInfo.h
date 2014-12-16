//
//  BaseUserInfo.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/21/14.
//
//

#ifndef __DragonVideoPoker__BaseUserInfo__
#define __DragonVideoPoker__BaseUserInfo__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class BaseUserInfo: public CCObject
{
public:
    
    BaseUserInfo();
    virtual ~BaseUserInfo();
    
    static BaseUserInfo* create();
    virtual void reset();
    
    const char*  getFirstName();
    const char*  getLastName();
    const char*  getProfileID();
    const char*  getHomeTown();
    const char*  getPresentLocation();
    const char*  getFullName();
    const char*  getPhotoPath();
    const char*  getLocation();
    
    void         setFirstName(const char* str);
    void         setLastName(const char* str);
    void         setProfileID(const char* str);
    void         setHomeTown(const char* str);
    void         setPresentLocation(const char* str);
    void         setUserPhotoPath(const char *  photoPath);
    void         setLocation(const char *  str);
    void         resetFullName();
    void         detectFBAccount();
    
    // currency info
    CC_SYNTHESIZE(long long, totalChips, TotalChips);
    
    // levelup system
    CC_SYNTHESIZE(long, level, Level);
    CC_SYNTHESIZE(long, gender, Gender);
    
    // system ID
    CC_SYNTHESIZE(long, userID, UserID);                   // system id from server
    
    // avatar type
    CC_SYNTHESIZE(long, userAvatarType, UserAvatarType);
    
    // It's me?
    CC_SYNTHESIZE(bool, isFBAccount, IsFBAccount);
    
protected:
    // fb info
    string *firstName;
    string *lastName;
    string *fullname;
    string *profileID;
    string *hometown;
    string *presentLocation;
    string *userPhotoPath;
    string *location;
};

#endif /* defined(__DragonVideoPoker__BaseUserInfo__) */
