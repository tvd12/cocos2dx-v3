// ===================================================================
//
// Description		
//		Contains the definition of AdminMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __AdminMessageRequest__
#define __AdminMessageRequest__

#include "../Util/Common.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer
#include "GenericMessageRequest.h"
#include "MessageRecipientMode.h"
#include "GenericMessageType.h"
#include "../Entities/Data/ISFSObject.h"

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Send a Admin Message to a specific User or groups of Users
	/// </summary>
	/// <remarks>
	/// The sender must have the admin privileges to be able to send these kinds of messages.<br/>
	/// The <b>recipient</b> parameter can be used to specify if the message is sent to a User, a Room, the Room Group or the whole Zone.
	/// </remarks>
	/// 
	/// <seealso cref="MessageRecipientMode"/>
	/// <seealso cref="Core.SFSEvent.ADMIN_MESSAGE"/>
	class DLLImportExport AdminMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary/>
		/// Constructor
		/// <example>
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ADMIN_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnAdminMessage, (unsigned long long)this));
		///
		/// 			// Say 'Hello' to every one
		///				boost::shared_ptr<IRequest> request (new AdminMessageRequest("Hello from the Admin!")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
		///				}
		///			\endcode
		/// </example>
		/// 
		/// <param name="message">
		/// the admin message
		/// </param>
		/// <param name="recipientMode">
		/// the recipient mode (message can be sent to single User, a Room, the whole Room Group or the Zone)
		/// </param>
		/// <param name="parameters">
		/// custom extra parameters
		/// </param>
		/// 
		/// <seealso cref="Core.SFSEvent.ADMIN_MESSAGE"/>
		/// <seealso cref="MessageRecipientMode"/>
		/// <seealso cref="ModeratorMessageRequest"/>
		AdminMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// <see cref="AdminMessageRequest(string, boost::shared_ptr<MessageRecipientMode>, boost::shared_ptr<ISFSObject>)"/>
		/// </summary>
		AdminMessageRequest(string message, boost::shared_ptr<MessageRecipientMode> recipientMode);
		virtual ~AdminMessageRequest();

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
