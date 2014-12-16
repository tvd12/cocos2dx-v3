// ===================================================================
//
// Description		
//		Contains the definition of SFSGameSettings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSGameSettings__
#define __SFSGameSettings__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../RoomSettings.h"
#include "../../Entities/Room.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Match/MatchExpression.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Match;

namespace Sfs2X {
namespace Requests {
namespace Game {

	/// <summary>
	/// This class provides all the settings required to create an <b>SFSGame(*)</b>.
	/// </summary>
	/// <remarks>
	/// The <b>SFSGame(*)</b> object extends the <b>Room</b> object providing new advanced features such as Player matching, Game invitations, public and private Games, quick game joining etc... 
	/// <para/>
	/// (*) = the SFSGame class exists only on the server side as extension of the SFSRoom class. On the client side it's seen as a regular Room.
	/// <para/>
	/// <h3>Overview</h3>
	/// This is a quick overview of the settings that you can use to setup an <b>SFSGame</b>
	/// <ul>
	/// 		<li>
	/// 			<b>isGamePublic</b>: a public game can be joined by any Player whose variables match the SFSGame Player Match Expression.
	/// 			Private games are based on invitations sent by the Game creator.
	/// 		</li>
	/// 
	/// 		<li>
	/// 			<b>minPlayersToStartGame</b>: the minimum number of players to start the game.
	/// 		</li>
	/// 
	/// 		<li>
	/// 			<b>invitedPlayers</b>: (private games only) a list of players invited in the Game
	/// 		</li>
	/// 		
	/// 		<li>
	/// 			<b>searchableRooms</b>: (private games only) a list of Rooms where the Game API can search for more players to invite. 
	/// 			The API will look for more players if the number of people invited is smaller than the <b>minPlayersToStartGame</b>. This way you can add your friends to the game and let the system find more players to start it.
	/// 		</li>
	/// 		
	/// 		<li>
	/// 			<b>leaveLastJoinedRoom</b>: auto-remove players from their previous Room after successful join
	/// 		</li>
	/// 
	/// 		<li>
	/// 			<b>playerMatchExpression</b>: an expression to match players willing to play the game, by default no expression is used
	/// 		</li>
	/// 
	///		<li>
	/// 			<b>spectatorMatchExpression</b>: an expression to match spectators willing to play the game, by default no expression is used
	/// 		</li>	
	/// 
	/// 		<li>
	/// 			<b>invitationExpiryTime</b>: the amount of time allowed for invited players to accept / refuse
	/// 		</li>
	/// 		
	/// 		<li>
	/// 			<b>invitationParameters</b>: optional custom invitation parameters.These could provide details about the inviter, the game, an invitation message etc...
	/// 		</li>		
	/// 
	/// 		<li>
	/// 			<b>notifyGameStartedViaRoomVariable</b>: automatically update a reserved Room Variable to signal that the game is started/stopped. 
	/// 			The Room variable uses the <b>global</b> setting to be broadcast outside of the Room. This can be used on the client side to show the game state in your game list.
	/// 		</li>
	/// 
	/// </ul>
	/// </remarks>
	/// <seealso cref="CreateSFSGameRequest"/>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport SFSGameSettings : public RoomSettings
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		SFSGameSettings(string name);
		~SFSGameSettings();

		/// <summary>
		/// Check if the Game is public or private
		/// </summary>
		bool IsPublic();

		/// <summary>
		/// Check if the Game is public or private
		/// </summary>
		void IsPublic(bool value);

		/// <summary>
		/// The minimum number of players to start the Game
		/// </summary>
		long int MinPlayersToStartGame();
		
		/// <summary>
		/// The minimum number of players to start the Game
		/// </summary>
		void MinPlayersToStartGame(long int value);

		/// <summary>
		/// Private games only: the list of invited Players (an Array of Users)
		/// </summary>
		boost::shared_ptr<list<boost::shared_ptr<User> > > InvitedPlayersUser();

		/// <summary>
		/// Private games only: the list of invited Players (an Array of Users)
		/// </summary>
		void InvitedPlayersUser(boost::shared_ptr<list<boost::shared_ptr<User> > > value);

		/// <summary>
		/// Private games only: the list of invited Players (an Array of Users)
		/// </summary>
		boost::shared_ptr<list<boost::shared_ptr<Buddy> > > InvitedPlayersBuddy();

		/// <summary>
		/// Private games only: the list of invited Players (an Array of Users)
		/// </summary>
		void InvitedPlayersBuddy(boost::shared_ptr<list<boost::shared_ptr<Buddy> > > value);

		/// <summary>
		/// Private games only: An list of room groups (Array of String) where to search for more players
		/// </summary>
		boost::shared_ptr<list<boost::shared_ptr<string> > > SearchableRooms();

		/// <summary>
		/// Private games only: An list of room groups (Array of String) where to search for more players
		/// </summary>
		void SearchableRooms(boost::shared_ptr<list<boost::shared_ptr<string> > > value);

		/// <summary>
		/// The amount of time (in seconds) available for the User to reply to the invitation.
		/// </summary>
		/// <remarks>
		/// Suggested range 10-40 seconds
		/// </remarks>
		long int InvitationExpiryTime();

		/// <summary>
		/// The amount of time (in seconds) available for the User to reply to the invitation.
		/// </summary>
		/// <remarks>
		/// Suggested range 10-40 seconds
		/// </remarks>
		void InvitationExpiryTime(long int value);

		/// <summary>
		/// Determines if the Players will leave their previous Room when joining the Game
		/// </summary>
		bool LeaveLastJoinedRoom();

		/// <summary>
		/// Determines if the Players will leave their previous Room when joining the Game
		/// </summary>
		void LeaveLastJoinedRoom(bool value);

		/// <summary>
		/// Uses a "reserved" global Room Variable to notify the started/stopped status of the game.
		/// </summary>
		/// <remarks>
		/// This depends on the number of Users inside the Room.
		/// </remarks>
		/// <seealso cref="Entities.Variables.SFSRoomVariable"/>
		/// <seealso cref="Entities.Variables.ReservedRoomVariables"/>
		bool NotifyGameStarted();

		/// <summary>
		/// Uses a "reserved" global Room Variable to notify the started/stopped status of the game.
		/// </summary>
		/// <remarks>
		/// This depends on the number of Users inside the Room.
		/// </remarks>
		/// <seealso cref="Entities.Variables.SFSRoomVariable"/>
		/// <seealso cref="Entities.Variables.ReservedRoomVariables"/>
		void NotifyGameStarted(bool value);

		/// <summary>
		/// A MatchExpression for filtering Users joining the Game.
		/// </summary>
		/// <remarks>
		/// Recommended for public Games only
		/// </remarks>
		/// <seealso cref="MatchExpression"/>
		boost::shared_ptr<MatchExpression> PlayerMatchExpression();

		/// <summary>
		/// A MatchExpression for filtering Users joining the Game.
		/// </summary>
		/// <remarks>
		/// Recommended for public Games only
		/// </remarks>
		/// <seealso cref="MatchExpression"/>
		void PlayerMatchExpression(boost::shared_ptr<MatchExpression> value);

		/// <summary>
		/// A MatchExpression for filtering Spectators joining the Game.
		/// </summary>
		/// <seealso cref="MatchExpression"/>
		boost::shared_ptr<MatchExpression> SpectatorMatchExpression();

		/// <summary>
		/// A MatchExpression for filtering Spectators joining the Game.
		/// </summary>
		/// <seealso cref="MatchExpression"/>
		void SpectatorMatchExpression(boost::shared_ptr<MatchExpression> value);

		/// <summary>
		/// An optional custom object with parameters (e.g. a message, game details etc...)
		/// </summary>
		boost::shared_ptr<ISFSObject> InvitationParams();

		/// <summary>
		/// An optional custom object with parameters (e.g. a message, game details etc...)
		/// </summary>
		void InvitationParams(boost::shared_ptr<ISFSObject> value);

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

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		bool isPublic;
		long int minPlayersToStartGame;
		boost::shared_ptr<list<boost::shared_ptr<User> > > invitedPlayersUser;
		boost::shared_ptr<list<boost::shared_ptr<Buddy> > > invitedPlayersBuddy;
		boost::shared_ptr<list<boost::shared_ptr<string> > > searchableRooms;
		boost::shared_ptr<MatchExpression> playerMatchExpression;
		boost::shared_ptr<MatchExpression> spectatorMatchExpression;
		long int invitationExpiryTime; 
		bool leaveJoinedLastRoom;
		bool notifyGameStarted;
		boost::shared_ptr<ISFSObject> invitationParams;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
