// ===================================================================
//
// Description		
//		Contains the implementation of JoinRoomRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "JoinRoomRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> JoinRoomRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> JoinRoomRequest::KEY_USER_LIST (new string("ul"));
boost::shared_ptr<string> JoinRoomRequest::KEY_ROOM_NAME (new string("n"));
boost::shared_ptr<string> JoinRoomRequest::KEY_ROOM_ID (new string("i"));
boost::shared_ptr<string> JoinRoomRequest::KEY_PASS (new string("p"));
boost::shared_ptr<string> JoinRoomRequest::KEY_ROOM_TO_LEAVE (new string("rl"));
boost::shared_ptr<string> JoinRoomRequest::KEY_AS_SPECTATOR (new string("sp"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(boost::shared_ptr<Room> id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(string id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(long int id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(boost::shared_ptr<Room> id, string pass, boost::shared_ptr<long int> roomIdToLeave)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(string id, string pass, boost::shared_ptr<long int> roomIdToLeave)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(long int id, string pass, boost::shared_ptr<long int> roomIdToLeave)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(boost::shared_ptr<Room> id, string pass)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(string id, string pass)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(long int id, string pass)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(new string(pass)), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(boost::shared_ptr<Room> id)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(string id)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(long int id)
	: BaseRequest (RequestType_JoinRoom)
{
	Init(id, boost::shared_ptr<string>(), boost::shared_ptr<long int>(), false);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
JoinRoomRequest::~JoinRoomRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(boost::shared_ptr<Room> id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
{
	this->id = -1;
	this->id = id->Id();

	this->pass = pass;
	this->roomIdToLeave = roomIdToLeave;
	this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(string id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
{
	this->id = -1;
	this->name = boost::shared_ptr<string>(new string (id));

	this->pass = pass;
	this->roomIdToLeave = roomIdToLeave;
	this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(long int id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator)
{
	this->id = -1;
	this->id = id;

	this->pass = pass;
	this->roomIdToLeave = roomIdToLeave;
	this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void JoinRoomRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	if (this->id < 0 && this->name == NULL) {
		boost::shared_ptr<list<string> > errors (new list<string>());
		errors->push_back("Missing Room id or name, you should provide at least one");

		boost::shared_ptr<string> message (new string("JoinRoomRequest Error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void JoinRoomRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	if (this->id > -1) {
		boost::shared_ptr<long int> valueId (new long int());
		*valueId = this->id;
		this->sfso->PutInt(KEY_ROOM_ID, valueId);
	} else if (this->name != NULL) {
		this->sfso->PutUtfString(KEY_ROOM_NAME, this->name);
	}

	if (this->pass != NULL) {
		this->sfso->PutUtfString(KEY_PASS, this->pass);
	}

	/*
	* If == null 	--->> Leave Last Joined Room
	* If > 0 		--->> Leave the Room with that ID
	* If < 0		--->> Do not leave any Room  
	*/	
	if (this->roomIdToLeave != NULL) {
		this->sfso->PutInt(KEY_ROOM_TO_LEAVE, this->roomIdToLeave);
	}

	if (this->asSpectator) {
		boost::shared_ptr<bool> valueAsSpectator (new bool());
		*valueAsSpectator = this->asSpectator;
		this->sfso->PutBool(KEY_AS_SPECTATOR, valueAsSpectator);
	}
}
 

}	// namespace Requests
}	// namespace Sfs2X



