// ===================================================================
//
// Description		
//		Contains the definition of SFSError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSError.h"

namespace Sfs2X {
namespace Exceptions {


// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSError::SFSError (boost::shared_ptr<string> message) 
{
	this->message = message;
}

}	// namespace Exceptions
}	// namespace Sfs2X
