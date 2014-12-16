//
//  TdgServerIap.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/3/14.
//
//

#ifndef __DragonVideoPoker__TdgServerIap__
#define __DragonVideoPoker__TdgServerIap__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class NotificationObject;

class TdgServerIap : public SingLeton<TdgServerIap>, public CCObject
{
public:
    TdgServerIap();
    
    void fetchingInAppPurchaseList(boost::shared_ptr<ISFSArray> iapList);
    void processVerifyIapResult(boost::shared_ptr<ISFSObject> iapResultData);

private:
    NotificationObject* getNotificationMessage(string* message);
    
};

#define SERVER_IAP() TdgServerIap::getSingleton()
#define SERVER_IAPptr() TdgServerIap::getSingletonPtr()

#endif /* defined(__DragonVideoPoker__TdgServerIap__) */
