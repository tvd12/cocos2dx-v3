// ===================================================================
//
// Description		
//		Contains the definition of AddBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __AddBuddyRequest__
#define __AddBuddyRequest__

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
	/// Add a new Buddy to the current Buddy List
	/// </summary>
	class DLLImportExport AddBuddyRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="buddyName">
		/// the name of the buddy to add
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSBuddyEvent::BUDDY_ADD, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyAdded, (unsigned long long)this));
		///			ptrSmartFox->AddEventListener(SFSBuddyEvent::BUDDY_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyError, (unsigned long long)this));
		///
		/// 		// Add a new buddy in the buddy list
		///			boost::shared_ptr<IRequest> request (new AddBuddyRequest("Swedish Cook")); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnBuddyAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				// Buddy was added
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
		///				boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
		///			}
		///
		///			void CMyClass::OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				// Room password change failed
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///				boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///			}
		///		\endcode
		/// </example>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ADD"/>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ERROR"/>
		/// <seealso cref="RemoveBuddyRequest"/>
		AddBuddyRequest(string buddyName);
		virtual ~AddBuddyRequest();

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
