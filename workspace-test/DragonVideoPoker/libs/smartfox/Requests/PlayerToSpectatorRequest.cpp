// ===================================================================
//
// Description		
//		Contains the implementation of PlayerToSpectatorRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PlayerToSpectatorRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> PlayerToSpectatorRequest::KEY_ROOM_ID (new string("r"));
boost::shared_ptr<string> PlayerToSpectatorRequest::KEY_USER_ID (new string("u"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::PlayerToSpectatorRequest()
	: BaseRequest (RequestType_PlayerToSpectator)
{
	Init(boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::PlayerToSpectatorRequest(boost::shared_ptr<Room> targetRoom)
	: BaseRequest (RequestType_PlayerToSpectator)
{
	Init(targetRoom);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::~PlayerToSpectatorRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void PlayerToSpectatorRequest::Init(boost::shared_ptr<Room> targetRoom)
{
	this->room = targetRoom;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void PlayerToSpectatorRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// No validation needed
	if (sfs->JoinedRooms()->size() < 1)
		errors->push_back("You are not joined in any rooms");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("LeaveRoom request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void PlayerToSpectatorRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	if (room == NULL) {
		room = sfs->LastJoinedRoom();
	}

	boost::shared_ptr<long int> valueId (new long int());
	*valueId = room->Id();
	sfso->PutInt(KEY_ROOM_ID, valueId);
}

}	// namespace Requests
}	// namespace Sfs2X



