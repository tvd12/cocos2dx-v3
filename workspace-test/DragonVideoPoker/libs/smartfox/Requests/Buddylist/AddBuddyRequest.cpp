// ===================================================================
//
// Description		
//		Contains the implementation of AddBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "AddBuddyRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> AddBuddyRequest::KEY_BUDDY_NAME (new string("bn"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
AddBuddyRequest::AddBuddyRequest(string buddyName)
	: BaseRequest (RequestType_AddBuddy)
{
	name = boost::shared_ptr<string>(new string(buddyName));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
AddBuddyRequest::~AddBuddyRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void AddBuddyRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");

	if (name == NULL || name->size() < 1)
		errors->push_back("Invalid buddy name");

	if (sfs->BuddyManager()->MyOnlineState() == false)
		errors->push_back("Can't add buddy while off-line");

	// Duplicate buddy only allowed if the existing buddy is temp
	boost::shared_ptr<Buddy> buddy = sfs->BuddyManager()->GetBuddyByName(*name);
	if (buddy != NULL && !buddy->IsTemp())
		errors->push_back("Can't add buddy, it is already in your list: " + (*name));

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
void AddBuddyRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_BUDDY_NAME, name);
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
