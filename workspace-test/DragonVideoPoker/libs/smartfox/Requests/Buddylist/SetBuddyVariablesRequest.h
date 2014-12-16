// ===================================================================
//
// Description		
//		Contains the definition of SetBuddyVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SetBuddyVariablesRequest__
#define __SetBuddyVariablesRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Exceptions/SFSValidationError.h"
#include "../../Entities/Variables/BuddyVariable.h"

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
	/// Sets one or more BuddyVariables for the current User. This will update all Users in the Zona who have this User as Buddy in their Buddy Lists.
	/// </summary>
	class DLLImportExport SetBuddyVariablesRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="buddyVariables">
		/// a list of BuddyVariables
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			// Add event listener for BuddyVariables
		///			ptrSmartFox->AddEventListener(SFSEvent::BUDDY_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnBuddyVarsUpdate, (unsigned long long)this));
		///
		/// 		// This function could be invoked by a button click in the application GUI
		/// 		// It updates a BuddyVariable with the title of the current track that the Users is listening to
		///			boost::shared_ptr<list<boost::shared_ptr<BuddyVariable>>> myVars (new list<boost::shared_ptr<BuddyVariable>>());
		///			boost::shared_ptr<SFSBuddyVariable> currentTrack (new SFSBuddyVariable("track", "Beethoven's 8th Symphony", VARIABLETYPE_STRING));
		///			myVars->push_back(currentTrack);
		///			boost::shared_ptr<IRequest> request (new SetBuddyVariablesRequest(myVars)); 
		///			ptrSmartFox->Send(request);
		///
		///			static void OnBuddyVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		/// 		// This function will handle any Variables update from Buddies in our BuddyList
		///			void CMyClass::OnBuddyVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
		///				boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
		///				// Buddy was added
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_VARIABLES_UPDATE"/>
		/// <seealso cref="SFSBuddyVariable"/>
		SetBuddyVariablesRequest(boost::shared_ptr<list<boost::shared_ptr<BuddyVariable> > > buddyVariables);

		virtual ~SetBuddyVariablesRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_BUDDY_NAME;

		static boost::shared_ptr<string> KEY_BUDDY_VARS;

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
		boost::shared_ptr<list<boost::shared_ptr<BuddyVariable> > > buddyVariables;
	};

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X

#endif
