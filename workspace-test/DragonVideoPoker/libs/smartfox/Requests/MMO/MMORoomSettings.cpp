// ===================================================================
//
// Description		
//		Contains the implementation of MMORoomSettings
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MMORoomSettings.h"

namespace Sfs2X {
namespace Requests {
namespace MMO {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMORoomSettings::MMORoomSettings (string name)
	: RoomSettings(name)
{
	this->defaultAOI = boost::shared_ptr<Vec3D>();
	this->mapLimits = boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits>();
	this->userMaxLimboSeconds = 50;
	this->proximityListUpdateMillis = 250;
	this->sendAOIEntryPoint = true;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMORoomSettings::~MMORoomSettings()
{
}

// -------------------------------------------------------------------
// DefaultAOI
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MMORoomSettings::DefaultAOI()
{
	return defaultAOI;
}

// -------------------------------------------------------------------
// DefaultAOI
// -------------------------------------------------------------------
void MMORoomSettings::DefaultAOI(boost::shared_ptr<Vec3D> value)
{
	defaultAOI = value;
}

// -------------------------------------------------------------------
// MapLimits
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits> MMORoomSettings::MapLimits()
{
	return mapLimits;
}

// -------------------------------------------------------------------
// MapLimits
// -------------------------------------------------------------------
void MMORoomSettings::MapLimits(boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits> value)
{
	mapLimits = value;
}

// -------------------------------------------------------------------
// UserMaxLimboSeconds
// -------------------------------------------------------------------
long int MMORoomSettings::UserMaxLimboSeconds()
{
	return userMaxLimboSeconds;
}

// -------------------------------------------------------------------
// UserMaxLimboSeconds
// -------------------------------------------------------------------
void MMORoomSettings::UserMaxLimboSeconds(long int value)
{
	userMaxLimboSeconds = value;
}

// -------------------------------------------------------------------
// ProximityListUpdateMillis
// -------------------------------------------------------------------
long int MMORoomSettings::ProximityListUpdateMillis()
{
	return proximityListUpdateMillis;
}

// -------------------------------------------------------------------
// ProximityListUpdateMillis
// -------------------------------------------------------------------
void MMORoomSettings::ProximityListUpdateMillis(long int value)
{
	proximityListUpdateMillis = value;
}

// -------------------------------------------------------------------
// SendAOIEntryPoint
// -------------------------------------------------------------------
bool MMORoomSettings::SendAOIEntryPoint()
{
	return sendAOIEntryPoint;
}

// -------------------------------------------------------------------
// SendAOIEntryPoint
// -------------------------------------------------------------------
void MMORoomSettings::SendAOIEntryPoint(bool value)
{
	sendAOIEntryPoint = value;
}

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X


