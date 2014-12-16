// ===================================================================
//
// Description		
//		Contains the implementation of BanUserRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BanUserRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> BanUserRequest::KEY_USER_ID (new string("u"));
boost::shared_ptr<string> BanUserRequest::KEY_MESSAGE (new string("m"));
boost::shared_ptr<string> BanUserRequest::KEY_DELAY (new string("d"));
boost::shared_ptr<string> BanUserRequest::KEY_BAN_MODE (new string("b"));
boost::shared_ptr<string> BanUserRequest::KEY_BAN_DURATION_HOURS (new string("dh"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId)
	: BaseRequest (RequestType_BanUser)
{
	Init(userId, "", BANMODE_BY_NAME, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, string message)
	: BaseRequest (RequestType_BanUser)
{
	Init(userId, message, BANMODE_BY_NAME, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, string message, BanMode banMode)
	: BaseRequest (RequestType_BanUser)
{
	Init(userId, message, banMode, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, string message, BanMode banMode, long int delaySeconds)
	: BaseRequest (RequestType_BanUser)
{
	Init(userId, message, banMode, delaySeconds, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, string message, BanMode banMode, long int delaySeconds, long int durationHours)
	: BaseRequest (RequestType_BanUser)
{
	Init(userId, message, banMode, delaySeconds, durationHours);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BanUserRequest::~BanUserRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void BanUserRequest::Init(long int userId, string message, BanMode banMode, long int delaySeconds, long int durationHours)
{
	this->userId = userId;
	this->message = boost::shared_ptr<string>(new string(message));
	this->banMode = banMode;
	this->delay = delaySeconds;
	this->durationHours = durationHours;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void BanUserRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());

	// No valudation needed
	if (!sfs->MySelf()->IsModerator() && !sfs->MySelf()->IsAdmin())
		errors->push_back("You don't have enough permissions to execute this request.");
				
	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("BanUser request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void BanUserRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<long int> valueUserId (new long int());
	*valueUserId = userId;
	sfso->PutInt(KEY_USER_ID, valueUserId);

	boost::shared_ptr<long int> valueDelay (new long int());
	*valueDelay = delay;
	sfso->PutInt(KEY_DELAY, valueDelay);

	boost::shared_ptr<long int> valueBanMode (new long int());
	*valueBanMode = banMode;
	sfso->PutInt(KEY_BAN_MODE, valueBanMode);

	boost::shared_ptr<long int> valueDurationHours (new long int());
	*valueDurationHours = durationHours;
	sfso->PutInt(KEY_BAN_DURATION_HOURS, valueDurationHours);
				
	if (message != NULL && message->size() > 0)
		sfso->PutUtfString(KEY_MESSAGE, message);
}

}	// namespace Requests
}	// namespace Sfs2X


