// ===================================================================
//
// Description		
//		Contains the implementation of ChangeRoomPasswordStateRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ChangeRoomPasswordStateRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> ChangeRoomPasswordStateRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> ChangeRoomPasswordStateRequest::KEY_PASS (new string("p"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ChangeRoomPasswordStateRequest::ChangeRoomPasswordStateRequest(boost::shared_ptr<Room> room, string newPass)
	: BaseRequest (RequestType_ChangeRoomPassword)
{
	this->room = room;
	this->newPass = boost::shared_ptr<string>(new string(newPass));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ChangeRoomPasswordStateRequest::~ChangeRoomPasswordStateRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ChangeRoomPasswordStateRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// Missing room id
	if (this->room == NULL)
		errors->push_back("Provided room is null");

	if (newPass == NULL)
		errors->push_back("Invalid new room password. It must be a non-null string.");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("ChangePassState request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomPasswordStateRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<long int> valueId (new long int());
	*valueId = room->Id();
	sfso->PutInt(KEY_ROOM, valueId);

	sfso->PutUtfString(KEY_PASS, newPass);
}

}	// namespace Requests
}	// namespace Sfs2X

