// ===================================================================
//
// Description		
//		Contains the definition of BlockBuddyRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BlockBuddyRequest__
#define __BlockBuddyRequest__

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
	/// Block/Unblock a Buddy in the User's BuddyList
	/// </summary>
	/// <remarks>
	/// Blocked buddies won't be able to see the the User online status and send messages or events
	/// </remarks>
	class DLLImportExport BlockBuddyRequest : public BaseRequest
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
		/// <param name="blocked">
		/// the blocked status
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_BLOCK, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyBlock, (unsigned long long)this));
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyError, (unsigned long long)this));
		///
		/// 		// Block a buddy in the current buddy list
		///			boost::shared_ptr<IRequest> request (new BlockBuddyRequest("Swedish Cook", true)); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyBlock(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnBuddyBlock(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				// Buddy block status was changed
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
		///				boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
		///			}
		///
		///			void CMyClass::OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				// Buddy error
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///				boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_BLOCK"/>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ERROR"/>
		/// <seealso cref="AddBuddyRequest"/>
		/// <seealso cref="RemoveBuddyRequest"/>
		BlockBuddyRequest(string buddyName, bool blocked);

		virtual ~BlockBuddyRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_BUDDY_NAME;

		static boost::shared_ptr<string> KEY_BUDDY_BLOCK_STATE;

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
		boost::shared_ptr<string> buddyName;
		bool blocked;
	};

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X

#endif
