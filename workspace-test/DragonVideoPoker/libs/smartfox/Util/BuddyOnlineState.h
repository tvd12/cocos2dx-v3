// ===================================================================
//
// Description		
//		Contains the definition of BuddyOnlineState
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BuddyOnlineState__
#define __BuddyOnlineState__

namespace Sfs2X {
namespace Util {

	/// <summary>
	/// Provide information on the Online Status of the Buddy
	/// </summary>
	typedef enum BuddyOnlineState
    {
		/// <summary>
		/// The Buddy is online
		/// </summary>
		BUDDYONLINESTATE_ONLINE = 0,
		
		/// <summary>
		/// The Buddy is offline in the Buddy system
		/// </summary>
		BUDDYONLINESTATE_OFFLINE = 1,
		
		/// <summary>
		/// The Buddy left the server
		/// </summary>
		BUDDYONLINESTATE_LEFT_THE_SERVER = 2
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
