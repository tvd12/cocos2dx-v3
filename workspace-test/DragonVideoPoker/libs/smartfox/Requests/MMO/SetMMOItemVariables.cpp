// ===================================================================
//
// Description		
//		Contains the implementation of SetMMOItemVariables
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "SetMMOItemVariables.h"

namespace Sfs2X {
namespace Requests {
namespace MMO {

boost::shared_ptr<string> SetMMOItemVariables::KEY_ROOM_ID (new string("r"));
boost::shared_ptr<string> SetMMOItemVariables::KEY_ITEM_ID (new string("i"));
boost::shared_ptr<string> SetMMOItemVariables::KEY_VAR_LIST (new string("v"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetMMOItemVariables::SetMMOItemVariables()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetMMOItemVariables::~SetMMOItemVariables()
{
}

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X


