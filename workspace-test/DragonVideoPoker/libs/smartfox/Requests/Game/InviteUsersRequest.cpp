// ===================================================================
//
// Description		
//		Contains the implementation of InviteUsersRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "InviteUsersRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

boost::shared_ptr<string> InviteUsersRequest::KEY_USER (new string("u"));
boost::shared_ptr<string> InviteUsersRequest::KEY_USER_ID (new string("ui"));
boost::shared_ptr<string> InviteUsersRequest::KEY_INVITATION_ID (new string("ii"));
boost::shared_ptr<string> InviteUsersRequest::KEY_TIME (new string("t"));
boost::shared_ptr<string> InviteUsersRequest::KEY_PARAMS (new string("p"));
boost::shared_ptr<string> InviteUsersRequest::KEY_INVITEE_ID (new string("ee"));
boost::shared_ptr<string> InviteUsersRequest::KEY_INVITED_USERS (new string("iu"));
boost::shared_ptr<string> InviteUsersRequest::KEY_REPLY_ID (new string("ri"));
const long int InviteUsersRequest::MAX_INVITATIONS_FROM_CLIENT_SIDE = 8;
const long int InviteUsersRequest::MIN_EXPIRY_TIME = 5;
const long int InviteUsersRequest::MAX_EXPIRY_TIME = 300;

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------		
InviteUsersRequest::InviteUsersRequest(boost::shared_ptr<list<boost::shared_ptr<User> > > invitedUsers, long int secondsForReply, boost::shared_ptr<ISFSObject> parameters)
	: BaseRequest (RequestType_InviteUser)
{
	this->invitedUsers = invitedUsers;
	this->invitedBuddy = boost::shared_ptr<list<boost::shared_ptr<Buddy> > >();
	this->secondsForAnswer = secondsForReply;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------		
InviteUsersRequest::InviteUsersRequest(boost::shared_ptr<list<boost::shared_ptr<Buddy> > > invitedUsers, long int secondsForReply, boost::shared_ptr<ISFSObject> parameters)
	: BaseRequest (RequestType_InviteUser)
{
	this->invitedUsers = boost::shared_ptr<list<boost::shared_ptr<User> > >();
	this->invitedBuddy = invitedUsers;
	this->secondsForAnswer = secondsForReply;
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------		
InviteUsersRequest::~InviteUsersRequest()
{
	if (invitedUsers != NULL)
	{
		invitedUsers->clear();
	}

	if (invitedBuddy != NULL)
	{
		invitedBuddy->clear();
	}
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void InviteUsersRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());

	long int counterInvited = 0;

	if (invitedUsers != NULL)
	{
		counterInvited += invitedUsers->size();
	}

	if (invitedBuddy != NULL)
	{
		counterInvited += invitedBuddy->size();
	}

	if (counterInvited < 1)
		errors->push_back("No invitation(s) to send");

	if (counterInvited > MAX_INVITATIONS_FROM_CLIENT_SIDE)
		errors->push_back("Too many invitations. Max allowed from client side is: " + MAX_INVITATIONS_FROM_CLIENT_SIDE);

	if (secondsForAnswer < 5 || secondsForAnswer > 300)
	{
		char buffer[512];
		sprintf (buffer, "SecondsForAnswer value is out of range (%ld-%ld)", MIN_EXPIRY_TIME, MAX_EXPIRY_TIME);
		string str = buffer;

		errors->push_back(str);
	}

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("InvitationReply request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void InviteUsersRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<vector<boost::shared_ptr<long int> > > invitedUserIds (new vector<boost::shared_ptr<long int> >());

	// Check items validity, accept any User or Buddy object(s)
	list<boost::shared_ptr<User> >::iterator iteratorInvitedUser;
	list<boost::shared_ptr<Buddy> >::iterator iteratorInvitedBuddy;

	if (invitedUsers != NULL)
	{
		for (iteratorInvitedUser = invitedUsers->begin(); iteratorInvitedUser != invitedUsers->end(); iteratorInvitedUser++)
		{
			// Can't invite myself!
			if ((*iteratorInvitedUser) == sfs->MySelf())
				continue;

			boost::shared_ptr<long int> valueId (new long int());
			*valueId = (*iteratorInvitedUser)->Id();
			invitedUserIds->push_back(valueId);
		}
	}

	if (invitedBuddy != NULL)
	{
		for (iteratorInvitedBuddy = invitedBuddy->begin(); iteratorInvitedBuddy != invitedBuddy->end(); iteratorInvitedBuddy++)
		{
			boost::shared_ptr<long int> valueId (new long int());
			*valueId = (*iteratorInvitedBuddy)->Id();
			invitedUserIds->push_back(valueId);
		}
	}

	// List of invited people
	sfso->PutIntArray(KEY_INVITED_USERS, invitedUserIds);

	// Time to answer
	boost::shared_ptr<short int> valueSecondsForAnswer (new short int());
	*valueSecondsForAnswer = (short int)secondsForAnswer;

	sfso->PutShort(KEY_TIME, (boost::static_pointer_cast<short int>)(valueSecondsForAnswer));

	// Custom params
	if (parameters != NULL)
		sfso->PutSFSObject(KEY_PARAMS, parameters);
}

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X





