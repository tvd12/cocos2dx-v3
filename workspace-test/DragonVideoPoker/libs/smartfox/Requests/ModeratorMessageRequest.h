// ===================================================================
//
// Description		
//		Contains the definition of ModeratorMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ModeratorMessageRequest__
#define __ModeratorMessageRequest__

#include "../Util/Common.h"
#include "GenericMessageRequest.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Send a Moderator Message to a specific User or groups of Users
	/// </summary>
	/// <remarks>
	/// The sender must have the moderator privileges to be able to send these kinds of messages.<br/>
	/// The <b>recipient</b> parameter can be used to specify if the message is sent to a User, a Room, the Room Group or the whole Zone.
	/// </remarks>
	/// <seealso cref="MessageRecipientMode"/>
	/// <seealso cref="Core.SFSEvent.MODERATOR_MESSAGE"/>
	class DLLImportExport ModeratorMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">
		/// the moderator message
		/// </param>
		/// <param name="recipientMode">
		/// the recipient mode (message can be sent to single User, a Room, the whole Room Group or the Zone)
		/// </param>
		/// <param name="parameters">
		/// custom extra parameters (optional)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::MODERATOR_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnModeratorMessage, (unsigned long long)this));
		///
		/// 			// Say 'Hello' to everyone
		///				boost::shared_ptr<IRequest> request (new ModeratorMessageRequest("Hello from the Moderator!")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
		///					string* message = new string("Message: " +  (*ptrNotifiedMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.MODERATOR_MESSAGE"/>
		/// <seealso cref="MessageRecipientMode"/>
		/// <seealso cref="AdminMessageRequest"/>
		ModeratorMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// <see cref="ModeratorMessageRequest(string, boost::shared_ptr<MessageRecipientMode>, boost::shared_ptr<ISFSObject>)"/>
		/// </summary>
		ModeratorMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode);

		virtual ~ModeratorMessageRequest();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
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
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
