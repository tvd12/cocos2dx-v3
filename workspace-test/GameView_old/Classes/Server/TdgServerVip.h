//
//  TdgServerVip.h
//  DragonVideoPoker
//
//  Created by ThanhNguyen on 5/22/14.
//
//

#ifndef __DragonVideoPoker__TdgServerVip__
#define __DragonVideoPoker__TdgServerVip__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerVip : public SingLeton<TdgServerVip>, public CCObject
{
public:
    TdgServerVip();
    
    void fetchingVipInfo(boost::shared_ptr<ISFSArray> vipInfoList);
    
private:
};

#define SERVER_VIP() TdgServerVip::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerVip__) */
