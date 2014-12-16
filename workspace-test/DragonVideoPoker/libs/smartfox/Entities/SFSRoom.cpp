// ===================================================================
//
// Description		
//		Contains the implementation of SFSRoom
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSRoom.h"
#include "MMORoom.h"
#include "Room.h"
#include "./Managers/SFSUserManager.h"
#include "./Variables/SFSRoomVariable.h"

namespace Sfs2X {
namespace Entities {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoom::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	// An MMO Room contains 14 properties
	bool isMMORoom = sfsa->Size() == 14;

	boost::shared_ptr<Room> newRoom = boost::shared_ptr<Room>();

	if (isMMORoom)
		newRoom = boost::shared_ptr<Room>(new MMORoom(sfsa->GetInt(0), *(sfsa->GetUtfString(1)), *(sfsa->GetUtfString(2))));
	else
		newRoom = boost::shared_ptr<Room>(new SFSRoom(sfsa->GetInt(0), *(sfsa->GetUtfString(1)), *(sfsa->GetUtfString(2))));
		
	newRoom->IsGame(sfsa->GetBool(3));
	newRoom->IsHidden(sfsa->GetBool(4));
	newRoom->IsPasswordProtected(sfsa->GetBool(5));
	newRoom->UserCount(sfsa->GetShort(6));
	newRoom->MaxUsers(sfsa->GetShort(7));
			
	// Room vars
	boost::shared_ptr<ISFSArray> varsList = sfsa->GetSFSArray(8);
	if (varsList->Size() > 0) 
	{
		boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > vars (new vector<boost::shared_ptr<RoomVariable> >());
			
		for (int j = 0; j < varsList->Size(); j++) 
		{
			vars->push_back(SFSRoomVariable::FromSFSArray(varsList->GetSFSArray(j)));
		}
				
		((boost::static_pointer_cast<SFSRoom>)(newRoom))->SetVariables(vars);
	}
			
	if (newRoom->IsGame()) 
	{
		newRoom->SpectatorCount(sfsa->GetShort(9));
		newRoom->MaxSpectators(sfsa->GetShort(10));
	}
		
	if (isMMORoom)
	{
		boost::shared_ptr<MMORoom> mmoRoom = (boost::static_pointer_cast<MMORoom>)(newRoom);
		mmoRoom->DefaultAOI(Vec3D::fromArray(sfsa->GetWrappedElementAt(11)->Type(), sfsa->GetElementAt(11)));
				
		// Check if map limits are non null
		if (!sfsa->IsNull(13))
		{
			mmoRoom->LowerMapLimit(Vec3D::fromArray(sfsa->GetWrappedElementAt(12)->Type(), sfsa->GetElementAt(12)));
			mmoRoom->HigherMapLimit(Vec3D::fromArray(sfsa->GetWrappedElementAt(13)->Type(), sfsa->GetElementAt(13)));
		}
	}

	return newRoom;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoom::SFSRoom(long int id, string name)
{
	Init(id, name, "default");
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoom::SFSRoom(long int id, string name, string groupId) 
{
	Init(id, name, groupId);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSRoom::~SFSRoom() 
{
	variables->clear();
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void SFSRoom::Init(long int id, string name, string groupId) 
{
	this->id = id;
	this->name = boost::shared_ptr<string>(new string(name));
	this->groupId = boost::shared_ptr<string>(new string(groupId));
			
	// default flags
	this->isJoined = this->isGame = this->isHidden = false;
	this->isManaged = true;
			
	// counters
	this->userCount = this->specCount = 0;
			
	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<RoomVariable> > >(new map<string, boost::shared_ptr<RoomVariable> >());
	this->variables->clear();

	this->properties = boost::shared_ptr<map<string, string> >(new map<string, string>());
	this->properties->clear();
						
	// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
	// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
	// Here we set userManager to NULL and its initialization to SFSUserManager instance will be done at the first access of userManager
	this->userManager = boost::shared_ptr<IUserManager>();

	this->roomManager = boost::shared_ptr<IRoomManager>();
	this->maxSpectators = 0;
}		

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int SFSRoom::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoom::Name()
{
	return name;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
void SFSRoom::Name(string value)
{
	name = boost::shared_ptr<string> (new string(value));
}

// -------------------------------------------------------------------
// GroupId
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoom::GroupId()
{
	return groupId;
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
bool SFSRoom::IsGame()
{
	return isGame;
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
void SFSRoom::IsGame(bool value)
{
	isGame = value;
}

// -------------------------------------------------------------------
// IsHidden
// -------------------------------------------------------------------
bool SFSRoom::IsHidden()
{
	return isHidden;
}

// -------------------------------------------------------------------
// IsHidden
// -------------------------------------------------------------------
void SFSRoom::IsHidden(bool value)
{
	isHidden = value;
}

// -------------------------------------------------------------------
// IsJoined
// -------------------------------------------------------------------
bool SFSRoom::IsJoined()
{
	return isJoined;
}

// -------------------------------------------------------------------
// IsJoined
// -------------------------------------------------------------------
void SFSRoom::IsJoined(bool value)
{
	isJoined = value;
}

// -------------------------------------------------------------------
// IsPasswordProtected
// -------------------------------------------------------------------
bool SFSRoom::IsPasswordProtected()
{
	return isPasswordProtected;
}

// -------------------------------------------------------------------
// IsPasswordProtected
// -------------------------------------------------------------------
void SFSRoom::IsPasswordProtected(bool value)
{
	isPasswordProtected = value;
}

// -------------------------------------------------------------------
// IsManaged
// -------------------------------------------------------------------
bool SFSRoom::IsManaged()
{
	return isManaged;
}

// -------------------------------------------------------------------
// IsManaged
// -------------------------------------------------------------------
void SFSRoom::IsManaged(bool value)
{
	isManaged = value;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
long int SFSRoom::MaxSpectators()
{
	return maxSpectators;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
void SFSRoom::MaxSpectators(long int value)
{
	maxSpectators = value;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
boost::shared_ptr<map<string, string> > SFSRoom::Properties()
{
	return properties;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
void SFSRoom::Properties(boost::shared_ptr<map<string, string> > value)
{
	properties = value;
}

// -------------------------------------------------------------------
// GetVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > SFSRoom::GetVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > result (new vector<boost::shared_ptr<RoomVariable> >());
	
	map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	return result;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<RoomVariable> SFSRoom::GetVariable(string name)
{
	map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
	iterator = variables->find(name);
	if (iterator == variables->end())
	{
		return boost::shared_ptr<RoomVariable>();
	}

	return iterator->second;
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
long int SFSRoom::UserCount()
{
	if (!isJoined) 
	{
		return userCount;
	}			
	else 
	{
		// For game rooms, return only player count
		if (isGame) 
		{
			return PlayerList()->size();
		}
		// For regular rooms, return the full user count
		else 
		{
			if (userManager == NULL)
			{
				// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
				// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
				// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
				this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
			}

			return userManager->UserCount();
		}
	}
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
void SFSRoom::UserCount(long int value)
{
	userCount = value;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
long int SFSRoom::MaxUsers()
{
	return maxUsers;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
void SFSRoom::MaxUsers(long int value)
{
	maxUsers = value;
}

// -------------------------------------------------------------------
// Capacity
// -------------------------------------------------------------------
long int SFSRoom::Capacity()
{
	return maxUsers + maxSpectators;
}

// -------------------------------------------------------------------
// SpectatorCount
// -------------------------------------------------------------------
long int SFSRoom::SpectatorCount()
{
	if (!isGame) 
	{
		return 0;
	}
			
	// Joined Room? Dynamically calculate spectators
	if (isJoined) 
	{
		return SpectatorList()->size();
	}
	// Not joined, use the static value sent by the server
	else 
	{
		return specCount;
	}		
}

// -------------------------------------------------------------------
// SpectatorCount
// -------------------------------------------------------------------
void SFSRoom::SpectatorCount(long int value)
{
	specCount = value;
}

// -------------------------------------------------------------------
// GetUserByName
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSRoom::GetUserByName(string name)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	return userManager->GetUserByName(name);
}

// -------------------------------------------------------------------
// GetUserById
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSRoom::GetUserById(long int id)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	return userManager->GetUserById(id);
}

// -------------------------------------------------------------------
// UserList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > SFSRoom::UserList()
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	return userManager->GetUserList();
}

// -------------------------------------------------------------------
// PlayerList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > SFSRoom::PlayerList()
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	boost::shared_ptr<vector<boost::shared_ptr<User> > > playerList (new vector<boost::shared_ptr<User> >());

	vector<boost::shared_ptr<User> >::iterator iterator;

	boost::shared_ptr<vector<boost::shared_ptr<User> > > listUsers = userManager->GetUserList();
	for (iterator = listUsers->begin(); iterator != listUsers->end(); iterator++)
	{
		boost::shared_ptr<User> user = (*iterator);
		if (user->IsPlayerInRoom(shared_from_this()))
		{
			playerList->push_back(user);
		}
	}

	return playerList;
}

// -------------------------------------------------------------------
// SpectatorList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > SFSRoom::SpectatorList()
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	boost::shared_ptr<vector<boost::shared_ptr<User> > > spectatorList (new vector<boost::shared_ptr<User> >());

	vector<boost::shared_ptr<User> >::iterator iterator;

	boost::shared_ptr<vector<boost::shared_ptr<User> > > listUsers = userManager->GetUserList();
	for (iterator = listUsers->begin(); iterator != listUsers->end(); iterator++)
	{
		boost::shared_ptr<User> user = (*iterator);
		if (user->IsSpectatorInRoom(shared_from_this()))
		{
			spectatorList->push_back(user);
		}
	}

	return spectatorList;
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSRoom::RemoveUser(boost::shared_ptr<User> user)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	userManager->RemoveUser(user);
}

// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void SFSRoom::SetVariable(boost::shared_ptr<RoomVariable> roomVariable)
{
	// If varType == NULL delete var
	if (roomVariable->IsNull()) 
	{
		map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
		iterator = variables->find(*roomVariable->Name());
		if (iterator != variables->end())
		{
			variables->erase(iterator);
		}
	}
	else
	{
		map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
		iterator = variables->find(*roomVariable->Name());
		if (iterator != variables->end())
		{
			iterator->second = roomVariable;
		}
		else
		{
			variables->insert(pair<string, boost::shared_ptr<RoomVariable> >(*roomVariable->Name(), roomVariable));
		}
	}
}

// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void SFSRoom::SetVariables(boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables)
{
	vector<boost::shared_ptr<RoomVariable> >::iterator iterator;
	for (iterator = roomVariables->begin(); iterator != roomVariables->end(); iterator++)
	{
		SetVariable(*iterator);
	}
}

// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool SFSRoom::ContainsVariable(string name)
{
	map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
	iterator = variables->find(name);
	if (iterator == variables->end())
	{
		return false;
	}

	return true;
}

// -------------------------------------------------------------------
// RemoveUserVariable
// -------------------------------------------------------------------
void SFSRoom::RemoveUserVariable(string varName)
{
	map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
	iterator = variables->find(varName);
	if (iterator != variables->end())
	{
		variables->erase(iterator);
	}
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void SFSRoom::AddUser(boost::shared_ptr<User> user)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	userManager->AddUser(user);
}

// -------------------------------------------------------------------
// ContainsUser
// -------------------------------------------------------------------
bool SFSRoom::ContainsUser(boost::shared_ptr<User> user)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	return userManager->ContainsUser(user);
}

// -------------------------------------------------------------------
// RoomManager
// -------------------------------------------------------------------
boost::shared_ptr<IRoomManager> SFSRoom::RoomManager()
{
	return roomManager;
}

// -------------------------------------------------------------------
// RoomManager
// -------------------------------------------------------------------
void SFSRoom::RoomManager(boost::shared_ptr<IRoomManager> value)
{
	if (roomManager != NULL) 
	{
		boost::shared_ptr<string> message(new string("Room manager already assigned. Room: " + *(this->Name()))); 
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
				
	roomManager = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoom::ToString()
{
	char buffer[512];
	sprintf (buffer, "[Room: %s, Id: %ld, GroupId: %s]", name->c_str(), id, groupId->c_str());

	return boost::shared_ptr<string>(new string (buffer));
}

// -------------------------------------------------------------------
// Merge
// -------------------------------------------------------------------
void SFSRoom::Merge(boost::shared_ptr<Room> anotherRoom)
{
	if (userManager == NULL)
	{
		// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
		// so any initialization that need of instance shared pointer (like userManager) should be moved into other methods
		// In class constructor we have set userManager to NULL and real initialization to SFSUserManager instance is done at the first access 
		this->userManager = boost::shared_ptr<IUserManager>(new SFSUserManager(shared_from_this()));
	}

	vector<boost::shared_ptr<RoomVariable> >::iterator iteratorRoomVariable;
	boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > collectionAnotherRoomVariables = anotherRoom->GetVariables();

	for (iteratorRoomVariable = collectionAnotherRoomVariables->begin(); iteratorRoomVariable != collectionAnotherRoomVariables->end(); iteratorRoomVariable++)
	{
		boost::shared_ptr<RoomVariable> rv = (*iteratorRoomVariable);
		map<string, boost::shared_ptr<RoomVariable> >::iterator iterator;
		iterator = variables->find(*rv->Name());
		if (iterator != variables->end())
		{
			iterator->second = rv;
		}
		else
		{
			variables->insert(pair<string, boost::shared_ptr<RoomVariable> >(*rv->Name(), rv));
		}
	}

	// Rebuild User List
	userManager->ClearAll();

	vector<boost::shared_ptr<User> >::iterator iteratorUser;
	boost::shared_ptr<vector<boost::shared_ptr<User> > > collectionAnotherRoomUserList = anotherRoom->UserList();
	for (iteratorUser = collectionAnotherRoomUserList->begin(); iteratorUser != collectionAnotherRoomUserList->end(); iteratorUser++)
	{
		boost::shared_ptr<User> user = (*iteratorUser);
		userManager->AddUser(user);
	}
}

}	// namespace Entities
}	// namespace Sfs2X

