// ===================================================================
//
// Description		
//		Contains the definition of SFSRoom
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSRoom__
#define __SFSRoom__

#include "Data/ISFSArray.h"
#include "Room.h"
#include "./Managers/IRoomManager.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object 
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Managers;
using namespace Sfs2X::Entities::Variables;

using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {

	/// <summary>
	/// The <b>Room</b> object represent a server Room.
	/// </summary>
	/// <remarks>
	/// The client API don't know about all Rooms on the server side but only about those that are joined and those in the Room Groups that were subscribed.
	/// <para/>
	/// Subscribing to one or more Group allows the client to listen for Room events in specific "areas" of the Zone without having to know and download details for all Rooms available.
    /// <para/>
	/// The RoomList is created after a succesful login in the <c>SmartFox.RoomList</c> object and it is kept updated at all times by the Server.
	/// </remarks>
	/// <seealso cref="SmartFox.RoomList"/>
	/// <seealso cref="Requests.CreateRoomRequest"/>
    /// <seealso cref="Requests.JoinRoomRequest"/>
    /// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
    /// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
    /// <seealso cref="Requests.ChangeRoomNameRequest"/>
    /// <seealso cref="Requests.ChangeRoomPasswordStateRequest"/>
    /// <seealso cref="Requests.ChangeRoomCapacityRequest"/>
	class DLLImportExport SFSRoom : public Room, public boost::enable_shared_from_this<SFSRoom>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSRoom(long int id, string name);
		SFSRoom(long int id, string name, string groupId);
		virtual ~SFSRoom();
		static boost::shared_ptr<Room> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);
		long int Id();

		/// <summary>
		/// The Room name
		/// </summary>
		boost::shared_ptr<string> Name();

		/// <summary>
		/// The Room name
		/// </summary>
		void Name(string value);

		/// <summary>
		/// The Room Group. Each Room is assigned to its Group.
		/// </summary>
		/// <remarks>
		/// By default SmartFoxServer uses one single group called <i>default</i>
		/// </remarks>
		boost::shared_ptr<string> GroupId();

		/// <summary>
		/// Determines if a Room is a Game Room
		/// </summary>
		bool IsGame();

		/// <summary>
		/// Determines if a Room is a Game Room
		/// </summary>
		void IsGame(bool value);

		/// <summary>
		/// Determines if the Room is hidden
		/// </summary>
		bool IsHidden();

		/// <summary>
		/// Determines if the Room is hidden
		/// </summary>
		void IsHidden(bool value);

		/// <summary>
		/// Returns true if the Room is joined by the current User
		/// </summary>
		bool IsJoined();

		/// <summary>
		/// Returns true if the Room is joined by the current User
		/// </summary>
		void IsJoined(bool value);

		/// <summary>
		/// Returns true if the Room requires a password for joining it
		/// </summary>
		bool IsPasswordProtected();

		/// <summary>
		/// Returns true if the Room requires a password for joining it
		/// </summary>
		void IsPasswordProtected(bool value);

		bool IsManaged();

		void IsManaged(bool value);

		long int MaxSpectators();
		void MaxSpectators(long int value);

		boost::shared_ptr<map<string, string> > Properties();
		void Properties(boost::shared_ptr<map<string, string> > value);

		/// <summary>
		/// Returns all the Room Variables
		/// </summary>
		/// <returns>
		/// A vector of <see cref="RoomVariable"/> pointers
		/// </returns>
		boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > GetVariables();

		/// <summary>
		/// Get a Room Variable
		/// </summary>
		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <returns>
		/// the Room Variable, or null if no variable exists with that name
		/// </returns>
		boost::shared_ptr<RoomVariable> GetVariable(string name);

		/// <summary>
		/// Get the current number of users
		/// </summary>
		/// <remarks>
		/// If the room is joined the user count is taken from the Room's UserManager otherwise we return the static counter (which will work only if you have activated the uCount updates)
		/// </remarks>
		long int UserCount();

		/// <summary>
		/// Get the current number of users
		/// </summary>
		/// <remarks>
		/// If the room is joined the user count is taken from the Room's UserManager otherwise we return the static counter (which will work only if you have activated the uCount updates)
		/// </remarks>
		void UserCount(long int value);

		/// <summary>
		/// Get the maximum number of users allowed for this Room
		/// </summary>
		long int MaxUsers();

		/// <summary>
		/// Get the maximum number of users allowed for this Room
		/// </summary>
		void MaxUsers(long int value);

		/// <summary>
		/// Returns the max amount of users (both Users and Spectators) that can be contained in this room
		/// </summary>
		long int Capacity();

		/// <summary>
		/// Get the number of spectators (only for Game Rooms)
		/// </summary>
		long int SpectatorCount();

		/// <summary>
		/// Get the number of spectators (only for Game Rooms)
		/// </summary>
		void SpectatorCount(long int value);

		/// <summary>
		/// Get a User from its name
		/// </summary>
		/// <param name="name">
		/// A string pointer
		/// </param>
		/// <returns>
		/// the User, or null if no User with that name exists in the Room
		/// </returns>
		boost::shared_ptr<User> GetUserByName(string name);

		/// <summary>
		/// Get a User from its ID
		/// </summary>
		/// <param name="id">
		/// A long integer
		/// </param>
		/// <returns>
		/// the User, or null if no User with that ID exists in the Room
		/// </returns>
		boost::shared_ptr<User> GetUserById(long int id);

		/// <summary>
		/// Get the full list of users in the Room
		/// </summary>
		boost::shared_ptr<vector<boost::shared_ptr<User> > > UserList();

		boost::shared_ptr<vector<boost::shared_ptr<User> > > PlayerList();

		boost::shared_ptr<vector<boost::shared_ptr<User> > > SpectatorList();

		void RemoveUser(boost::shared_ptr<User> user);

		void SetVariable(boost::shared_ptr<RoomVariable> roomVariable);

		void SetVariables(boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables);

		/// <summary>
		/// Check for the presence of a Room Variable 
		/// </summary>
		/// <param name="name">
		/// A string pointer
		/// </param>
		/// <returns>
		/// true if the the Room Variable exists
		/// </returns>
		bool ContainsVariable(string name);

		void AddUser(boost::shared_ptr<User> user);

		/// <summary>
		/// Checks if a User is joined in this Room
		/// </summary>
		/// <param name="user">
		/// Pointer to an <see cref="User"/> instance
		/// </param>
		/// <returns>
		/// true if the User exists in the Room
		/// </returns>
		bool ContainsUser(boost::shared_ptr<User> user);

		boost::shared_ptr<IRoomManager> RoomManager();
		void RoomManager(boost::shared_ptr<IRoomManager> value);

		boost::shared_ptr<string> ToString();

		void Merge(boost::shared_ptr<Room> anotherRoom);

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

		long int id;
		boost::shared_ptr<string> name;
		boost::shared_ptr<string> groupId;
		bool isGame;
		bool isHidden;
		bool isJoined;
		bool isPasswordProtected;
		bool isManaged;
		boost::shared_ptr<map<string, boost::shared_ptr<RoomVariable> > > variables;
		boost::shared_ptr<map<string, string> > properties;
		boost::shared_ptr<IUserManager> userManager;
		long int maxUsers;
		long int maxSpectators;
		long int userCount; 				// only for non joined rooms
		long int specCount; 				// only for non joined rooms
		boost::shared_ptr<IRoomManager> roomManager;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		void Init(long int id, string name, string groupId);
		void RemoveUserVariable(string varName);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
