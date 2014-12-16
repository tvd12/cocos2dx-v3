//
//  TdgServerBuddy.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/5/14.
//
//

#ifndef __DragonVideoPoker__TdgServerBuddy__
#define __DragonVideoPoker__TdgServerBuddy__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerBuddy : public SingLeton<TdgServerBuddy>, public CCObject
{
public:
    TdgServerBuddy();
    
    //smartfox callbacks
	static void OnBuddyListInit(unsigned long long ptrContext, BASE_EVENT ptrEvent);
    
    void addBuddyEventListeners();
    
    // send init buddy list
    void sendInitBuddyList();

private:
    
    // extension request
    vector<TdgServerExtensionRequest *> mUserVariableUpdateListeners;
    
};

#define SERVER_BUDDY() TdgServerBuddy::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerBuddy__) */
