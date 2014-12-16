// ===================================================================
//
// Description		
//		Contains the implementation of PrivateMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PrivateMessageRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PrivateMessageRequest::PrivateMessageRequest(string message, long int recipientId, boost::shared_ptr<ISFSObject> parameters)
{
	this->type = (long int)GENERICMESSAGETYPE_PRIVATE_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->recipientInt = boost::shared_ptr<long int>(new long int());
	*(this->recipientInt) = recipientId;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PrivateMessageRequest::PrivateMessageRequest(string message, long int recipientId)
{
	this->type = (long int)GENERICMESSAGETYPE_PRIVATE_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->recipientInt = boost::shared_ptr<long int>(new long int());
	*(this->recipientInt) = recipientId;
	this->parameters = boost::shared_ptr<ISFSObject>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PrivateMessageRequest::~PrivateMessageRequest()
{
}

}	// namespace Requests
}	// namespace Sfs2X


