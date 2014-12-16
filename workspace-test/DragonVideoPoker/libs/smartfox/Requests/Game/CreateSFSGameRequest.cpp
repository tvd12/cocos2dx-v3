// ===================================================================
//
// Description		
//		Contains the implementation of CreateSFSGameRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "CreateSFSGameRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

boost::shared_ptr<string> CreateSFSGameRequest::KEY_IS_PUBLIC (new string("gip"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_MIN_PLAYERS (new string("gmp"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_INVITED_PLAYERS (new string("ginp"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_SEARCHABLE_ROOMS (new string("gsr"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_PLAYER_MATCH_EXP (new string("gpme"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_SPECTATOR_MATCH_EXP (new string("gsme"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_INVITATION_EXPIRY (new string("gie"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_LEAVE_ROOM (new string("glr"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_NOTIFY_GAME_STARTED (new string("gns"));
boost::shared_ptr<string> CreateSFSGameRequest::KEY_INVITATION_PARAMS (new string("ip"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
CreateSFSGameRequest::CreateSFSGameRequest(boost::shared_ptr<SFSGameSettings> settings)
	: BaseRequest (RequestType_CreateSFSGame)
{
	this->settings = settings;
	this->createRoomRequest = boost::shared_ptr<CreateRoomRequest>(new CreateRoomRequest(settings, false, boost::shared_ptr<Room>()));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
CreateSFSGameRequest::~CreateSFSGameRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void CreateSFSGameRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// First validate Room settings
	try {
		createRoomRequest->Validate(sfs);
	}
	catch(SFSValidationError err) {
		// Take the current errors and continue checking...
		errors = err.Errors();
	}

	if (settings->MinPlayersToStartGame() > settings->MaxUsers())
		errors->push_back("minPlayersToStartGame cannot be greater than maxUsers");

	if (settings->InvitationExpiryTime() < InviteUsersRequest::MIN_EXPIRY_TIME || settings->InvitationExpiryTime() > InviteUsersRequest::MAX_EXPIRY_TIME)
	{
		char buffer[512];
		sprintf (buffer, "Expiry time value is out of range (%ld-%ld)", InviteUsersRequest::MIN_EXPIRY_TIME, InviteUsersRequest::MAX_EXPIRY_TIME);
		string str = buffer;

		errors->push_back(str);
	}

	long int counterPlayers = 0;
	if (settings->InvitedPlayersUser() != NULL)
	{
		counterPlayers += (long int)(settings->InvitedPlayersUser()->size());
	}

	if (settings->InvitedPlayersBuddy() != NULL)
	{
		counterPlayers += (long int)(settings->InvitedPlayersBuddy()->size());
	}

	if (counterPlayers > InviteUsersRequest::MAX_INVITATIONS_FROM_CLIENT_SIDE)
	{
		char buffer[512];
		sprintf (buffer, "Cannot invite more than %ld players from client side", InviteUsersRequest::MAX_INVITATIONS_FROM_CLIENT_SIDE);
		string str = buffer;

		errors->push_back(str);
	}

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("CreateSFSGame request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void CreateSFSGameRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	// Execute the parent Request and grab the populated SFSObject
	createRoomRequest->Execute(sfs);
	sfso = createRoomRequest->Message()->Content();

	// Proceed populating the other fields in the child class
	boost::shared_ptr<bool> valueIsPublic (new bool());
	*valueIsPublic = settings->IsPublic();
	sfso->PutBool(KEY_IS_PUBLIC, valueIsPublic);

	boost::shared_ptr<short int> valueMinPlayersToStartGame (new short int());
	*valueMinPlayersToStartGame = (short int)(settings->MinPlayersToStartGame());
	sfso->PutShort(KEY_MIN_PLAYERS, (boost::static_pointer_cast<short int>)(valueMinPlayersToStartGame));

	boost::shared_ptr<short int> valueInvitationExpiryTime (new short int());
	*valueInvitationExpiryTime = (short int)(settings->InvitationExpiryTime());
	sfso->PutShort(KEY_INVITATION_EXPIRY, (boost::static_pointer_cast<short int>)(valueInvitationExpiryTime));
	
	boost::shared_ptr<bool> valueLeaveLastJoinedRoom (new bool());
	*valueLeaveLastJoinedRoom = settings->LeaveLastJoinedRoom();
	sfso->PutBool(KEY_LEAVE_ROOM, valueLeaveLastJoinedRoom);

	boost::shared_ptr<bool> valueNotifyGameStarted (new bool());
	*valueNotifyGameStarted = settings->NotifyGameStarted();
	sfso->PutBool(KEY_NOTIFY_GAME_STARTED, valueNotifyGameStarted);

	if (settings->PlayerMatchExpression() != NULL)
		sfso->PutSFSArray(KEY_PLAYER_MATCH_EXP, settings->PlayerMatchExpression()->ToSFSArray());

	if (settings->SpectatorMatchExpression() != NULL)
		sfso->PutSFSArray(KEY_SPECTATOR_MATCH_EXP, settings->SpectatorMatchExpression()->ToSFSArray());

	// Invited players
	if ((settings->InvitedPlayersUser() != NULL) || (settings->InvitedPlayersBuddy() != NULL)) {
		boost::shared_ptr<vector<boost::shared_ptr<long int> > > playerIds (new vector<boost::shared_ptr<long int> >());

		list<boost::shared_ptr<User> >::iterator iteratorUsers;
		list<boost::shared_ptr<Buddy> >::iterator iteratorBuddy;

		for (iteratorUsers = settings->InvitedPlayersUser()->begin(); iteratorUsers != settings->InvitedPlayersUser()->end(); iteratorUsers++)
		{
			boost::shared_ptr<User> player = (*iteratorUsers);

			boost::shared_ptr<long int> valueId (new long int());
			*valueId = player->Id();
			playerIds->push_back(valueId);
		} 

		for (iteratorBuddy = settings->InvitedPlayersBuddy()->begin(); iteratorBuddy != settings->InvitedPlayersBuddy()->end(); iteratorBuddy++)
		{
			boost::shared_ptr<Buddy> player = (*iteratorBuddy);

			boost::shared_ptr<long int> valueId (new long int());
			*valueId = player->Id();
			playerIds->push_back(valueId);
		} 

		sfso->PutIntArray(KEY_INVITED_PLAYERS, playerIds);
	}

	// Searchable rooms
	if (settings->SearchableRooms() != NULL)
	{
		boost::shared_ptr<vector<boost::shared_ptr<string> > > searchableRooms (new vector<boost::shared_ptr<string> >(settings->SearchableRooms()->begin(), settings->SearchableRooms()->end()));
		sfso->PutUtfStringArray(KEY_SEARCHABLE_ROOMS, searchableRooms);
	}

	// Invitation params
	if (settings->InvitationParams() != NULL)
		sfso->PutSFSObject(KEY_INVITATION_PARAMS, settings->InvitationParams());
}

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X


