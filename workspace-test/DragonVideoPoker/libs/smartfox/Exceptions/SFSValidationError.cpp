// ===================================================================
//
// Description		
//		Contains the implementation of SFSValidationError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSValidationError.h"

namespace Sfs2X {
namespace Exceptions {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSValidationError::SFSValidationError(boost::shared_ptr<string> message, boost::shared_ptr<list<string> > errors)
{
	this->message = message;
	this->errors = errors;
}

// -------------------------------------------------------------------
// Errors
// -------------------------------------------------------------------
boost::shared_ptr<list<string> > SFSValidationError::Errors()
{
	return errors;
}

}	// namespace Exceptions
}	// namespace Sfs2X
