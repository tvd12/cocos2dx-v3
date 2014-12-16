// ===================================================================
//
// Description		
//		Contains the implementation of SetBuddyVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SetBuddyVariablesRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

boost::shared_ptr<string> SetBuddyVariablesRequest::KEY_BUDDY_NAME (new string("bn"));
boost::shared_ptr<string> SetBuddyVariablesRequest::KEY_BUDDY_VARS (new string("bv"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetBuddyVariablesRequest::SetBuddyVariablesRequest(boost::shared_ptr<list<boost::shared_ptr<BuddyVariable> > > buddyVariables)
	: BaseRequest (RequestType_SetBuddyVariables)
{
	this->buddyVariables = buddyVariables;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetBuddyVariablesRequest::~SetBuddyVariablesRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void SetBuddyVariablesRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");

	if (sfs->BuddyManager()->MyOnlineState() == false)
		errors->push_back("Can't set buddy variables while off-line");

	if (buddyVariables == NULL || buddyVariables->size() == 0)
		errors->push_back("No variables were specified");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("SetBuddyVariables request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void SetBuddyVariablesRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<ISFSArray> varList = SFSArray::NewInstance();

	list<boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = buddyVariables->begin(); iterator != buddyVariables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> item = (*iterator);
		varList->AddSFSArray(item->ToSFSArray());
	}

	sfso->PutSFSArray(KEY_BUDDY_VARS, varList);
}

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X
