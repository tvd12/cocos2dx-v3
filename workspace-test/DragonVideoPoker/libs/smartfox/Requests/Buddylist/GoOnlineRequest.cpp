// ===================================================================
//
// Description		
//		Contains the implementation of GoOnlineRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "GoOnlineRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> GoOnlineRequest::KEY_ONLINE (new string("o"));
boost::shared_ptr<string> GoOnlineRequest::KEY_BUDDY_NAME (new string("bn"));
boost::shared_ptr<string> GoOnlineRequest::KEY_BUDDY_ID (new string("bi"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
GoOnlineRequest::GoOnlineRequest(bool online)
	: BaseRequest (RequestType_GoOnline)
{
	this->online = online;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
GoOnlineRequest::~GoOnlineRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void GoOnlineRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("GoOnline request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void GoOnlineRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	/*
	* Locally we already set the flag without the need of a server response
	* There's no need to fire an asynchronous event for this request. 
	* As soon as the command is sent the local flag is set
	*/
	sfs->BuddyManager()->MyOnlineState(online);

	boost::shared_ptr<bool> valueOnline (new bool());
	*valueOnline = online;
	sfso->PutBool(KEY_ONLINE, valueOnline);
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
