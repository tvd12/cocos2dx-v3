// ===================================================================
//
// Description		
//		Contains the implementation of SetRoomVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SetRoomVariablesRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> SetRoomVariablesRequest::KEY_VAR_ROOM (new string("r"));
boost::shared_ptr<string> SetRoomVariablesRequest::KEY_VAR_LIST (new string("vl"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetRoomVariablesRequest::SetRoomVariablesRequest (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables, boost::shared_ptr<Room> room)
	: BaseRequest (RequestType_SetRoomVariables)
{
	Init (roomVariables, room);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetRoomVariablesRequest::SetRoomVariablesRequest (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables)
	: BaseRequest (RequestType_SetRoomVariables)
{
	Init (roomVariables, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetRoomVariablesRequest::~SetRoomVariablesRequest()
{
	if (roomVariables != NULL)
	{
		roomVariables->clear();
	}
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void SetRoomVariablesRequest::Init (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables, boost::shared_ptr<Room> room)
{
	this->roomVariables = roomVariables;
	this->room = room;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void SetRoomVariablesRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// Make sure that the user is joined in the room where variables are going to be set
	if (room != NULL) {
		if (!room->ContainsUser(sfs->MySelf()))
			errors->push_back ("You are not joined in the target room");
	} else {
		if (sfs->LastJoinedRoom() == NULL)
			errors->push_back ("You are not joined in any rooms");
	}

	if (roomVariables == NULL || roomVariables->size() == 0)
		errors->push_back ("No variables were specified");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("SetRoomVariables request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void SetRoomVariablesRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<ISFSArray> varList (SFSArray::NewInstance ());

	vector<boost::shared_ptr<RoomVariable> >::iterator iterator;
	for(iterator = roomVariables->begin(); iterator != roomVariables->end(); ++iterator)
	{
		varList->AddSFSArray ((*iterator)->ToSFSArray ());
	}

	if (room == NULL)
		room = sfs->LastJoinedRoom();

	sfso->PutSFSArray (KEY_VAR_LIST, varList);

	boost::shared_ptr<long int> valueId (new long int());
	*valueId = room->Id();
	sfso->PutInt (KEY_VAR_ROOM, valueId);
}

}	// namespace Requests
}	// namespace Sfs2X


