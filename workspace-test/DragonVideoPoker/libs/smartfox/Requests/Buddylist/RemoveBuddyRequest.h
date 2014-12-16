// ===================================================================
//
// Description		
//		Contains the definition of RemoveBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RemoveBuddyRequest__
#define __RemoveBuddyRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Exceptions/SFSValidationError.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

	/// <summary>
	/// Remove a new Buddy fron the current Buddy List
	/// </summary>
	class DLLImportExport RemoveBuddyRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="buddyName">
		/// the name of the buddy to remove
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_REMOVE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyRemoved, (unsigned long long)this));
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyError, (unsigned long long)this));
		///
		/// 		// Remove a buddy from the buddy list
		///			boost::shared_ptr<IRequest> request (new RemoveBuddyRequest("Gonzo The Great")); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyRemoved(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnBuddyRemoved(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
		///				boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
		///				// Buddy was removed
		///			}
		///
		///			void CMyClass::OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///				boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_REMOVE"/>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ERROR"/>
		/// <seealso cref="AddBuddyRequest"/>
		RemoveBuddyRequest(string buddyName);

		virtual ~RemoveBuddyRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_BUDDY_NAME;

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
		boost::shared_ptr<string> name;
	};

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X

#endif
