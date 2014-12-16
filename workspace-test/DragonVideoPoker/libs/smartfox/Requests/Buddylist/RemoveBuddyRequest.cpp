// ===================================================================
//
// Description		
//		Contains the implementation of RemoveBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RemoveBuddyRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> RemoveBuddyRequest::KEY_BUDDY_NAME (new string("bn"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RemoveBuddyRequest::RemoveBuddyRequest(string buddyName)
	: BaseRequest (RequestType_RemoveBuddy)
{
	name = boost::shared_ptr<string>(new string(buddyName));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
RemoveBuddyRequest::~RemoveBuddyRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void RemoveBuddyRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");

	if (sfs->BuddyManager()->MyOnlineState() == false)
		errors->push_back("Can't remove buddy while off-line");

	if (!sfs->BuddyManager()->ContainsBuddy(*name))
		errors->push_back("Can't remove buddy, it's not in your list: " + (*name));

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("BuddyList request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void RemoveBuddyRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_BUDDY_NAME, name);
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
