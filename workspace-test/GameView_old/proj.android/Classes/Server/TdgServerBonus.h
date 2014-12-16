//
//  TdgServerBonus.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/16/14.
//
//

#ifndef __DragonVideoPoker__TdgServerBonus__
#define __DragonVideoPoker__TdgServerBonus__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerBonus : public SingLeton<TdgServerBonus>, public CCObject
{
public:
    TdgServerBonus();
    
    // process hourly & daily bonus
    void processHourlyBonusData(boost::shared_ptr<ISFSObject> data);
    void processDailyBonusData(boost::shared_ptr<ISFSObject> data);

    void fetchingHourlyBonusData(boost::shared_ptr<ISFSObject> data);
    void fetchingDailyBonusData(boost::shared_ptr<ISFSObject> data);
    
private:
    
};

#define SERVER_BONUS() TdgServerBonus::getSingleton()
#define SERVER_BONUSptr() TdgServerBonus::getSingletonPtr()

#endif /* defined(__DragonVideoPoker__TdgServerBonus__) */
