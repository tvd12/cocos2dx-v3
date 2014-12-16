// ===================================================================
//
// Description		
//		Contains the implementation of SFSRoomManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSRoomManager.h"
#include <typeinfo>

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomManager::SFSRoomManager(boost::shared_ptr<SmartFox> sfs)
{
	smartFox = sfs;
	ownerZone = boost::shared_ptr<string>();
	groups.clear();
	roomsById.clear();
	roomsByName.clear();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSRoomManager::~SFSRoomManager()
{
}

// -------------------------------------------------------------------
// OwnerZone
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomManager::OwnerZone()
{
	return ownerZone;
}

// -------------------------------------------------------------------
// OwnerZone
// -------------------------------------------------------------------
void SFSRoomManager::OwnerZone(string value)
{
	ownerZone = boost::shared_ptr<string>(new string(value));
}

// -------------------------------------------------------------------
// SmartFoxClient
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> SFSRoomManager::SmartFoxClient()
{
	return smartFox;
}

// -------------------------------------------------------------------
// AddRoom
// -------------------------------------------------------------------
void SFSRoomManager::AddRoom(boost::shared_ptr<Room> room)
{
	AddRoom(room, true);
}

// -------------------------------------------------------------------
// AddRoom
// -------------------------------------------------------------------
void SFSRoomManager::AddRoom(boost::shared_ptr<Room> room, bool addGroupIfMissing)
{
	roomsById.insert(pair<long int, boost::shared_ptr<Room> >(room->Id(), room));
	roomsByName.insert(pair<string, boost::shared_ptr<Room> >(*room->Name(), room));

	// If group is not known, add it to the susbscribed list
	if (addGroupIfMissing) 
	{
		if (!ContainsGroup(*(room->GroupId()))) 
		{
			AddGroup(*(room->GroupId()));
		}
	}
			
	/*
	* We don't add a group that was not subscribed
	* Instead we mark the Room as *NOT MANAGED* which means that it will be removed from the local
	* RoomList as soon as we leave it
	*/
	else 
	{
		room->IsManaged(false);
	}		
}

// -------------------------------------------------------------------
// ReplaceRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::ReplaceRoom(boost::shared_ptr<Room> room)
{
	return ReplaceRoom(room, true);
}

// -------------------------------------------------------------------
// ReplaceRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::ReplaceRoom(boost::shared_ptr<Room> room, bool addToGroupIfMissing)
{
	// Take the Room object that should be replaced
	boost::shared_ptr<Room> oldRoom = GetRoomById(room->Id());
			
	/*
	* If found, the Room is already in the RoomList and we don't want 
	* to replace the object, only update it
	*/
	if (oldRoom != NULL) 
	{
		oldRoom->Merge(room);
		return oldRoom;
	}
					
	// There's no previous instance, just add it			
	else 
	{
		AddRoom(room, addToGroupIfMissing);
		return room;
	}
}

// -------------------------------------------------------------------
// ChangeRoomName
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomName(boost::shared_ptr<Room> room, string newName)
{
	string oldName = *room->Name();
	room->Name(newName);
			
	// Update keys in the byName collection
	roomsByName.insert(pair<string, boost::shared_ptr<Room> >(newName, room));

	map<string, boost::shared_ptr<Room> >::iterator iterator; 
	iterator = roomsByName.find(oldName);
	if (iterator != roomsByName.end())
	{
		roomsByName.erase(iterator);
	}
}

// -------------------------------------------------------------------
// ChangeRoomPasswordState
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomPasswordState(boost::shared_ptr<Room> room, bool isPassProtected)
{
	room->IsPasswordProtected(isPassProtected);
}

// -------------------------------------------------------------------
// ChangeRoomCapacity
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomCapacity(boost::shared_ptr<Room> room, long int maxUsers, long int maxSpect)
{
	room->MaxUsers(maxUsers);
 	room->MaxSpectators(maxSpect);
}

// -------------------------------------------------------------------
// GetRoomGroups
// -------------------------------------------------------------------
boost::shared_ptr<vector<string> > SFSRoomManager::GetRoomGroups()
{
	boost::shared_ptr<vector<string> > returned (new vector<string>(groups));
	return returned;
}

// -------------------------------------------------------------------
// AddGroup
// -------------------------------------------------------------------
void SFSRoomManager::AddGroup(string groupId)
{
	groups.push_back(groupId);
}

// -------------------------------------------------------------------
// RemoveGroup
// -------------------------------------------------------------------
void SFSRoomManager::RemoveGroup(string groupId)
{
	// remove group
	vector<string>::iterator iterator;
	iterator = std::find(groups.begin(), groups.end(), groupId);
	if (iterator != groups.end())
	{
		groups.erase(iterator);
	}

	boost::shared_ptr<vector<boost::shared_ptr<Room> > > roomsInGroup = GetRoomListFromGroup(groupId);
			
	/*
	* We remove all rooms from the Group with the exception
	* of those that are joined. The joined Rooms must remain in the local Room List
	* but they are marked as unmanaged because we no longer subscribe to their Group
	*
	* The unmanaged Room(s) will be removed as soon as we leave it 
	*/
	vector<boost::shared_ptr<Room> >::iterator iteratorRooms;
	for (iteratorRooms = roomsInGroup->begin(); iteratorRooms != roomsInGroup->end(); iteratorRooms++)
	{
		boost::shared_ptr<Room> room = (*iteratorRooms);
		if (!room->IsJoined())
		{
			RemoveRoom(room);
		}
		else 
		{
			room->IsManaged(false);
		}		
	}
}

// -------------------------------------------------------------------
// ContainsGroup
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsGroup(string groupId)
{
	vector<string>::iterator iterator;
	iterator = std::find(groups.begin(), groups.end(), groupId);
	return iterator == groups.end() ? false : true;
}

// -------------------------------------------------------------------
// ContainsRoom
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsRoom(boost::shared_ptr<void> idOrName)
{
	if (typeid(idOrName) != typeid(boost::shared_ptr<long int>)) 
	{
		map<long int, boost::shared_ptr<Room> >::iterator iterator; 
		iterator = roomsById.find(*((long int*)idOrName.get()));
		return iterator == roomsById.end() ? false : true;
	}		
	else 
	{
		map<string, boost::shared_ptr<Room> >::iterator iterator; 
		iterator = roomsByName.find(*((string*)idOrName.get()));
		return iterator == roomsByName.end() ? false : true;
	}
}

// -------------------------------------------------------------------
// ContainsRoomInGroup
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsRoomInGroup(boost::shared_ptr<void> idOrName, string groupId)
{
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > roomList = GetRoomListFromGroup(groupId);
	bool searchById = (typeid(idOrName) == typeid(boost::shared_ptr<long int>));
			
	vector<boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomList->begin(); iterator != roomList->end(); iterator++)
	{
		boost::shared_ptr<Room> room = (*iterator);

		if (searchById)	
		{
			if (room->Id() == *((long int*)idOrName.get())) 
			{
				return true;
			}
		}
		else 
		{
			if ((*room->Name()) == *((string*)idOrName.get())) 
			{
				return true;
			}	
		}
	}
	
	return false;
}

// -------------------------------------------------------------------
// GetRoomById
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::GetRoomById(long int id)
{
	map<long int, boost::shared_ptr<Room> >::iterator iterator; 
	iterator = roomsById.find(id);
	if (iterator == roomsById.end())
	{
		return boost::shared_ptr<Room>();
	}

	return iterator->second;
}

// -------------------------------------------------------------------
// GetRoomByName
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::GetRoomByName(string name)
{
	map<string, boost::shared_ptr<Room> >::iterator iterator; 
	iterator = roomsByName.find(name);
	if (iterator == roomsByName.end())
	{
		return boost::shared_ptr<Room>();
	}

	return iterator->second;
}

// -------------------------------------------------------------------
// GetRoomList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SFSRoomManager::GetRoomList()
{
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms (new vector<boost::shared_ptr<Room> >());
	
	map<long int, boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomsById.begin(); iterator != roomsById.end(); iterator++)
	{
		rooms->push_back(iterator->second);
	}

	return rooms;
}

// -------------------------------------------------------------------
// GetRoomCount
// -------------------------------------------------------------------
long int SFSRoomManager::GetRoomCount()
{
	return roomsById.size();
}

// -------------------------------------------------------------------
// GetRoomListFromGroup
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SFSRoomManager::GetRoomListFromGroup(string groupId)
{
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms (new vector<boost::shared_ptr<Room> >());

	map<long int, boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomsById.begin(); iterator != roomsById.end(); iterator++)
	{
		boost::shared_ptr<Room> room = iterator->second;
		if ((*room->GroupId()) == groupId)
		{
			rooms->push_back(iterator->second);
		}
	}

	return rooms;			
}

// -------------------------------------------------------------------
// RemoveRoom
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoom(boost::shared_ptr<Room> room)
{
	RemoveRoom(room->Id(), *(room->Name()));
}

// -------------------------------------------------------------------
// RemoveRoomById
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoomById(long int id)
{
	map<long int, boost::shared_ptr<Room> >::iterator iterator; 
	iterator = roomsById.find(id);
	if (iterator == roomsById.end())
	{
		return;
	}

	boost::shared_ptr<Room> room = iterator->second;
	RemoveRoom(id, *(room->Name()));
}

// -------------------------------------------------------------------
// RemoveRoomByName
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoomByName(string name)
{
	map<string, boost::shared_ptr<Room> >::iterator iterator; 
	iterator = roomsByName.find(name);
	if (iterator == roomsByName.end())
	{
		return;
	}

	boost::shared_ptr<Room> room = iterator->second;
	RemoveRoom(room->Id(), name);
}

// -------------------------------------------------------------------
// GetJoinedRooms
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SFSRoomManager::GetJoinedRooms()
{
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms (new vector<boost::shared_ptr<Room> >());

	map<long int, boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomsById.begin(); iterator != roomsById.end(); iterator++)
	{
		boost::shared_ptr<Room> room = iterator->second;
		if (room->IsJoined())
		{
			rooms->push_back(iterator->second);
		}
	}

	return rooms;			
}

// -------------------------------------------------------------------
// GetUserRooms
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SFSRoomManager::GetUserRooms(boost::shared_ptr<User> user)
{
	boost::shared_ptr<vector<boost::shared_ptr<Room> > > rooms (new vector<boost::shared_ptr<Room> >());

	map<long int, boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomsById.begin(); iterator != roomsById.end(); iterator++)
	{
		boost::shared_ptr<Room> room = iterator->second;
		if (room->ContainsUser(user))
		{
			rooms->push_back(iterator->second);
		}
	}

	return rooms;			
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSRoomManager::RemoveUser(boost::shared_ptr<User> user)
{
	map<long int, boost::shared_ptr<Room> >::iterator iterator;
	for (iterator = roomsById.begin(); iterator != roomsById.end(); iterator++)
	{
		boost::shared_ptr<Room> room = iterator->second;
		if (room->ContainsUser(user))
		{
			room->RemoveUser(user);
		}
	}
}

// -------------------------------------------------------------------
// RemoveRoom
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoom(long int id, string name)
{
	map<long int, boost::shared_ptr<Room> >::iterator iteratorById; 
	iteratorById = roomsById.find(id);
	if (iteratorById != roomsById.end())
	{
		roomsById.erase(iteratorById);
	}

	map<string, boost::shared_ptr<Room> >::iterator iteratorByName; 
	iteratorByName = roomsByName.find(name);
	if (iteratorByName != roomsByName.end())
	{
		roomsByName.erase(iteratorByName);
	}
}

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X
