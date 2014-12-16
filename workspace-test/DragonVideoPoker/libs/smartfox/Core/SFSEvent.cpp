// ===================================================================
//
// Description		
//		Contains the implementation of SFSEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSEvent.h"

using namespace Sfs2X::Core;

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Core {

boost::shared_ptr<string> SFSEvent::HANDSHAKE (new string("handshake"));
boost::shared_ptr<string> SFSEvent::UDP_INIT (new string("udpInit"));
boost::shared_ptr<string> SFSEvent::CONNECTION (new string("connection"));
boost::shared_ptr<string> SFSEvent::PING_PONG (new string("pingPong"));
boost::shared_ptr<string> SFSEvent::SFS_SOCKET_ERROR (new string("socketError"));
boost::shared_ptr<string> SFSEvent::CONNECTION_LOST (new string("connectionLost"));
boost::shared_ptr<string> SFSEvent::CONNECTION_RETRY (new string("connectionRetry"));
boost::shared_ptr<string> SFSEvent::CONNECTION_RESUME (new string("connectionResume"));
boost::shared_ptr<string> SFSEvent::CONNECTION_ATTEMPT_HTTP (new string("connectionAttemptHttp"));
boost::shared_ptr<string> SFSEvent::CONFIG_LOAD_SUCCESS (new string("configLoadSuccess"));
boost::shared_ptr<string> SFSEvent::CONFIG_LOAD_FAILURE (new string("configLoadFailure"));
boost::shared_ptr<string> SFSEvent::LOGIN (new string("login"));
boost::shared_ptr<string> SFSEvent::LOGIN_ERROR (new string("loginError"));
boost::shared_ptr<string> SFSEvent::LOGOUT (new string("logout"));
boost::shared_ptr<string> SFSEvent::ROOM_ADD (new string("roomAdd"));
boost::shared_ptr<string> SFSEvent::ROOM_REMOVE (new string("roomRemove"));
boost::shared_ptr<string> SFSEvent::ROOM_CREATION_ERROR (new string("roomCreationError"));
boost::shared_ptr<string> SFSEvent::ROOM_JOIN (new string("roomJoin"));
boost::shared_ptr<string> SFSEvent::ROOM_JOIN_ERROR (new string("roomJoinError"));
boost::shared_ptr<string> SFSEvent::USER_ENTER_ROOM (new string("userEnterRoom"));
boost::shared_ptr<string> SFSEvent::USER_EXIT_ROOM (new string("userExitRoom"));
boost::shared_ptr<string> SFSEvent::USER_COUNT_CHANGE (new string("userCountChange"));
boost::shared_ptr<string> SFSEvent::PUBLIC_MESSAGE (new string("publicMessage"));
boost::shared_ptr<string> SFSEvent::PRIVATE_MESSAGE (new string("privateMessage"));
boost::shared_ptr<string> SFSEvent::MODERATOR_MESSAGE (new string("moderatorMessage"));
boost::shared_ptr<string> SFSEvent::ADMIN_MESSAGE (new string("adminMessage"));
boost::shared_ptr<string> SFSEvent::OBJECT_MESSAGE (new string("objectMessage"));
boost::shared_ptr<string> SFSEvent::EXTENSION_RESPONSE (new string("extensionResponse"));
boost::shared_ptr<string> SFSEvent::ROOM_VARIABLES_UPDATE (new string("roomVariablesUpdate"));
boost::shared_ptr<string> SFSEvent::USER_VARIABLES_UPDATE (new string("userVariablesUpdate"));
boost::shared_ptr<string> SFSEvent::ROOM_GROUP_SUBSCRIBE (new string("roomGroupSubscribe"));
boost::shared_ptr<string> SFSEvent::ROOM_GROUP_UNSUBSCRIBE (new string("roomGroupUnsubscribe"));
boost::shared_ptr<string> SFSEvent::ROOM_GROUP_SUBSCRIBE_ERROR (new string("roomGroupSubscribeError"));
boost::shared_ptr<string> SFSEvent::ROOM_GROUP_UNSUBSCRIBE_ERROR (new string("roomGroupUnsubscribeError"));
boost::shared_ptr<string> SFSEvent::SPECTATOR_TO_PLAYER (new string("spectatorToPlayer"));
boost::shared_ptr<string> SFSEvent::PLAYER_TO_SPECTATOR (new string("playerToSpectator"));
boost::shared_ptr<string> SFSEvent::SPECTATOR_TO_PLAYER_ERROR (new string("spectatorToPlayerError"));
boost::shared_ptr<string> SFSEvent::PLAYER_TO_SPECTATOR_ERROR (new string("playerToSpectatorError"));
boost::shared_ptr<string> SFSEvent::ROOM_NAME_CHANGE (new string("roomNameChange"));
boost::shared_ptr<string> SFSEvent::ROOM_NAME_CHANGE_ERROR (new string("roomNameChangeError"));
boost::shared_ptr<string> SFSEvent::ROOM_PASSWORD_STATE_CHANGE (new string("roomPasswordStateChange"));
boost::shared_ptr<string> SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR (new string("roomPasswordStateChangeError"));
boost::shared_ptr<string> SFSEvent::ROOM_CAPACITY_CHANGE (new string("roomCapacityChange"));
boost::shared_ptr<string> SFSEvent::ROOM_CAPACITY_CHANGE_ERROR (new string("roomCapacityChangeError"));
boost::shared_ptr<string> SFSEvent::ROOM_FIND_RESULT (new string("roomFindResult"));
boost::shared_ptr<string> SFSEvent::USER_FIND_RESULT (new string("userFindResult"));
boost::shared_ptr<string> SFSEvent::INVITATION (new string("invitation"));
boost::shared_ptr<string> SFSEvent::INVITATION_REPLY (new string("invitationReply"));
boost::shared_ptr<string> SFSEvent::INVITATION_REPLY_ERROR (new string("invitationReplyError"));
boost::shared_ptr<string> SFSEvent::DEBUG_MESSAGE (new string("debugMessage"));
boost::shared_ptr<string> SFSEvent::PROXIMITY_LIST_UPDATE (new string("proximityListUpdate"));
boost::shared_ptr<string> SFSEvent::MMOITEM_VARIABLES_UPDATE (new string("mmoItemVariablesUpdate"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSEvent::SFSEvent(boost::shared_ptr<string> type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSEvent::SFSEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > data)
	: BaseEvent (type, data)
{
}

}	// namespace Core
}	// namespace Sfs2X
