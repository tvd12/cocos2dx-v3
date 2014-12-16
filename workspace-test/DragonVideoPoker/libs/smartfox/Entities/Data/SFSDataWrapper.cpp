// ===================================================================
//
// Description		
//		Contains the implementation of SFSDataWrapper
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSDataWrapper.h"
#include "ISFSObject.h"

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(long int type, boost::shared_ptr<void> data)
{
	this->type = type;
	this->data = data;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(SFSDataType tp, boost::shared_ptr<void> data)
{
	this->type = (long int)tp;
	this->data = data;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSDataWrapper::~SFSDataWrapper()
{
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
long int SFSDataWrapper::Type()
{
	return type;
}

// -------------------------------------------------------------------
// Data
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSDataWrapper::Data()
{
	return data;
}


}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

