// ===================================================================
//
// Description		
//		Contains the implementation of UserProperties
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "UserProperties.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

namespace Sfs2X {
namespace Entities {
namespace Match {

boost::shared_ptr<string> UserProperties::NAME (new string("${N}"));
boost::shared_ptr<string> UserProperties::IS_PLAYER (new string("${ISP}"));
boost::shared_ptr<string> UserProperties::IS_SPECTATOR (new string("${ISS}"));
boost::shared_ptr<string> UserProperties::IS_NPC (new string("${ISN}"));
boost::shared_ptr<string> UserProperties::PRIVILEGE_ID (new string("${PRID}"));
boost::shared_ptr<string> UserProperties::IS_IN_ANY_ROOM (new string("${IAR}"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
UserProperties::UserProperties()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("This class cannot be instantiated"))); 
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


