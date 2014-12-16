//
//  EziHelper.cpp
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 8/29/13.
//
//

#include "EziHelper.h"

#include "EziSocialObject.h"
#include "EziSocialDefinition.h"
#include "EziFacebookFriend.h"

#include "GameParams.h"
#include "UserInfo.h"
#include "VipInfo.h"

#include "CCLocalization.h"
#include "SceneController.h"

#include "TdgServer.h"
#include "TdgServerDefine.h"

#ifdef CC_TARGET_OS_IPHONE
#import <FacebookSDK/FacebookSDK.h>
#else

#endif

EziHelper::EziHelper()
{
    EziSocialObject::sharedObject()->setFacebookDelegate(this);

    // Init Incoming request
//    EziFBIncomingRequestManager::sharedManager();

    profileID = "";
    
    m_pListener = NULL;
    m_pfnSelector = NULL;

    mSharingStatus = kNoneSharingMessage;
    mJackpotValue = 0;
    
#ifdef CC_TARGET_OS_IPHONE
//    FBFrictionlessRecipientCache* mFriendCache = [[FBFrictionlessRecipientCache alloc] init];
//    [mFriendCache prefetchAndCacheForSession:nil
//                               completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
//                               }];
#else
    
#endif

}

#pragma mark - Facebook Actions

void EziHelper::loginViaFacebook()
{
    isAutoLoggedIn = false;
    isConnecting = true;
    
    if (EziSocialObject::sharedObject()->isFacebookSessionActive() == false)
    {
        bool needsPublishPermission = true;
        EziSocialObject::sharedObject()->performLoginUsingFacebook(needsPublishPermission);
    }
    else
    {
        // User is already logined via Facebook. Just show him the main screen.
        fetchFBUserDetails();
    }
}

void EziHelper::logoutFromFacebook()
{
    EziSocialObject::sharedObject()->perfromLogoutFromFacebook();
}

void EziHelper::getUserPhoto()
{
    if (strcmp("", profileID) == 0)
    {
        CCMessageBox("Fetch User Details first", "Profile ID Error");
    }
    else
    {
        EziSocialObject::sharedObject()->getProfilePicForID(profileID,
                                                            GPARAMS().CMM_ICON_FB_SIZE.width,
                                                            GPARAMS().CMM_ICON_FB_SIZE.height,
                                                            false);      // !forceDownload
    }
}

void EziHelper::checkIfUserLikeMyFacebookPage()
{
    EziSocialObject::sharedObject()->hasUserLikedMyFBPage(FACEBOOK_PAGE_ID);
}

void EziHelper::fetchFBUserDetails()
{
//    EziSocialObject::sharedObject()->fetchFBUserDetails(true); // get email
    EziSocialObject::sharedObject()->fetchFBUserDetails(false); // get email
}

void EziHelper::openFacebookPage()
{
    EziSocialObject::sharedObject()->openFacebookPage(FACEBOOK_PAGE_ID, true);
}

void EziHelper::getUserFriends()
{
    EziSocialObject::sharedObject()->getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::ONLY_INSTALLED);
}

void EziHelper::getAgeRange()
{
    
}

bool EziHelper::isConnectedToFbAccount()
{
    std::string storedUserID;
    storedUserID = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID,
                                                                       "");
    if (storedUserID.length() > 0) {
        return true;
    }

    return false;
}

#pragma mark - Facebook request

void EziHelper::inviteFriends()
{
#ifdef CC_TARGET_OS_IPHONE
    NSDictionary *parameters = nil;
//    FBFrictionlessRecipientCache *mFriendCache;
    FBFrictionlessRecipientCache* mFriendCache = [[FBFrictionlessRecipientCache alloc] init];
    [mFriendCache prefetchAndCacheForSession:nil
                           completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
                           }];
    [FBWebDialogs presentRequestsDialogModallyWithSession:nil
                                                  message:@"Please come play Video Poker with me!"
                                                    title:@"Invite a Friend"
                                               parameters:parameters
                                                  handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
                                                      if (result == FBWebDialogResultDialogCompleted) {
                                                          NSLog(@"Web dialog complete: %@", resultURL);
                                                      } else {
                                                          NSLog(@"Web dialog not complete, error: %@", error.description);
                                                      }
                                                  }
                                              friendCache:mFriendCache];
#else
    EziSocialObject::sharedObject()->sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE,
                                                          "Please come play Video Poker with me!",
                                                          NULL,
                                                          NULL);
#endif
}


#pragma mark - Facebook Delegates

void EziHelper::fbSessionCallback(int responseCode, const char* responseMessage)
{
    CCLOG("responseCode = %d", responseCode);

    switch (responseCode)
    {
        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_SUCCESSFUL:
        {
            // Update user details
            fetchFBUserDetails();
            
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_FAILED:
        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_PERMISSION_DENIED:
        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_APP_NOT_ALLOWERD_TO_USE_FB:
        {
            isConnecting = false;
            
            // Clear sharing session
            mSharingStatus = kNoneSharingMessage;

            // Reset user info
//            if (mCurrentFacebookUser) {
//                mCurrentFacebookUser->release();
//            }
//            mCurrentFacebookUser = NULL;
            profileID = "";
            
            CCUserDefault::sharedUserDefault()->setStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
            CCUserDefault::sharedUserDefault()->flush();
            
            // Reset a new login scene
            SCONTROL().showLoginScene();
            
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGOUT_SUCCESSFUL:
        {
            isConnecting = false;
            
            // Update UI after logged out success
//            mAvatarPixHandlerLayer->removeChildByTag(AVATAR_PICTURE_TAG, true);
            
            // Reset user info
            mCurrentFacebookUser->release();
            mCurrentFacebookUser = NULL;
            profileID = "";
            
            CCUserDefault::sharedUserDefault()->setStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
            CCUserDefault::sharedUserDefault()->flush();
            
            // Log to GA
//            GAHelper::sharedHelper()->sendFacebookEvent(kFBEventLoggedOut, 1);
            
            break;
        }
        default:
            break;
    }
}

void EziHelper::fbUserDetailCallback(int responseCode, const char* responseMessage, EziFacebookUser* fbUser)
{
    if (fbUser)
    {
        if (SERVER().getLoginType() == kFacebookLogin) {
            // Update current user and profileID
            mCurrentFacebookUser = fbUser;
            mCurrentFacebookUser->retain();

            // send to Game Param
            USERINFO()->importFBUser(fbUser);
            
            profileID = fbUser->getProfileID();
            
            // Update friends
            this->getUserFriends();
            
            // Get user photo if need
            this->getUserPhoto();
        }
    }

    // continue post on fb if need
    if (mSharingStatus == kSharingGotLevelUp) {
        postLevelUpMessageOnFacebookWall();
    }
    else if (mSharingStatus == kSharingGotVIPCardUpgrade) {
        postVipUpgradeMessageOnFacebookWall();
    }
    else if (mSharingStatus == kSharingGotJackpot) {
        postJackpotMessageOnFacebookWall(-1);
    }
}

void EziHelper::fbMessageCallback(int responseCode, const char* responseMessage)
{
    const char* title = "";
    
    switch (responseCode)
    {
        case EziSocialWrapperNS::RESPONSE_CODE::FB_NORMAL_MESSAGE_PUBLISHED:
        {
            // Report Achievement to GC
//            GameKitHelper::sharedHelper()->reportAchievement(ACHIEVEMENT_SHARE_WITH_FRIENDS, 100.0f);
            // clear share state
            mSharingStatus = kNoneSharingMessage;

            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_NORMAL_MESSAGE_CANCELLED:
        {
            // clear share state
            mSharingStatus = kNoneSharingMessage;
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_NORMAL_MESSAGE_ERROR:
        {
            title = "Post Message Fail";
            CCMessageBox("Unable to post message!", title);
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_AUTO_MESSAGE_PUBLISHED:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_AUTO_MESSAGE_ERROR:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_SCORE_POSTED:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_SCORE_POSTING_ERROR:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_SCORE_DELETED:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_SCORE_DELETE_ERROR:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::ERROR_PUBLISH_PERMISSION_ERROR:
        {
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::ERROR_INTERNET_NOT_AVAILABLE:
        {
            break;
        }
            
        default:
            break;
    }
    
}

void EziHelper::fbSendRequestCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friendsGotRequests)
{
    switch (responseCode)
    {
        case EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_SENDING_ERROR:
            CCMessageBox(responseMessage, "Gift Request Error");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_SENDING_CANCELLED:
            //            CCMessageBox(responseMessage, "Gift Request Cancelled");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_SENT:
        {
            // Calcualate bonus chips
            
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLENGE_SENDING_ERROR:
            CCMessageBox(responseMessage, "Challenge Request Error");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLEGE_CANCELLED:
            //            CCMessageBox(responseMessage, "Challenge Request Cancelled");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLEGE_SENT:
            CCMessageBox(responseMessage, "Challenge Request Success");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_SENDING_ERROR:
//            CCMessageBox(responseMessage, "Invite Request Error");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_CANCELLED:
            //            CCMessageBox(responseMessage, "Invite Request Cancelled");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_SENT:
        {
            // Calcualate bonus chips

            break;
        }
            
        default:
            break;
    }
}

void EziHelper::fbIncomingRequestCallback(int responseCode, const char* responseMessage, int totalIncomingRequests)
{
    // Just log this info
    CCLOG("Total Incoming Request: %d", totalIncomingRequests);
}

void EziHelper::fbPageLikeCallback(int responseCode, const char* responseMessage)
{
    switch (responseCode)
    {
        case EziSocialWrapperNS::RESPONSE_CODE::FB_PAGELIKE_ERROR:
        case EziSocialWrapperNS::RESPONSE_CODE::FB_PAGELIKE_NEGATIVE:
        case EziSocialWrapperNS::RESPONSE_CODE::ERROR_INTERNET_NOT_AVAILABLE:
        {
//            CCMessageBox(responseMessage, "Page Like Fail!");
            break;
        }
        case EziSocialWrapperNS::RESPONSE_CODE::FB_PAGELIKE_POSITIVE:
        {
            //            CCMessageBox(responseMessage, "PageLike Response");
            
            // Bonus coins to user
            std::string likePage = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_EZI_LIKE_PAGE_ID, "");
            
            // User don't like Facebook Page before
            if (likePage.compare("") == 0)
            {
                // Masked as liked
                CCUserDefault::sharedUserDefault()->setStringForKey(KEY_EZI_LIKE_PAGE_ID, "LIKED");
                
                // Play button sound effect
//                SoundManager::sharedManager()->playSound(SOUND_BUTTON_COLLECT_COINS);
//                
//                // Update to UI
//                int bonus = FB_LIKE_ACTION_BONUS;
//                CCString *message = CCString::createWithFormat("You've got %d chips bonus!", bonus);
//                CCMessageBox(message->getCString(), "Like Page Success");
//                
//                // Update to game params and DB
//                GPARAMS().totalChips = decodeParam(GPARAMS().totalChips);
//                GPARAMS().totalChips += bonus;
//                GPARAMS().totalChips = encodeParam(GPARAMS().totalChips);
//                
//                DBManager::sharedManager()->updateGameParamsToDB();
//                
//                // Send to GA
//                GAHelper::sharedHelper()->sendFacebookEvent(kFBEventLikePage, 1);
            }
            
            break;
        }
            
        default:
            break;
    }
}

void EziHelper::fbPostPhotoCallback(int responseCode, const char* responseMessage)
{
    CCMessageBox(responseMessage, CCString::createWithFormat("Response Code = %d", responseCode, NULL)->getCString());
}

void EziHelper::fbRecieveRequestCallback(int responseCode,
                                           const char* message,
                                           const char* senderName,
                                           cocos2d::CCDictionary* dataDictionary)
{
    //    CCString *messageTittle;
    switch (responseCode)
    {
        case EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLENGE_RECEIVE:
            //            messageTittle = CCString::createWithFormat("%s send you a request!", senderName);
            //            CCMessageBox(messageTittle->getCString(), "New Challenge Request");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_RECEIVE:
            //            messageTittle = CCString::createWithFormat("%s send you a request!", senderName);
            //            CCMessageBox(messageTittle->getCString(), "New Invite Request");
            break;
            
        case EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_RECEIVE:
        {
            // Update total pending request
            break;
        }
            
        default:
            break;
    }
}

void EziHelper::fbUserPhotoCallback(const char *userPhotoPath)
{
    if (mCurrentFacebookUser)
    {
        // Update user photo path
        mCurrentFacebookUser->setUserPhotoPath(userPhotoPath);
        USERINFO()->setUserPhotoPath(userPhotoPath);
        
        // Update to avatar if need
        if (m_pListener != NULL) {
            CCSprite* userPhoto = EziSocialObject::sharedObject()->generateCCSprite(userPhotoPath);
            (m_pListener->*m_pfnSelector)(userPhoto, NULL);
        }
        
        // Display user photo if need
//        if (mAvatarPixHandlerLayer != NULL) {
//            CCSprite* userPhoto = EziSocialObject::sharedObject()->generateCCSprite(userPhotoPath);
//            float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
//            float imageSize = GPARAMS().SELECT_THEME_FB_AVATAR_SIZE.width * scaleFactor;
//            userPhoto->setScale(imageSize / 200.0f);
//            
//            CCSprite *avatarFrame = CCSprite::createWithSpriteFrameName("avatar_mask.png");
//            
//            CCSprite *avatarPhoto = maskedSprites(userPhoto, avatarFrame);
//            avatarPhoto->setAnchorPoint(ccp(0.5f, 0.5f));
//            avatarPhoto->setScaleX(GPARAMS().circleScale);
//            avatarPhoto->setPosition(GPARAMS().SELECT_THEME_FB_AVATAR_POSITION);
//            
//            // Add to layer
//            mAvatarPixHandlerLayer->removeChildByTag(AVATAR_PICTURE_TAG, true);
//            mAvatarPixHandlerLayer->addChild(avatarPhoto, AVATAR_PICTURE_ORDER, AVATAR_PICTURE_TAG);
//        }
    }
}

void EziHelper::fbFriendsCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friends)
{
    std::string *fbFriends = new std::string;
    
    for (int i = 0; i < friends->count(); i++) {
        EziFacebookFriend *fbFriend = (EziFacebookFriend *)friends->objectAtIndex(i);
//        fbFriends->append("_");
        fbFriends->append(fbFriend->getFBID());
        fbFriends->append(";");
    }
    
    CCLOG("friends len = %ld", strlen(fbFriends->c_str()));
    CCLOG("friends = %s", fbFriends->c_str());
    
    // save friends list
    mCurrentFacebookUser->saveUserFriends(fbFriends->c_str());
    USERINFO()->saveUserFriends(fbFriends->c_str());
    delete fbFriends;
    
    // connect to server if need
    if (USERINFO()->getPlayerType() == kPlayerTypeZombie) {
        // Connect to Smartfox server
        SERVER().connectToServer();
//        SERVER().sendFbUserInfo();
    }
}

#pragma mark - C Callback

void EziHelper::setAvatarDownloadedCallback(CCObject *listener, AvatarLoadedCallback selector)
{
    m_pListener = listener;
    m_pfnSelector = selector;
    
    // update avatar if got it
    if (mCurrentFacebookUser != NULL) {
        if (mCurrentFacebookUser->getPhotoPath() != NULL) {
            CCSprite* userPhoto = EziSocialObject::sharedObject()->generateCCSprite(mCurrentFacebookUser->getPhotoPath());
            (m_pListener->*m_pfnSelector)(userPhoto, NULL);
        }
    }
}

#pragma mark - Post on FB wall

void EziHelper::postLevelUpMessageOnFacebookWall()
{
    mSharingStatus = kSharingGotLevelUp;
    
    if (!EziSocialObject::sharedObject()->isFacebookSessionActive()) {
        loginViaFacebook();
        return;
    }
    
    int level = USERINFO()->getLevel();
    
    CCString *message;
    message = CCString::createWithFormat("I reached level %d in Video Poker - Progressive Jackpot!",
                                         level);
    
    EziSocialObject::sharedObject()->postMessageOnWall(SHARE_HEADING,
                                                       SHARE_CAPTION,
                                                       "",
                                                       message->getCString(),
                                                       SHARE_LVL_ICON_LINK,
                                                       GAME_LINK);
}

void EziHelper::postVipUpgradeMessageOnFacebookWall()
{
    mSharingStatus = kSharingGotVIPCardUpgrade;
    
    if (!EziSocialObject::sharedObject()->isFacebookSessionActive()) {
        loginViaFacebook();
        return;
    }
        
    CCString *message;
    message = CCString::createWithFormat("Congrats, you become a %s level member!",
                                         VIPINFOLIST()->at(USERINFO()->getVipType())->getVipText());
    
    EziSocialObject::sharedObject()->postMessageOnWall(SHARE_HEADING,
                                                       SHARE_CAPTION,
                                                       "",
                                                       message->getCString(),
                                                       SHARE_LVL_ICON_LINK,
                                                       GAME_LINK);
}

void EziHelper::postJackpotMessageOnFacebookWall(long long jackpotValue)
{
    mSharingStatus = kSharingGotJackpot;
    if (jackpotValue > 0) {
        mJackpotValue = jackpotValue;
    }
    
    if (!EziSocialObject::sharedObject()->isFacebookSessionActive()) {
        loginViaFacebook();
        return;
    }
    
    CCString *message;
    message = CCString::createWithFormat("OMG! I got %lld chips JACKPOT",
                                         mJackpotValue);
    
    EziSocialObject::sharedObject()->postMessageOnWall(SHARE_HEADING,
                                                       SHARE_CAPTION,
                                                       "",
                                                       message->getCString(),
                                                       SHARE_LVL_ICON_LINK,
                                                       GAME_LINK);
}

