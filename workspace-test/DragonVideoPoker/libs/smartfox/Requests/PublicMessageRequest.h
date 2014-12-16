// ===================================================================
//
// Description		
//		Contains the definition of PublicMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PublicMessageRequest__
#define __PublicMessageRequest__

#include "../Util/Common.h"
#include "GenericMessageRequest.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Entities/Room.h"

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
	/// Sends a chat Public Message to other users in the Room
	/// </summary>
	/// <remarks>
	/// Public Messages are broadcast to all users in the specified Room
	/// <para/>
	/// An optional custom SFSObject can be sent together with the message. The extra parameters can be used to transmit information 
	/// about the font and color of the message or any other properties that are relevant to the message.
	/// </remarks>
	class DLLImportExport PublicMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">
		/// the chat message
		/// </param>
		/// <param name="parameters">
		/// custom extra parameters (optional)
		/// </param>
		/// <param name="targetRoom">
		/// he target room (optional). By default it is used the last joined Room
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::PUBLIC_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnPublicMessage, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<User> messageRecipient = ptrSmartFox->UserManager()->GetUserByName("Piggy");
		///
		/// 			// Say 'Hello' to every one
		///				boost::shared_ptr<IRequest> request (new PublicMessageRequest("Hello everyone!")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
		///					string* message = new string("Message: " +  (*ptrNotifiedMessage) + ", Sender: " + *user->Name());
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.PUBLIC_MESSAGE"/>
		/// <seealso cref="PrivateMessageRequest"/>
		PublicMessageRequest(string message, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> targetRoom);

		/// <summary>
		/// <see cref="PublicMessageRequest(string, boost::shared_ptr<ISFSObject>, boost::shared_ptr<Room>)"/>
		/// </summary>
		PublicMessageRequest(string, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// <see cref="PublicMessageRequest(string*, boost::shared_ptr<Room>)"/>
		/// </summary>
		PublicMessageRequest(string message);

		virtual ~PublicMessageRequest();

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
