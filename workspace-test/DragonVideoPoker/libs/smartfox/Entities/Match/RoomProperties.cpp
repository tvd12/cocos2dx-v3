// ===================================================================
//
// Description		
//		Contains the implementation of RoomProperties
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomProperties.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

namespace Sfs2X {
namespace Entities {
namespace Match {

boost::shared_ptr<string> RoomProperties::NAME (new string("${N}"));
boost::shared_ptr<string> RoomProperties::GROUP_ID (new string("${G}"));
boost::shared_ptr<string> RoomProperties::MAX_USERS (new string("${MXU}"));
boost::shared_ptr<string> RoomProperties::MAX_SPECTATORS (new string("${MXS}"));
boost::shared_ptr<string> RoomProperties::USER_COUNT (new string("${UC}"));
boost::shared_ptr<string> RoomProperties::SPECTATOR_COUNT (new string("${SC}"));
boost::shared_ptr<string> RoomProperties::IS_GAME (new string("${ISG}"));
boost::shared_ptr<string> RoomProperties::IS_PRIVATE (new string("${ISP}"));
boost::shared_ptr<string> RoomProperties::HAS_FREE_PLAYER_SLOTS (new string("${HFP}"));
boost::shared_ptr<string> RoomProperties::IS_TYPE_SFSGAME (new string("${IST}"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomProperties::RoomProperties()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("This class cannot be instantiated"))); 
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


