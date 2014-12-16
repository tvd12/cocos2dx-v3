//
//  TdgServerExtensionListener.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#ifndef __DragonVideoPoker__TdgServerExtensionListener__
#define __DragonVideoPoker__TdgServerExtensionListener__

#include "cocos2d.h"

#include "SingLeton.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerExtensionListener : public SingLeton<TdgServerExtensionListener>, public CCObject
{
public:
    TdgServerExtensionListener();
    
	static void OnExtensionResponse(unsigned long long context, BASE_EVENT event);

    // add extension listener
    void addExtensionListeners();
    
private:
    void processUserInfoData(boost::shared_ptr<ISFSObject> userInfoData);
    
    void addExtensionListener(string extensionName,
                              CCObject* target,
                              ExtensionCallback selector);

    // process game play extension
    void processDealCardsData(boost::shared_ptr<ISFSObject> data);
    void processDrawCardsData(boost::shared_ptr<ISFSObject> data);
    void processDonDealerCardData(boost::shared_ptr<ISFSObject> data);
    void processDonCardsData(boost::shared_ptr<ISFSObject> data);

    // extension request
    vector<TdgServerExtensionRequest *> mExtensionListeners;
};

#define SERVER_LISTENER() TdgServerExtensionListener::getSingleton()
#define SERVER_LISTENERptr() TdgServerExtensionListener::getSingletonPtr()

#endif /* defined(__DragonVideoPoker__TdgServerExtensionListener__) */
