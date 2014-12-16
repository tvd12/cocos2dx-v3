// ===================================================================
//
// Description		
//		Contains the definition of BuddyVariable interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BuddyVariable__
#define __BuddyVariable__

#include "UserVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

	class DLLImportExport BuddyVariable : public UserVariable
	{
	public:
		/// <summary>
		/// Return true if this is an offline Buddy Variable
		/// </summary>
		/// <remarks>
		/// By convention any Buddy Variable whose name starts with the dollar sign ($)
		/// will be regarded as persistent and stored locally by the server.
		/// 
		/// These variables are also referred to as "offline variables" because they are available
		/// to other Users even when the Buddy is offline.
		/// </remarks>
		virtual bool IsOffline() = 0;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
