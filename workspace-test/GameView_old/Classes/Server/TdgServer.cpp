//
//  TdgServer.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "TdgServerConfig.h"
#include "TdgServerBaseEvent.h"
#include "TdgServerRoom.h"
#include "TdgServerExtensionListener.h"
#include "TdgServerUser.h"
#include "TdgServerBuddy.h"

#include "TdgDealCardData.h"
#include "TdgDrawCardData.h"
#include "TdgDonCardData.h"

#include "LoginRequest.h"
#include "LogoutRequest.h"
#include "JoinRoomRequest.h"

#include "UserInfo.h"
#include "RoomInfo.h"
#include "PaytableCell.h"
#include "HourlyBonusInfo.h"
#include "DailyBonusInfo.h"
#include "VipInfo.h"
#include "IapProduct.h"
#include "UserStatistics.h"

#include "ExtensionRequest.h"

#include <support/base64.h>

TdgServer::TdgServer()
{
    // create user info
    mUserInfo = UserInfo::create();
    
    // room info
    mCurrentRoomInfo = new RoomInfo();

    // add extension listeners
    SERVER_LISTENER().addExtensionListeners();
    
    // add user variable update listeners
    SERVER_USER().addUserVariablesUpdateListeners();
    
    // add room variable update listeners
    SERVER_ROOM().addRoomVariablesUpdateListeners();
    
    // init room info list
    mRoomInfos = new vector<RoomInfo *>();
    
    // init paytable cell list
    mPaytableCells = new vector<PaytableCell *>();
    
    // init level max array
    mLevelMaxs = new vector<long long>();
    
    // init user statistics
    mUserStatistics = UserStatistics::create();
    mUserStatistics->retain();
    
    // init iap list -> always fixed and don't reset
    mIapProductList = new vector<IapProduct *>(6);
    for (int i = 0; i < 6; i++) {
        IapProduct* iapProduct = IapProduct::create();
        iapProduct->retain();
        iapProduct->resetDefaultPriceWithType(i);
        mIapProductList->at(i) = iapProduct;
    }

    // init bonus data
    mHourlyBonusInfo = new HourlyBonusInfo();
    mDailyBonusInfo = DailyBonusInfo::create();
    mDailyBonusInfo->retain();
    
    // init vip info list
    mVipInfoList = new vector<VipInfo *>();
    
    // init cards data
    mDealCardData = TdgDealCardData::create();
    mDealCardData->retain();
    mDrawCardData = TdgDrawCardData::create();
    mDrawCardData->retain();
    mDonCardData = TdgDonCardData::create();
    mDonCardData->retain();

    // others
    mDeviceToken = NULL;
}

#pragma mark - authenticate

void TdgServer::initServer()
{
    SERVER().resetSmartFox();
    
	mSmartFox = boost::shared_ptr<SmartFox>(new SmartFox(true));
	mSmartFox->ThreadSafeMode(false);
    mSmartFox->Debug(false);
    mSmartFox->Log()->LoggingLevel(LOGLEVEL_ERROR);
    
    // add base events listener
    SERVER_BASE().addBaseEventListeners();
    
    // add room events listener
    SERVER_ROOM().addRoomEventListeners();
    
    // add user events listener
    SERVER_USER().addUserEventListeners();
    
    // add buddy events listener
    SERVER_BUDDY().addBuddyEventListeners();
}

void TdgServer::connectToServer()
{
    // init server first
    SERVER().initServer();
    
    mSmartFox->Connect(*SERVER_CONFIG().getIp(), SERVER_CONFIG().getPort());
    
    // update logging status
    SERVER().setLoginStatus(kUserConnectingServer);
}

void TdgServer::login()
{
    CCLOG("********** Server IP: %s", mSmartFox->CurrentIp()->c_str());
    
//    mIsUserInfoSent = false;
    
	// login zone when connect success
    string userName;
    string passwords;
    
    if (mLoginType == kGuestLogin) {
        userName = string("_");
        userName.append(*SERVER().getDeviceUdid());
        passwords = SERVER().getGuessPassword();
    }
    else if (mLoginType == kFacebookLogin) {
        userName = string(USERINFO()->getProfileID());
        passwords = SERVER().getFacebookPassword();
    }
    
	boost::shared_ptr<IRequest> request (new LoginRequest(userName,
                                                          passwords,
                                                          *SERVER_CONFIG().getZone()));

	mSmartFox->Send(request);
    
    // update logging status
    SERVER().setLoginStatus(kUserLoggingInServer);
}

void TdgServer::logout()
{
	boost::shared_ptr<IRequest> request (new LogoutRequest());
	mSmartFox->Send(request);
}

void TdgServer::joinRoom(string roomName)
{
    // join room as spectator
//	boost::shared_ptr<IRequest> request (new JoinRoomRequest(roomName,
//                                                             string(),
//                                                             boost::shared_ptr<long int>(),
//                                                             false));
	boost::shared_ptr<IRequest> request (new JoinRoomRequest(roomName,
                                                             string(),
                                                             boost::shared_ptr<long int>()));
	mSmartFox->Send(request);
    
    // update logging status
    SERVER().setLoginStatus(kUserJoiningLobbyRoom);
}

void TdgServer::resetSmartFox()
{
    if (mSmartFox.get() != NULL) {
        mSmartFox.get()->RemoveAllEventListeners();
        mSmartFox.reset();
    }
    
    // reset flags
    mIsJoinedGameFirstTime = false;
    mIsGotUserInfo = false;

    USERINFO()->setPlayerType(kPlayerTypeZombie);
    USERINFO()->resetFullName();
    
    // reset paytable of old game if have
    if (PAYTABLE()->size() > 0) {
        for (int i = 0; i < PAYTABLE()->size(); i++) {
            PaytableCell* paytable = PAYTABLE()->at(i);
            if (paytable != NULL) {
                paytable->release();
            }
        }
        
        PAYTABLE()->clear();
    }
    
    // reset bonus
    mHourlyBonusInfo->resetHourlyBonusInfo();
    mDailyBonusInfo->resetDailyBonusInfo();
    
    // level max array
    mLevelMaxs->clear();
    
    // vip info
    if (VIPINFOLIST()->size() > 0) {
        for (int i = 0; i < VIPINFOLIST()->size(); i++) {
            VipInfo* vipInfo = VIPINFOLIST()->at(i);
            if (vipInfo != NULL) {
                vipInfo->release();
            }
        }
        
        VIPINFOLIST()->clear();
    }

    // do not reset iap list
    
    // reset room info list
    mRoomInfos->clear();

    // simulate daily bonus
//    mDailyBonusInfo->simulateDailyBonus();
}

#pragma mark - send info to server

void TdgServer::sendFbUserInfo()
{
	//add the params
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    
    // add basic info
    SERVER().attachBasicUserInfo(parameters);
    
	parameters->PutUtfString(EX_REQUEST_PARAM_USER_FIRST_NAME,
                             string(USERINFO()->getFirstName()));
    
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_LAST_NAME,
                             string(USERINFO()->getLastName()));
    
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_EMAIL,
                             string(USERINFO()->getEmailID()));
    
    parameters->PutInt(EX_REQUEST_PARAM_USER_SEX,
                       USERINFO()->getGender());
    
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_FRIENDS,
                             string(USERINFO()->getUserFriends()));
    
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_HOMETOWN,
                             string(USERINFO()->getHomeTown()));
    
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_LOCATION,
                             string(USERINFO()->getPresentLocation()));
    
	//send request
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_SEND_USER_INFO,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendGuestUserInfo()
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    
    // add basic info
    attachBasicUserInfo(parameters);
    
	//send request
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_SEND_USER_INFO,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::attachBasicUserInfo(boost::shared_ptr<ISFSObject> parameters)
{
    CCLOG("**** start attachBasicUserInfo");
    if (SERVER().getDeviceToken() == NULL) {
        SERVER().setDeviceToken(new string("errorToken"));
    }
    parameters->PutUtfString(EX_REQUEST_PARAM_USER_DEVICE_TOKEN,
                             *SERVER().getDeviceToken());
    
    parameters->PutUtfString(EX_REQUEST_PARAM_GAME_VERSION_PARAM,
                             *SERVER().getGameVersion());
    
    parameters->PutUtfString(EX_REQUEST_PARAM_OS_VERSION_PARAM,
                             *SERVER().getOsVersion());
    
    parameters->PutInt(EX_REQUEST_PARAM_GAME_TYPE_PARAM,
                       DISTRIBUTOR_ID);
    
    parameters->PutInt(EX_REQUEST_PARAM_USER_INTERFACE_LANGUAGE,
                       GAME_LANGUAGE);
    CCLOG("**** end attachBasicUserInfo");
}

void TdgServer::sendClaimDailyBonus()
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_CLAIM_DAILY_BONUS,
                                                              parameters));
	mSmartFox->Send(request);
}

bool TdgServer::sendClaimHourlyBonus(long hourlyBonus)
{
    if (hourlyBonus < 10) {
        return false;
    }
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutInt(EX_REQUEST_PARAM_HOURLY_BONUS_CURRENT,
                       hourlyBonus);

	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_CLAIM_HOURLY_BONUS,
                                                              parameters));
	mSmartFox->Send(request);
    
    return true;
}

#pragma mark - Game Play Requests

void TdgServer::sendDealCardsRequest(long long betChips)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutLong(EX_REQUEST_PARAM_BET_CHIPS,
                       betChips);

	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_DEAL_CARDS,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendDrawCardsRequest(int drawCardsBitMask)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutInt(EX_REQUEST_PARAM_HOLD_CARD_BITS,
                       drawCardsBitMask);

	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_DRAW_CARDS,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendDonDealerCardRequest(bool isPlayDon)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutBool(EX_REQUEST_PARAM_DON_ACCEPTED,
                        isPlayDon);
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_DON_DEALER_CARD,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendDonCardsRequest(int heldPosition)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutInt(EX_REQUEST_PARAM_DON_SELECT_CARD,
                       heldPosition);
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_DON_CARDS,
                                                              parameters));
	mSmartFox->Send(request);
}

#pragma mark - In-app purchase Requests

void TdgServer::sendGetIapList()
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_IN_APP_LIST,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendVerifyIapData(std::string *data)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutUtfString(EX_REQUEST_PARAM_IAP_VERIFY_DATA,
                             *data);
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_IN_APP_VERIFY_RESULT,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::sendVerifyIapAndroidData(const char *package, const char *productId, const char *token)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutUtfString(EX_REQUEST_PARAM_IAP_ANDROID_PACKAGE_ID,
                             std::string(package));
    parameters->PutUtfString(EX_REQUEST_PARAM_IAP_ANDROID_PRODUCT_ID,
                             std::string(productId));
    parameters->PutUtfString(EX_REQUEST_PARAM_IAP_ANDROID_TOKEN,
                             std::string(token));
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_IN_APP_VERIFY_RESULT,
                                                              parameters));
	mSmartFox->Send(request);
}

#pragma mark - send update avatar command

void TdgServer::sendUpdateAvatarRequest(long avatarId)
{
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
    parameters->PutInt(EX_REQUEST_PARAM_USER_AVATAR,
                       avatarId);
    
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_UPDATE_AVATAR,
                                                              parameters));
	mSmartFox->Send(request);
}

void TdgServer::updateNewestUserStatistics()
{
    SERVER_USER().fetchingUserStatistics();
}

#pragma mark - decode password for fb & guess

string TdgServer::getFacebookPassword()
{
    unsigned int dataLen = strlen(FACEBOOK_PASSWORD);
    unsigned char *buffer = NULL;
    int decodeLen = base64Decode((unsigned char*)FACEBOOK_PASSWORD, dataLen, &buffer);
    const char* decodeStr = reinterpret_cast<const char*>(buffer);
    
    string password = string(decodeStr, decodeStr + decodeLen);
    password.append(getPasswordTail());
    
    CC_SAFE_DELETE_ARRAY(buffer);

    return password;
}

string TdgServer::getGuessPassword()
{
    unsigned int dataLen = strlen(GUESS_PASSWORD);
    unsigned char *buffer = NULL;
    int decodeLen = base64Decode((unsigned char*)GUESS_PASSWORD, dataLen, &buffer);
    const char* decodeStr = reinterpret_cast<const char*>(buffer);
    
    string password = string(decodeStr, decodeStr + decodeLen);
    password.append(getPasswordTail());
    
    CC_SAFE_DELETE_ARRAY(buffer);
    
    return password;
}

string TdgServer::getPasswordTail()
{
    unsigned int dataLen = strlen(PASSWORD_TAIL);
    unsigned char *buffer = NULL;
    unsigned char *buffer2 = NULL;
    int decodeLen = base64Decode((unsigned char*)PASSWORD_TAIL, dataLen, &buffer);
    int decodeLen2 = base64Decode(buffer, decodeLen, &buffer2);
    const char* decodeStr = reinterpret_cast<const char*>(buffer2);

    string password = string(decodeStr, decodeStr + decodeLen2);
    CC_SAFE_DELETE_ARRAY(buffer);
    CC_SAFE_DELETE_ARRAY(buffer2);
    
    return password;
}

