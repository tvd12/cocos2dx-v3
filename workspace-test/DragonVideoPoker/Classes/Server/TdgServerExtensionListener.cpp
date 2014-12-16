//
//  TdgServerExtensionListener.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#include "TdgServerExtensionListener.h"
#include "TdgServer.h"
#include "TdgServerIap.h"
#include "TdgServerRoom.h"
#include "TdgServerUser.h"
#include "TdgServerBonus.h"
#include "TdgServerVip.h"
#include "TdgServerPaytable.h"
#include "TdgServerIap.h"

#include "UserInfo.h"
#include "RoomInfo.h"

#include "TdgDealCardData.h"
#include "TdgDrawCardData.h"
#include "TdgDonCardData.h"
#include "Leaderboard.h"


TdgServerExtensionListener::TdgServerExtensionListener()
{
}

void TdgServerExtensionListener::addExtensionListeners()
{
    // process user info data
    addExtensionListener(EX_REQUEST_COMMAND_SEND_USER_INFO,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processUserInfoData));
    
    // process iap info data
    addExtensionListener(EX_REQUEST_COMMAND_IN_APP_VERIFY_RESULT,
                         SERVER_IAPptr(),
                         extension_selector(TdgServerIap::processVerifyIapResult));

    // process paytable data
    addExtensionListener(EX_REQUEST_COMMAND_PAYTABLE,
                         SERVER_PAYTABLEptr(),
                         extension_selector(TdgServerPaytable::processPaytableData));
    
    // process game play data
    addExtensionListener(EX_REQUEST_COMMAND_DEAL_CARDS,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processDealCardsData));
    addExtensionListener(EX_REQUEST_COMMAND_DRAW_CARDS,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processDrawCardsData));
    addExtensionListener(EX_REQUEST_COMMAND_DON_DEALER_CARD,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processDonDealerCardData));
    addExtensionListener(EX_REQUEST_COMMAND_DON_CARDS,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processDonCardsData));

    // daily & hourly bonus
    addExtensionListener(EX_REQUEST_COMMAND_CLAIM_HOURLY_BONUS,
                         SERVER_BONUSptr(),
                         extension_selector(TdgServerBonus::processHourlyBonusData));
    addExtensionListener(EX_REQUEST_COMMAND_CLAIM_DAILY_BONUS,
                         SERVER_BONUSptr(),
                         extension_selector(TdgServerBonus::processDailyBonusData));
    addExtensionListener(EX_REQUEST_NAME_UPDATE,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processUpdateUserFirstName));
    addExtensionListener(EX_REQUEST_GET_LEADER_BOARD,
                         SERVER_LISTENERptr(),
                         extension_selector(TdgServerExtensionListener::processUpdateLeaderboard));
    
}

// add extension listener
void TdgServerExtensionListener::addExtensionListener(string extensionName,
                                              CCObject* target,
                                              ExtensionCallback selector)
{
    TdgServerExtensionRequest *extensionRequest = new TdgServerExtensionRequest(extensionName,
                                                                                target,
                                                                                selector);
    mExtensionListeners.push_back(extensionRequest);
}

void TdgServerExtensionListener::OnExtensionResponse(unsigned long long context,
                                                     BASE_EVENT event)
{
    // get command
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = event->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEventParams)["cmd"];
	boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)
                                                (ptrEventParamValueCmd));
    
    // get params
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEventParams)["params"];
	boost::shared_ptr<ISFSObject> ptrNotifiedISFSObject = ((boost::static_pointer_cast<ISFSObject>)
                                                           (ptrEventParamValueParams));
    
    TdgServerExtensionRequest *extensionRequest;
    bool isEventHandled = false;
    
    vector<TdgServerExtensionRequest *>::iterator iterator;
    
    for (iterator = SERVER_LISTENER().mExtensionListeners.begin();
         iterator != SERVER_LISTENER().mExtensionListeners.end(); ++iterator) {
        extensionRequest = (*iterator);
        if (extensionRequest->getExtensionName()->compare(ptrNotifiedCmd->c_str()) == 0) {
            extensionRequest->invoke(&ptrNotifiedISFSObject);
            isEventHandled = true;
        }
    }
    
    if (!isEventHandled) {
        CCLog("Got an event but have no handler!!!");
    }
}

#pragma mark - process user info data

void TdgServerExtensionListener::processUserInfoData(boost::shared_ptr<ISFSObject> userInfoData)
{
	CCLOG("processUserInfoData");

    // update user info
    boost::shared_ptr<ISFSObject> userInfo = userInfoData->GetSFSObject(EX_REQUEST_PARAM_USER_INFO);
    SERVER_USER().fetchingBaseUserInfo(userInfo);
    
    // update special user info
    SERVER_USER().fetchingSpecialUserVariables();
    
    // update room static
    boost::shared_ptr<ISFSArray> roomStatics = userInfoData->GetSFSArray(EX_REQUEST_PARAM_ROOM_STATIC);
    SERVER_ROOM().fetchingGameRoomInfo(roomStatics);
    
    // update room dynamic
    Room *lobbyRoom = SERVER().getSmartFox()->LastJoinedRoom().get();
    SERVER_ROOM().fetchingLobbyRoomInfo(lobbyRoom);
    
    // read level max array on lobby
    boost::shared_ptr<ISFSArray> levelList = userInfoData->GetSFSArray(EX_REQUEST_PARAM_LEVEL_LIST);
    SERVER_ROOM().fetchingLevelInfo(levelList);
    
    // fetching hourly bonus
    boost::shared_ptr<ISFSObject> hourlyBonusInfo = userInfoData->GetSFSObject(EX_REQUEST_PARAM_HOURLY_BONUS);
    SERVER_BONUS().fetchingHourlyBonusData(hourlyBonusInfo);
    
    // fetching daily bonus
    boost::shared_ptr<ISFSObject> dailyBonusInfo = userInfoData->GetSFSObject(EX_REQUEST_PARAM_DAILY_BONUS);
    SERVER_BONUS().fetchingDailyBonusData(dailyBonusInfo);
    
    // read vip array on lobby
    boost::shared_ptr<ISFSArray> vipList = userInfoData->GetSFSArray(EX_REQUEST_PARAM_VIP_CARD_LIST);
    SERVER_VIP().fetchingVipInfo(vipList);
    
    // in-app purchase list
    boost::shared_ptr<ISFSArray> iapList = userInfoData->GetSFSArray(EX_REQUEST_PARAM_PURCHASE_LIST);
    SERVER_IAP().fetchingInAppPurchaseList(iapList);

    // is joined game for the first time
    bool *isTheFirstTime;
    isTheFirstTime = userInfo->GetBool(EX_REQUEST_PARAM_USER_FIRST_JOIN_GAME).get();
    if (isTheFirstTime != NULL) {
        SERVER().setIsJoinedGameFirstTime(*isTheFirstTime);
    }
    else {
        SERVER().setIsJoinedGameFirstTime(false);
    }
    
//    //test
//    SERVER().setIsJoinedGameFirstTime(true);

    // finish getting user info from server
    SERVER().setIsGotUserInfo(true);
    
    // finish joining to lobby room
    SERVER().setJoiningStatus(kJoinedLobbyRoom);
}

#pragma mark - process bonus

#pragma mark - process game play

void TdgServerExtensionListener::processDealCardsData(boost::shared_ptr<ISFSObject> data)
{
    ISFSArray* dealCardsServer = data->GetSFSArray(EX_REQUEST_PARAM_DEAL_CARDS).get();
    long* hintBits = data->GetInt(EX_REQUEST_PARAM_HINT_BITS).get();
    
    vector<int>* dealCards = DEALCARDS()->getDealCards();
    
    CCLOG("Got 5 deal cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%ld", dealCardsServer->GetInt(i));
        dealCards->at(i) = dealCardsServer->GetInt(i);
    }
    CCLOG("Deal card hint: %ld", *hintBits);
    
    DEALCARDS()->setHintBits(*hintBits);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DEAL_CARDS,
                                                                       DEALCARDS());

}

void TdgServerExtensionListener::processDrawCardsData(boost::shared_ptr<ISFSObject> data)
{
    ISFSArray* drawCardsServer = data->GetSFSArray(EX_REQUEST_PARAM_DRAW_CARDS).get();
    long* wonBits = data->GetInt(EX_REQUEST_PARAM_HINT_BITS).get();
    long* wonHandId = data->GetInt(EX_REQUEST_PARAM_RESULT_HAND_ID).get();
    long long* wonChips = data->GetLong(EX_REQUEST_PARAM_WON_CHIPS).get();
    long long* jackpotWon = data->GetLong(ROOM_PARAM_JACKPOT).get();

    vector<int>* drawCards = DRAWCARDS()->getDrawCards();
    
    CCLOG("Got 5 draw cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%ld", drawCardsServer->GetInt(i));
        drawCards->at(i) = drawCardsServer->GetInt(i);
    }
    
    CCLOG("won Bits: %ld", *wonBits);
    CCLOG("won id: %ld", *wonHandId);
    CCLOG("won chips: %lld", *wonChips);
    
    DRAWCARDS()->setWonBit(*wonBits);
    DRAWCARDS()->setWonHandType(*wonHandId);
    DRAWCARDS()->setWonValue(*wonChips);
    
    if (jackpotWon) {
        if (*jackpotWon > 0) {
            DRAWCARDS()->setIsGotJackpot(true);
        }
        else {
            DRAWCARDS()->setIsGotJackpot(false);
        }
    }
    else {
        DRAWCARDS()->setIsGotJackpot(false);
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DRAW_CARDS,
                                                                       DRAWCARDS());
}

void TdgServerExtensionListener::processDonDealerCardData(boost::shared_ptr<ISFSObject> data)
{
    long* donDealerCard = data->GetInt(EX_REQUEST_PARAM_DON_DEALER_CARD).get();
    vector<int>* donCards = DONCARDS()->getDonCards();
    donCards->at(0) = *donDealerCard;
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DON_DEALER_CARD,
                                                                       DONCARDS());
}

void TdgServerExtensionListener::processDonCardsData(boost::shared_ptr<ISFSObject> data)
{
    ISFSArray* donCardsServer = data->GetSFSArray(EX_REQUEST_PARAM_DON_PLAYER_CARDS).get();
    long long* wonChips = data->GetLong(EX_REQUEST_PARAM_WON_CHIPS).get();
    vector<int>* donCards = DONCARDS()->getDonCards();
    
    CCLOG("Got 5 DON cards: ");
    for (int i = 0; i < 5; i++) {
        CCLOG("%ld", donCardsServer->GetInt(i));
        donCards->at(i) = donCardsServer->GetInt(i);
    }
    DONCARDS()->setWonChips(*wonChips);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_DON_CARDS,
                                                                       DONCARDS());
}

void TdgServerExtensionListener::processUpdateUserFirstName(boost::shared_ptr<ISFSObject> data) {
    boost::shared_ptr<long> statusPtr = data->GetInt(EX_REQUEST_NAME_STATUS_KEY);
    if(statusPtr) {
        CCLOG("update user first name status = %ld", *statusPtr.get());
    } else {
        CCLOG("update user first name status error");
    }
}

void TdgServerExtensionListener::processUpdateLeaderboard(boost::shared_ptr<ISFSObject> data) {
    if(!data) {
        return;
    }
    CCLOG("processUpdateLeaderboard");
    boost::shared_ptr<string> userChipRankPtr = data->GetUtfString(EX_REQUEST_PARAM_USER_CHIP_RANK);
    string userChipRank = (userChipRankPtr) ? string(userChipRankPtr->c_str()) : "";
    LEADERBOARD()->setUserChipRank(userChipRank);
    
    CCLOG("processUpdateLeaderboard::userChipRank: %s", userChipRank.c_str());
    
    boost::shared_ptr<ISFSArray> userArray =
    data->GetSFSArray(EX_REQUEST_LEADER_BOARD_KEY);
    long arrSize = userArray->Size();
    vector<UserInfo*> userInfos = vector<UserInfo*>(arrSize);
    for(int i = 0 ; i < arrSize ; i++) {
        userInfos[i] = UserInfo::create();
//        userInfos[i]->retain();
        boost::shared_ptr<ISFSObject> obj = userArray->GetSFSObject(i);
        boost::shared_ptr<string> firstNameStr =
        obj->GetUtfString(EX_REQUEST_LEADER_BOARD_FIRSTNAME);
        string firstName = (firstNameStr) ? string(firstNameStr->c_str()) : "";
        
        boost::shared_ptr<string> lastNameStr =
        obj->GetUtfString(EX_REQUEST_LEADER_BOARD_LASTNAME);
        string lastName = (lastNameStr) ? string(lastNameStr->c_str()) : "";
        
        boost::shared_ptr<long long> chipsPtr = obj->GetLong(EX_REQUEST_LEADER_BOARD_CHIPS);
        long long chips = (chipsPtr) ? *chipsPtr.get() : 0;
        
        boost::shared_ptr<string> profileIdStr = obj->GetUtfString(EX_REQUEST_LEADER_BOARD_PROFILE_ID);
        string profileId = (profileIdStr) ? string(profileIdStr->c_str()) : "";
        
        boost::shared_ptr<long> avatarIdPtr = obj->GetInt(EX_REQUEST_LEADER_BOARD_AVATAR_ID);
        long avatarId = (avatarIdPtr) ? *avatarIdPtr.get() : 0;
        
        CCLOG("processUpdateLeaderboard::data: fname = %s, lname = %s, chips = %lld, profileId = %s, avatarId = %ld",
              firstName.c_str(), lastName.c_str(), chips, profileId.c_str(), avatarId, NULL);
        userInfos[i]->setFirstName(firstName.c_str());
        userInfos[i]->setLastName(lastName.c_str());
        userInfos[i]->setTotalChips(chips);
        userInfos[i]->setProfileID(profileId.c_str());
        userInfos[i]->setUserAvatarType(avatarId);
    
    }
    
    LEADERBOARD()->setUserInfos(userInfos);
    
    CCNotificationCenter::sharedNotificationCenter()
        ->postNotification(NOTIFICATION_GET_LEADERBOARD_FINISHED,
                       NULL);
}


