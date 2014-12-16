// ===================================================================
//
// Description		
//		Contains the implementation of ModeratorMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ModeratorMessageRequest.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ModeratorMessageRequest::ModeratorMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode, boost::shared_ptr<ISFSObject> parameters)
{
	if (recipientMode == NULL) {
		boost::throw_exception(boost::enable_error_info (std::runtime_error("RecipientMode cannot be null!"))); 
	}

	this->type = (long int)GENERICMESSAGETYPE_MODERATOR_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->parameters = parameters;
	this->recipientInt = boost::shared_ptr<long int>(new long int());
	*this->recipientInt = recipientMode->TargetInt();
	this->recipientUser = recipientMode->TargetUser();
	this->recipientRoom = recipientMode->TargetRoom();
	this->recipientString = recipientMode->TargetString();
	this->recipientUsersCollection = recipientMode->TargetUsersCollection();
	this->sendMode = recipientMode->Mode();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ModeratorMessageRequest::ModeratorMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode)
{
	if (recipientMode == NULL) {
		boost::throw_exception(boost::enable_error_info (std::runtime_error("RecipientMode cannot be null!"))); 
	}

	this->type = (long int)GENERICMESSAGETYPE_MODERATOR_MSG;
	this->message = boost::shared_ptr<string>(new string(message));
	this->parameters = boost::shared_ptr<ISFSObject>();
	this->recipientInt = boost::shared_ptr<long int>(new long int());
	*this->recipientInt = recipientMode->TargetInt();
	this->recipientUser = recipientMode->TargetUser();
	this->recipientRoom = recipientMode->TargetRoom();
	this->recipientString = recipientMode->TargetString();
	this->recipientUsersCollection = recipientMode->TargetUsersCollection();
	this->sendMode = recipientMode->Mode();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ModeratorMessageRequest::~ModeratorMessageRequest()
{
}

}	// namespace Requests
}	// namespace Sfs2X

