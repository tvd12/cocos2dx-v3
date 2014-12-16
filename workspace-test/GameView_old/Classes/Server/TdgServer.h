//
//  TdgServer.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/19/14.
//
//

#ifndef __DragonVideoPoker__TdgServer__
#define __DragonVideoPoker__TdgServer__


#include "cocos2d.h"

#include "SingLeton.h"

#include "SmartFox.h"
#include "TdgServerDelegate.h"


using namespace Sfs2X;
USING_NS_CC;

class UserInfo;
class RoomInfo;
class PaytableCell;
class TdgDealCardData;
class TdgDrawCardData;
class TdgDonCardData;
class HourlyBonusInfo;
class DailyBonusInfo;
class VipInfo;
class IapProduct;
class UserStatistics;

class TdgServer : public SingLeton<TdgServer>, public CCObject
{
public:
    
	TdgServer();
    
    boost::shared_ptr<SmartFox> getSmartFox(){ return mSmartFox;};

    //
    //comunicate to smartfox
    //
    void initServer();
    void connectToServer();
    void login();
    void logout();
    void joinRoom(string roomName);
    void resetSmartFox();

    // send info to server
    void sendFbUserInfo();
    void sendGuestUserInfo();
    
    // send claim inform
    void sendClaimDailyBonus();
    bool sendClaimHourlyBonus(long hourlyBonus);

    // send game command
    void sendDealCardsRequest(long long betChips);
    void sendDrawCardsRequest(int drawCardsBitMask);
    
    void sendDonDealerCardRequest(bool isPlayDon = false);
    void sendDonCardsRequest(int heldPosition);

    // send get iap list
    void sendGetIapList();
    void sendVerifyIapData(std::string *data);
    void sendVerifyIapAndroidData(const char *package, const char *productId, const char *token);

    // send update avatar command
    void sendUpdateAvatarRequest(long avatarId);

    // update user statistics
    void updateNewestUserStatistics();
    
    // user info
    CC_SYNTHESIZE(UserInfo*, mUserInfo, UserInfo);

    CC_SYNTHESIZE(int, mLoginType, LoginType);
    CC_SYNTHESIZE(int, mLoginStatus, LoginStatus);
    CC_SYNTHESIZE(int, mJoiningStatus, JoiningStatus);
    
    CC_SYNTHESIZE(string *, mDeviceToken, DeviceToken);
    CC_SYNTHESIZE(string *, mGameVersion, GameVersion);
    CC_SYNTHESIZE(string *, mOsVersion, OsVersion);
    CC_SYNTHESIZE(string *, mDeviceUdid, DeviceUdid);

    // user joined game for the 1st time
    CC_SYNTHESIZE(bool, mIsJoinedGameFirstTime, IsJoinedGameFirstTime);
    
    // user got info from server -> need to update UI here!!!
    CC_SYNTHESIZE(bool, mIsGotUserInfo, IsGotUserInfo);

    // manage room info list
    CC_SYNTHESIZE(vector<RoomInfo *> *, mRoomInfos, RoomInfos);
    CC_SYNTHESIZE(RoomInfo*, mCurrentRoomInfo, CurrentRoomInfo);

    // manage current paytable of game room
    CC_SYNTHESIZE(vector<PaytableCell*>*, mPaytableCells, PaytableCells);

    // cards received from server
    CC_SYNTHESIZE(TdgDealCardData*, mDealCardData, DealCardData);
    CC_SYNTHESIZE(TdgDrawCardData*, mDrawCardData, DrawCardData);
    CC_SYNTHESIZE(TdgDonCardData*, mDonCardData, DonCardData);

    // level max array
    CC_SYNTHESIZE(vector<long long>*, mLevelMaxs, LevelMaxs);
    
    // bonus info
    CC_SYNTHESIZE(HourlyBonusInfo*, mHourlyBonusInfo, HourlyBonusInfo);
    CC_SYNTHESIZE(DailyBonusInfo*, mDailyBonusInfo, DailyBonusInfo);

    // server delegate
    CC_SYNTHESIZE(TdgServerDelegate *, mDelegate, Delegate);

    // Vip info array
    CC_SYNTHESIZE(vector<VipInfo*>*, mVipInfoList, VipInfoList);
    
    // statistics data
    CC_SYNTHESIZE(UserStatistics*, mUserStatistics, UserStatistics);

    // Iap array
    CC_SYNTHESIZE(vector<IapProduct*>*, mIapProductList, IapProductList);

private:
    
    void attachBasicUserInfo(boost::shared_ptr<ISFSObject> parameters);
    
    string getFacebookPassword();
    string getGuessPassword();
    string getPasswordTail();
    
    // smartfox client
    boost::shared_ptr<SmartFox> mSmartFox;
};

#define SERVER()        TdgServer::getSingleton()
#define USERINFO()      TdgServer::getSingleton().getUserInfo()
#define ROOMINFO()      TdgServer::getSingleton().getCurrentRoomInfo()
#define PAYTABLE()      TdgServer::getSingleton().getPaytableCells()
#define DEALCARDS()     TdgServer::getSingleton().getDealCardData()
#define DRAWCARDS()     TdgServer::getSingleton().getDrawCardData()
#define DONCARDS()      TdgServer::getSingleton().getDonCardData()
#define HOURLYBONUS()   TdgServer::getSingleton().getHourlyBonusInfo()
#define DAILYBONUS()    TdgServer::getSingleton().getDailyBonusInfo()
#define VIPINFOLIST()   TdgServer::getSingleton().getVipInfoList()
#define IAPLIST()       TdgServer::getSingleton().getIapProductList()
#define USERSTATS()     TdgServer::getSingleton().getUserStatistics()


#endif /* defined(__DragonVideoPoker__TdgServer__) */
