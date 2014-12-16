// ===================================================================
//
// Description		
//		Contains the implementation of ChangeRoomNameRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ChangeRoomNameRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> ChangeRoomNameRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> ChangeRoomNameRequest::KEY_NAME (new string("n"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ChangeRoomNameRequest::ChangeRoomNameRequest(boost::shared_ptr<Room> room, string newName)
	: BaseRequest (RequestType_ChangeRoomName)
{
	this->room = room;
	this->newName = boost::shared_ptr<string>(new string(newName));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ChangeRoomNameRequest::~ChangeRoomNameRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ChangeRoomNameRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());


	// Missing room id
	if (this->room == NULL)
		errors->push_back("Provided room is null");
				
	if (this->newName == NULL || this->newName->size() == 0)
		errors->push_back("Invalid new room name. It must be a non-null and non-empty string.");
					
	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("ChangeRoomName request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomNameRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<long int> valueId (new long int());
	*valueId = room->Id();
	sfso->PutInt(KEY_ROOM, valueId);
	sfso->PutUtfString(KEY_NAME, newName);
}

}	// namespace Requests
}	// namespace Sfs2X


