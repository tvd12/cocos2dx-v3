// ===================================================================
//
// Description		
//		Contains the implementation of MessageRecipientMode
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "MessageRecipientMode.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MessageRecipientMode::MessageRecipientMode(long int mode, boost::shared_ptr<User> target)
{
	if (mode < (long int)MESSAGERECIPIENTTYPE_TO_USER || mode > (long int)MESSAGERECIPIENTTYPE_TO_ZONE ) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Illegal recipient mode: " + mode))); 
	}
				
	this->mode = mode;
	this->targetUser = target;
	this->targetRoom = boost::shared_ptr<Room>();
	this->targetString = boost::shared_ptr<string>();
	this->targetInt = boost::shared_ptr<long int>();
	this->targetUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MessageRecipientMode::MessageRecipientMode(long int mode, boost::shared_ptr<Room> target)
{
	if (mode < (long int)MESSAGERECIPIENTTYPE_TO_USER || mode > (long int)MESSAGERECIPIENTTYPE_TO_ZONE ) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Illegal recipient mode: " + mode))); 
	}
				
	this->mode = mode;
	this->targetUser = boost::shared_ptr<User>();
	this->targetRoom = target;
	this->targetString = boost::shared_ptr<string>();
	this->targetInt = boost::shared_ptr<long int>();
	this->targetUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MessageRecipientMode::MessageRecipientMode(long int mode, string target)
{
	if (mode < (long int)MESSAGERECIPIENTTYPE_TO_USER || mode > (long int)MESSAGERECIPIENTTYPE_TO_ZONE ) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Illegal recipient mode: " + mode))); 
	}
				
	this->mode = mode;
	this->targetUser = boost::shared_ptr<User>();
	this->targetRoom = boost::shared_ptr<Room>();
	this->targetString = boost::shared_ptr<string>(new string(target));
	this->targetInt = boost::shared_ptr<long int>();
	this->targetUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MessageRecipientMode::~MessageRecipientMode()
{
	if (targetUsersCollection != NULL)
	{
		targetUsersCollection->clear();
	}
}

// -------------------------------------------------------------------
// TargetInt
// -------------------------------------------------------------------
long int MessageRecipientMode::TargetInt()
{
	if (this->targetInt == NULL)
		return 0;

	return *(this->targetInt);
}

// -------------------------------------------------------------------
// TargetUser
// -------------------------------------------------------------------
boost::shared_ptr<User> MessageRecipientMode::TargetUser()
{
	return this->targetUser;
}

// -------------------------------------------------------------------
// TargetRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room> MessageRecipientMode::TargetRoom()
{
	return this->targetRoom;
}

// -------------------------------------------------------------------
// TargetString
// -------------------------------------------------------------------
boost::shared_ptr<string> MessageRecipientMode::TargetString()
{
	if (this->targetString == NULL)
		return boost::shared_ptr<string>();

	return this->targetString;
}

// -------------------------------------------------------------------
// TargetUsersCollection
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > MessageRecipientMode::TargetUsersCollection()
{
	return this->targetUsersCollection;
}

// -------------------------------------------------------------------
// Mode
// -------------------------------------------------------------------
long int MessageRecipientMode::Mode()
{
	return this->mode;
}

		
}	// namespace Requests
}	// namespace Sfs2X

