// ===================================================================
//
// Description		
//		Contains the definition of UserPrivileges
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UserPrivileges__
#define __UserPrivileges__

namespace Sfs2X {
namespace Entities {

    typedef enum UserPrivileges 
    {
		/// <summary>
		/// Guest user, usually the lowest level in the permission scale
		/// </summary>
		USERPRIVILEGES_GUEST = 0,
		
		/// <summary>
		/// The standard user is usally registered in system and uses a unique name and password to login
		/// </summary>
		USERPRIVILEGES_STANDARD = 1,
		
		/// <summary>
		/// The moderator has powers to send ModeratorMessages, kicking users and banning them
		/// </summary>
		USERPRIVILEGES_MODERATOR = 2,
		
		/// <summary>
		/// The administrator has powers to send AdminMessages, kicking users and banning them
		/// </summary>
		USERPRIVILEGES_ADMINISTRATOR = 3
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
