// ===================================================================
//
// Description		
//		Contains the implementation of SFSUser
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#include "SFSUser.h"
#include "./Variables/SFSUserVariable.h"
#include "UserPrivileges.h"

namespace Sfs2X {
namespace Entities {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUser::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa, boost::shared_ptr<Room> room)
{
	// Pass id and name
	boost::shared_ptr<User> newUser (new SFSUser(sfsa->GetInt(0), *(sfsa->GetUtfString(1))));

	// Set privileges
	newUser->PrivilegeId(sfsa->GetShort(2));
			
	// Set playerId
	if (room != NULL) 
	{
		newUser->SetPlayerId(sfsa->GetShort(3), room);
	}
			
	// Populate variables
	boost::shared_ptr<ISFSArray> uVars = sfsa->GetSFSArray(4);
	for (int i = 0; i < uVars->Size(); i++) 
	{
		newUser->SetVariable(SFSUserVariable::FromSFSArray(uVars->GetSFSArray(i)));
	}
			
	return newUser;
}

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUser::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	return FromSFSArray(sfsa, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUser::SFSUser(long int id, string name)
{
	Init(id, name, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUser::SFSUser(long int id, string name, bool isItMe)
{
	Init(id, name, isItMe);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUser::~SFSUser()
{
	variables->clear();
	playerIdByRoomId->clear();
	properties->clear();
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void SFSUser::Init(long int id, string name, bool isItMe)
{
	this->id = id;
	this->name = boost::shared_ptr<string>(new string(name));
	this->isItMe = isItMe;
	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<UserVariable> > >(new map<string, boost::shared_ptr<UserVariable> >());
	this->variables->clear();
	this->properties = boost::shared_ptr<map<string, boost::shared_ptr<void> > >(new map<string, boost::shared_ptr<void> >());
	this->properties->clear();
	this->isModerator = false;
	this->playerIdByRoomId = boost::shared_ptr<map<long int, long int> >(new map<long int, long int>());
	this->playerIdByRoomId->clear();
	this->privilegeId = 0;
	this->userManager = boost::shared_ptr<IUserManager>();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int SFSUser::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSUser::Name()
{
	return name;
}

// -------------------------------------------------------------------
// PlayerId
// -------------------------------------------------------------------
long int SFSUser::PlayerId()
{
	// Return from default room
	return GetPlayerId(userManager->SmartFoxClient()->LastJoinedRoom());
} 

// -------------------------------------------------------------------
// IsJoinedInRoom
// -------------------------------------------------------------------
bool SFSUser::IsJoinedInRoom(boost::shared_ptr<Room> room)
{
	return room->ContainsUser(shared_from_this());
}

// -------------------------------------------------------------------
// PrivilegeId
// -------------------------------------------------------------------
long int SFSUser::PrivilegeId()
{
	return privilegeId;
}

// -------------------------------------------------------------------
// PrivilegeId
// -------------------------------------------------------------------
void SFSUser::PrivilegeId(long int value)
{
	privilegeId = value;
}

// -------------------------------------------------------------------
// IsGuest
// -------------------------------------------------------------------
bool SFSUser::IsGuest()
{
	return privilegeId == (long int)USERPRIVILEGES_GUEST;
}
		
// -------------------------------------------------------------------
// IsStandardUser
// -------------------------------------------------------------------
bool SFSUser::IsStandardUser()
{
	return privilegeId == (long int)USERPRIVILEGES_STANDARD;
}

// -------------------------------------------------------------------
// IsModerator
// -------------------------------------------------------------------
bool SFSUser::IsModerator()
{
	return privilegeId == (long int)USERPRIVILEGES_MODERATOR;
}
				
// -------------------------------------------------------------------
// IsAdmin
// -------------------------------------------------------------------
bool SFSUser::IsAdmin()
{
	return privilegeId == (long int)USERPRIVILEGES_ADMINISTRATOR;
}

// -------------------------------------------------------------------
// IsPlayer
// -------------------------------------------------------------------
bool SFSUser::IsPlayer()
{
	return this->PlayerId() > 0;
}

// -------------------------------------------------------------------
// IsSpectator
// -------------------------------------------------------------------
bool SFSUser::IsSpectator()
{
	return !this->IsPlayer();
}

// -------------------------------------------------------------------
// GetPlayerId
// -------------------------------------------------------------------
long int SFSUser::GetPlayerId (boost::shared_ptr<Room> room)
{
	long int pId = 0;
			
	map<long int, long int>::iterator iterator;
	iterator = playerIdByRoomId->find(room->Id());

	if (iterator != playerIdByRoomId->end()) 
	{
		pId = iterator->second;
	}
			
	return pId;
}

// -------------------------------------------------------------------
// SetPlayerId
// -------------------------------------------------------------------
void SFSUser::SetPlayerId(long int id, boost::shared_ptr<Room> room)
{
	map<long int, long int>::iterator iterator;
	iterator = playerIdByRoomId->find(room->Id());
	if (iterator != playerIdByRoomId->end())
	{
		iterator->second = id;
	}
	else 
	{
		playerIdByRoomId->insert(std::make_pair(room->Id(), id));
    }
}

// -------------------------------------------------------------------
// RemovePlayerId
// -------------------------------------------------------------------
void SFSUser::RemovePlayerId(boost::shared_ptr<Room> room)
{
	map<long int, long int>::iterator iterator;
	iterator = playerIdByRoomId->find(room->Id());
	if (iterator != playerIdByRoomId->end())
	{
		playerIdByRoomId->erase(iterator);
	}
}

// -------------------------------------------------------------------
// IsPlayerInRoom
// -------------------------------------------------------------------
bool SFSUser::IsPlayerInRoom(boost::shared_ptr<Room> room)
{
	map<long int, long int>::iterator iterator;
	iterator = playerIdByRoomId->find(room->Id());
	if (iterator == playerIdByRoomId->end())
	{
		return false;
	}
	return iterator->second > 0;
}

// -------------------------------------------------------------------
// IsSpectatorInRoom
// -------------------------------------------------------------------
bool SFSUser::IsSpectatorInRoom(boost::shared_ptr<Room> room)
{			
	map<long int, long int>::iterator iterator;
	iterator = playerIdByRoomId->find(room->Id());
	if (iterator == playerIdByRoomId->end())
	{
		return true;
	}
	return iterator->second < 0;
}

// -------------------------------------------------------------------
// IsItMe
// -------------------------------------------------------------------
bool SFSUser::IsItMe()
{
	return isItMe;
}

// -------------------------------------------------------------------
// UserManager
// -------------------------------------------------------------------
boost::shared_ptr<IUserManager> SFSUser::UserManager()
{
	return userManager;
}

// -------------------------------------------------------------------
// UserManager
// -------------------------------------------------------------------
void SFSUser::UserManager(boost::shared_ptr<IUserManager> value)
{
	if (userManager != NULL) 
	{
		boost::shared_ptr<string> message (new string("Cannot re-assign the User manager. Already set. User: " + *(this->Name())));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
				
	userManager = value;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> SFSUser::AOIEntryPoint()
{
	return aoiEntryPoint;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
void SFSUser::AOIEntryPoint(boost::shared_ptr<Vec3D> value)
{
	aoiEntryPoint = value;
}

// -------------------------------------------------------------------
// GetVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > SFSUser::GetVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > result (new vector<boost::shared_ptr<UserVariable> >());
	
	map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	return result;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<UserVariable> SFSUser::GetVariable(string varName)
{
	map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
	iterator = variables->find(varName);
	if (iterator == variables->end())
	{
		return boost::shared_ptr<UserVariable>();
	}

	return iterator->second;
}

// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void SFSUser::SetVariable(boost::shared_ptr<UserVariable> userVariable)
{
	if (userVariable != NULL) 
	{
		// If varType == NULL delete var
		if (userVariable->IsNull()) 
		{
			map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
			iterator = variables->find(*userVariable->Name());
			if (iterator != variables->end())
			{
				variables->erase(iterator);
			}
		}
		else 
		{
			map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
			iterator = variables->find(*userVariable->Name());
			if (iterator != variables->end())
			{
				iterator->second = userVariable;
			}
			else
			{
				variables->insert(pair<string, boost::shared_ptr<UserVariable> >(*userVariable->Name(), userVariable));
			}
		}
	}
}

// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void SFSUser::SetVariables(boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > userVaribles)
{
	vector<boost::shared_ptr<UserVariable> >::iterator iterator;
	for (iterator = userVaribles->begin(); iterator != userVaribles->end(); iterator++)
	{
		SetVariable(*iterator);
	}
}

// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool SFSUser::ContainsVariable(string name)
{
	map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
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
void SFSUser::RemoveUserVariable(string varName)
{
	map<string, boost::shared_ptr<UserVariable> >::iterator iterator;
	iterator = variables->find(varName);
	if (iterator != variables->end())
	{
		variables->erase(iterator);
	}
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
boost::shared_ptr<map<string, boost::shared_ptr<void> > > SFSUser::Properties()
{
	return properties;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
void SFSUser::Properties(boost::shared_ptr<map<string, boost::shared_ptr<void> > > value)
{
	properties = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSUser::ToString()
{
	char buffer[512];
	sprintf (buffer, "[User: %s, Id: %ld, isMe: %ld]", name->c_str(), id, isItMe);

	return boost::shared_ptr<string>(new string(buffer));
}

}	// namespace Entities
}	// namespace Sfs2X
