// ===================================================================
//
// Description		
//		Contains the implementation of ObjectMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ObjectMessageRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ObjectMessageRequest::ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<Room> targetRoom, boost::shared_ptr<vector<boost::shared_ptr<User> > > recipients)
{
	this->type = (long int)GENERICMESSAGETYPE_OBJECT_MSG;
	this->parameters = obj;
	this->room = targetRoom;
	this->recipientInt = boost::shared_ptr<long int>();
	this->recipientUser = boost::shared_ptr<User>();
	this->recipientRoom = boost::shared_ptr<Room>();
	this->recipientString = boost::shared_ptr<string>();
	this->recipientUsersCollection = recipients;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ObjectMessageRequest::ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<Room> targetRoom)
{
	this->type = (long int)GENERICMESSAGETYPE_OBJECT_MSG;
	this->parameters = obj;
	this->room = targetRoom;
	this->recipientInt = boost::shared_ptr<long int>();
	this->recipientUser = boost::shared_ptr<User>();
	this->recipientRoom = boost::shared_ptr<Room>();
	this->recipientString = boost::shared_ptr<string>();
	this->recipientUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ObjectMessageRequest::ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj)
{
	this->type = (long int)GENERICMESSAGETYPE_OBJECT_MSG;
	this->parameters = obj;
	this->room = boost::shared_ptr<Room>();
	this->recipientInt = boost::shared_ptr<long int>();
	this->recipientUser = boost::shared_ptr<User>();
	this->recipientRoom = boost::shared_ptr<Room>();
	this->recipientString = boost::shared_ptr<string>();
	this->recipientUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ObjectMessageRequest::~ObjectMessageRequest()
{
}

}	// namespace Requests
}	// namespace Sfs2X


