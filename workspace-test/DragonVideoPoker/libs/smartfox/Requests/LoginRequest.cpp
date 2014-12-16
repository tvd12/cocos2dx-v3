// ===================================================================
//
// Description		
//		Contains the implementation of LoginRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "LoginRequest.h"
#include "../Util/md5/md5.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> LoginRequest::KEY_ZONE_NAME (new string("zn"));
boost::shared_ptr<string> LoginRequest::KEY_USER_NAME (new string("un"));
boost::shared_ptr<string> LoginRequest::KEY_PASSWORD (new string("pw"));
boost::shared_ptr<string> LoginRequest::KEY_PARAMS (new string("p"));
boost::shared_ptr<string> LoginRequest::KEY_PRIVILEGE_ID (new string("pi"));
boost::shared_ptr<string> LoginRequest::KEY_ID (new string("id"));
boost::shared_ptr<string> LoginRequest::KEY_ROOMLIST (new string("rl"));
boost::shared_ptr<string> LoginRequest::KEY_RECONNECTION_SECONDS (new string("rs"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LoginRequest::LoginRequest(string userName, string password, string zoneName, boost::shared_ptr<ISFSObject> parameters)
	: BaseRequest(RequestType_Login)
{
	Init(userName, password, zoneName, parameters);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LoginRequest::LoginRequest(string userName, string password, string zoneName)
	: BaseRequest(RequestType_Login)
{
	Init(userName, password, zoneName, boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LoginRequest::LoginRequest(string userName, string password)
	: BaseRequest(RequestType_Login)
{
	Init(userName, password, "", boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LoginRequest::LoginRequest(string userName)
	: BaseRequest(RequestType_Login)
{
	Init(userName, "", "", boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
LoginRequest::~LoginRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void LoginRequest::Init(string userName, string password, string zoneName, boost::shared_ptr<ISFSObject> parameters)
{
	this->userName = boost::shared_ptr<string>(new string(userName));
	this->password = boost::shared_ptr<string>(new string(password));
	this->zoneName = boost::shared_ptr<string>(new string(zoneName));
	this->parameters = parameters;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void LoginRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	if (sfs->MySelf() != NULL) 
	{
		boost::shared_ptr<list<string> > log (new list<string>());
		log->push_back("You are already logged in. Logout first");

		boost::shared_ptr<string> message (new string("LoginRequest Error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, log));
		throw exception;
	}

	// Attempt to use config data, if any
	if (((zoneName == NULL) || (zoneName->size() == 0)) && sfs->Config() != NULL)
	{
		zoneName = boost::shared_ptr<string>(new string(sfs->Config()->Zone()));
	}

	if ((zoneName == NULL) || (zoneName->size() == 0)) 
	{
		boost::shared_ptr<list<string> > log (new list<string>());
		log->push_back("Missing Zone name");

		boost::shared_ptr<string> message (new string("LoginRequest Error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, log));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void LoginRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_ZONE_NAME, zoneName);
	sfso->PutUtfString(KEY_USER_NAME, userName);
			
	/*
	* password: use secure login system based on CHAP technique
	* http://www.networkworld.com/newsletters/web/2004/0419web1.html
	*/
	if ((password != NULL) && (password->size() > 0)) 
	{
		string passwordToEncode;
		passwordToEncode = (*(sfs->SessionToken())) + (*password);

		md5_byte_t digest[16];
		md5_state_t state;
		md5_init(&state);
		md5_append(&state, (const md5_byte_t *)passwordToEncode.c_str(), passwordToEncode.size());
		md5_finish(&state, digest);

		char hex_output[16*2 + 1];
		for (int enumerator = 0; enumerator < 16; ++enumerator)
		{
			sprintf(hex_output + enumerator * 2, "%02x", digest[enumerator]);
		}
		password->clear();
		password->assign(hex_output);
	}
			
	sfso->PutUtfString(KEY_PASSWORD, password);
						
	if (parameters != NULL) 
	{
		sfso->PutSFSObject(KEY_PARAMS, parameters);
	}
}

}	// namespace Requests
}	// namespace Sfs2X
