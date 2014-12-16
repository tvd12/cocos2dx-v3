// ===================================================================
//
// Description		
//		Contains the implementation of RoomPermissions
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomPermissions.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomPermissions::RoomPermissions()
{
}

// -------------------------------------------------------------------
// AllowNameChange
// -------------------------------------------------------------------
bool RoomPermissions::AllowNameChange()
{
	return this->allowNameChange;
}

// -------------------------------------------------------------------
// AllowNameChange
// -------------------------------------------------------------------
void RoomPermissions::AllowNameChange(bool value)
{
	this->allowNameChange = value;
}

// -------------------------------------------------------------------
// AllowPasswordStateChange
// -------------------------------------------------------------------
bool RoomPermissions::AllowPasswordStateChange()
{
	return this->allowPasswordStateChange;
}

// -------------------------------------------------------------------
// AllowPasswordStateChange
// -------------------------------------------------------------------
void RoomPermissions::AllowPasswordStateChange(bool value)
{
	this->allowPasswordStateChange = value;
}

// -------------------------------------------------------------------
// AllowPublicMessages
// -------------------------------------------------------------------
bool RoomPermissions::AllowPublicMessages()
{
	return this->allowPublicMessages;
}

// -------------------------------------------------------------------
// AllowPublicMessages
// -------------------------------------------------------------------
void RoomPermissions::AllowPublicMessages(bool value)
{
	this->allowPublicMessages = value;
}

// -------------------------------------------------------------------
// AllowResizing
// -------------------------------------------------------------------
bool RoomPermissions::AllowResizing()
{
	return this->allowResizing;
}

// -------------------------------------------------------------------
// AllowResizing
// -------------------------------------------------------------------
void RoomPermissions::AllowResizing(bool value)
{
	this->allowResizing = value;
}

}	// namespace Requests
}	// namespace Sfs2X

