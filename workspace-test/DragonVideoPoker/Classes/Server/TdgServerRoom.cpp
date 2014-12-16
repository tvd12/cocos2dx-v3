//
//  TdgServerRoom.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#include "TdgServerRoom.h"
#include "TdgServer.h"
#include "TdgServerConfig.h"
#include "TdgServerBuddy.h"
#include "TdgServerUser.h"
#include "TdgServerPaytable.h"

#include "UserInfo.h"
#include "RoomInfo.h"
#include "Leaderboard.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>


TdgServerRoom::TdgServerRoom()
{
}

void TdgServerRoom::addRoomVariablesUpdateListeners()
{
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_1_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_2_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_3_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_4_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_5_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_6_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_7_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    addRoomVariablesUpdateListener(ROOM_PARAM_GAME_8_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateGameInfoDynamic));
    
    addRoomVariablesUpdateListener(ROOM_PARAM_CURRENT_GAME_DYNAMIC,
                                   extension_selector_D(TdgServerRoom::roomVariableUpdateCurrentGameDynamic));
}

void TdgServerRoom::addRoomVariablesUpdateListener(string extensionName,
                                                   ExtensionDataCallback selector)
{
    TdgServerExtensionRequest *extensionDataRequest = new TdgServerExtensionRequest(extensionName,
                                                                                    this,
                                                                                    selector);
    mRoomVariableUpdateListeners.push_back(extensionDataRequest);
}

#pragma mark - smartfox callbacks

void TdgServerRoom::OnSmartFoxRoomJoin(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
    boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
    Room* room = ptrNotifiedRoom.get();

    CCLOG("**** Joined room: %s", room->Name()->c_str());

    // joined to lobby room
    if (strcmp(GAME_LOBBY_NAME, room->Name()->c_str()) == 0) {
        // just login successed
        if (USERINFO()->getPlayerType() == kPlayerTypeZombie) {
            // send user info from client to sever to update
            if (SERVER().getLoginType() == kFacebookLogin) {
//                SERVER_CONFIG().updateAutoLoginStatus(kAutoLoginFacebook);
            }
            else if (SERVER().getLoginType() == kGuestLogin) {
//                SERVER_CONFIG().updateAutoLoginStatus(kAutoLoginGuest);
            }
            
            // init buddy list
            SERVER_BUDDY().sendInitBuddyList();
        }
        else {
            // finish joining to lobby room
            SERVER().setJoiningStatus(kJoinedLobbyRoom);
            
            // update chips
            SERVER_USER().fetchingSpecialUserVariables();
        }
        
        // clear current paytable
        PAYTABLE()->clear();

        // just a user
        USERINFO()->setPlayerType(kPlayerTypeUser);
    }
    
    // joined to game room
    else {
        // send paytable extension request
        USERINFO()->setPlayerType(kPlayerTypePlayer);
        
        // get room static data from extension
        SERVER_PAYTABLE().sendPaytableRequest();
    }

    CCLOG("**** End Joined room");
}

void TdgServerRoom::OnSmartFoxRoomJoinError(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    if (SERVER().getJoiningStatus() == kJoiningLobbyRoom) {
        SERVER().setJoiningStatus(kJoinLobbyRoomFailed);
    }
    else if (SERVER().getJoiningStatus() == kJoiningGameRoom) {
        SERVER().setJoiningStatus(kJoinGameRoomFailed);
    }
}

void TdgServerRoom::OnRoomVariablesUpdate(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    
    // get room info
    boost::shared_ptr<void> ptrEventParamRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> room = ((boost::static_pointer_cast<Room>)(ptrEventParamRoom));
    
    // get variables updated
    boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
    boost::shared_ptr<vector<string> > changedVars =
    ((boost::static_pointer_cast<vector<string> >)(ptrEventParamValueVars));
    
    TdgServerExtensionRequest *extensionRequest;
    bool isEventHandled = false;
    
    vector<TdgServerExtensionRequest *>::iterator iterator;
    
    for (iterator = SERVER_ROOM().mRoomVariableUpdateListeners.begin();
         iterator != SERVER_ROOM().mRoomVariableUpdateListeners.end();
         ++iterator) {
        extensionRequest = (*iterator);
        
        bool isValueChanged = std::find(changedVars->begin(),
                                        changedVars->end(),
                                        *(extensionRequest->getExtensionName())) != changedVars->end();
        
        if (isValueChanged) {
            extensionRequest->invokeWithData(&room, extensionRequest->getExtensionName());
            isEventHandled = true;
        }
    }
    
    if (!isEventHandled) {
        CCLog("Got a room variable update but have no handler!!!");
    }
}

void TdgServerRoom::addRoomEventListeners()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();

    // handle room messages
	smartFox->AddEventListener(SFSEvent::ROOM_JOIN,
                               PTR_ELD (new ELD(TdgServerRoom::OnSmartFoxRoomJoin,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::ROOM_JOIN_ERROR,
                               PTR_ELD (new ELD(TdgServerRoom::OnSmartFoxRoomJoinError,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::ROOM_VARIABLES_UPDATE,
                               PTR_ELD (new ELD(TdgServerRoom::OnRoomVariablesUpdate,
                                                (unsigned long long)this)));
}

#pragma mark - room variable updates

void TdgServerRoom::roomVariableUpdateGameInfoDynamic(boost::shared_ptr<Room> room,
                                                      string *roomName)
{
    vector<RoomInfo *>* rooms = SERVER().getRoomInfos();
    if (rooms->size() < 1) {
        return;
    }
    // get game list
    ISFSObject *roomDynamic = room->GetVariable(*roomName)->GetSFSObjectValue().get();
    
    // update if need
    for (vector<RoomInfo *>::iterator it = rooms->begin(); it != rooms->end(); ++it) {
        RoomInfo* roomInfo = *it;
        
        if (roomInfo != NULL) {
            string param = string(ROOM_PARAM_CURRENT_GAME_DYNAMIC);
            stringstream ss;
            ss << roomInfo->getIndex();
            string str = ss.str();
            param.append(str);
            
            if (roomName->compare(param.c_str()) == 0) {
                // update dynamic values
                long long *jackpot = roomDynamic->GetLong(ROOM_PARAM_JACKPOT).get();
                if (jackpot) {
                    roomInfo->setJackpot(*jackpot);
                }
                long *numberOnlinePlayers = roomDynamic->GetInt(ROOM_PARAM_NUMBER_PLAYERS_ONLINE).get();
                if (numberOnlinePlayers) {
                    roomInfo->setNumberOnlinePlayers(*numberOnlinePlayers);
                }
                
                break;
            }
        }
    }
}

void TdgServerRoom::roomVariableUpdateCurrentGameDynamic(boost::shared_ptr<Room> room,
                                                         string *roomName)
{
    ISFSObject *roomDynamic = room->GetVariable(*roomName)->GetSFSObjectValue().get();

    long long *jackpot = roomDynamic->GetLong(ROOM_PARAM_JACKPOT).get();
    if (jackpot) {
        ROOMINFO()->setJackpot(*jackpot);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_JACKPOT_UPDATE,
                                                                           NULL);
    }
    long *numberOnlinePlayers = roomDynamic->GetInt(ROOM_PARAM_NUMBER_PLAYERS_ONLINE).get();
    if (numberOnlinePlayers) {
        ROOMINFO()->setNumberOnlinePlayers(*numberOnlinePlayers);
    }
}

#pragma mark - fetching room info

void TdgServerRoom::fetchingGameRoomInfo(boost::shared_ptr<ISFSArray> roomStatics)
{
    vector<RoomInfo*>* rooms = SERVER().getRoomInfos();
    for (int i = 0; i < NUMBER_OF_GAMES; i++) {
        CCLOG("Start static room: %d", i);
        RoomInfo* roomInfo = new RoomInfo();
        roomInfo->setIndex(i+1);
        
        // update static info
        ISFSObject* roomStatic = roomStatics->GetSFSObject(i).get();
        long *jackpotHand = roomStatic->GetInt(ROOM_PARAM_JACKPOT_HAND).get();
        if (jackpotHand) {
            roomInfo->setJackpotHand(*jackpotHand);
        }
        long *jackpotReset = roomStatic->GetInt(ROOM_PARAM_JACKPOT_RESET).get();
        if (jackpotReset) {
            roomInfo->setJackpotReset(*jackpotReset);
        }
        long *jackpotPercent = roomStatic->GetInt(ROOM_PARAM_JACKPOT_PERCENT).get();
        if (jackpotPercent) {
            roomInfo->setJackpotPercent(*jackpotPercent);
        }
        long *minStake = roomStatic->GetInt(ROOM_PARAM_MIN_STAKES).get();
        if (minStake) {
            roomInfo->setMinStakes(*minStake);
        }
        long *maxStake = roomStatic->GetInt(ROOM_PARAM_MAX_STAKES).get();
        if (maxStake) {
            roomInfo->setMaxStakes(*maxStake);
        }
        long *levelRequire = roomStatic->GetInt(ROOM_PARAM_LEVEL_REQUIRED).get();
        if (levelRequire) {
            roomInfo->setLevelRequired(*levelRequire);
        }
        string *chipType = roomStatic->GetUtfString(ROOM_PARAM_BET_CHIP_TYPE).get();
        if (chipType) {
            roomInfo->updateChipTypeValueFromString(chipType);
        }
        string* roomName = roomStatic->GetUtfString(ROOM_PARAM_ROOM_NAME).get();
        if (roomName) {
            roomInfo->setRoomName(new string(*roomName));
        }
        
        // add to room infos
        rooms->push_back(roomInfo);
        CCLOG("End static room: %d", i);
    }
}

void TdgServerRoom::fetchingLobbyRoomInfo(Room* room)
{
    vector<RoomInfo *>* rooms = SERVER().getRoomInfos();
    for (int i = 0; i < rooms->size(); i++) {
        CCLOG("Start dynamic room: %d", i);
        RoomInfo* roomInfo = rooms->at(i);
        
        // update dynamic info
        CCString* roomNameDynamic = CCString::createWithFormat("vd%d", i + 1);
        ISFSObject* roomDynamic = room->GetVariable(string(roomNameDynamic->getCString()))->GetSFSObjectValue().get();
        if (roomDynamic != NULL) {
            long long* jackpot = roomDynamic->GetLong(ROOM_PARAM_JACKPOT).get();
            if (jackpot) {
                roomInfo->setJackpot(*jackpot);
            }
            long *numberOnlinePlayers = roomDynamic->GetInt(ROOM_PARAM_NUMBER_PLAYERS_ONLINE).get();
            if (numberOnlinePlayers) {
                roomInfo->setNumberOnlinePlayers(*numberOnlinePlayers);
            }
        }
        CCLOG("End dynamic room: %d", i);
    }
    
    
}

#pragma mark - fetching level info

void TdgServerRoom::fetchingLevelInfo(boost::shared_ptr<ISFSArray> levelList)
{
    vector<long long>* levelMaxs = SERVER().getLevelMaxs();

    for (int i = 0; i < levelList->Size(); i++) {
        ISFSObject* levelInfo = levelList->GetSFSObject(i).get();
        long long* maxExperience = levelInfo->GetLong(ROOM_PARAM_LEVEL_MAX_EXPERIENCE).get();
        if (maxExperience != NULL) {
            levelMaxs->push_back(*maxExperience);
            // update level max to user
            if (i + 1 == USERINFO()->getLevel()) {
                USERINFO()->setExperienceMax(*maxExperience);
            }
        }
    }
}
