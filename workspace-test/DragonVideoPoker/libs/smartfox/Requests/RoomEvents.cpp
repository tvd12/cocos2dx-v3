// ===================================================================
//
// Description		
//		Contains the implementation of RoomEvents
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#include "RoomEvents.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomEvents::RoomEvents()
{
	this->allowUserEnter = false;
	this->allowUserExit = false;
	this->allowUserCountChange = false;
	this->allowUserVariablesUpdate = false;
}

// -------------------------------------------------------------------
// AllowUserEnter
// -------------------------------------------------------------------
bool RoomEvents::AllowUserEnter()
{
	return this->allowUserEnter;
}

// -------------------------------------------------------------------
// AllowUserEnter
// -------------------------------------------------------------------
void RoomEvents::AllowUserEnter(bool value)
{
	this->allowUserEnter = value;
}

// -------------------------------------------------------------------
// AllowUserExit
// -------------------------------------------------------------------
bool RoomEvents::AllowUserExit()
{
	return this->allowUserExit;
}

// -------------------------------------------------------------------
// AllowUserExit
// -------------------------------------------------------------------
void RoomEvents::AllowUserExit(bool value)
{
	this->allowUserExit = value;
}

// -------------------------------------------------------------------
// AllowUserCountChange
// -------------------------------------------------------------------
bool RoomEvents::AllowUserCountChange()
{
	return this->allowUserCountChange;
}

// -------------------------------------------------------------------
// AllowUserCountChange
// -------------------------------------------------------------------
void RoomEvents::AllowUserCountChange(bool value)
{
	this->allowUserCountChange = value;
}

// -------------------------------------------------------------------
// AllowUserVariablesUpdate
// -------------------------------------------------------------------
bool RoomEvents::AllowUserVariablesUpdate()
{
	return this->allowUserVariablesUpdate;
}

// -------------------------------------------------------------------
// AllowUserVariablesUpdate
// -------------------------------------------------------------------
void RoomEvents::AllowUserVariablesUpdate(bool value)
{
	this->allowUserVariablesUpdate = value;
}
		
}	// namespace Requests
}	// namespace Sfs2X

