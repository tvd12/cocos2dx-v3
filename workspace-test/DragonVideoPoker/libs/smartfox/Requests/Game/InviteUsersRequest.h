// ===================================================================
//
// Description		
//		Contains the definition of InviteUsersRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __InviteUsersRequest__
#define __InviteUsersRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../CreateRoomRequest.h"
#include "../../Entities/Invitation/Invitation.h"
#include "../../Entities/Invitation/InvitationReply.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Buddy.h"
#include "../../Entities/User.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Invitation;

namespace Sfs2X {
namespace Requests {
namespace Game {

	/// <summary>
	/// end one or more generic invitations to a list of Users.
	/// </summary>
	/// <remarks>
	/// Invitations can be used for different purposes such as playing games, visiting a specific Room, Buddy requests etc...
	/// </remarks>
	/// <seealso cref="SFSInvitation"/>
	class DLLImportExport InviteUsersRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="invitedUsers">
		/// a list of invited Users
		/// </param>
		/// <param name="secondsForReply">
		/// the amount of seconds allowed to the invited User to reply (recommended range 15-40 seconds)
		/// </param>
		/// <param name="parameters">
		/// optional custom invitation parameters 
		/// </param>
		/// <example>
		///		\code{.cpp}
		/// 		// Add event listener for the Invitation reply event
		///			ptrSmartFox->AddEventListener(SFSEvent::INVITATION_REPLY, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnInvitationReply, (unsigned long long)this)));
		///
		/// 		// Prepare the invitation
		///			boost::shared_ptr<User> user1 = = ptrSmartFox->UserManager()->GetUserByName("Piggy");
		///			boost::shared_ptr<User> user2 = = ptrSmartFox->UserManager()->GetUserByName("Gonzo");
		///
		///			boost::shared_ptr<list<boost::shared_ptr<User>>> invitedUsers (new list<boost::shared_ptr<User>());
		///			invitedUsers->push_back(user1);
		///			invitedUsers->push_back(user2);
		///
		/// 		// Send invitation
		///			boost::shared_ptr<IRequest> request (new InviteUsersRequest(invitedUsers, 20, boost::shared_ptr<ISFSObject>()));
		///			ptrSmartFox->Send(request);
		///
		///			static void OnInvitationReply(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		/// 		// Handle responses from invited users
		///			void CMyClass::OnInvitationReply(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///			{
		///				// Get the pointer to my class
		///				CMyClass* instance = (CMyClass*)ptrContext;
		///
		///				// If User accepts the invitation, send the Room id to join (as promised)
		///				boost::shared_ptr<void> ptrEventParamValueReply = (*ptrEventParams)["reply"];
		///				boost::shared_ptr<unsigned char> ptrNotifiedReply = ((boost::static_pointer_cast<unsigned char>))(ptrEventParamValueReply);
		///				if (*ptrNotifiedReply) == INVITATIONREPLY_ACCEPT)
		///				{
		/// 				// Send a game move to all players
		///					boost::shared_ptr<ISFSObject> dataObj (new SFSObject());
		/// 				dataObj->PutInt("roomId", aRoomReference->Id());
		///
		///					boost::shared_ptr<IRequest> request (new ObjectMessageRequest(dataObj));
		///					ptrSmartFox->Send(request);
		///				}
		///				else
		///				{
		///					// User has refused the invitation
		///					boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["invitee"];
		///					boost::shared_ptr<User> ptrNotifiedReply = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
		///				}
		/// 		}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.INVITATION_REPLY"/>
		/// <seealso cref="SFSInvitation"/>
		/// <seealso cref="InvitationReply"/>
		InviteUsersRequest(boost::shared_ptr<list<boost::shared_ptr<User> > > invitedUsers, long int secondsForReply, boost::shared_ptr<ISFSObject> parameters);
		InviteUsersRequest(boost::shared_ptr<list<boost::shared_ptr<Buddy> > > invitedUsers, long int secondsForReply, boost::shared_ptr<ISFSObject> parameters);

		virtual ~InviteUsersRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_USER;
		
		static boost::shared_ptr<string> KEY_USER_ID;
		
		static boost::shared_ptr<string> KEY_INVITATION_ID;
		
		static boost::shared_ptr<string> KEY_TIME;
		
		static boost::shared_ptr<string> KEY_PARAMS;
		
		static boost::shared_ptr<string> KEY_INVITEE_ID;
		
		static boost::shared_ptr<string> KEY_INVITED_USERS;
		
		static boost::shared_ptr<string> KEY_REPLY_ID;
		
		static const long int MAX_INVITATIONS_FROM_CLIENT_SIDE;
		static const long int MIN_EXPIRY_TIME;
		static const long int MAX_EXPIRY_TIME;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<list<boost::shared_ptr<User> > > invitedUsers;
		boost::shared_ptr<list<boost::shared_ptr<Buddy> > > invitedBuddy;
		long int secondsForAnswer;
		boost::shared_ptr<ISFSObject> parameters;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
