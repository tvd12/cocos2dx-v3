// ===================================================================
//
// Description		
//		Contains the implementation of PingPongRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PingPongRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PingPongRequest::PingPongRequest()
	: BaseRequest (RequestType_PingPong)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PingPongRequest::~PingPongRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void PingPongRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	// No params are sent
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void PingPongRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	// Maybe check last send time?
}

}	// namespace Requests
}	// namespace Sfs2X


