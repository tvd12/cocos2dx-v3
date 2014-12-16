// ===================================================================
//
// Description		
//		Contains the implementation of SFSGlobalUserManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSGlobalUserManager.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSGlobalUserManager::SFSGlobalUserManager(boost::shared_ptr<SmartFox> sfs)
	: SFSUserManager(sfs)
{
	roomRefCount.clear();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSGlobalUserManager::SFSGlobalUserManager(boost::shared_ptr<Room> room)
	: SFSUserManager(room)
{
	roomRefCount.clear();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSGlobalUserManager::~SFSGlobalUserManager()
{
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void SFSGlobalUserManager::AddUser(boost::shared_ptr<User> user)
{
	// Doesn't exist create and set refCount
	map<boost::shared_ptr<User>, long int>::iterator iterator; 
	iterator = roomRefCount.find(user);

	if (iterator == roomRefCount.end())
	{
		//Console.WriteLine("User duplicate NOT FOUND. Adding as new")
		SFSUserManager::AddUser(user);
		roomRefCount.insert(pair<boost::shared_ptr<User>, long int>(user, 1));
	}
	else 	
	{
		//Console.WriteLine("User duplicate FOUND. Incrementing value")
		roomRefCount[user] += 1;
	}		
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSGlobalUserManager::RemoveUser(boost::shared_ptr<User> user)
{
	map<boost::shared_ptr<User>, long int>::iterator iterator; 
	iterator = roomRefCount.find(user);

	if (iterator != roomRefCount.end())
	{
		/* Debug Only */
		if (roomRefCount[user] < 1) 
		{
			boost::shared_ptr<string> message (new string("GlobalUserManager RefCount is already at zero. User: " + (*user->Name())));
			LogWarn(message);
			return;
		}
				
		roomRefCount[user] -= 1;
												
		if (roomRefCount[user] == 0) 
		{
			SFSUserManager::RemoveUser(user);
			roomRefCount.erase(iterator);
		}
	}
	else 
	{
		boost::shared_ptr<string> message(new string("Can't remove User from GlobalUserManager. RefCount missing. User: " + (*user->Name())));
		LogWarn(message);
	}
}

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X
