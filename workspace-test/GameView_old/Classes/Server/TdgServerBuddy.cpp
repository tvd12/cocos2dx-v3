//
//  TdgServerBuddy.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/5/14.
//
//

#include "TdgServerBuddy.h"
#include "TdgServer.h"
#include "Buddy.h"

#include "InitBuddyListRequest.h"
#include "../../libs/smartfox/Core/SFSBuddyEvent.h"


TdgServerBuddy::TdgServerBuddy()
{
    
}

void TdgServerBuddy::addBuddyEventListeners()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();
    
    // handle room messages
	smartFox->AddEventListener(SFSBuddyEvent::BUDDY_LIST_INIT,
                               PTR_ELD (new ELD(TdgServerBuddy::OnBuddyListInit,
                                                (unsigned long long)this)));
}

//smartfox callbacks
void TdgServerBuddy::OnBuddyListInit(unsigned long long ptrContext, BASE_EVENT ptrEvent)
{
    if (SERVER().getLoginType() == kFacebookLogin) {
        SERVER().sendFbUserInfo();
    }
    else if (SERVER().getLoginType() == kGuestLogin) {
        SERVER().sendGuestUserInfo();
    }
}


// send init buddy list
void TdgServerBuddy::sendInitBuddyList()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();
	boost::shared_ptr<IRequest> request (new Sfs2X::Requests::Buddylist::InitBuddyListRequest());
	smartFox->Send(request);
}
