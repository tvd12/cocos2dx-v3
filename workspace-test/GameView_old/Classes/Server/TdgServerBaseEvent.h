//
//  TdgServerBaseEvent.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 3/27/14.
//
//

#ifndef __DragonVideoPoker__TdgServerBaseEvent__
#define __DragonVideoPoker__TdgServerBaseEvent__

#include "SingLeton.h"

#include "TdgServerDefine.h"

#include "SmartFox.h"
#include "BaseEvent.h"

using namespace Sfs2X;

class TdgServerBaseEvent : public SingLeton<TdgServerBaseEvent>
{
public:
    
	TdgServerBaseEvent();
    void addBaseEventListeners();
    
    //smartfox callback
	static void OnSmartFoxConnection(unsigned long long context, BASE_EVENT event);
	static void OnSmartFoxConnectionLost(unsigned long long context, BASE_EVENT event);
	static void OnSmartFoxDisconnection(unsigned long long context, BASE_EVENT event);
    
	static void OnSmartFoxIOError(unsigned long long context, BASE_EVENT event);
    static void OnSmartFoxSecurityError(unsigned long long context, BASE_EVENT event);
	static void OnSmartFoxDataError(unsigned long long context, BASE_EVENT event);
    
	static void OnSmartFoxLogin(unsigned long long context, BASE_EVENT event);
	static void OnSmartFoxLoginError(unsigned long long context, BASE_EVENT event);
	static void OnSmartFoxLogout(unsigned long long context, BASE_EVENT event);
	
private:
    
};

#define SERVER_BASE() TdgServerBaseEvent::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerBaseEvent__) */
