// ===================================================================
//
// Description		
//		Contains the definition of SFSRoomManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSRoomManager__
#define __SFSRoomManager__

#include "IRoomManager.h"
#include "../../SmartFox.h"
#include "../Room.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	// -------------------------------------------------------------------
	// Class SFSRoomManager
	// -------------------------------------------------------------------
	class SFSRoomManager : public IRoomManager
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSRoomManager(boost::shared_ptr<SmartFox> sfs);
		virtual ~SFSRoomManager();
		boost::shared_ptr<string> OwnerZone();
		void OwnerZone(string value);
		boost::shared_ptr<SmartFox> SmartFoxClient();
		void AddRoom(boost::shared_ptr<Room> room);
		void AddRoom(boost::shared_ptr<Room> room, bool addGroupIfMissing);
		boost::shared_ptr<Room> ReplaceRoom(boost::shared_ptr<Room> room);
		boost::shared_ptr<Room> ReplaceRoom(boost::shared_ptr<Room> room, bool addToGroupIfMissing);
		void ChangeRoomName(boost::shared_ptr<Room> room, string newName);
		void ChangeRoomPasswordState(boost::shared_ptr<Room> room, bool isPassProtected);
		void ChangeRoomCapacity(boost::shared_ptr<Room> room, long int maxUsers, long int maxSpect);
		boost::shared_ptr<vector<string> > GetRoomGroups();
		void AddGroup(string groupId);
		void RemoveGroup(string groupId);
		bool ContainsGroup(string groupId);
		bool ContainsRoom(boost::shared_ptr<void> idOrName);
		bool ContainsRoomInGroup(boost::shared_ptr<void> idOrName, string groupId);
		boost::shared_ptr<Room> GetRoomById(long int id);
		boost::shared_ptr<Room> GetRoomByName(string name);
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetRoomList();
		long int GetRoomCount();
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetRoomListFromGroup(string groupId);
		void RemoveRoom(boost::shared_ptr<Room> room);
		void RemoveRoomById(long int id);
		void RemoveRoomByName(string name);

		/// <summary>
		/// Return rooms joined by local user
		/// </summary>
		/// <returns>
		/// A vector of <see cref="Room"/> pointers
		/// </returns>		boost::shared_ptr<vector<boost::shared_ptr<Room>>> GetJoinedRooms();
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetJoinedRooms();

		boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetUserRooms(boost::shared_ptr<User> user);
		void RemoveUser(boost::shared_ptr<User> user);
		
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

		boost::shared_ptr<SmartFox> smartFox;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		void RemoveRoom(long int id, string name);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<string> ownerZone;
		vector<string> groups;
		map<long int, boost::shared_ptr<Room> > roomsById;
		map<string, boost::shared_ptr<Room> > roomsByName;
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
