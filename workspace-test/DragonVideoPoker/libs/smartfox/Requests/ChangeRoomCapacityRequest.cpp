// ===================================================================
//
// Description		
//		Contains the implementation of ChangeRoomCapacityRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ChangeRoomCapacityRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> ChangeRoomCapacityRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> ChangeRoomCapacityRequest::KEY_USER_SIZE (new string("u"));
boost::shared_ptr<string> ChangeRoomCapacityRequest::KEY_SPEC_SIZE (new string("s"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ChangeRoomCapacityRequest::ChangeRoomCapacityRequest(boost::shared_ptr<Room> room, long int newMaxUsers, long int newMaxSpect)
	: BaseRequest (RequestType_ChangeRoomCapacity)
{
	this->room = room;
	this->newMaxUsers = newMaxUsers;
	this->newMaxSpect = newMaxSpect;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ChangeRoomCapacityRequest::~ChangeRoomCapacityRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ChangeRoomCapacityRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// Missing room id
	if (this->room == NULL)
		errors->push_back("Provided room is null");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("ChangeRoomCapacity request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomCapacityRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<long int> valueId (new long int());
	*valueId = room->Id();
	sfso->PutInt(KEY_ROOM, valueId);

	boost::shared_ptr<long int> valueNewMaxUsers (new long int());
	*valueNewMaxUsers = newMaxUsers;
	sfso->PutInt(KEY_USER_SIZE, valueNewMaxUsers);

	boost::shared_ptr<long int> valueNewMaxSpect (new long int());
	*valueNewMaxSpect = newMaxSpect;
	sfso->PutInt(KEY_SPEC_SIZE, valueNewMaxSpect);
}

}	// namespace Requests
}	// namespace Sfs2X


