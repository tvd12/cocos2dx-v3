// ===================================================================
//
// Description		
//		Contains the definition of GenericMessageType
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __GenericMessageType__
#define __GenericMessageType__

namespace Sfs2X {
namespace Requests {

    typedef enum GenericMessageType 
    {
		GENERICMESSAGETYPE_PUBLIC_MSG = 0,
		GENERICMESSAGETYPE_PRIVATE_MSG = 1,
		GENERICMESSAGETYPE_MODERATOR_MSG = 2,
		GENERICMESSAGETYPE_ADMIN_MSG = 3,
		GENERICMESSAGETYPE_OBJECT_MSG = 4,
		GENERICMESSAGETYPE_BUDDY_MSG = 5
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
