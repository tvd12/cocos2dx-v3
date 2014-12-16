// ===================================================================
//
// Description		
//		Contains the implementation of SFSInvitation
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSInvitation.h"

namespace Sfs2X {
namespace Entities {
namespace Invitation {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSInvitation::SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee)
{
	Init(inviter, invitee, 15, boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSInvitation::SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer)
{
	Init(inviter, invitee, secondsForAnswer, boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSInvitation::SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer, boost::shared_ptr<ISFSObject> parameters)
{
	Init(inviter, invitee, secondsForAnswer, parameters);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSInvitation::~SFSInvitation()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void SFSInvitation::Init(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer, boost::shared_ptr<ISFSObject> parameters)
{
	this->inviter = inviter;
	this->invitee = invitee;
	this->secondsForAnswer = secondsForAnswer;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int SFSInvitation::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void SFSInvitation::Id(long int value)
{
	id = value;
}

// -------------------------------------------------------------------
// Inviter
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSInvitation::Inviter()
{
	return inviter;
}

// -------------------------------------------------------------------
// Invitee
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSInvitation::Invitee()
{
	return invitee;
}

// -------------------------------------------------------------------
// SecondsForAnswer
// -------------------------------------------------------------------
long int SFSInvitation::SecondsForAnswer()
{
	return secondsForAnswer;
}

// -------------------------------------------------------------------
// Params
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSInvitation::Params()
{
	return parameters;
}

}	// namespace Invitation
}	// namespace Entities
}	// namespace Sfs2X

