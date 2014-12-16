//
//  TdgServerBaseEvent.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#include "TdgServerBaseEvent.h"
#include "TdgServer.h"
#include "TdgServerDefine.h"
#include "TdgServerExtensionListener.h"

#include "NotificationObject.h"
#include "UserInfo.h"


TdgServerBaseEvent::TdgServerBaseEvent()
{
}

#pragma mark - extension listener

void TdgServerBaseEvent::addBaseEventListeners()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();

	smartFox->AddEventListener(SFSEvent::CONNECTION,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxConnection,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::CONNECTION_LOST,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxConnectionLost,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(BitSwarmEvent::DISCONNECT,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxDisconnection,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(BitSwarmEvent::IO_ERROR,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxIOError,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(BitSwarmEvent::SECURITY_ERROR,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxSecurityError,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(BitSwarmEvent::DATA_ERROR,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxDataError,
                                                (unsigned long long)this)));
    
	smartFox->AddEventListener(SFSEvent::LOGIN,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxLogin,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::LOGIN_ERROR,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxLoginError,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::LOGOUT,
                               PTR_ELD (new ELD(TdgServerBaseEvent::OnSmartFoxLogout,
                                                (unsigned long long)this)));
    
	smartFox->AddEventListener(SFSEvent::EXTENSION_RESPONSE,
                               PTR_ELD (new ELD(TdgServerExtensionListener::OnExtensionResponse,
                                                (unsigned long long)SERVER_LISTENERptr())));

//    // handle messages
//	smartFox->AddEventListener(SFSEvent::PUBLIC_MESSAGE,
//                                PTR_ELD (new ELD(PokerServerMessage::OnSmartFoxPublicMessage,
//                                                                                                    (unsigned long long)DPMESSAGEptr())));
//	smartFox->AddEventListener(SFSEvent::PRIVATE_MESSAGE,
//                                PTR_ELD (new ELD(PokerServerMessage::OnSmartFoxPivateMessage,
//                                                                                                    (unsigned long long)DPMESSAGEptr())));
//    
//    // handle buddy messages
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_VARIABLES_UPDATE,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyVariablesUpdate,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_ADD,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyAdded,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_REMOVE,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyRemoved,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_ERROR,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyError,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_LIST_INIT,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyListInited,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
//    smartFox->AddEventListener(SFSBuddyEvent::BUDDY_ONLINE_STATE_UPDATE,
//                                PTR_ELD (new ELD(PokerServerBuddy::OnBuddyOnlineStateUpdate,
//                                                                                                    (unsigned long long)DPBUDDYptr())));
}

#pragma mark - smartfox callback

void TdgServerBaseEvent::OnSmartFoxConnection(unsigned long long context,
                                              BASE_EVENT event)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = event->Params();
	boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
	boost::shared_ptr<bool> ptrValue = (boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess);
    
    if ( *ptrValue == true ) {
		SERVER().login();
    }
    
	// show connect dialog to try again
	else {
        boost::shared_ptr<void> ptrEventParamError = (*ptrEventParams)["reason"];
        boost::shared_ptr<string> ptrValue = (boost::static_pointer_cast<string>)(ptrEventParamError);
        
        SERVER().setLoginStatus(kUserLoggingInIDLE);
        
        // show alert message
        const char * message = "Can not connect to game server!";
        if (ptrValue.get() != NULL && strcmp(ptrValue->c_str(), "unknown")) {
            message = ptrValue->c_str();
        }
        
        NotificationObject* object = NotificationObject::create();
        object->setTitle(new string("Connection failed"));
        object->setMessage(new string(message));
        object->setButton1Type(kButtonOk);
        object->setButton2Type(kButtonNone);
        object->setNotificationType(kNotificationConnectFailedToServer);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_CONNECT_FAILED_TO_SERVER,
                                                                           object);
    }
}

void TdgServerBaseEvent::OnSmartFoxConnectionLost(unsigned long long context,
                                                  BASE_EVENT event)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = event->Params();
	boost::shared_ptr<void> ptrEventParamError = (*ptrEventParams)["reason"];
	boost::shared_ptr<string> ptrValue = (boost::static_pointer_cast<string>)(ptrEventParamError);
    
    // show alert message
    const char * message = "Please check your Internet connection!";
    if (ptrValue.get() != NULL && strcmp(ptrValue->c_str(), "unknown")) {
        message = ptrValue->c_str();
    }
    
    NotificationObject* object = NotificationObject::create();
    object->setTitle(new string("Connection Lost"));
    object->setMessage(new string("Please check your Internet connection!"));
    object->setButton1Type(kButtonOk);
    object->setButton2Type(kButtonNone);
    object->setNotificationType(kNotificationConnectionLost);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_LOST_SERVER_CONNECTION,
                                                                       object);

    USERINFO()->setPlayerType(kPlayerTypeZombie);
}

void TdgServerBaseEvent::OnSmartFoxDisconnection(unsigned long long context,
                                                 BASE_EVENT event)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = event->Params();
	boost::shared_ptr<void> ptrEventParamError = (*ptrEventParams)["reason"];
	boost::shared_ptr<string> ptrValue = (boost::static_pointer_cast<string>)(ptrEventParamError);
    
    // show alert message
    const char * message = "Please check your Internet connection!";
    if (ptrValue.get() != NULL && strcmp(ptrValue->c_str(), "unknown")) {
        message = ptrValue->c_str();
    }
    
    NotificationObject* object = NotificationObject::create();
    object->setTitle(new string("Disconnected"));
    object->setMessage(new string("You've disconnected from server!"));
    object->setButton1Type(kButtonOk);
    object->setButton2Type(kButtonNone);
    object->setNotificationType(kNotificationDisconnected);

    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_LOST_SERVER_CONNECTION,
                                                                       object);
  
    USERINFO()->setPlayerType(kPlayerTypeZombie);
}

void TdgServerBaseEvent::OnSmartFoxIOError(unsigned long long context,
                                           BASE_EVENT event)
{
    SERVER().setLoginType(kUserLoginFail);
//    SCONTROL().showLoginScene();
}

void TdgServerBaseEvent::OnSmartFoxSecurityError(unsigned long long context,
                                                 BASE_EVENT event)
{
    SERVER().setLoginType(kUserLoginFail);
//    SCONTROL().showLoginScene();
}

void TdgServerBaseEvent::OnSmartFoxDataError(unsigned long long context,
                                             BASE_EVENT event)
{
    SERVER().setLoginType(kUserLoginFail);
//    SCONTROL().showLoginScene();
}

void TdgServerBaseEvent::OnSmartFoxLogin(unsigned long long context,
                                         BASE_EVENT event)
{
	// join the lobby room
    SERVER().setJoiningStatus(kJoiningLobbyRoom);
    SERVER().joinRoom(GAME_LOBBY_NAME);
}

void TdgServerBaseEvent::OnSmartFoxLoginError(unsigned long long context,
                                              BASE_EVENT event)
{
    SERVER().setLoginType(kUserLoginFail);
//    SCONTROL().showLoginScene();
}

void TdgServerBaseEvent::OnSmartFoxLogout(unsigned long long context,
                                          BASE_EVENT event)
{
    // update server status
    USERINFO()->setPlayerType(kPlayerTypeZombie);
    SERVER().setLoginType(kUserLogOut);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_LOGOUT,
                                                                       NULL);

    // update user status
//    USERINFO()->reset();
//    USERINFO()->setPlayerType(kDPPlayerTypeZombie);
    
    // reset play with friends list
//    DPBUDDY().resetPlayWithFriendsList();
    
    // move to login scene
//    SCONTROL().showLoginScene();
}

