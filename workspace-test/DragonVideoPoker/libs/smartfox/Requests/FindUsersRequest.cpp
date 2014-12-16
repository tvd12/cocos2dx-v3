// ===================================================================
//
// Description		
//		Contains the implementation of FindUsersRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "FindUsersRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> FindUsersRequest::KEY_EXPRESSION (new string("e"));
boost::shared_ptr<string> FindUsersRequest::KEY_GROUP (new string("g"));
boost::shared_ptr<string> FindUsersRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> FindUsersRequest::KEY_LIMIT (new string("l"));
boost::shared_ptr<string> FindUsersRequest::KEY_FILTERED_USERS (new string("fu"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindUsersRequest::FindUsersRequest(boost::shared_ptr<MatchExpression> expr)
	: BaseRequest (RequestType_FindUsers)
{
	Init(expr);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindUsersRequest::FindUsersRequest(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target)
	: BaseRequest (RequestType_FindUsers)
{
	Init(expr, target, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindUsersRequest::FindUsersRequest(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target, long int limit)
	: BaseRequest (RequestType_FindUsers)
{
	Init(expr, target, limit);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindUsersRequest::FindUsersRequest(boost::shared_ptr<MatchExpression> expr, string target)
	: BaseRequest (RequestType_FindUsers)
{
	Init(expr, target, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindUsersRequest::FindUsersRequest(boost::shared_ptr<MatchExpression> expr, string target, long int limit)
	: BaseRequest (RequestType_FindUsers)
{
	Init(expr, target, limit);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
FindUsersRequest::~FindUsersRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void FindUsersRequest::Init(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target, long int limit)
{
	this->matchExpr = expr;
	this->targetRoom = target;
	this->targetString = boost::shared_ptr<string>();
	this->limit = limit;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void FindUsersRequest::Init(boost::shared_ptr<MatchExpression> expr, string target, long int limit)
{
	this->matchExpr = expr;
	this->targetRoom = boost::shared_ptr<Room>();
	this->targetString = boost::shared_ptr<string>(new string(target));
	this->limit = limit;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void FindUsersRequest::Init(boost::shared_ptr<MatchExpression> expr)
{
	this->matchExpr = expr;
	this->targetRoom = boost::shared_ptr<Room>();
	this->targetString = boost::shared_ptr<string>();
	this->limit = 0;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void FindUsersRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (matchExpr == NULL)
		errors->push_back("Missing Match Expression");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("FindUsers request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void FindUsersRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutSFSArray(KEY_EXPRESSION, matchExpr->ToSFSArray());
	
	if (targetRoom != NULL)
	{
		boost::shared_ptr<long int> valueId (new long int());
		*valueId = targetRoom->Id();
		sfso->PutInt(KEY_ROOM, valueId);
	}

	else if (targetString != NULL)
	{
		sfso->PutUtfString(KEY_GROUP, targetString);
	}
	else
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back("Unsupport target type for FindUsersRequest");

		sfs->Log()->Warn(messages);
	}

	// 2^15 is already too many Rooms :)
	if (limit > 0)
	{
		boost::shared_ptr<short int> valueLimit (new short int());
		*valueLimit = (short int)limit;
		sfso->PutShort(KEY_LIMIT, valueLimit);
	}
}

}	// namespace Requests
}	// namespace Sfs2X



