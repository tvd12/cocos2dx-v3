// ===================================================================
//
// Description		
//		Contains the implementation of HandshakeRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "HandshakeRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> HandshakeRequest::KEY_SESSION_TOKEN (new string("tk"));
boost::shared_ptr<string> HandshakeRequest::KEY_API (new string("api"));
boost::shared_ptr<string> HandshakeRequest::KEY_COMPRESSION_THRESHOLD (new string("ct"));
boost::shared_ptr<string> HandshakeRequest::KEY_RECONNECTION_TOKEN (new string("rt"));
boost::shared_ptr<string> HandshakeRequest::KEY_CLIENT_TYPE (new string("cl"));
boost::shared_ptr<string> HandshakeRequest::KEY_MAX_MESSAGE_SIZE (new string("ms"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
HandshakeRequest::HandshakeRequest(string apiVersion, string reconnectionToken, string clientDetails)
	: BaseRequest (RequestType_Handshake)
{
	sfso->PutUtfString(KEY_API, boost::shared_ptr<string>(new string(apiVersion)));		
	sfso->PutUtfString(KEY_CLIENT_TYPE, boost::shared_ptr<string>(new string(clientDetails)));		

	boost::shared_ptr<bool> value (new bool());
	*value = true;

	sfso->PutBool("bin", value);
			
	// send reconnection token, if any
	if (reconnectionToken.size() > 0)
	{
		sfso->PutUtfString(KEY_RECONNECTION_TOKEN, boost::shared_ptr<string>(new string(reconnectionToken)));
	}		
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
HandshakeRequest::~HandshakeRequest()
{
}

}	// namespace Requests
}	// namespace Sfs2X
