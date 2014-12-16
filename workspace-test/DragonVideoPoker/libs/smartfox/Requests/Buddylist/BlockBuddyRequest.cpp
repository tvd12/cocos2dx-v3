// ===================================================================
//
// Description		
//		Contains the implementation of BlockBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BlockBuddyRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> BlockBuddyRequest::KEY_BUDDY_NAME (new string("bn"));
boost::shared_ptr<string> BlockBuddyRequest::KEY_BUDDY_BLOCK_STATE (new string("bs"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BlockBuddyRequest::BlockBuddyRequest(string buddyName, bool blocked)
	: BaseRequest (RequestType_BlockBuddy)
{
	this->buddyName = boost::shared_ptr<string>(new string(buddyName));
	this->blocked = blocked;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BlockBuddyRequest::~BlockBuddyRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void BlockBuddyRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");

	if (buddyName == NULL || buddyName->size() < 1)
		errors->push_back("Invalid buddy name");

	if (sfs->BuddyManager()->MyOnlineState() == false)
		errors->push_back("Can't block buddy while off-line");

	boost::shared_ptr<Buddy> buddy = sfs->BuddyManager()->GetBuddyByName(*buddyName);

	if (buddy == NULL)
		errors->push_back("Can't block buddy, it's not in your list: " + *buddyName);

	else if (buddy->IsBlocked() == blocked)
	{
		string message;
		message = "BuddyBlock flag is already in the requested state: ";
		message += (blocked == true ? "blocked" : "unblocked");
		message += ", for buddy: ";
		message += (*buddy->Name());
		errors->push_back(message);
	}

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
void BlockBuddyRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(BlockBuddyRequest::KEY_BUDDY_NAME, buddyName);

	boost::shared_ptr<bool> valueBlockState (new bool());
	*valueBlockState = blocked;
	sfso->PutBool(BlockBuddyRequest::KEY_BUDDY_BLOCK_STATE, valueBlockState);
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
