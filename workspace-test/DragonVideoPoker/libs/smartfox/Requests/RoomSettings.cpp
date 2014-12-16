// ===================================================================
//
// Description		
//		Contains the implementation of RoomSettings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomSettings.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomSettings::RoomSettings(string name)
{
	// Default settings
	this->name = boost::shared_ptr<string> (new string(name));
	this->password = boost::shared_ptr<string>(new string(""));
	this->isGame = false;
	this->maxUsers = 10;
	this->maxSpectators = 0;
	this->maxVariables = 5;
	this->groupId = boost::shared_ptr<string>(new string(*SFSConstants::DEFAULT_GROUP_ID));
	this->variables = boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > >();
	this->permissions = boost::shared_ptr<RoomPermissions>();
	this->events = boost::shared_ptr<RoomEvents>();
	this->extension = boost::shared_ptr<RoomExtension>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
RoomSettings::~RoomSettings()
{
	if (variables != NULL)
	{
		variables->clear();
	}
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomSettings::Name()
{
	return this->name;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
void RoomSettings::Name(string value)
{
	this->name = boost::shared_ptr<string> (new string(value));
}

// -------------------------------------------------------------------
// Password
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomSettings::Password()
{
	return this->password;
}

// -------------------------------------------------------------------
// Password
// -------------------------------------------------------------------
void RoomSettings::Password(string value)
{
	this->password = boost::shared_ptr<string> (new string(value));
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
bool RoomSettings::IsGame()
{
	return this->isGame;
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
void RoomSettings::IsGame(bool value)
{
	this->isGame = value;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
short int RoomSettings::MaxUsers()
{
	return this->maxUsers;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
void RoomSettings::MaxUsers(short int value)
{
	this->maxUsers = value;
}

// -------------------------------------------------------------------
// MaxVariables
// -------------------------------------------------------------------
short int RoomSettings::MaxVariables()
{
	return this->maxVariables;
}

// -------------------------------------------------------------------
// MaxVariables
// -------------------------------------------------------------------
void RoomSettings::MaxVariables(short int value)
{
	this->maxVariables = value;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
short int RoomSettings::MaxSpectators()
{
	return this->maxSpectators;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
void RoomSettings::MaxSpectators(short int value)
{
	this->maxSpectators = value;
}

// -------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > RoomSettings::Variables()
{
	return this->variables;
}

// -------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
void RoomSettings::Variables(boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > value)
{
	this->variables = value;
}

// -------------------------------------------------------------------
// Permissions
// -------------------------------------------------------------------
boost::shared_ptr<RoomPermissions> RoomSettings::Permissions()
{
	return this->permissions;
}

// -------------------------------------------------------------------
// Permissions
// -------------------------------------------------------------------
void RoomSettings::Permissions(boost::shared_ptr<RoomPermissions> value)
{
	this->permissions = value;
}

// -------------------------------------------------------------------
// Events
// -------------------------------------------------------------------
boost::shared_ptr<RoomEvents> RoomSettings::Events()
{
	return this->events;
}

// -------------------------------------------------------------------
// Events
// -------------------------------------------------------------------
void RoomSettings::Events(boost::shared_ptr<RoomEvents> value)
{
	this->events = value;
}

// -------------------------------------------------------------------
// Extension
// -------------------------------------------------------------------
boost::shared_ptr<RoomExtension> RoomSettings::Extension()
{
	return this->extension;
}

// -------------------------------------------------------------------
// Extension
// -------------------------------------------------------------------
void RoomSettings::Extension(boost::shared_ptr<RoomExtension> value)
{
	this->extension = value;
}

// -------------------------------------------------------------------
// GroupId
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomSettings::GroupId()
{
	return this->groupId;
}

// -------------------------------------------------------------------
// GroupId
// -------------------------------------------------------------------
void RoomSettings::GroupId(string value)
{
	this->groupId = boost::shared_ptr<string>(new string(value));
}


}	// namespace Requests
}	// namespace Sfs2X

