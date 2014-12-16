// ===================================================================
//
// Description		
//		Contains the implementation of BuddyMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BuddyMessageRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BuddyMessageRequest::BuddyMessageRequest(string message, boost::shared_ptr<Buddy> targetBuddy)
{
	this->type = (long int)GENERICMESSAGETYPE_BUDDY_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	boost::shared_ptr<long int> recipient (new long int());
	*recipient = targetBuddy != NULL ? targetBuddy->Id() : -1;
	this->recipientInt = recipient;
	this->parameters = boost::shared_ptr<ISFSObject>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BuddyMessageRequest::BuddyMessageRequest(string message, boost::shared_ptr<Buddy> targetBuddy, boost::shared_ptr<ISFSObject> parameters)
{
	this->type = (long int)GENERICMESSAGETYPE_BUDDY_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	boost::shared_ptr<long int> recipient (new long int());
	*recipient = targetBuddy != NULL ? targetBuddy->Id() : -1;
	this->recipientInt = recipient;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BuddyMessageRequest::~BuddyMessageRequest()
{
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
