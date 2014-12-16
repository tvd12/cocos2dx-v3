// ===================================================================
//
// Description		
//		Contains the definition of SystemController
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SystemController__
#define __SystemController__

// Forward class declaration
namespace Sfs2X {
namespace Controllers {
	class SystemController;
}	// namespace Controllers
}	// namespace Sfs2X

#include "../Bitswarm/BaseController.h"
#include "../Bitswarm/BitSwarmClient.h"
#include "../Bitswarm/IMessage.h"
#include "../Core/SFSEvent.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Entities/Data/ISFSArray.h"
#include "../Entities/Variables/RoomVariable.h"
#include "../Entities/Variables/SFSUserVariable.h"
#include "../Entities/Variables/SFSRoomVariable.h"
#include "../Entities/Invitation/Invitation.h"
#include "../Entities/Invitation/SFSInvitation.h"
#include "../Entities/User.h"
#include "../Entities/SFSUser.h"
#include "../Entities/Room.h"
#include "../Entities/SFSRoom.h"
#include "../Requests/Game/InviteUsersRequest.h"
#include "../Requests/RequestType.h"
#include "../Entities/Managers/IRoomManager.h"
#include "../Util/DelegateOneArgument.h"			// Delegate with one parameter
#include "../Requests/LoginRequest.h"
#include "../Requests/LogoutRequest.h"
#include "../Requests/CreateRoomRequest.h"
#include "../Requests/JoinRoomRequest.h"
#include "../Requests/SubscribeRoomGroupRequest.h"
#include "../Requests/GenericMessageRequest.h"
#include "../Requests/ChangeRoomNameRequest.h"
#include "../Requests/SetRoomVariablesRequest.h"
#include "../Requests/SetUserVariablesRequest.h"
#include "../Requests/UnsubscribeRoomGroupRequest.h"
#include "../Requests/ChangeRoomPasswordStateRequest.h"
#include "../Requests/ChangeRoomCapacityRequest.h"
#include "../Requests/SpectatorToPlayerRequest.h"
#include "../Requests/PlayerToSpectatorRequest.h"
#include "../Requests/FindRoomsRequest.h"
#include "../Requests/FindUsersRequest.h"
#include "../Requests/MMO/SetUserPositionRequest.h"
#include "../Requests/MMO/SetMMOItemVariables.h"
#include "../Util/SFSErrorCodes.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Core;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Variables;
using namespace Sfs2X::Entities::Invitation;
using namespace Sfs2X::Requests;
using namespace Sfs2X::Requests::Game;
using namespace Sfs2X::Requests::MMO;
using namespace Sfs2X::Util;
using namespace Sfs2X::Entities::Managers;

namespace Sfs2X {
namespace Controllers {

	typedef DelegateOneArgument<boost::shared_ptr<IMessage> > RequestDelegate;

	// -------------------------------------------------------------------
	// Class SystemController
	// -------------------------------------------------------------------
	class SystemController : public BaseController, public boost::enable_shared_from_this<SystemController>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		SystemController(boost::shared_ptr<BitSwarmClient> bitSwarm);
		virtual ~SystemController();
		void Initialize();

		void HandleMessage(boost::shared_ptr<IMessage> message);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		void InitRequestHandlers();

		//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Handlers
		//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		static void FnHandshake(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnLogin(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnCreateRoom(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnJoinRoom(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnUserEnterRoom(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnUserCountChange(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnUserLost(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnRoomLost(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnUserExitRoom(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnClientDisconnection(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSetRoomVariables(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSetUserVariables(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSubscribeRoomGroup(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnUnsubscribeRoomGroup(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnChangeRoomName(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnChangeRoomPassword(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnChangeRoomCapacity(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnLogout(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSetMMOItemVariables(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnReconnectionFailure(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSetUserPosition(unsigned long long context, boost::shared_ptr<IMessage> msg);

		boost::shared_ptr<User> GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj);
		boost::shared_ptr<User> GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj, bool addToGlobalManager);
		boost::shared_ptr<User> GetOrCreateUser(boost::shared_ptr<ISFSArray> userObj, bool addToGlobalManager, boost::shared_ptr<Room> room);

		static void FnSpectatorToPlayer(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnPlayerToSpectator(unsigned long long context, boost::shared_ptr<IMessage> msg);

		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// BuddyList Handlers
		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		static void FnInitBuddyList(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnAddBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnRemoveBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnBlockBuddy(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnGoOnline(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnSetBuddyVariables(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnFindRooms(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnFindUsers(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnInviteUsers(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnInvitationReply(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnQuickJoinGame(unsigned long long context, boost::shared_ptr<IMessage> msg);
		static void FnPingPong(unsigned long long context, boost::shared_ptr<IMessage> msg);

		void PopulateRoomList(boost::shared_ptr<ISFSArray> roomList);

		static void FnGenericMessage(unsigned long long context, boost::shared_ptr<IMessage> msg);
		void HandlePublicMessage(boost::shared_ptr<ISFSObject> sfso);
		void HandlePrivateMessage(boost::shared_ptr<ISFSObject> sfso);
		void HandleBuddyMessage(boost::shared_ptr<ISFSObject> sfso);
		void HandleModMessage(boost::shared_ptr<ISFSObject> sfso);
		void HandleAdminMessage(boost::shared_ptr<ISFSObject> sfso);
		void HandleModMessage(boost::shared_ptr<ISFSObject> sfso, boost::shared_ptr<string> evt);
		void HandleObjectMessage(boost::shared_ptr<ISFSObject> sfso);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		map <long int, boost::shared_ptr<RequestDelegate> > requestHandlers;
	};

}	// namespace Controllers
}	// namespace Sfs2X

#endif
