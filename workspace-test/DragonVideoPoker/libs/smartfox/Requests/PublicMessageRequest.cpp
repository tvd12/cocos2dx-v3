// ===================================================================
//
// Description		
//		Contains the implementation of PublicMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PublicMessageRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PublicMessageRequest::PublicMessageRequest(string message, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> targetRoom)
{
	this->type = (long int)GENERICMESSAGETYPE_PUBLIC_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->room = targetRoom;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PublicMessageRequest::PublicMessageRequest(string message, boost::shared_ptr<ISFSObject> parameters)
{
	this->type = (long int)GENERICMESSAGETYPE_PUBLIC_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->room = boost::shared_ptr<Room>();
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PublicMessageRequest::PublicMessageRequest(string message)
{
	this->type = (long int)GENERICMESSAGETYPE_PUBLIC_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->room = boost::shared_ptr<Room>();
	this->parameters = boost::shared_ptr<ISFSObject>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PublicMessageRequest::~PublicMessageRequest()
{
}

}	// namespace Requests
}	// namespace Sfs2X


