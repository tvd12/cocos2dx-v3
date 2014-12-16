// ===================================================================
//
// Description		
//		Contains the implementation of SFSCodecError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSCodecError.h"

namespace Sfs2X {
namespace Exceptions {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSCodecError::SFSCodecError(boost::shared_ptr<string> message)
{
	this->message = message;
}

}	// namespace Exceptions
}	// namespace Sfs2X
