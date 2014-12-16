// ===================================================================
//
// Description		
//		Contains the definition of BuddyMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BuddyMessageRequest__
#define __BuddyMessageRequest__

#include "../../Util/Common.h"
#include "../GenericMessageRequest.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Buddy.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

	/// <summary>
	/// BuddyMessage(s) are similar to private chat messages but are specifically designed for the Buddy List system.
	/// </summary>
	/// <remarks>
	/// They don't require any Room parameter, nor they require that Users are joined into any particular Room. Additionally the Buddy Message
	/// performs specific validation such as making sure that the recipient is in the User's BuddyList and verifies the Buddy block status.
	/// </remarks>
	class DLLImportExport BuddyMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		BuddyMessageRequest(string message, boost::shared_ptr<Buddy> targetBuddy);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">
		/// the message
		/// </param>
		/// <param name="targetBuddy">
		/// the recipient of the message
		/// </param>
		/// <param name="parameters">
		/// custom parameters (e.g. the textfield font and color, a sender avatar id, or any other data...)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyMessage, (unsigned long long)this));
		///
		/// 		// Obtain the recipient of the message
		/// 		boost::shared_ptr<Buddy> kermitTheFrog = ptrSmartFox->BuddyListManager()->GetBuddyByName("KermitTheFrog");
		///
		///			boost::shared_ptr<IRequest> request (new BuddyMessageRequest("Hello Kermit!", kermitTheFrog)); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnBuddyMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
		///				boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
		///
		///				boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///				boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
		///
		///				boost::shared_ptr<void> ptrEventParamValueIsItMe = (*ptrEventParams)["isItMe"];
		///				boost::shared_ptr<bool> ptrNotifiedIsItMe = ((boost::static_pointer_cast<bool>)(ptrEventParamValueIsItMe));
		///
		///				if ((*ptrNotifiedIsItMe) == true)
		///				{
		///					string* message = new string("I said: " +  (*ptrNotifiedMessage));
		///				}
		///				else
		///				{
		///					string* message = new string("Buddy said: " +  (*ptrNotifiedMessage));
		///				}
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_MESSAGE"/>
		/// <seealso cref="AddBuddyRequest"/>
		/// <seealso cref="RemoveBuddyRequest"/>
		/// <seealso cref="BlockBuddyRequest"/>
		BuddyMessageRequest(string message, boost::shared_ptr<Buddy> targetBuddy, boost::shared_ptr<ISFSObject> parameters);

		virtual ~BuddyMessageRequest();

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

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X

#endif
