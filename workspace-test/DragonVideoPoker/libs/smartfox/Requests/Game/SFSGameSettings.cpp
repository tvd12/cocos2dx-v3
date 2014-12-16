// ===================================================================
//
// Description		
//		Contains the implementation of SFSGameSettings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSGameSettings.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSGameSettings::SFSGameSettings(string name)
	: RoomSettings(name)
{
	isPublic = true;
	minPlayersToStartGame = 2;
	invitationExpiryTime = 15;
	leaveJoinedLastRoom = true;
	invitedPlayersUser = boost::shared_ptr<list<boost::shared_ptr<User> > >(new list<boost::shared_ptr<User> >());
	invitedPlayersBuddy = boost::shared_ptr<list<boost::shared_ptr<Buddy> > >(new list<boost::shared_ptr<Buddy> >());
	searchableRooms = boost::shared_ptr<list<boost::shared_ptr<string> > >(new list<boost::shared_ptr<string> >());
	invitationParams = boost::shared_ptr<ISFSObject>();
	playerMatchExpression = boost::shared_ptr<MatchExpression>();
	spectatorMatchExpression = boost::shared_ptr<MatchExpression>();
	notifyGameStarted = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSGameSettings::~SFSGameSettings()
{
	invitedPlayersUser->clear();
	invitedPlayersBuddy->clear();
	searchableRooms->clear();
}

// -------------------------------------------------------------------
// IsPublic
// -------------------------------------------------------------------
bool SFSGameSettings::IsPublic()
{
	return isPublic;
}

// -------------------------------------------------------------------
// IsPublic
// -------------------------------------------------------------------
void SFSGameSettings::IsPublic(bool value)
{
	isPublic = value;
}

// -------------------------------------------------------------------
// MinPlayersToStartGame
// -------------------------------------------------------------------
long int SFSGameSettings::MinPlayersToStartGame()
{
	return minPlayersToStartGame;
}
		
// -------------------------------------------------------------------
// MinPlayersToStartGame
// -------------------------------------------------------------------
void SFSGameSettings::MinPlayersToStartGame(long int value)
{
	minPlayersToStartGame = value;
}

// -------------------------------------------------------------------
// InvitedPlayersUser
// -------------------------------------------------------------------
boost::shared_ptr<list<boost::shared_ptr<User> > > SFSGameSettings::InvitedPlayersUser()
{
	return invitedPlayersUser;
}

// -------------------------------------------------------------------
// InvitedPlayersUser
// -------------------------------------------------------------------
void SFSGameSettings::InvitedPlayersUser(boost::shared_ptr<list<boost::shared_ptr<User> > > value)
{
	invitedPlayersUser = value;
}

// -------------------------------------------------------------------
// InvitedPlayersBuddy
// -------------------------------------------------------------------
boost::shared_ptr<list<boost::shared_ptr<Buddy> > > SFSGameSettings::InvitedPlayersBuddy()
{
	return invitedPlayersBuddy;
}

// -------------------------------------------------------------------
// InvitedPlayersBuddy
// -------------------------------------------------------------------
void SFSGameSettings::InvitedPlayersBuddy(boost::shared_ptr<list<boost::shared_ptr<Buddy> > > value)
{
	invitedPlayersBuddy = value;
}

// -------------------------------------------------------------------
// SearchableRooms
// -------------------------------------------------------------------
boost::shared_ptr<list<boost::shared_ptr<string> > > SFSGameSettings::SearchableRooms()
{
	return searchableRooms;
}

// -------------------------------------------------------------------
// SearchableRooms
// -------------------------------------------------------------------
void SFSGameSettings::SearchableRooms(boost::shared_ptr<list<boost::shared_ptr<string> > > value)
{
	searchableRooms = value;
}

// -------------------------------------------------------------------
// InvitationExpiryTime
// -------------------------------------------------------------------
long int SFSGameSettings::InvitationExpiryTime()
{
	return invitationExpiryTime;
}

// -------------------------------------------------------------------
// InvitationExpiryTime
// -------------------------------------------------------------------
void SFSGameSettings::InvitationExpiryTime(long int value)
{
	invitationExpiryTime = value;
}

// -------------------------------------------------------------------
// LeaveLastJoinedRoom
// -------------------------------------------------------------------
bool SFSGameSettings::LeaveLastJoinedRoom()
{
	return leaveJoinedLastRoom;
}

// -------------------------------------------------------------------
// LeaveLastJoinedRoom
// -------------------------------------------------------------------
void SFSGameSettings::LeaveLastJoinedRoom(bool value)
{
	leaveJoinedLastRoom = value;
}

// -------------------------------------------------------------------
// NotifyGameStarted
// -------------------------------------------------------------------
bool SFSGameSettings::NotifyGameStarted()
{
	return notifyGameStarted;
}

// -------------------------------------------------------------------
// NotifyGameStarted
// -------------------------------------------------------------------
void SFSGameSettings::NotifyGameStarted(bool value)
{
	notifyGameStarted = value;
}

// -------------------------------------------------------------------
// NotifyGameStarted
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> SFSGameSettings::PlayerMatchExpression()
{
	return playerMatchExpression;
}

// -------------------------------------------------------------------
// PlayerMatchExpression
// -------------------------------------------------------------------
void SFSGameSettings::PlayerMatchExpression(boost::shared_ptr<MatchExpression> value)
{
	playerMatchExpression = value;
}

// -------------------------------------------------------------------
// SpectatorMatchExpression
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> SFSGameSettings::SpectatorMatchExpression()
{
	return spectatorMatchExpression;
}

// -------------------------------------------------------------------
// SpectatorMatchExpression
// -------------------------------------------------------------------
void SFSGameSettings::SpectatorMatchExpression(boost::shared_ptr<MatchExpression> value)
{
	spectatorMatchExpression = value;
}

// -------------------------------------------------------------------
// InvitationParams
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSGameSettings::InvitationParams()
{
	return invitationParams;
}

// -------------------------------------------------------------------
// InvitationParams
// -------------------------------------------------------------------
void SFSGameSettings::InvitationParams(boost::shared_ptr<ISFSObject> value)
{
	invitationParams = value;
}


}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X



