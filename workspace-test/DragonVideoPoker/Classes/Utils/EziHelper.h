//
//  EziHelper.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 8/29/13.
//
//

#ifndef __Dragon_Poker__EziHelper__
#define __Dragon_Poker__EziHelper__

#include "SingLeton.h"
#include "cocos2d.h"
#include "EziSocialDelegate.h"
#include "EziFacebookUser.h"

#include "GameParams.h"


USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Share Level Up on Wall Post
////////////////////////////////////////////////////////////////////////////////////////////////////
#define SHARE_LVL_ICON_LINK             "http://twindragonsgames.com/inapp/dragonvideopoker-KHd889ds/Icon.png"
#define GAME_LINK                       "http://twindragonsgames.com/inapp/dragonvideopoker-KHd889ds/facebookshare.php"

#define SHARE_HEADING                   "Video Poker - Progressive Jackpot"
#define SHARE_CAPTION                   "Best Video Pokers on mobile"
#define SHARE_DESCRIPTION               "Are you good enough to catch up to me? Play Video Poker - Progressive Jackpot now and see if you have what it takes!"
#define SHARE_VIP_DESCRIPTION           "Welcome to VIP club"

typedef enum {
    kNoneSharingMessage                     = 0,
    kSharingGotLevelUp                      = 1,
    kSharingGotVIPCardUpgrade               = 2,
    kSharingGotJackpot                      = 3,
} FBSharingMessageStatus;

//class FBFrictionlessRecipientCache;

class EziHelper : public SingLeton<EziHelper>, public EziFacebookDelegate
{
public:
	EziHelper( );
	virtual ~EziHelper(){};
    
    // Facebook Delegate Methods
    virtual void fbSessionCallback(int responseCode, const char* responseMessage);
    virtual void fbUserDetailCallback(int responseCode, const char* responseMessage, EziFacebookUser *fbUser);
    virtual void fbMessageCallback(int responseCode, const char* responseMessage);
    virtual void fbPageLikeCallback(int responseCode, const char* responseMessage);
    
    virtual void fbUserPhotoCallback(const char *userPhotoPath);
    
    virtual void fbSendRequestCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friendsGotRequests);
    virtual void fbPostPhotoCallback(int responseCode, const char* responseMessage);
    
    virtual void fbIncomingRequestCallback(int responseCode, const char* responseMessage, int totalIncomingRequests);
    
    virtual void fbRecieveRequestCallback(int responseCode,
                                          const char* message,
                                          const char* senderName,
                                          CCDictionary* dataDictionary);
    
//    virtual void fbFriendsCallback(int responseCode, const char* responseMessage, const char* friends);
    virtual void fbFriendsCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friends);


    // Facebook Action Items
    void loginViaFacebook();
    void logoutFromFacebook();
    void checkIfUserLikeMyFacebookPage();
    void fetchFBUserDetails();
//    void postScore();
    void openFacebookPage();
    void getUserPhoto();
    void getUserFriends();
    void getAgeRange();
    
    void autoLoggedIn();
    
    const char *getProfileID() {return profileID;};
    EziFacebookUser *getCurrentUser() {return mCurrentFacebookUser;};
    
    // Update avatar downloaded callback
    void setAvatarDownloadedCallback(CCObject *listener, AvatarLoadedCallback selector);
    
    bool isConnecting;
    bool isConnectedToFbAccount();
    
    // post on fb wall
    void postLevelUpMessageOnFacebookWall();
    void postVipUpgradeMessageOnFacebookWall();
    void postJackpotMessageOnFacebookWall(long long jackpotValue);

    // Facebook request
    void inviteFriends();

private:
    
    const char* profileID;
    EziFacebookUser* mCurrentFacebookUser;
    bool isAutoLoggedIn;
    
    // Network Status
    bool checkNetworkStatus();
    
    CCObject* m_pListener;
    AvatarLoadedCallback    m_pfnSelector;

    // Sharing status
    int mSharingStatus;
    long long mJackpotValue;
    
#ifdef CC_TARGET_OS_IPHONE
//    FBFrictionlessRecipientCache* mFriendCache;
#else
    
#endif

};

#define EZI() EziHelper::getSingleton()

#endif /* defined(__Dragon_Poker__EziHelper__) */
