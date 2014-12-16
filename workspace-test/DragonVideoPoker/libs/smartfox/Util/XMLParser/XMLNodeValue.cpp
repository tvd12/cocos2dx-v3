// ===================================================================
//
// Description		
//		Contains the implementation of XMLNodeValue
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "XMLNodeValue.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNodeValue::XMLNodeValue()
	  : std::string() 
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNodeValue::XMLNodeValue(const boost::shared_ptr<XMLNodeValue> other)
	  : std::string(*other) 
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNodeValue::XMLNodeValue(const boost::shared_ptr<char> other)
	  : std::string(other.get()) 
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNodeValue::XMLNodeValue(string other)
	:  std::string(other) 
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
XMLNodeValue::~XMLNodeValue()
{
}

}	// namespace Util
}	// namespace Sfs2X

