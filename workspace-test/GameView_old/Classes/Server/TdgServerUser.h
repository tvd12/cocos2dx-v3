//
//  TdgServerUser.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#ifndef __DragonVideoPoker__TdgServerUser__
#define __DragonVideoPoker__TdgServerUser__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerUser : public SingLeton<TdgServerUser>, public CCObject
{
public:
    TdgServerUser();
    
    //smartfox callbacks
	static void OnUserVariablesUpdate(unsigned long long ptrContext, BASE_EVENT ptrEvent);
    static void OnUserExitRoom(unsigned long long ptrContext, BASE_EVENT ptrEvent);

    void addUserEventListeners();
    void addUserVariablesUpdateListeners();

    void fetchingSpecialUserVariables();
    void fetchingUserStatistics();
    void fetchingBaseUserInfo(boost::shared_ptr<ISFSObject> userInfoData);
    void fetchingHourlyBonusInfo(boost::shared_ptr<ISFSObject> userInfoData);

private:
    
    void addUserVariablesUpdateListener(string extensionName, ExtensionCallback selector);

    void userVariableUpdateChips(boost::shared_ptr<User> user);
    void userVariableUpdateLevel(boost::shared_ptr<User> user);
    void userVariableUpdateExperience(boost::shared_ptr<User> user);
    
    // extension request
    vector<TdgServerExtensionRequest *> mUserVariableUpdateListeners;

};

#define SERVER_USER() TdgServerUser::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerUser__) */
