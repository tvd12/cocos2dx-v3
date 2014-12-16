// ===================================================================
//
// Description		
//		Contains the definition of InvitationReplyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __InvitationReplyRequest__
#define __InvitationReplyRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../CreateRoomRequest.h"
#include "../../Entities/Invitation/Invitation.h"
#include "../../Entities/Invitation/InvitationReply.h"
#include "../../Entities/Data/ISFSObject.h"

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
	/// Send a reply to an Invitation.
	/// </summary>
	/// <remarks>
	/// The reply can be either an ACCEPT or REFUSE. If the reply doesn't get to the inviter within the expected amount of time the system will handle it as a REFUSE.
	/// </remarks>
	class DLLImportExport InvitationReplyRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// <see cref="InvitationReplyRequest(Invitation*, InvitationReply*, ISFSObject*)"/>
		/// </summary>
		InvitationReplyRequest(boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation, boost::shared_ptr<InvitationReply> reply);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="invitation">
		/// a reference to the received invitation
		/// </param>
		/// <param name="reply">
		/// the reply code
		/// </param>
		/// <param name="parameters">
		/// custom reply parameters
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::INVITATION, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnInvitationReceived, (unsigned long long)this)));
		///			ptrSmartFox->AddEventListener(SFSEvent::INVITATION_REPLY_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnInvitationReplyError, (unsigned long long)this)));
		///
		///			static void OnInvitationReceived(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnInvitationReplyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnInvitationReceived(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///			{
		///				// Get the pointer to my class
		///				CMyClass* instance = (CMyClass*)ptrContext;
		///
		///				// Let's accept this invitation
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueInvitation = (*ptrEventParams)["invitation"];
		///				boost::shared_ptr<Invitation> ptrNotifiedInvitation = ((boost::static_pointer_cast<User>))(ptrEventParamValueInvitation);
		///
		///				boost::shared_ptr<IRequest> request (new InvitationReplyRequest(ptrNotifiedInvitation, INVITATIONREPLY_ACCEPT));
		///				ptrSmartFox->Send(request);
		///			}
		///
		///			void CMyClass::OnInvitationReceived(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///			{
		///				// Get the pointer to my class
		///				CMyClass* instance = (CMyClass*)ptrContext;
		///
		///				// Handle problems with the invitation reply
		///				boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["errorMessage"];
		///				boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///			}
		/// 	\endcode
		/// </example>
        /// <seealso cref="Core.SFSEvent.INVITATION_REPLY_ERROR"/>
		/// <seealso cref="SFSInvitation"/>
		/// <seealso cref="InvitationReply"/>
		InvitationReplyRequest(boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation, boost::shared_ptr<InvitationReply> reply, boost::shared_ptr<ISFSObject> parameters);

		virtual ~InvitationReplyRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_INVITATION_ID;
		
		static boost::shared_ptr<string> KEY_INVITATION_REPLY;

		static boost::shared_ptr<string> KEY_INVITATION_PARAMS;

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
		void Init(boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation, boost::shared_ptr<InvitationReply> reply, boost::shared_ptr<ISFSObject> parameters);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation;
		boost::shared_ptr<InvitationReply> reply;
		boost::shared_ptr<ISFSObject> parameters;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
