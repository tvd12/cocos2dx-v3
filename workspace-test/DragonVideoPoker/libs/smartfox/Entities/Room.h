// ===================================================================
//
// Description		
//		Contains the definition of Room interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Room__
#define __Room__

namespace Sfs2X {
namespace Entities {
	class Room;
}	// namespace Entities
}	// namespace Sfs2X

#include "User.h"
#include "../Util/Common.h"
#include "Variables/RoomVariable.h"
#include "Managers/IRoomManager.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Managers;
using namespace Sfs2X::Entities::Variables;

namespace Sfs2X {
namespace Entities {

	class DLLImportExport Room
	{
	public:

		/// <summary>
		/// The unique Id of the Room
		/// </summary>
		virtual long int Id() = 0;
		
		/// <summary>
		/// The unique name of the Room
		/// </summary>
		virtual boost::shared_ptr<string> Name() = 0;

		/// <summary>
		/// The unique name of the Room
		/// </summary>
		virtual void Name(string value) = 0;

		/// <summary>
		/// The Room <b>Group</b> name
		/// </summary>
		/// <remarks>
		/// Each <b>Group</b> is identified by a unique String and it represent a different 'container' for Rooms.
		/// The idea behind the Room Groups is to enable the developer to organize Rooms under different types or categories and let clients select only those Groups they are interested in.
        /// This is done via the <c>SubscribeRoomGroupRequest</c> and <c>UnsubscribeRoomGroupRequest</c> requests.
		/// </remarks>
		/// 
		/// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
        /// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
		virtual boost::shared_ptr<string> GroupId() = 0;

		/// <summary>
		/// Returns true if the Room is joined by the client User
		/// </summary>
		virtual bool IsJoined() = 0;

		/// <summary>
		/// Returns true if the Room is joined by the client User
		/// </summary>
		virtual void IsJoined(bool value) = 0;

		/// <summary>
		/// Returns true is this is a game Room
		/// </summary>
		virtual bool IsGame() = 0;

		/// <summary>
		/// Returns true is this is a game Room
		/// </summary>
		virtual void IsGame(bool value) = 0;

		/// <summary>
		/// Returns true if the Room <b>hidden</b> flag is turned on.
		/// </summary>
		/// <remarks>
		/// The flag can be used to hide the rooms marked with this flag from the User  
		/// </remarks>
		virtual bool IsHidden() = 0;

		/// <summary>
		/// Returns true if the Room <b>hidden</b> flag is turned on.
		/// </summary>
		/// <remarks>
		/// The flag can be used to hide the rooms marked with this flag from the User  
		/// </remarks>
		virtual void IsHidden(bool value) = 0;

		/// <summary>
		/// Returns true if the Room requires a password to be joined
		/// </summary>
		virtual bool IsPasswordProtected() = 0;

		/// <summary>
		/// Returns true if the Room requires a password to be joined
		/// </summary>
		virtual void IsPasswordProtected(bool value) = 0;

		virtual bool IsManaged() = 0;

		virtual void IsManaged(bool value) = 0;

		/// <summary>
		/// Get the number of Users in the Room
		/// </summary>
		virtual long int UserCount() = 0;

		/// <summary>
		/// Get the number of Users in the Room
		/// </summary>
		virtual void UserCount(long int value) = 0;

		/// <summary>
		/// Get the max number of Users allowed in the Room
		/// </summary>
		virtual long int MaxUsers() = 0;

		/// <summary>
		/// Get the max number of Users allowed in the Room
		/// </summary>
		virtual void MaxUsers(long int value) = 0;

		/// <summary>
		/// Get the number of Spectators in the Room (applies only for game Rooms)
		/// </summary>
		virtual long int SpectatorCount() = 0;

		/// <summary>
		/// Get the number of Spectators in the Room (applies only for game Rooms)
		/// </summary>
		virtual void SpectatorCount(long int value) = 0;

		/// <summary>
		/// Get the max number of Spectators allowed in the Room (applies only for game Rooms)
		/// </summary>
		virtual long int MaxSpectators() = 0;

		/// <summary>
		/// Get the max number of Spectators allowed in the Room (applies only for game Rooms)
		/// </summary>
		virtual void MaxSpectators(long int value) = 0;

		// ???????????????????????????????????????
		virtual long int Capacity() = 0;
		
		virtual void AddUser(boost::shared_ptr<User> user) = 0;

		virtual void RemoveUser(boost::shared_ptr<User> user) = 0; 
		
		/// <summary>
		/// Returns true if the the User is found in this Room
		/// </summary>
		/// <param name="user">
		/// Pointer to an <see cref="User"/> instance
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool ContainsUser(boost::shared_ptr<User> user) = 0;
		
		/// <summary>
		/// Finds a User from its name
		/// </summary>
		/// <param name="name">
		/// the User name
		/// </param>
		/// <returns>
		/// the User or null if not found
		/// </returns>
		virtual boost::shared_ptr<User> GetUserByName(string name) = 0;

		/// <summary>
		/// Finds a User from its Id
		/// </summary>
		/// <param name="id">
		/// the User Id
		/// </param>
		/// <returns>
		/// the User or null if not found
		/// </returns>
		virtual boost::shared_ptr<User> GetUserById(long int id) = 0;
		
		/// <summary>
		/// The Room User-list
		/// </summary>
		virtual boost::shared_ptr<vector<boost::shared_ptr<User> > > UserList() = 0;
		
		/// <summary>
		/// Gets a RoomVariable in the Room
		/// </summary>
		/// <param name="name">
		/// the variable name
		/// </param>
		/// <returns>
		/// the RoomVariable or null if the variable doesn't exist
		/// </returns>
		/// <seealso cref="RoomVariable"/>
		virtual boost::shared_ptr<RoomVariable> GetVariable(string name) = 0;
		
		/// <summary>
		/// Return the full list of RoomVariables in the Room 
		/// </summary>
		/// <returns>
		/// A vector of <see cref="RoomVariable"/> pointers
		/// </returns>
		/// <seealso cref="RoomVariable"/>
		virtual boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > GetVariables() = 0;
		
		virtual void SetVariable(boost::shared_ptr<RoomVariable> roomVariable) = 0;
		
		void SetVariables(boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables);
		
		/// <summary>
		/// Returns true if a RoomVariable with the passed name exists in the Room
		/// </summary>
		/// <param name="name">
		/// A string 
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		/// <seealso cref="RoomVariable"/>
		virtual bool ContainsVariable(string name) = 0;
		
		/// <summary>
		/// A generic object that can be used to store any Room custom data needed at runtime.
		/// </summary>
		/// <remarks>
		/// The values added/removed in this object are for client side use only an are never transmitted to the Server.
		/// </remarks>
		virtual boost::shared_ptr<map<string, string> > Properties() = 0;

		/// <summary>
		/// A generic object that can be used to store any Room custom data needed at runtime.
		/// </summary>
		/// <remarks>
		/// The values added/removed in this object are for client side use only an are never transmitted to the Server.
		/// </remarks>
		virtual void Properties(boost::shared_ptr<map<string, string> > value) = 0;

		/// <summary>
		/// A reference to the RoomManager, managing this Room
		/// </summary>
		virtual boost::shared_ptr<IRoomManager> RoomManager() = 0;

		/// <summary>
		/// A reference to the RoomManager, managing this Room
		/// </summary>
		virtual void RoomManager(boost::shared_ptr<IRoomManager> value) = 0;

		virtual void Merge(boost::shared_ptr<Room> anotherRoom) = 0;
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
