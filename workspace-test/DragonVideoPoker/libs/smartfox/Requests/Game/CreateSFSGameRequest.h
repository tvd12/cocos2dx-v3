// ===================================================================
//
// Description		
//		Contains the definition of CreateSFSGameRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __CreateSFSGameRequest__
#define __CreateSFSGameRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../CreateRoomRequest.h"
#include "SFSGameSettings.h"
#include "InviteUsersRequest.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {
namespace Game {

	/// <summary>
	/// The request launches a new public or private game, including game invitations, player matching and a lot more.
	/// </summary>
	/// <remarks>
	/// The game is launched via the creation of an <b>SFSGame</b>, a specialized Room type that provides advanced features during the creation phase of a game. 
	/// <para/>
	/// A more in-depth overview of the SFS2X Game API is provided in the general documentation
	/// </remarks>
	/// <seealso cref="SFSGameSettings"/>
	class DLLImportExport CreateSFSGameRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="settings">
		/// the game Room settings
		/// </param>
		/// <example>
		///		\code{.cpp}
		/// 		// Prepare the settings for a public game
		///			boost::shared_ptr<vector<boost::shared_ptr<RoomVariable>>> collectionRoomVariables (new vector<boost::shared_ptr<RoomVariable>>());
		///			boost::shared_ptr<RoomVariable> variable (new SFSRoomVariable("desc", boost::shared_ptr<string>(new string("Darts game, public, bestScore > 100")), VARIABLETYPE_STRING));
		///			collectionRoomVariables->push_back(variable);
		///
		///			boost::shared_ptr<SFSGameSettings> settings (new SFSGameSettings("DartsGame"));
		///			settings->MaxUsers(2);
		///			settings->MaxSpectators(8);
		///			settings->IsPublic(true);
		///			settings->MinPlayersToStartGame(2);
		///			settings->NotifyGameStarted(true);
		///			settings->Variables(collectionRoomVariables);
		///
		/// 		// The Match expression for filtering users joining the Room
		///			boost::shared_ptr<long int> value (new long int());
		///			*value = 100;
		///			boost::shared_ptr<MatchExpression> expression (new MatchExpression("bestScore", NumberMatch::GREATER_THAN, value, MatchExpression::MatchExpressionValueType::MatchExpression_ValueOther));
		/// 		settings->PlayerMatchExpression(expression);
		///
		///			boost::shared_ptr<IRequest> request (new CreateSFSGameRequest(settings)); 
		///			ptrSmartFox->Send(request);
		///
		///		\endcode
		/// </example>
		/// <seealso cref="SFSGameSettings"/>
		/// <seealso cref="Entities.Match.MatchExpression"/>
		/// <seealso cref="Entities.Invitation.SFSInvitation"/>
		/// <seealso cref="Core.SFSEvent.ROOM_ADD"/>
		/// <seealso cref="Core.SFSEvent.ROOM_CREATION_ERROR"/>
		CreateSFSGameRequest(boost::shared_ptr<SFSGameSettings> settings);

		virtual ~CreateSFSGameRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_IS_PUBLIC;

		static boost::shared_ptr<string> KEY_MIN_PLAYERS;

		static boost::shared_ptr<string> KEY_INVITED_PLAYERS;

		static boost::shared_ptr<string> KEY_SEARCHABLE_ROOMS;

		static boost::shared_ptr<string> KEY_PLAYER_MATCH_EXP;

		static boost::shared_ptr<string> KEY_SPECTATOR_MATCH_EXP;

		static boost::shared_ptr<string> KEY_INVITATION_EXPIRY;

		static boost::shared_ptr<string> KEY_LEAVE_ROOM;

		static boost::shared_ptr<string> KEY_NOTIFY_GAME_STARTED;

		static boost::shared_ptr<string> KEY_INVITATION_PARAMS;

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

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<CreateRoomRequest> createRoomRequest;
		boost::shared_ptr<SFSGameSettings> settings;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
