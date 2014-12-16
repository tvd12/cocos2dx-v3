// ===================================================================
//
// Description		
//		Contains the implementation of LogoutRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "LogoutRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> LogoutRequest::KEY_ZONE_NAME (new string("zn"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LogoutRequest::LogoutRequest()
	: BaseRequest (RequestType_Logout)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
LogoutRequest::~LogoutRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void LogoutRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	if (sfs->MySelf() == NULL)
	{
		boost::shared_ptr<list<string> > log (new list<string>());
		log->push_back("You are not logged in at the moment!");

		boost::shared_ptr<string> message (new string("LogoutRequest Error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, log));
		throw exception;
	}
}


}	// namespace Requests
}	// namespace Sfs2X
