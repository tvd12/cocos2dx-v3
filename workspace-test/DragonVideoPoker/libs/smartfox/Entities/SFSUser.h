// ===================================================================
//
// Description		
//		Contains the definition of SFSUser
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSUser__
#define __SFSUser__

#include "User.h"
#include "Data/Vec3D.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object 
#include <list>							// STL library: list object
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Managers;
using namespace Sfs2X::Entities::Variables;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Entities {

	/// <summary>
	/// The <b>User</b> object represent a client logged in the Server.
    /// </summary>
    /// <remarks>
    /// The client API don't know about all Users connected to the server side but only about those that are in the same Rooms where the client is joined.
    /// <para/>
    /// In order to interact with other Users the client can join different Rooms or use a BuddyList to keep track of and interact with his friends.
    /// </remarks>	
	class DLLImportExport SFSUser : public User, public boost::enable_shared_from_this<SFSUser>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<User> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa, boost::shared_ptr<Room> room);
		static boost::shared_ptr<User> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		SFSUser(long int id, string name);
		SFSUser(long int id, string name, bool isItMe);
		virtual ~SFSUser();

		/// <summary>
		/// Get the unique User Id
		/// </summary>
		long int Id();
		
		/// <summary>
		/// The user name
		/// </summary>
		boost::shared_ptr<string> Name();

		/// <summary>
		/// Get the <b>playerId</b> of the User.
		/// </summary>
		/// <remarks>
		/// The <b>playerId</b> is different from the User ID and it used to indicate which player number is the user inside a Game Room.
		/// Example: in a Game Room for 5 players the first client joining will have <b>playerId = 1</b>, the 2nd will have <b>playerId = 2</b> and so forth. 
		/// When a User leaves the Room its player slot is freed up and the next User joining the Room will take it.
		/// 
		/// The <b>playerId</b> is only applicable for Game Rooms, in the other Rooms it is always == 0
		/// A playerId < 0 indicates that the User is a spectator.
		/// 
		/// If the User is joined in multiple game Rooms at the same time he will be assigned one <b>playerId</b> per Room.
		/// In order to obtain a specific <b>playerId</b> you can use the <c>User.GetPlayerId(Room room)</c> method.
		/// </remarks>
		long int PlayerId();
		
		/// <summary>
		/// Return true if the User is a Player (playerId > 0) in the last joined Room
		/// </summary>
		/// <remarks>
		/// Non game Rooms will always return false
		/// </remarks>
		/// <seealso cref="SmartFox.LastJoinedRoom"/>
		bool IsPlayer();
		
		/// <summary>
		/// Return true if the User is a Spectator (playerId < 0) in the last joined Room
		/// </summary>
		/// <remarks>
		/// Non game Rooms will always return false
		/// </remarks>
		/// <seealso cref="SmartFox.LastJoinedRoom"/>
		bool IsSpectator();
		
		/// <summary>
		/// Return the <b>playerId</b> for the specific Room.
		/// </summary>
		/// <remarks>
		/// If you don't use multi-room you can use <c>User.PlayerId</c>
		/// </remarks>
		/// <param name="room">
		/// Pointer to a <see cref="Room"/> instance
		/// </param>
		/// <returns>
		/// A long integer
		/// </returns>
		/// <seealso cref="PlayerId"/>
		long int GetPlayerId (boost::shared_ptr<Room> room);

		void SetPlayerId(long int id, boost::shared_ptr<Room> room);
		
		void RemovePlayerId(boost::shared_ptr<Room> room);

		/// <summary>
		/// Get the privilegeId of the User
		/// </summary>
		/// <seealso cref="UserPrivileges"/>
		long int PrivilegeId();

		/// <summary>
		/// Get the privilegeId of the User
		/// </summary>
		/// <seealso cref="UserPrivileges"/>
		void PrivilegeId(long int value);

		/// <summary>
		/// Get the UserManager of this User
		/// </summary>
		/// <seealso cref="SFSUserManager"/>
		boost::shared_ptr<IUserManager> UserManager();

		/// <summary>
		/// Get the UserManager of this User
		/// </summary>
		/// <seealso cref="SFSUserManager"/>
		void UserManager(boost::shared_ptr<IUserManager> value);

		/// <inheritdoc />
		boost::shared_ptr<Vec3D> AOIEntryPoint();

		/// <inheritdoc />
		void AOIEntryPoint(boost::shared_ptr<Vec3D> value);
		
		//--------------------------------------------------
		
		/// <summary>
		/// Return true if the User is logged in as guest user
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsGuest();
		
		/// <summary>
		/// Return true if the User is logged in as standard user
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsStandardUser();
		
		/// <summary>
		/// Return true if the User is logged in as moderator user
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsModerator();
				
		/// <summary>
		/// Return true if the User is logged in as administrator user
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsAdmin();
		
		/// <summary>
		/// Return true if the User is a Player in the specified Room
		/// </summary>
		/// <param name="room">
		/// Pointer to a <see cref="Room"/> instance
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsPlayerInRoom(boost::shared_ptr<Room> room);

		/// <summary>
		/// Return true if the User is a Spectator in the specified Room
		/// </summary>
		/// <param name="room">
		/// Pointer to a <see cref="Room"/> instance
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsSpectatorInRoom(boost::shared_ptr<Room> room);

		/// <summary>
		/// Return true if the User is joined in the specified Room
		/// </summary>
		/// <param name="room">
		/// Pointer to a <see cref="Room"/> instance
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		bool IsJoinedInRoom(boost::shared_ptr<Room> room);
		
		/// <summary>
		/// Return true if the User object is the client's User object, also known as <c>SmartFox.MySelf</c>
		/// </summary>
		bool IsItMe();
		
		/// <summary>
		/// Get all the User Variables
		/// </summary>
		/// <returns>
		/// A vector of <see cref="UserVariable"/> pointers
		/// </returns>
		/// <seealso cref="UserVariable"/>
		boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > GetVariables();
		
		/// <summary>
		/// Get a UserVariable
		/// </summary>
		/// <param name="varName">
		/// the name of the variable
		/// </param>
		/// <returns>
		/// the UserVariable or null if the variable doesn't exist
		/// </returns>
		/// <seealso cref="UserVariable"/>
		boost::shared_ptr<UserVariable> GetVariable(string varName);
		
		void SetVariable(boost::shared_ptr<UserVariable> userVariable);
		
		virtual void SetVariables(boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > userVaribles);
		
		/// <summary>
		/// Check if a UserVariable exists 
		/// </summary>
		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <returns>
		/// true if the UserVariable exists
		/// </returns>
		/// <seealso cref="UserVariable"/>
		bool ContainsVariable(string name);
		
		/// <summary>
		/// A generic object that can be used to store any User custom data needed at runtime.
		/// </summary>
		/// <remarks>
		/// The values added/removed in this object are for client side use only an are never transmitted to the Server.
		/// </remarks>
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > Properties();

		/// <summary>
		/// A generic object that can be used to store any User custom data needed at runtime.
		/// </summary>
		/// <remarks>
		/// The values added/removed in this object are for client side use only an are never transmitted to the Server.
		/// </remarks>
		void Properties(boost::shared_ptr<map<string, boost::shared_ptr<void> > > value);

		boost::shared_ptr<string> ToString();

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
		long int privilegeId;
		boost::shared_ptr<string> name;
		bool isItMe;
		boost::shared_ptr<map<string, boost::shared_ptr<UserVariable> > > variables;
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > properties;
		bool isModerator;
		boost::shared_ptr<map<long int, long int> > playerIdByRoomId;
		boost::shared_ptr<IUserManager> userManager;
		boost::shared_ptr<Vec3D> aoiEntryPoint;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		void Init(long int id, string name, bool isItMe);
		void RemoveUserVariable(string varName);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
