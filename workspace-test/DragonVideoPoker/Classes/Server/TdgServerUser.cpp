//
//  TdgServerUser.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#include "TdgServerUser.h"
#include "TdgServer.h"
#include "UserInfo.h"
#include "HourlyBonusInfo.h"
#include "UserStatistics.h"

#include <algorithm>
#include <boost/tokenizer.hpp>

#include "Leaderboard.h"


TdgServerUser::TdgServerUser()
{
    
}

void TdgServerUser::addUserEventListeners()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();
    
    // handle room messages
	smartFox->AddEventListener(SFSEvent::USER_VARIABLES_UPDATE,
                               PTR_ELD (new ELD(TdgServerUser::OnUserVariablesUpdate,
                                                (unsigned long long)this)));
	smartFox->AddEventListener(SFSEvent::USER_EXIT_ROOM,
                               PTR_ELD (new ELD(TdgServerUser::OnUserExitRoom,
                                                (unsigned long long)this)));
}

void TdgServerUser::addUserVariablesUpdateListeners()
{
    addUserVariablesUpdateListener(EX_REQUEST_PARAM_USER_CHIPS,
                                   extension_selector(TdgServerUser::userVariableUpdateChips));
    addUserVariablesUpdateListener(EX_REQUEST_PARAM_USER_LEVEL,
                                   extension_selector(TdgServerUser::userVariableUpdateLevel));
    addUserVariablesUpdateListener(EX_REQUEST_PARAM_USER_EXPERIENCE,
                                   extension_selector(TdgServerUser::userVariableUpdateExperience));
}

void TdgServerUser::addUserVariablesUpdateListener(string extensionName,
                                                   ExtensionCallback selector)
{
    TdgServerExtensionRequest *extensionRequest = new TdgServerExtensionRequest(extensionName,
                                                                                this,
                                                                                selector);
    mUserVariableUpdateListeners.push_back(extensionRequest);
}


#pragma mark - smartfox callbacks

void TdgServerUser::OnUserVariablesUpdate(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    
    // get user
	boost::shared_ptr<void> ptrEventParamUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> user = ((boost::static_pointer_cast<User>)(ptrEventParamUser));
    
    if (!user->IsItMe()) {
        return;
    }
    
    // get variables updated
    boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
    boost::shared_ptr<vector<string> > changedVars =
    ((boost::static_pointer_cast<vector<string> >)(ptrEventParamValueVars));

    TdgServerExtensionRequest *extensionRequest;
    bool isEventHandled = false;
    
    vector<TdgServerExtensionRequest *>::iterator iterator;
    
    CCLOG("User: %s changes variable 0: %s", user->Name()->c_str(), changedVars->at(0).c_str());
    
    for (iterator = SERVER_USER().mUserVariableUpdateListeners.begin();
         iterator != SERVER_USER().mUserVariableUpdateListeners.end();
         ++iterator) {
        extensionRequest = (*iterator);
        
        bool isValueChanged = std::find(changedVars->begin(),
                                        changedVars->end(),
                                        *extensionRequest->getExtensionName()) != changedVars->end();

        if (isValueChanged) {
            extensionRequest->invoke(&user);
            isEventHandled = true;
        }
    }
    
    if (!isEventHandled) {
        CCLog("Got an user variable update but have no handler!!!");
    }
}

void TdgServerUser::OnUserExitRoom(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    
}

void TdgServerUser::fetchingSpecialUserVariables()
{
    User* me = SERVER().getSmartFox()->MySelf().get();
    
    // get chips and gold
    double* totalChips = me->GetVariable(EX_REQUEST_PARAM_USER_CHIPS)->GetDoubleValue().get();
    // get level
    long* level = me->GetVariable(EX_REQUEST_PARAM_USER_LEVEL)->GetIntValue().get();
    double* levelExperience = me->GetVariable(EX_REQUEST_PARAM_USER_EXPERIENCE)->GetDoubleValue().get();
    // get avatar
    long *avatar = me->GetVariable(EX_REQUEST_PARAM_USER_AVATAR)->GetIntValue().get();
    // get VIP
    long *vipType = me->GetVariable(EX_REQUEST_PARAM_VIP_CARD_TYPE)->GetIntValue().get();
    long *vipCardPoint = me->GetVariable(EX_REQUEST_PARAM_USER_VIP_POINT)->GetIntValue().get();
    
    // update to user
    USERINFO()->setTotalChips((long long)*totalChips);
    USERINFO()->setLevel(*level);
    USERINFO()->setExperience((long long)*levelExperience);
    USERINFO()->setUserAvatarType(*avatar);
    USERINFO()->setVipType(*vipType);
    USERINFO()->setVipPoint(*vipCardPoint);
//    
//    // test
//    USERINFO()->setVipType(3);
//    USERINFO()->setVipPoint(500);
}

void TdgServerUser::fetchingBaseUserInfo(boost::shared_ptr<ISFSObject> userInfoData)
{
    // get user system ID
    long long *userID = userInfoData->GetLong(EX_REQUEST_PARAM_USER_USERID).get();
    USERINFO()->setUserID(*userID);

    // get gender
    long *gender = userInfoData->GetInt(EX_REQUEST_PARAM_USER_SEX).get();
    if (gender == NULL) {
        USERINFO()->setGender(2);
    }
    else {
        USERINFO()->setGender(*gender);
    }

    // get location displayed
    string *location = userInfoData->GetUtfString(EX_REQUEST_PARAM_USER_LOCATION_DISPLAY).get();
    if (location != NULL) {
        USERINFO()->setLocation(location->c_str());
    }
    else {
        USERINFO()->setLocation("UNKNOWN");
    }
    
    // get first name & profile ID if is Guest Login
    if (SERVER().getLoginType() == kGuestLogin) {
        string *firstname = userInfoData->GetUtfString(EX_REQUEST_PARAM_USER_FIRST_NAME).get();
        USERINFO()->setFirstName(firstname->c_str());
        USERINFO()->setLastName("");
        string *profileID = SERVER().getSmartFox()->MySelf()->Name().get();
        USERINFO()->setProfileID(profileID->c_str());
    }
    
    // get current hourly bonus
    long *lastHourlyBonus = userInfoData->GetInt(EX_REQUEST_PARAM_HOURLY_BONUS_CURRENT).get();
    if (lastHourlyBonus) {
        HOURLYBONUS()->setLastBonus(*lastHourlyBonus);
    }
    HOURLYBONUS()->updateLastBonusTime();

}

void TdgServerUser::fetchingUserStatistics()
{
    User* me = SERVER().getSmartFox()->MySelf().get();

    // get values from user variable
    long* handsPlayed = me->GetVariable(EX_REQUEST_PARAM_USER_HANDS_PLAYED)->GetIntValue().get();
    long* handsWon = me->GetVariable(EX_REQUEST_PARAM_USER_HANDS_WON)->GetIntValue().get();
    double* biggestWin = me->GetVariable(EX_REQUEST_PARAM_USER_BIGGEST_WIN)->GetDoubleValue().get();
    string* bestHandString = me->GetVariable(EX_REQUEST_PARAM_USER_BEST_HAND)->GetStringValue().get();
    
    // update to local
    if (handsPlayed) {
        USERSTATS()->setHandsPlayed(*handsPlayed);
    }
    if (handsWon) {
        USERSTATS()->setHandsWon(*handsWon);
    }
    if (biggestWin) {
        USERSTATS()->setBiggestWin((long long)*biggestWin);
    }
    if (bestHandString) {
        boost::char_separator<char> sep("_");
        boost::tokenizer<boost::char_separator<char> > toker(*bestHandString, sep);
        vector<string> words(toker.begin(), toker.end());
        if (words.size() < 5) {
            return;
        }
        for (int i = 0; i < 5; i++) {
            int hand = atoi(words[i].c_str());
            USERSTATS()->getBestHand()->at(i) = hand;
        }
    }
}

#pragma mark - user variable update listeners

void TdgServerUser::userVariableUpdateChips(boost::shared_ptr<User> user)
{
    
}

void TdgServerUser::userVariableUpdateLevel(boost::shared_ptr<User> user)
{
    long* level = user->GetVariable(EX_REQUEST_PARAM_USER_LEVEL)->GetIntValue().get();

    USERINFO()->setLevel(*level);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_LEVEL_UPDATE,
                                                                       NULL);
}

void TdgServerUser::userVariableUpdateExperience(boost::shared_ptr<User> user)
{
    double* levelExperience = user->GetVariable(EX_REQUEST_PARAM_USER_EXPERIENCE)->GetDoubleValue().get();

    USERINFO()->setExperience((long long)*levelExperience);
    CCLOG("Level Ex = %lld", USERINFO()->getExperience());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_GOT_LEVEL_EX_UPDATE,
                                                                       NULL);
}

