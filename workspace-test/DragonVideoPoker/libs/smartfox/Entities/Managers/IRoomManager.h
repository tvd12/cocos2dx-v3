// ===================================================================
//
// Description		
//		Contains the definition of IRoomManager interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IRoomManager__
#define __IRoomManager__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Managers {
	class IRoomManager;
}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#include "../Room.h"
#include "../../SmartFox.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	/// <summary>
	/// The Room Manager interface
	/// </summary>
	class DLLImportExport IRoomManager
	{
	public:
		virtual boost::shared_ptr<string> OwnerZone() = 0;
		virtual void AddRoom(boost::shared_ptr<Room> room, bool addGroupIfMissing) = 0;
		virtual void AddRoom(boost::shared_ptr<Room> room) = 0;
		virtual void AddGroup(string groupId) = 0;
		virtual boost::shared_ptr<Room> ReplaceRoom(boost::shared_ptr<Room> room, bool addToGroupIfMissing) = 0;
		virtual boost::shared_ptr<Room> ReplaceRoom(boost::shared_ptr<Room> room) = 0;
		virtual void RemoveGroup(string groupId) = 0;
		virtual bool ContainsGroup(string groupId) = 0;
		virtual bool ContainsRoom(boost::shared_ptr<void> idOrName) = 0;
		virtual bool ContainsRoomInGroup(boost::shared_ptr<void> idOrName, string groupId) = 0;
		virtual void ChangeRoomName(boost::shared_ptr<Room> room, string newName) = 0;
		virtual void ChangeRoomPasswordState(boost::shared_ptr<Room> room, bool isPassProtected) = 0;
		virtual void ChangeRoomCapacity(boost::shared_ptr<Room> room, long int maxUsers, long int maxSpect) = 0;
		virtual boost::shared_ptr<Room> GetRoomById(long int id) = 0;
		virtual boost::shared_ptr<Room> GetRoomByName(string name) = 0;
		virtual boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetRoomList() = 0;
		virtual long int GetRoomCount() = 0;
		virtual boost::shared_ptr<vector<string> > GetRoomGroups() = 0;
		virtual boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetRoomListFromGroup(string groupId) = 0;
		virtual boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetJoinedRooms() = 0;
		virtual boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetUserRooms(boost::shared_ptr<User> user) = 0;
		virtual void RemoveRoom(boost::shared_ptr<Room> room) = 0;
		virtual void RemoveRoomById(long int id) = 0;
		virtual void RemoveRoomByName(string name) = 0;
		virtual void RemoveUser(boost::shared_ptr<User> user) = 0;
		virtual boost::shared_ptr<SmartFox> SmartFoxClient() = 0;
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
