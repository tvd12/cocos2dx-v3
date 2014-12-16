// ===================================================================
//
// Description		
//		Contains the definition of InvitationReply
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __InvitationReply__
#define __InvitationReply__

namespace Sfs2X {
namespace Entities {
namespace Invitation {

	/// <summary>
	/// Provides two constants used for replying to an Invitation
	/// </summary>
	/// <seealso cref="SFSInvitation"/>
	/// <seealso cref="Requests.Game.InviteUsersRequest"/>
    typedef enum InvitationReply 
    {
		/// <summary>
		/// Accept the Invitation
		/// </summary>
		INVITATIONREPLY_ACCEPT = 0,
		
		/// <summary>
		/// Refuse the Invitation
		/// </summary>
		INVITATIONREPLY_REFUSE = 1
    };

}	// namespace Invitation
}	// namespace Entities
}	// namespace Sfs2X

#endif
