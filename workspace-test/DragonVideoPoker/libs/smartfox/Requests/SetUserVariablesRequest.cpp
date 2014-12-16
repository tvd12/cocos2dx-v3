// ===================================================================
//
// Description		
//		Contains the implementation of SetUserVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SetUserVariablesRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> SetUserVariablesRequest::KEY_USER (new string("u"));
boost::shared_ptr<string> SetUserVariablesRequest::KEY_VAR_LIST (new string("vl"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetUserVariablesRequest::SetUserVariablesRequest(boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > userVariables)
	: BaseRequest (RequestType_SetUserVariables)
{
	this->userVariables = userVariables;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetUserVariablesRequest::~SetUserVariablesRequest()
{
	if (userVariables != NULL)
	{
		userVariables->clear();
	}
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void SetUserVariablesRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (userVariables == NULL || userVariables->size() == 0)
		errors->push_back("No variables were specified");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("SetUserVariables request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void SetUserVariablesRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<ISFSArray> varList (SFSArray::NewInstance ());

	vector<boost::shared_ptr<UserVariable> >::iterator iterator;
	for(iterator = userVariables->begin(); iterator != userVariables->end(); ++iterator)
	{
		varList->AddSFSArray ((*iterator)->ToSFSArray ());
	}

	sfso->PutSFSArray (KEY_VAR_LIST, varList);
}

}	// namespace Requests
}	// namespace Sfs2X


