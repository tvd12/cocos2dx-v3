//
//  TdgServerPaytable.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/8/14.
//
//

#ifndef __DragonVideoPoker__TdgServerPaytable__
#define __DragonVideoPoker__TdgServerPaytable__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerPaytable : public SingLeton<TdgServerPaytable>, public CCObject
{
public:
    TdgServerPaytable();
    
    void sendPaytableRequest();
    void processPaytableData(boost::shared_ptr<ISFSObject> userInfoData);

private:
    void fetchingPaytableInfo(ISFSObject* paytable);
    
};

#define SERVER_PAYTABLE() TdgServerPaytable::getSingleton()
#define SERVER_PAYTABLEptr() TdgServerPaytable::getSingletonPtr()

#endif /* defined(__DragonVideoPoker__TdgServerPaytable__) */
