// ===================================================================
//
// Description		
//		Contains the definition of BanMode
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BanMode__
#define __BanMode__

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// The class contains constants to specify the banishmen modality for a BanUserRequest
	/// </summary>
	/// <seealso cref="BanUserRequest"/>    
	typedef enum BanMode 
    {
		/// <summary>
		/// User is banned by IP Address
		/// </summary>
		BANMODE_BY_ADDRESS = 0,
		
		/// <summary>
		/// User is banned by name
		/// </summary>
		BANMODE_BY_NAME = 1
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
