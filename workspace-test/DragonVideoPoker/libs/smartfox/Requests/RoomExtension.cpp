// ===================================================================
//
// Description		
//		Contains the implementation of RoomExtension
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomExtension.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomExtension::RoomExtension(string id, string className)
{
	this->id = boost::shared_ptr<string>(new string(id));
	this->className = boost::shared_ptr<string>(new string(className));
	this->propertiesFile = boost::shared_ptr<string>();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomExtension::Id()
{
	return this->id;
}

// -------------------------------------------------------------------
// ClassName
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomExtension::ClassName()
{
	return this->className;
}

// -------------------------------------------------------------------
// PropertiesFile
// -------------------------------------------------------------------
boost::shared_ptr<string> RoomExtension::PropertiesFile()
{
	return this->propertiesFile;
}

// -------------------------------------------------------------------
// PropertiesFile
// -------------------------------------------------------------------
void RoomExtension::PropertiesFile(string value)
{
	this->propertiesFile = boost::shared_ptr<string>(new string(value));
}

}	// namespace Requests
}	// namespace Sfs2X

