// ===================================================================
//
// Description		
//		Contains the implementation of InitBuddyListRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "InitBuddyListRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> InitBuddyListRequest::KEY_BLIST (new string("bl"));
boost::shared_ptr<string> InitBuddyListRequest::KEY_BUDDY_STATES (new string("bs"));
boost::shared_ptr<string> InitBuddyListRequest::KEY_MY_VARS (new string("mv"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
InitBuddyListRequest::InitBuddyListRequest()
	: BaseRequest (RequestType_InitBuddyList)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
InitBuddyListRequest::~InitBuddyListRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void InitBuddyListRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (sfs->BuddyManager()->Inited())
		errors->push_back("Buddy List is already initialized.");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("InitBuddyRequest error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void InitBuddyListRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	// no params to add
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
