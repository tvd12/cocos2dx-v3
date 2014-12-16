// ===================================================================
//
// Description		
//		Contains the implementation of SFSConstants
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSConstants.h"

namespace Sfs2X {
namespace Entities {

boost::shared_ptr<string> SFSConstants::DEFAULT_GROUP_ID (new string("default"));
boost::shared_ptr<string> SFSConstants::REQUEST_UDP_PACKET_ID (new string("$FS_REQUEST_UDP_TIMESTAMP"));

}	// namespace Entities
}	// namespace Sfs2X
