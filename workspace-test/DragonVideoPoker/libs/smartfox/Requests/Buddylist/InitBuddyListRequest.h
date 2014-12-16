// ===================================================================
//
// Description		
//		Contains the definition of InitBuddyListRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __InitBuddyListRequest__
#define __InitBuddyListRequest__

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
	/// Initializes the BuddyList system.
	/// </summary>
	/// <remarks>
	/// This involves loading any previously stored Buddy data from the server, such as the User's Buddy List, his previous state and his persistent Buddy Variables. 
	/// The init request is <b>the first operation required</b> to initialize the BuddyList system. 
	/// Once the Init is executed the User can have access to all his previous data and start to interact with his Buddies.
	/// </remarks>
	class DLLImportExport InitBuddyListRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Initializes the Buddy List. The initialization process is complete when the SFSBuddyEvent.BUDDY_LIST_INIT event is received.
		/// </summary>
		/// <example>
		///		\code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_LIST_INIT, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyInited, (unsigned long long)this));
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyError, (unsigned long long)this));
		///
		/// 		// Initialize buddy list
		///			boost::shared_ptr<IRequest> request (new InitBuddyListRequest()); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyInited(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnBuddyInited(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				// Buddy list was inited with success!
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
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_LIST_INIT"/>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ERROR"/>
		/// <seealso cref="SFSBuddy"/>
		/// <seealso cref="Entities.Variables.SFSBuddyVariable"/>
		InitBuddyListRequest();
		virtual ~InitBuddyListRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_BLIST;

		static boost::shared_ptr<string> KEY_BUDDY_STATES;

		static boost::shared_ptr<string> KEY_MY_VARS;

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
