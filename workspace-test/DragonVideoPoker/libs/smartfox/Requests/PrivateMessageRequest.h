// ===================================================================
//
// Description		
//		Contains the definition of PrivateMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PrivateMessageRequest__
#define __PrivateMessageRequest__

#include "../Util/Common.h"
#include "GenericMessageRequest.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Send a chat Private Message to another User
	/// </summary>
	/// <remarks>
	/// Private Messages can be exchanged between Users in the same Rooms or in different Rooms.<br/>
	/// They can also be sent between Users that are not joined to any Rooms at all. 
	/// </remarks>
	class DLLImportExport PrivateMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">
		/// the private chat message
		/// </param>
		/// <param name="recipientId">
		/// the id of the recipient User
		/// </param>
		/// <param name="parameters">
		/// custom extra parameters (optional)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::PRIVATE_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnPrivateMessage, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<User> messageRecipient = ptrSmartFox->UserManager()->GetUserByName("Piggy");
		///
		/// 			// Say 'Hello' to user Tom
		///				boost::shared_ptr<IRequest> request (new PrivateMessageRequest("Hello Piggy!", messageRecipient->Id())); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnPrivateMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnPrivateMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string&lg;)(ptrEventParamValueMessage));
		///					string* message = new string("Got PM: " +  (*ptrNotifiedMessage) + ", Sender: " + *user->Name());
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.PRIVATE_MESSAGE"/>
		/// <seealso cref="PublicMessageRequest"/>
		PrivateMessageRequest(string message, long int recipientId, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// <see cref="PrivateMessageRequest(string*, long int, boost::shared_ptr<ISFSObject>)"/>
		/// </summary>
		PrivateMessageRequest(string message, long int recipientId);

		virtual ~PrivateMessageRequest();

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
