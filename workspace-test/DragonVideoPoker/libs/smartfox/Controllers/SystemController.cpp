// ===================================================================
//
// Description		
//		Contains the implementation of SystemController
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SystemController.h"
#include "../Core/SFSBuddyEvent.h"
#include "../Requests/Buddylist/InitBuddyListRequest.h"
#include "../Requests/Buddylist/AddBuddyRequest.h"
#include "../Requests/Buddylist/RemoveBuddyRequest.h"
#include "../Requests/Buddylist/BlockBuddyRequest.h"
#include "../Requests/Buddylist/GoOnlineRequest.h"
#include "../Requests/Buddylist/SetBuddyVariablesRequest.h"
#include "../Entities/SFSBuddy.h"
#include "../Entities/MMOItem.h"
#include "../Entities/Variables/SFSBuddyVariable.h"
#include "../Entities/Variables/ReservedBuddyVariables.h"
#include "../Entities/Variables/MMOItemVariable.h"
#include "../Util/BuddyOnlineState.h"

using namespace Sfs2X::Requests::Buddylist;

namespace Sfs2X {
namespace Controllers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SystemController::SystemController(boost::shared_ptr<BitSwarmClient> bitSwarm)
	: BaseController (bitSwarm)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SystemController::~SystemController()
{
	requestHandlers.clear();
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void SystemController::Initialize()
{
	// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
	// so any initialization that need of instance shared pointer should be moved into this method that will be explicity called after constructor
	InitRequestHandlers();
}

// -------------------------------------------------------------------
// InitRequestHandlers
// -------------------------------------------------------------------
void SystemController::InitRequestHandlers()
{
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_Handshake, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnHandshake, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_Login, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnLogin, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_Logout, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnLogout, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_JoinRoom, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnJoinRoom, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_CreateRoom, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnCreateRoom, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_GenericMessage, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnGenericMessage, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_ChangeRoomName, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnChangeRoomName, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_ChangeRoomPassword, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnChangeRoomPassword, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_ChangeRoomCapacity, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnChangeRoomCapacity, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SetRoomVariables, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSetRoomVariables, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SetUserVariables, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSetUserVariables, (unsigned long long)this))));
//	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_CallExtension, FnCallExtension;
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SubscribeRoomGroup, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSubscribeRoomGroup, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_UnsubscribeRoomGroup, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnUnsubscribeRoomGroup, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SpectatorToPlayer, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSpectatorToPlayer, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_PlayerToSpectator, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnPlayerToSpectator, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_InitBuddyList, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnInitBuddyList, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_AddBuddy, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnAddBuddy, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_RemoveBuddy, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnRemoveBuddy, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_BlockBuddy, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnBlockBuddy, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_GoOnline, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnGoOnline, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SetBuddyVariables, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSetBuddyVariables, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_FindRooms, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnFindRooms, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_FindUsers, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnFindUsers, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_InviteUser, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnInviteUsers, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_InvitationReply, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnInvitationReply, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_QuickJoinGame, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnQuickJoinGame, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_PingPong, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnPingPong, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)RequestType_SetUserPosition, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSetUserPosition, (unsigned long long)this))));


	// Response only codes

	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1000, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnUserEnterRoom, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1001, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnUserCountChange, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1002, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnUserLost, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1003, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnRoomLost, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1004, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnUserExitRoom, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1005, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnClientDisconnection, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1006, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnReconnectionFailure, (unsigned long long)this))));
	requestHandlers.insert(pair<long int, boost::shared_ptr<RequestDelegate> >((long int)1007, boost::shared_ptr<RequestDelegate>(new RequestDelegate(&SystemController::FnSetMMOItemVariables, (unsigned long long)this))));
}

// -------------------------------------------------------------------
// HandleMessage
// -------------------------------------------------------------------
void SystemController::HandleMessage(boost::shared_ptr<IMessage> message)
{
	if (sfs->Debug()) 
	{
		boost::shared_ptr<string> err (new string());
		boost::shared_ptr<string> format (new string("Message: %d"));
		StringFormatter<long int> (err, format, message->Id());
		
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(*err);
		log->Info(logMessages);
	}
			
	map <long int, boost::shared_ptr<RequestDelegate> >::iterator iterator = requestHandlers.find(message->Id());

	if (iterator == requestHandlers.end()) 
	{
		boost::shared_ptr<string> err (new string());
		boost::shared_ptr<string> format (new string("Unknown message id: %d"));
		StringFormatter<long int> (err, format, message->Id());
		
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(*err);
		log->Warn(logMessages);

		return;
	}
				
	boost::shared_ptr<RequestDelegate> req = iterator->second;
	req->Invoke(message);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Handlers
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SystemController::FnHandshake(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	evtParams->insert(pair<string, boost::shared_ptr<void> >("message", msg->Content()));
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::HANDSHAKE, evtParams));
	instance->sfs->HandleHandShake(evt);
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnLogin(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> obj = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// Success
	if (obj->IsNull(BaseRequest::KEY_ERROR_CODE)) 
	{
		// Populate room list
		instance->PopulateRoomList(obj->GetSFSArray(LoginRequest::KEY_ROOMLIST));
			
		// create local user
		boost::shared_ptr<User> localUser (new SFSUser (*(obj->GetInt(LoginRequest::KEY_ID)), (*(obj->GetUtfString(LoginRequest::KEY_USER_NAME))), true));
		instance->sfs->MySelf(localUser);
				
		instance->sfs->MySelf()->UserManager(instance->sfs->UserManager());
		instance->sfs->MySelf()->PrivilegeId(*(obj->GetShort(LoginRequest::KEY_PRIVILEGE_ID)));
		instance->sfs->UserManager()->AddUser(instance->sfs->MySelf());
				
		// set the reconnection seconds
		instance->sfs->SetReconnectionSeconds(*(obj->GetShort(LoginRequest::KEY_RECONNECTION_SECONDS)));
				
		instance->sfs->MySelf()->PrivilegeId(*(obj->GetShort(LoginRequest::KEY_PRIVILEGE_ID)));
				
		// Fire success event
		evtParams->insert(pair<string, boost::shared_ptr<void> >("zone", obj->GetUtfString(LoginRequest::KEY_ZONE_NAME)));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("user", instance->sfs->MySelf()));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("data", obj->GetSFSObject(LoginRequest::KEY_PARAMS)));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::LOGIN, evtParams));

		instance->sfs->HandleLogin(evt);				
		instance->sfs->DispatchEvent(evt);
	}
	// Failure
	else 
	{
		boost::shared_ptr<short int> errorCode = obj->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), obj->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));

		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::LOGIN_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnCreateRoom(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> obj = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// Success
	if (obj->IsNull(BaseRequest::KEY_ERROR_CODE)) 
	{
		boost::shared_ptr<IRoomManager> roomManager = instance->sfs->RoomManager();
		boost::shared_ptr<Room> newRoom = SFSRoom::FromSFSArray(obj->GetSFSArray(CreateRoomRequest::KEY_ROOM));
		newRoom->RoomManager(instance->sfs->RoomManager());
				
		// Add room to room manager
		roomManager->AddRoom(newRoom);

		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", newRoom));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_ADD, evtParams));

		instance->sfs->DispatchEvent(evt);
	}
	// Failure
	else
	{
		boost::shared_ptr<short int> errorCode = obj->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), obj->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));

		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_CREATION_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnJoinRoom(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<IRoomManager> roomManager = instance->sfs->RoomManager();
	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// set flag off
	instance->sfs->IsJoining(false);

	// Success
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<ISFSArray> roomObj = sfso->GetSFSArray(JoinRoomRequest::KEY_ROOM);
		boost::shared_ptr<ISFSArray> userList = sfso->GetSFSArray(JoinRoomRequest::KEY_USER_LIST);

		// Get the joined Room data
		boost::shared_ptr<Room> room = SFSRoom::FromSFSArray(roomObj);
		room->RoomManager(instance->sfs->RoomManager());

		/*
		* We make sure that the associated Group is checked against the subscribed group list
		* If the Room group is not found, we mark this room as NOT managed.
		* This means that the Room shall be removed from the local Room List when we leave it
		* without the need for server notifications
		*
		* In other words all Rooms that are NOT managed belong to Group(s) to which the User
		* is not subscribed, therefore the server does not keep us updated.
		*/
		room = roomManager->ReplaceRoom(room, roomManager->ContainsGroup(*(room->GroupId())));

		// Populate room's user list
		for (long int j = 0; j < userList->Size(); j++)
		{
			boost::shared_ptr<ISFSArray> userObj = userList->GetSFSArray(j);

			// Get user if exist from main UserManager or create a new one
			boost::shared_ptr<User> user = instance->GetOrCreateUser(userObj, true, room);

			// Set the playerId
			user->SetPlayerId(userObj->GetShort(3), room);
			room->AddUser(user);

		}

		// Set as joined
		room->IsJoined(true);

		// Set as the last joined Room
		instance->sfs->LastJoinedRoom(room);

		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_JOIN, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
	// Failure
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_JOIN_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnUserEnterRoom(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<string> keyGetInt (new string("r"));
	boost::shared_ptr<Room> room = instance->sfs->RoomManager()->GetRoomById(*(sfso->GetInt(keyGetInt)));

	if (room != NULL) {
		boost::shared_ptr<string> keyGetSFSArray (new string("u"));
		boost::shared_ptr<ISFSArray> userObj = sfso->GetSFSArray(keyGetSFSArray);
		boost::shared_ptr<User> user = instance->GetOrCreateUser(userObj, true, room);

		room->AddUser(user);

		evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_ENTER_ROOM, evtParams));
		instance->sfs->DispatchEvent(evt);
	} 					
}

void SystemController::FnUserCountChange(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<string> keyGetInt (new string("r"));
	boost::shared_ptr<Room> room = instance->sfs->RoomManager()->GetRoomById(*(sfso->GetInt(keyGetInt)));

	if (room != NULL) {
		boost::shared_ptr<string> keyGetShort (new string("uc"));
		long int uCount = *(sfso->GetShort(keyGetShort));
		long int sCount = 0;

		// Check for optional spectator count
		boost::shared_ptr<string> keyContains (new string("sc"));
		if (sfso->ContainsKey(keyContains))
			sCount = *(sfso->GetShort(keyContains));

		room->UserCount(uCount);
		room->SpectatorCount(sCount);

		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

		boost::shared_ptr<long int> valueUCount (new long int());
		*valueUCount = uCount;
		evtParams->insert(pair<string, boost::shared_ptr<void> >("uCount", valueUCount));

		boost::shared_ptr<long int> valueSCount (new long int());
		*valueSCount = sCount;
		evtParams->insert(pair<string, boost::shared_ptr<void> >("sCount", valueSCount));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_COUNT_CHANGE, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

/*
* Server tells client that a certain user got disconnected
* This could be used to trigger a buddy-is-offline event as well... 
*/
void SystemController::FnUserLost(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();

	boost::shared_ptr<string> keyGetInt (new string("u"));
	long int uId = *(sfso->GetInt(keyGetInt));
	boost::shared_ptr<User> user = instance->sfs->UserManager()->GetUserById(uId);

	if (user != NULL) {
		// keep a copy of the rooms joined by this user
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > joinedRooms = instance->sfs->RoomManager()->GetUserRooms(user);

		// remove from all rooms
		instance->sfs->RoomManager()->RemoveUser(user);

		// remove from global user manager
		instance->sfs->UserManager()->RemoveUser(user);

		// Fire one event in each room
		vector<boost::shared_ptr<Room> >::iterator iteratorJoinedRooms;
		for (iteratorJoinedRooms = joinedRooms->begin(); iteratorJoinedRooms != joinedRooms->end(); iteratorJoinedRooms++)
		{
			boost::shared_ptr<Room> room = (*iteratorJoinedRooms);
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
			evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_EXIT_ROOM, evtParams));
			instance->sfs->DispatchEvent(evt);
		}
	}
}

void SystemController::FnRoomLost(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<string> keyGetInt (new string("r"));
	long int rId = *(sfso->GetInt(keyGetInt));
	boost::shared_ptr<Room> room = instance->sfs->RoomManager()->GetRoomById(rId);
	boost::shared_ptr<IUserManager> globalUserManager = instance->sfs->UserManager(); 

	if (room != NULL) {
		// remove from all rooms
		instance->sfs->RoomManager()->RemoveRoom(room);

		boost::shared_ptr<vector<boost::shared_ptr<User> > > users = room->UserList();
		vector<boost::shared_ptr<User> >::iterator iteratorUserList;
		// remove users in this room from user manager
		for (iteratorUserList = users->begin(); iteratorUserList != users->end(); iteratorUserList++)
		{
			boost::shared_ptr<User> user = (*iteratorUserList);
			globalUserManager->RemoveUser(user);
		}

		// Fire event			
		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_REMOVE, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnUserExitRoom(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<string> keyGetInt (new string("r"));
	long int rId = *(sfso->GetInt(keyGetInt));

	keyGetInt = boost::shared_ptr<string>(new string("u"));
	long int uId = *(sfso->GetInt(keyGetInt));
	boost::shared_ptr<Room> room = instance->sfs->RoomManager()->GetRoomById(rId);
	boost::shared_ptr<User> user = instance->sfs->UserManager()->GetUserById(uId);

	if (room != NULL && user != NULL) {
		room->RemoveUser(user);
		instance->sfs->UserManager()->RemoveUser(user);

		// If I have left a room I need to mark the room as NOT JOINED
		if (user->IsItMe() && room->IsJoined()) {
			// Turn of the Room's joined flag
			room->IsJoined(false);

			// Reset the lastJoinedRoom reference if no Room is currently joined
			if (instance->sfs->JoinedRooms()->size() == 0) {
				instance->sfs->LastJoinedRoom(boost::shared_ptr<Room>());
			}

			/*
			* Room is NOT managed, we need to remove it
			*/	
			if (!room->IsManaged()) {
				instance->sfs->RoomManager()->RemoveRoom(room);
			}
		}

		evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));

		// Fire event
		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_EXIT_ROOM, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
	else
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		string logMessage;
		logMessage = "Failed to handle UserExit event. Room: " + (room != NULL ? (*room->Name()) : " ") + ", User: " + (user != NULL ? (*user->Name()) : " ");

		logMessages->push_back(logMessage);
		instance->log->Debug(logMessages);
	}
}

void SystemController::FnClientDisconnection(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();

	boost::shared_ptr<string> keyGetByte (new string("dr"));
	long int reasonId = *(sfso->GetByte(keyGetByte));

	instance->sfs->HandleClientDisconnection(ClientDisconnectionReason::GetReason(reasonId));
}

void SystemController::FnSetRoomVariables(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	long int rId = *(sfso->GetInt(SetRoomVariablesRequest::KEY_VAR_ROOM));
	boost::shared_ptr<ISFSArray> varListData = sfso->GetSFSArray(SetRoomVariablesRequest::KEY_VAR_LIST);

	boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(rId);
	boost::shared_ptr<vector<string> > changedVarNames(new vector<string>());

	if (targetRoom != NULL) {
		for (long int j = 0; j < varListData->Size(); j++) {
			boost::shared_ptr<RoomVariable> roomVar = SFSRoomVariable::FromSFSArray(varListData->GetSFSArray(j));
			targetRoom->SetVariable(roomVar);

			changedVarNames->push_back(*roomVar->Name());
		}

		evtParams->insert(pair<string, boost::shared_ptr<void> >("changedVars", changedVarNames));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_VARIABLES_UPDATE, evtParams));
		instance->sfs->DispatchEvent(evt);
	} 		
	else
	{
		char buffer[512];
		sprintf (buffer, "RoomVariablesUpdate, unknown Room id = %ld", rId);
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		instance->log->Debug(logMessages);
	}
}

void SystemController::FnSetUserVariables(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	long int uId = *(sfso->GetInt(SetUserVariablesRequest::KEY_USER));
	boost::shared_ptr<ISFSArray> varListData = sfso->GetSFSArray(SetUserVariablesRequest::KEY_VAR_LIST);

	boost::shared_ptr<User> user = instance->sfs->UserManager()->GetUserById(uId);
	boost::shared_ptr<vector<string> > changedVarNames (new vector<string>());

	if (user != NULL) {
		for (long int j = 0; j < varListData->Size(); j++) {
			boost::shared_ptr<UserVariable> userVar = SFSUserVariable::FromSFSArray(varListData->GetSFSArray(j));
			user->SetVariable(userVar);

			changedVarNames->push_back(*userVar->Name());
		}

		evtParams->insert(pair<string, boost::shared_ptr<void> >("changedVars", changedVarNames));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_VARIABLES_UPDATE, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
	else
	{
		char buffer[512];
		sprintf (buffer, "UserVariablesUpdate: unknown user id =  %ld", uId);
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		instance->log->Warn(logMessages);
	}
}

void SystemController::FnSubscribeRoomGroup(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: Success ::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> groupId = sfso->GetUtfString(SubscribeRoomGroupRequest::KEY_GROUP_ID);
		boost::shared_ptr<ISFSArray> roomListData = sfso->GetSFSArray(SubscribeRoomGroupRequest::KEY_ROOM_LIST);

		// Integrity Check
		if (instance->sfs->RoomManager()->ContainsGroup(*groupId))
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("SubscribeGroup Error. Group:"+ *groupId + "already subscribed!");
			instance->log->Warn(logMessages);
		}

		instance->PopulateRoomList(roomListData);

		// Pass the groupId
		evtParams->insert(pair<string, boost::shared_ptr<void> >("groupId", groupId));

		// Pass the new rooms that are present in the subscribed group
		evtParams->insert(pair<string, boost::shared_ptr<void> >("newRooms", instance->sfs->RoomManager()->GetRoomListFromGroup(*groupId)));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_GROUP_SUBSCRIBE, evtParams));
		instance->sfs->DispatchEvent(evt);
	}

	// ::: Failure :::::::::::::::::::::::::::::::::::::::::::::::::::::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_GROUP_SUBSCRIBE_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnUnsubscribeRoomGroup(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> groupId (new string(*(sfso->GetUtfString(UnsubscribeRoomGroupRequest::KEY_GROUP_ID))));
		// Integrity Check
		if (!instance->sfs->RoomManager()->ContainsGroup(*groupId))
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("UnsubscribeGroup Error. Group:" + *groupId + "is not subscribed!");
			instance->log->Warn(logMessages);
		}

		instance->sfs->RoomManager()->RemoveGroup(*groupId);

		// Pass the groupId
		evtParams->insert(pair<string, boost::shared_ptr<void> >("groupId", groupId));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_GROUP_UNSUBSCRIBE, evtParams));
		instance->sfs->DispatchEvent(evt);
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_GROUP_UNSUBSCRIBE_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnChangeRoomName(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		// Obtain the target Room
		long int roomId = *(sfso->GetInt(ChangeRoomNameRequest::KEY_ROOM));
		boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

		if (targetRoom != NULL) 	{
			boost::shared_ptr<string> valueRoomName (new string (*targetRoom->Name()));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("oldName", valueRoomName));

			instance->sfs->RoomManager()->ChangeRoomName(targetRoom, *(sfso->GetUtfString(ChangeRoomNameRequest::KEY_NAME)));

			evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_NAME_CHANGE, evtParams));
			instance->sfs->DispatchEvent(evt);
		}

		// Room not found locally, log error
		else
		{
			char buffer[512];
			sprintf (buffer, "Room not found, ID: %ld, Room name change failed.", roomId);
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_NAME_CHANGE_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnChangeRoomPassword(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		// Obtain the target Room
		long int roomId = *(sfso->GetInt(ChangeRoomPasswordStateRequest::KEY_ROOM));
		boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

		if (targetRoom != NULL) {
			instance->sfs->RoomManager()->ChangeRoomPasswordState(targetRoom, *(sfso->GetBool(ChangeRoomPasswordStateRequest::KEY_PASS)));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_PASSWORD_STATE_CHANGE, evtParams));
			instance->sfs->DispatchEvent(evt);
		} else {
			char buffer[512];
			sprintf (buffer, "Room not found, ID: %ld, Room password change failed.", roomId);
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnChangeRoomCapacity(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		// Obtain the target Room
		long int roomId = *(sfso->GetInt(ChangeRoomCapacityRequest::KEY_ROOM));
		boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

		if (targetRoom != NULL) {
			instance->sfs->RoomManager()->ChangeRoomCapacity(
				targetRoom,
				*(sfso->GetInt(ChangeRoomCapacityRequest::KEY_USER_SIZE)), 
				*(sfso->GetInt(ChangeRoomCapacityRequest::KEY_SPEC_SIZE))
				);

			evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_CAPACITY_CHANGE, evtParams));
			instance->sfs->DispatchEvent(evt);
		} else {
			char buffer[512];
			sprintf (buffer, "Room not found, ID: %ld, Room capacity change failed.", roomId);
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_CAPACITY_CHANGE_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnLogout(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	instance->sfs->HandleLogout();
 			
	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
			
	evtParams->insert(pair<string, boost::shared_ptr<void> >("zoneName", sfso->GetUtfString(LogoutRequest::KEY_ZONE_NAME)));

	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::LOGOUT, evtParams));
	instance->sfs->DispatchEvent(evt);
}

boost::shared_ptr<User> SystemController::GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj)
{
	return GetOrCreateUser(userObj, false, boost::shared_ptr<Room>());
}

boost::shared_ptr<User> SystemController::GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj, bool addToGlobalManager)
{
	return GetOrCreateUser(userObj, addToGlobalManager, boost::shared_ptr<Room>());
}

boost::shared_ptr<User> SystemController::GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj, bool addToGlobalManager, boost::shared_ptr<Room> room)
{
	// Get id
	long int uId = userObj->GetInt(0);
	boost::shared_ptr<User> user = sfs->UserManager()->GetUserById(uId);

	// User is not managed, build the object from Server data
	if (user == NULL)
	{
		user = SFSUser::FromSFSArray(userObj, room);
		user->UserManager(sfs->UserManager());
	}
	// User is already managed, make sure to update the playerId
	else if (room != NULL) {
		user->SetPlayerId(userObj->GetShort(3), room);

		boost::shared_ptr<ISFSArray> uVars = userObj->GetSFSArray(4);
		for (long int i = 0; i < uVars->Size(); i++) {
			user->SetVariable(SFSUserVariable::FromSFSArray(uVars->GetSFSArray(i)));
		}
	}
	// Add if new
	if (addToGlobalManager) {
		sfs->UserManager()->AddUser(user);
	}	

	return user;
}

void SystemController::FnSpectatorToPlayer(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE))
	{
		// Obtain the target Room
		long int roomId = *(sfso->GetInt(SpectatorToPlayerRequest::KEY_ROOM_ID));
		long int userId = *(sfso->GetInt(SpectatorToPlayerRequest::KEY_USER_ID));
		long int playerId = *(sfso->GetShort(SpectatorToPlayerRequest::KEY_PLAYER_ID));

		boost::shared_ptr<User> user = instance->sfs->UserManager()->GetUserById(userId);
		boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

		if (targetRoom != NULL) {
			if (user != NULL) {
				if (user->IsJoinedInRoom(targetRoom)) {
					// Update the playerId
					user->SetPlayerId(playerId, targetRoom);

					evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));			// where it happened
					evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));				// who did it

					boost::shared_ptr<long int> valuePlayerId (new long int());
					*valuePlayerId = playerId;
					evtParams->insert(pair<string, boost::shared_ptr<void> >("playerId", valuePlayerId));		// the new playerId

					boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::SPECTATOR_TO_PLAYER, evtParams));
					instance->sfs->DispatchEvent(evt);
				}
				else
				{
					boost::shared_ptr<vector<string> > logMessages (new vector<string>());
					logMessages->push_back("User: " + (*user->Name()) + " not joined in Room: " + (*targetRoom->Name()) + ", SpectatorToPlayer failed.");
					instance->log->Warn(logMessages);
				}
			}
			else
			{
				char buffer[512];
				sprintf (buffer, "User not found, ID: %ld, SpectatorToPlayer failed.", userId);
				string logMessage = buffer;

				boost::shared_ptr<vector<string> > logMessages (new vector<string>());
				logMessages->push_back(logMessage);
				instance->log->Warn(logMessages);
			}
		}

		else
		{
			char buffer[512];
			sprintf (buffer, "Room not found, ID: %ld, SpectatorToPlayer failed.", roomId);
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else
	{
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::SPECTATOR_TO_PLAYER_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnPlayerToSpectator(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		// Obtain the target Room
		long int roomId = *(sfso->GetInt(PlayerToSpectatorRequest::KEY_ROOM_ID));
		long int userId = *(sfso->GetInt(PlayerToSpectatorRequest::KEY_USER_ID));

		boost::shared_ptr<User> user = instance->sfs->UserManager()->GetUserById(userId);
		boost::shared_ptr<Room> targetRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

		if (targetRoom != NULL) {
			if (user != NULL) {
				if (user->IsJoinedInRoom(targetRoom)) {
					// Update the playerId
					user->SetPlayerId(-1, targetRoom);

					evtParams->insert(pair<string, boost::shared_ptr<void> >("room", targetRoom));			// where it happened
					evtParams->insert(pair<string, boost::shared_ptr<void> >("user", user));				// who did it

					boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PLAYER_TO_SPECTATOR, evtParams));
					instance->sfs->DispatchEvent(evt);
				}
				else
				{
					boost::shared_ptr<vector<string> > logMessages (new vector<string>());
					logMessages->push_back("User: " + (*user->Name()) + " not joined in Room: " + (*targetRoom->Name()) + ", PlayerToSpectator failed.");
					instance->log->Warn(logMessages);
				}
			}
			else
			{
				char buffer[512];
				sprintf (buffer, "User not found, ID: %ld, PlayerToSpectator failed.", userId);
				string logMessage = buffer;

				boost::shared_ptr<vector<string> > logMessages (new vector<string>());
				logMessages->push_back(logMessage);
				instance->log->Warn(logMessages);
			}
		}
		else
		{
			char buffer[512];
			sprintf (buffer, "Room not found, ID: %ld, SpectatorToPlayer failed.", roomId);
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	else
	{
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PLAYER_TO_SPECTATOR_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// BuddyList Handlers
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SystemController::FnInitBuddyList(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		//var buddyList:Array = []
		boost::shared_ptr<ISFSArray> bListData = sfso->GetSFSArray(InitBuddyListRequest::KEY_BLIST);
		boost::shared_ptr<ISFSArray> myVarsData = sfso->GetSFSArray(InitBuddyListRequest::KEY_MY_VARS);
		boost::shared_ptr<vector<string> > buddyStates = sfso->GetUtfStringArray(InitBuddyListRequest::KEY_BUDDY_STATES);

		// Clear BuddyManager
		instance->sfs->BuddyManager()->ClearAll();

		// Populate the BuddyList
		for (int i = 0; i < bListData->Size(); i++) {

			boost::shared_ptr<Buddy> b = SFSBuddy::FromSFSArray(bListData->GetSFSArray(i));
			instance->sfs->BuddyManager()->AddBuddy(b);
		}

		// Set the buddy states
		if (buddyStates !=  NULL) {
			instance->sfs->BuddyManager()->BuddyStates(buddyStates);
		}

		// Populate MyBuddyVariables
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > myBuddyVariables (new vector<boost::shared_ptr<BuddyVariable> >());

		for (int i = 0; i < myVarsData->Size(); i++) {
			myBuddyVariables->push_back( SFSBuddyVariable::FromSFSArray(myVarsData->GetSFSArray(i)) );
		}

		instance->sfs->BuddyManager()->MyVariables(myBuddyVariables);
		instance->sfs->BuddyManager()->Inited(true);

		// Fire event
		evtParams->insert(pair<string, boost::shared_ptr<void> >("buddyList", instance->sfs->BuddyManager()->BuddyList()));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("myVariables", instance->sfs->BuddyManager()->MyVariables()));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_LIST_INIT, evtParams));
		instance->sfs->DispatchEvent(evt);
	}

	// ::: FAILURE :::
	else
	{
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnAddBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {

		boost::shared_ptr<Buddy> buddy = SFSBuddy::FromSFSArray( sfso->GetSFSArray(AddBuddyRequest::KEY_BUDDY_NAME) );
		instance->sfs->BuddyManager()->AddBuddy(buddy);

		// Fire event
		evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", buddy));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ADD, evtParams));
		instance->sfs->DispatchEvent(evt);
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnRemoveBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> buddyName = sfso->GetUtfString(RemoveBuddyRequest::KEY_BUDDY_NAME);
		boost::shared_ptr<Buddy> buddy = instance->sfs->BuddyManager()->RemoveBuddyByName(*buddyName);

		if (buddy != NULL) {
			// Fire event
			evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", buddy));

			boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_REMOVE, evtParams));
			instance->sfs->DispatchEvent(evt);
		} else {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("RemoveBuddy failed, buddy not found: "+ *buddyName);
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnBlockBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> buddyName = sfso->GetUtfString(BlockBuddyRequest::KEY_BUDDY_NAME);
		boost::shared_ptr<Buddy> buddy = instance->sfs->BuddyManager()->GetBuddyByName(*buddyName);

		if (buddy != NULL) {
			// Set the BuddyBlock State
			buddy->IsBlocked(*(sfso->GetBool(BlockBuddyRequest::KEY_BUDDY_BLOCK_STATE)));

			// Fire event
			evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", buddy));

			boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_BLOCK, evtParams));
			instance->sfs->DispatchEvent(evt);
		} else {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("BlockBuddy failed, buddy not found: "+ *buddyName + ", in local BuddyList");
			instance->log->Warn(logMessages);
		}
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnGoOnline(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> buddyName = sfso->GetUtfString(GoOnlineRequest::KEY_BUDDY_NAME);
		boost::shared_ptr<Buddy> buddy = instance->sfs->BuddyManager()->GetBuddyByName(*buddyName);
		bool isItMe = (*buddyName) == (*instance->sfs->MySelf()->Name());
		long int onlineValue = *(sfso->GetByte(GoOnlineRequest::KEY_ONLINE));
		bool onlineState = (onlineValue == (long int)BUDDYONLINESTATE_ONLINE);

		bool fireEvent = true;

		if (isItMe) {
			/*
			* This code should never run
			* The state was already updated when the request was sent, if they don't match something wrong
			* is happening.
			*/
			if (instance->sfs->BuddyManager()->MyOnlineState() != onlineState) {

				char buffer[512];
				sprintf (buffer, "Unexpected: MyOnlineState is not in synch with the server. Resynching: %ld", onlineState);
				string logMessage = buffer;

				boost::shared_ptr<vector<string> > logMessages (new vector<string>());
				logMessages->push_back(logMessage);
				instance->log->Warn(logMessages);

				instance->sfs->BuddyManager()->MyOnlineState(onlineState);
			}
		}

		// Another buddy in my list went online/offline
		else if (buddy != NULL) {
			// Set the BuddyBlock State
			buddy->Id(*(sfso->GetInt(GoOnlineRequest::KEY_BUDDY_ID)));
			boost::shared_ptr<bool> onlineStateValue (new bool());
			*onlineStateValue = onlineState;
			boost::shared_ptr<BuddyVariable> bvar (new SFSBuddyVariable(ReservedBuddyVariables::BV_ONLINE, onlineStateValue, VARIABLETYPE_BOOL));
			buddy->SetVariable(bvar);

			/*
			* Did the buddy leave the server?
			* If so we need to remove the volatile buddy variables (not persistent)
			*/
			if (onlineValue == (long int)BUDDYONLINESTATE_LEFT_THE_SERVER)
				buddy->ClearVolatileVariables();

			/*
			* Event is NOT fired if a buddy goes on/offline while I am off-line
			* This is equivalent to checking (buddy != null && sfs.buddyManager.myOnlineState) before firing the event
			*/
			fireEvent = instance->sfs->BuddyManager()->MyOnlineState();
		}

		// Buddy not found, it's not me... something is wrong
		else {
			// Log and Exit
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("GoOnline error, buddy not found: " + *buddyName + ", in local BuddyList.");
			instance->log->Warn(logMessages);

			return;
		}

		if (fireEvent) {
			evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", buddy));

			boost::shared_ptr<bool> isItMeValue (new bool());
			*isItMeValue = isItMe;
			evtParams->insert(pair<string, boost::shared_ptr<void> >("isItMe", isItMeValue));

			boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ONLINE_STATE_UPDATE, evtParams));
			instance->sfs->DispatchEvent(evt);
		} 
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnReconnectionFailure(unsigned long long context, boost::shared_ptr<IMessage> msg) 
{
	// Map context
	SystemController* instance = (SystemController*)context;

	instance->sfs->HandleReconnectionFailure();
}

void SystemController::FnSetBuddyVariables(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<string> buddyName = sfso->GetUtfString(SetBuddyVariablesRequest::KEY_BUDDY_NAME);
		boost::shared_ptr<ISFSArray> buddyVarsData = sfso->GetSFSArray(SetBuddyVariablesRequest::KEY_BUDDY_VARS);

		boost::shared_ptr<Buddy> buddy = instance->sfs->BuddyManager()->GetBuddyByName(*buddyName);

		bool isItMe = *buddyName == (*instance->sfs->MySelf()->Name());

		boost::shared_ptr<vector<string> > changedVarNames (new vector<string>());
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > variables (new vector<boost::shared_ptr<BuddyVariable> >());

		bool fireEvent = true;

		// Rebuild variables
		for (int j = 0; j < buddyVarsData->Size(); j++) {
			boost::shared_ptr<BuddyVariable> buddyVar = SFSBuddyVariable::FromSFSArray(buddyVarsData->GetSFSArray(j));

			variables->push_back(buddyVar);
			changedVarNames->push_back(*buddyVar->Name());
		}

		// If it's my user, change my local variables
		if (isItMe) {
			instance->sfs->BuddyManager()->MyVariables(variables);
		}

		// or ... change the variables of one of my buddies
		else if (buddy != NULL) 	{
			buddy->SetVariables(variables);

			// See GoOnline handler for more details on this
			fireEvent = instance->sfs->BuddyManager()->MyOnlineState();
		}

		// Unexpected: it's not me, it's not one of my buddies. Log and quit
		else {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("Unexpected. Target of BuddyVariables update not found: "+ *buddyName);
			instance->log->Warn(logMessages);

			return;
		}

		if (fireEvent) {
			boost::shared_ptr<bool> isItMeValue (new bool());
			*isItMeValue = isItMe;

			evtParams->insert(pair<string, boost::shared_ptr<void> >("isItMe", isItMeValue));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("changedVars", changedVarNames));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", buddy));

			boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_VARIABLES_UPDATE, evtParams));
			instance->sfs->DispatchEvent(evt);
		}
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnFindRooms(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<ISFSArray> roomListData = sfso->GetSFSArray(FindRoomsRequest::KEY_FILTERED_ROOMS);
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > roomList (new vector<boost::shared_ptr<Room> >());

	for (long int i = 0; i < roomListData->Size(); i++) 
	{
	//	roomList->push_back(SFSRoom::FromSFSArray(roomListData->GetSFSArray(i)));
		boost::shared_ptr<Room> theRoom = SFSRoom::FromSFSArray(roomListData->GetSFSArray(i));

		// Flag Rooms that are joined locally
		boost::shared_ptr<Room> localRoom = instance->sfs->RoomManager()->GetRoomById(theRoom->Id());

		if (localRoom != NULL)
			theRoom->IsJoined(localRoom->IsJoined());

		roomList->push_back(theRoom);
	}

	evtParams->insert(pair<string, boost::shared_ptr<void> >("rooms", roomList));

	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_FIND_RESULT, evtParams));
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnFindUsers(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<ISFSArray> userListData = sfso->GetSFSArray(FindUsersRequest::KEY_FILTERED_USERS);
	boost::shared_ptr<vector<boost::shared_ptr<User> > > userList (new vector<boost::shared_ptr<User> >());
	boost::shared_ptr<User> mySelf = instance->sfs->MySelf();

	for (long int i = 0; i < userListData->Size(); i++) {
		boost::shared_ptr<User> u = SFSUser::FromSFSArray(userListData->GetSFSArray(i));

		/*
		* Since 0.9.6
		* Swap the original object, this way we have the isItMe flag correctly populated
		*/
		if (u->Id() == mySelf->Id())
			u = mySelf;

		userList->push_back(u);	
	}

	evtParams->insert(pair<string, boost::shared_ptr<void> >("users", userList));
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::USER_FIND_RESULT, evtParams));
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnInviteUsers(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	boost::shared_ptr<User> inviter = boost::shared_ptr<User>();

	// Determine if the user is local (id was sent) or not (whole User object was sent)
	if (sfso->ContainsKey(InviteUsersRequest::KEY_USER_ID))
		inviter = instance->sfs->UserManager()->GetUserById(*(sfso->GetInt(InviteUsersRequest::KEY_USER_ID)));
	else
		inviter = SFSUser::FromSFSArray(sfso->GetSFSArray(InviteUsersRequest::KEY_USER));

	long int expiryTime = *(sfso->GetShort(InviteUsersRequest::KEY_TIME));
	long int invitationId = *(sfso->GetInt(InviteUsersRequest::KEY_INVITATION_ID));
	boost::shared_ptr<ISFSObject> invParams = sfso->GetSFSObject(InviteUsersRequest::KEY_PARAMS);
	boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation (new SFSInvitation(inviter, instance->sfs->MySelf(), expiryTime, invParams));
	invitation->Id(invitationId);

	evtParams->insert(pair<string, boost::shared_ptr<void> >("invitation", invitation));

	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::INVITATION, evtParams));
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnInvitationReply(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	// ::: SUCCESS :::
	if (sfso->IsNull(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<User> invitee = boost::shared_ptr<User>();

		// Determine if the invitee is local (id was sent) or not (whole User object was sent)
		if (sfso->ContainsKey(InviteUsersRequest::KEY_USER_ID))
			invitee = instance->sfs->UserManager()->GetUserById(*(sfso->GetInt(InviteUsersRequest::KEY_USER_ID)));
		else
			invitee = SFSUser::FromSFSArray(sfso->GetSFSArray(InviteUsersRequest::KEY_USER));

		boost::shared_ptr<unsigned char> reply = sfso->GetByte(InviteUsersRequest::KEY_REPLY_ID);
		boost::shared_ptr<ISFSObject> data = sfso->GetSFSObject(InviteUsersRequest::KEY_PARAMS);

		evtParams->insert(pair<string, boost::shared_ptr<void> >("invitee", invitee));

		evtParams->insert(pair<string, boost::shared_ptr<void> >("reply", reply));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("data", data));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::INVITATION_REPLY, evtParams));
		instance->sfs->DispatchEvent(evt);
	}

	// ::: FAILURE :::
	else {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::INVITATION_REPLY_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnQuickJoinGame(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// NOTE: this is called only in case of error, when no Games to join where found
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());


	// ::: GRAB ERROR :::
	if (sfso->ContainsKey(BaseRequest::KEY_ERROR_CODE)) {
		boost::shared_ptr<short int> errorCode = sfso->GetShort(BaseRequest::KEY_ERROR_CODE);
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*errorCode, instance->sfs->Log(), sfso->GetUtfStringArray(BaseRequest::KEY_ERROR_PARAMS));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::ROOM_JOIN_ERROR, evtParams));
		instance->sfs->DispatchEvent(evt);
	}
}

void SystemController::FnPingPong(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<long int> avg (new long int());
	*avg = instance->sfs->LagMonitor()->OnPingPong();

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	evtParams->insert(pair<string, boost::shared_ptr<void> >("lagValue", avg));

	// Redispatch at the user level
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PING_PONG, evtParams));
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnSetUserPosition(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	boost::shared_ptr<ISFSObject> sfso = msg->Content();

	long int roomId = *(sfso->GetInt(SetUserPositionRequest::KEY_ROOM));

	boost::shared_ptr<vector<long int> > minusUserList = sfso->GetIntArray(SetUserPositionRequest::KEY_MINUS_USER_LIST);
	boost::shared_ptr<ISFSArray> plusUserList = sfso->GetSFSArray(SetUserPositionRequest::KEY_PLUS_USER_LIST);

	boost::shared_ptr<vector<long int> > minusItemList = sfso->GetIntArray(SetUserPositionRequest::KEY_MINUS_ITEM_LIST);
	boost::shared_ptr<ISFSArray> plusItemList = sfso->GetSFSArray(SetUserPositionRequest::KEY_PLUS_ITEM_LIST);

	boost::shared_ptr<Room> theRoom = instance->sfs->RoomManager()->GetRoomById(roomId);

	// Lists of elements that will be passed in the event
	boost::shared_ptr<vector<boost::shared_ptr<User> > > addedUsers (new vector<boost::shared_ptr<User> >());
	boost::shared_ptr<vector<boost::shared_ptr<User> > > removedUsers (new vector<boost::shared_ptr<User> >());

	boost::shared_ptr<vector<boost::shared_ptr<IMMOItem> > > addedItems (new vector<boost::shared_ptr<IMMOItem> >());
	boost::shared_ptr<vector<boost::shared_ptr<IMMOItem> > > removedItems (new vector<boost::shared_ptr<IMMOItem> >());

	// Remove users that no longer are in proximity
	if (minusUserList != NULL && minusUserList->size() > 0)
	{
		vector<long int>::iterator iteratormiMinusUserList;
		for (iteratormiMinusUserList = minusUserList->begin(); iteratormiMinusUserList != minusUserList->end(); iteratormiMinusUserList++)
		{
			boost::shared_ptr<User> removedUser = theRoom->GetUserById(*iteratormiMinusUserList);
			if (removedUser != NULL)
			{
				theRoom->RemoveUser(removedUser);
				removedUsers->push_back(removedUser);
			}
		}
	}
			
	// Add new users that are now in proximity
	if (plusUserList != NULL)
	{
		for (long int i = 0; i < plusUserList->Size(); i++)
		{
			boost::shared_ptr<ISFSArray> encodedUser = plusUserList->GetSFSArray(i);
					
			boost::shared_ptr<User> newUser = instance->GetOrCreateUser(encodedUser, true, theRoom);
			addedUsers->push_back(newUser);
			theRoom->AddUser(newUser);
					
			/*
			* From the encoded User (as SFSArray) we extract the 5th extra/optional parameter 
			* which contains his location on the map, or the AOIEntryPoint as we will refer to it
			*/
			boost::shared_ptr<void> userEntryPos = encodedUser->GetElementAt(5);
					
			if (userEntryPos != NULL)
			{
				((boost::static_pointer_cast<SFSUser>)(newUser))->AOIEntryPoint(Vec3D::fromArray(encodedUser->GetWrappedElementAt(5)->Type(), userEntryPos));
			}
		}
	}

	boost::shared_ptr<MMORoom> mmoRoom = ((boost::static_pointer_cast<MMORoom>)(theRoom));
			
	// If there are items to remove simply pass the list of MMOItem ids
	if (minusItemList != NULL)
	{
		vector<long int>::iterator iteratormiMinusItemList;
		for (iteratormiMinusItemList = minusItemList->begin(); iteratormiMinusItemList != minusItemList->end(); iteratormiMinusItemList++)
		{
			boost::shared_ptr<IMMOItem> mmoItem = mmoRoom->GetMMOItem(*iteratormiMinusItemList);
					
			if (mmoItem != NULL)
			{
				// Remove from Room Item list
				mmoRoom->RemoveItem(*iteratormiMinusItemList);
						
				// Add to event list
				removedItems->push_back(mmoItem);	
			}
		}
	}

	// Prepare a list of new MMOItems in view
	if (plusItemList != NULL)
	{
		for (long int i = 0; i < plusItemList->Size(); i++)
		{
			boost::shared_ptr<ISFSArray> encodedItem = plusItemList->GetSFSArray(i);
					
			// Create the MMO Item with the server side ID (Index = 0 of the SFSArray)
			boost::shared_ptr<IMMOItem> newItem = MMOItem::FromSFSArray(encodedItem);
					
			// Add to event list
			addedItems->push_back(newItem);
					
			// Add to Room Item List
			mmoRoom->AddMMOItem(newItem);
					
			/*
			* From the encoded Item (as SFSArray) we extract the 2nd extra/optional parameter 
			* which contains its location on the map, or the AOIEntryPoint as we will refer to it
			*/
			boost::shared_ptr<void> itemEntryPos = encodedItem->GetElementAt(2);
					
			if (itemEntryPos != NULL)
				((boost::static_pointer_cast<MMOItem>)(newItem))->AOIEntryPoint (Vec3D::fromArray(encodedItem->GetWrappedElementAt(2)->Type(), itemEntryPos));
		}
	}

	// Prepare and dispatch!
	evtParams->insert(pair<string, boost::shared_ptr<void> >("addedItems", addedItems));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("removedItems", removedItems));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("removedUsers", removedUsers));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("addedUsers", addedUsers));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("room", ((boost::static_pointer_cast<MMORoom>)(theRoom))));

	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PROXIMITY_LIST_UPDATE, evtParams));
	instance->sfs->DispatchEvent(evt);
}

void SystemController::FnSetMMOItemVariables(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	boost::shared_ptr<ISFSObject> sfso = msg->Content();

	long int roomId = *(sfso->GetInt(SetMMOItemVariables::KEY_ROOM_ID));
	long int mmoItemId = *(sfso->GetInt(SetMMOItemVariables::KEY_ITEM_ID));
	boost::shared_ptr<ISFSArray> varList = sfso->GetSFSArray(SetMMOItemVariables::KEY_VAR_LIST);
			
	boost::shared_ptr<MMORoom> mmoRoom = ((boost::static_pointer_cast<MMORoom>)(instance->sfs->GetRoomById(roomId)));
	boost::shared_ptr<vector<string> > changedVarNames (new vector<string>());
			
	if (mmoRoom != NULL)
	{
		boost::shared_ptr<IMMOItem> mmoItem = mmoRoom->GetMMOItem(mmoItemId);
			
		if (mmoItem != NULL)
		{
			for (long int i = 0; i < varList->Size(); i++)
			{
				boost::shared_ptr<IMMOItemVariable> itemVar = MMOItemVariable::FromSFSArray(varList->GetSFSArray(i));
				mmoItem->SetVariable(itemVar);
						
				changedVarNames->push_back(*(itemVar->Name()));
			}
					
			evtParams->insert(pair<string, boost::shared_ptr<void> >("changedVars", changedVarNames));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("mmoItem", mmoItem));
			evtParams->insert(pair<string, boost::shared_ptr<void> >("room", mmoRoom));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::MMOITEM_VARIABLES_UPDATE, evtParams));
			instance->sfs->DispatchEvent(evt);
		}
	}
}

void SystemController::PopulateRoomList(boost::shared_ptr<ISFSArray> roomList)
{
	boost::shared_ptr<IRoomManager> roomManager = sfs->RoomManager();
			
	// Cycle through each room object
	for (int j = 0; j < roomList->Size(); j++) 
	{
		boost::shared_ptr<ISFSArray> roomObj = roomList->GetSFSArray(j);
		boost::shared_ptr<Room> newRoom = SFSRoom::FromSFSArray(roomObj);
		roomManager->ReplaceRoom(newRoom);
	}
}

void SystemController::FnGenericMessage(unsigned long long context, boost::shared_ptr<IMessage> msg)
{
	// Map context
	SystemController* instance = (SystemController*)context;

	boost::shared_ptr<ISFSObject> sfso = msg->Content();
	long int msgType = *(sfso->GetByte(GenericMessageRequest::KEY_MESSAGE_TYPE));

	switch ((GenericMessageType)msgType) {
	case GENERICMESSAGETYPE_PUBLIC_MSG:
		instance->HandlePublicMessage(sfso);
		break;
	case GENERICMESSAGETYPE_PRIVATE_MSG:
		instance->HandlePrivateMessage(sfso);
		break;
	case GENERICMESSAGETYPE_BUDDY_MSG:
		instance->HandleBuddyMessage(sfso);
		break;
	case GENERICMESSAGETYPE_MODERATOR_MSG:
		instance->HandleModMessage(sfso);
		break;
	case GENERICMESSAGETYPE_ADMIN_MSG:
		instance->HandleAdminMessage(sfso);
		break;
	case GENERICMESSAGETYPE_OBJECT_MSG:
		instance->HandleObjectMessage(sfso);
		break;
	}
}

void SystemController::HandlePublicMessage(boost::shared_ptr<ISFSObject> sfso)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());

	long int rId = *(sfso->GetInt(GenericMessageRequest::KEY_ROOM_ID));
	boost::shared_ptr<Room> room = sfs->RoomManager()->GetRoomById(rId);

	if (room != NULL) {
		evtParams->insert(pair<string, boost::shared_ptr<void> >("room", room));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("sender", sfs->UserManager()->GetUserById(*(sfso->GetInt(GenericMessageRequest::KEY_USER_ID)))));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("message", sfso->GetUtfString(GenericMessageRequest::KEY_MESSAGE)));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("data", sfso->GetSFSObject(GenericMessageRequest::KEY_XTRA_PARAMS)));

		// Fire event
		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PUBLIC_MESSAGE, evtParams));
		sfs->DispatchEvent(evt);
	}
	else {
		char buffer[512];
		sprintf (buffer, "Unexpected, PublicMessage target room doesn't exist. RoomId: %ld", rId);
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		log->Warn(logMessages);
	}
}

void SystemController::HandlePrivateMessage(boost::shared_ptr<ISFSObject> sfso)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	long int senderId = *(sfso->GetInt(GenericMessageRequest::KEY_USER_ID));

	// See if user exists locally
	boost::shared_ptr<User> sender = sfs->UserManager()->GetUserById(senderId);

	// Not found locally, see if user details where passed by the Server
	if (sender == NULL) {
		if (!sfso->ContainsKey(GenericMessageRequest::KEY_SENDER_DATA)) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("Unexpected. Private message has no Sender details!");
			log->Warn(logMessages);

			return;
		}

		sender = SFSUser::FromSFSArray(sfso->GetSFSArray(GenericMessageRequest::KEY_SENDER_DATA));
	}

	evtParams->insert(pair<string, boost::shared_ptr<void> >("sender", sender));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("message", sfso->GetUtfString(GenericMessageRequest::KEY_MESSAGE)));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("data", sfso->GetSFSObject(GenericMessageRequest::KEY_XTRA_PARAMS)));

	// Fire event
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::PRIVATE_MESSAGE, evtParams));
	sfs->DispatchEvent(evt);
}

void SystemController::HandleBuddyMessage(boost::shared_ptr<ISFSObject> sfso)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	boost::shared_ptr<long int> senderId = sfso->GetInt(GenericMessageRequest::KEY_USER_ID);

	/*
	* Look for Buddy
	* NOTE: There is a possible situation in which this could result null.
	* 
	* When there's no mutual Buddy adding (default) and the receiver doesn't have the sender in his BList
	* If your turn on the useTempBuddy feature, a Temp Buddy will be added to the BList before the message arrives
	*/
	boost::shared_ptr<Buddy> senderBuddy = sfs->BuddyManager()->GetBuddyById(*senderId);

	boost::shared_ptr<bool> isItMeValue (new bool());
	*isItMeValue = sfs->MySelf()->Id() == (*senderId);
	evtParams->insert(pair<string, boost::shared_ptr<void> >("isItMe", isItMeValue));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("buddy", senderBuddy));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("message", sfso->GetUtfString(GenericMessageRequest::KEY_MESSAGE)));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("data", sfso->GetSFSObject(GenericMessageRequest::KEY_XTRA_PARAMS)));

	// Fire event
	boost::shared_ptr<SFSBuddyEvent> evt (new SFSBuddyEvent(SFSBuddyEvent::BUDDY_MESSAGE, evtParams));
	sfs->DispatchEvent(evt);
}

void SystemController::HandleModMessage(boost::shared_ptr<ISFSObject> sfso)
{
	HandleModMessage(sfso, SFSEvent::MODERATOR_MESSAGE);
}

void SystemController::HandleAdminMessage(boost::shared_ptr<ISFSObject> sfso)
{
	HandleModMessage(sfso, SFSEvent::ADMIN_MESSAGE);
}

void SystemController::HandleModMessage(boost::shared_ptr<ISFSObject> sfso, boost::shared_ptr<string> evt)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
			
	evtParams->insert(pair<string, boost::shared_ptr<void> >("sender", SFSUser::FromSFSArray(sfso->GetSFSArray(GenericMessageRequest::KEY_SENDER_DATA))));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("message", sfso->GetUtfString(GenericMessageRequest::KEY_MESSAGE)));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("data", sfso->GetSFSObject(GenericMessageRequest::KEY_XTRA_PARAMS)));

	// Fire event
	boost::shared_ptr<SFSEvent> firedEvent (new SFSEvent(evt, evtParams));
	sfs->DispatchEvent(firedEvent);
}

void SystemController::HandleObjectMessage(boost::shared_ptr<ISFSObject> sfso)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	long int senderId = *(sfso->GetInt(GenericMessageRequest::KEY_USER_ID));

	evtParams->insert(pair<string, boost::shared_ptr<void> >("sender", sfs->UserManager()->GetUserById(senderId)));
	evtParams->insert(pair<string, boost::shared_ptr<void> >("message", sfso->GetSFSObject(GenericMessageRequest::KEY_XTRA_PARAMS)));

	// Fire event
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::OBJECT_MESSAGE, evtParams));
	sfs->DispatchEvent(evt);
}

}	// namespace Controllers
}	// namespace Sfs2X
