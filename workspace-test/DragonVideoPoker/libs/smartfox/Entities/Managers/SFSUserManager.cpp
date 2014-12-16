// ===================================================================
//
// Description		
//		Contains the implementation of SFSUserManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSUserManager.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(boost::shared_ptr<SmartFox> sfs)
{
	this->sfs = sfs;
	usersByName = boost::shared_ptr<map<string, boost::shared_ptr<User> > >(new map<string, boost::shared_ptr<User> >());
	usersById = boost::shared_ptr<map<long int, boost::shared_ptr<User> > >(new map<long int, boost::shared_ptr<User> >());
	room = boost::shared_ptr<Room>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(boost::shared_ptr<Room> room)
{
	this->sfs = boost::shared_ptr<SmartFox>();
	this->room = room;
	usersByName = boost::shared_ptr<map<string, boost::shared_ptr<User> > >(new map<string, boost::shared_ptr<User> >());
	usersById = boost::shared_ptr<map<long int, boost::shared_ptr<User> > >(new map<long int, boost::shared_ptr<User> >());
	room = boost::shared_ptr<Room>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUserManager::~SFSUserManager()
{
	usersByName->clear();
	usersById->clear();
}

// -------------------------------------------------------------------
// ContainsUserName
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserName(string userName)
{
	map<string, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersByName->find(userName);
	return iterator == usersByName->end() ? false : true;
}

// -------------------------------------------------------------------
// ContainsUserId
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserId(long int userId)
{
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(userId);
	return iterator == usersById->end() ? false : true;
}

// -------------------------------------------------------------------
// ContainsUser
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUser(boost::shared_ptr<User> user)
{
	map<string, boost::shared_ptr<User> >::iterator iterator; 
	for (iterator = usersByName->begin(); iterator != usersByName->end(); iterator++)
	{
		if (iterator->second == user)
		{
			return true;
		}
	}

	return false;
}

// -------------------------------------------------------------------
// GetUserByName
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUserManager::GetUserByName(string userName)
{
	map<string, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersByName->find(userName);
	return iterator == usersByName->end() ? boost::shared_ptr<User>() : iterator->second;
}

// -------------------------------------------------------------------
// GetUserById
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUserManager::GetUserById(long int userId)
{
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(userId);
	return iterator == usersById->end() ? boost::shared_ptr<User>() : iterator->second;
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void SFSUserManager::AddUser(boost::shared_ptr<User> user)
{
	// very defensive, no need to fire exception, however we keep it for debugging
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(user->Id());

	if (iterator != usersById->end()) 
	{
		boost::shared_ptr<string> message (new string("Unexpected: duplicate user in UserManager: " + (*user->Name())));
		LogWarn(message);
	}
				
	AddUserInternal(user);
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSUserManager::RemoveUser(boost::shared_ptr<User> user)
{
	map<long int, boost::shared_ptr<User> >::iterator iteratorById; 
	iteratorById = usersById->find(user->Id());
	if (iteratorById != usersById->end())
	{
		usersById->erase(iteratorById);
	}

	map<string, boost::shared_ptr<User> >::iterator iteratorByName; 
	iteratorByName = usersByName->find(*user->Name());
	if (iteratorByName != usersByName->end())
	{
		usersByName->erase(iteratorByName);
	}
}

// -------------------------------------------------------------------
// RemoveUserById
// -------------------------------------------------------------------
void SFSUserManager::RemoveUserById(long int id)
{
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(id);
	if (iterator != usersById->end())
	{
		RemoveUser(iterator->second);
	}
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
long int SFSUserManager::UserCount()
{
	return usersById->size();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> SFSUserManager::SmartFoxClient()
{
	return sfs;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > SFSUserManager::GetUserList()
{
	boost::shared_ptr<vector<boost::shared_ptr<User> > > result (new vector<boost::shared_ptr<User> >());
		
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	for (iterator = usersById->begin(); iterator != usersById->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	return result;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
void SFSUserManager::ClearAll()
{
	usersById->clear();
	usersByName->clear();
}

// -------------------------------------------------------------------
// LogWarn
// -------------------------------------------------------------------
void SFSUserManager::LogWarn(boost::shared_ptr<string> msg)
{
	if (sfs != NULL) 
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back(*msg);

		sfs->Log()->Warn(messages);
		return;
	}
			
	if (room != NULL && room->RoomManager() != NULL) 
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back(*msg);

		room->RoomManager()->SmartFoxClient()->Log()->Warn(messages);
		return;
	}
}

// -------------------------------------------------------------------
// AddUserInternal
// -------------------------------------------------------------------
void SFSUserManager::AddUserInternal(boost::shared_ptr<User> user)
{
	usersById->insert(pair<long int, boost::shared_ptr<User> >(user->Id(), user));
	usersByName->insert(pair<string, boost::shared_ptr<User> >(*user->Name(), user));
}

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X
