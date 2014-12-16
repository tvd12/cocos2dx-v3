// ===================================================================
//
// Description		
//		Contains the definition of UnsubscribeRoomGroupRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UnsubscribeRoomGroupRequest__
#define __UnsubscribeRoomGroupRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Stop listening to events of a specific Room Group
	/// </summary>
	class DLLImportExport UnsubscribeRoomGroupRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="groupId">
		/// the name of the group
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_GROUP_UNSUBSCRIBE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnUnsubscribeRoomGroup, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_GROUP_UNSUBSCRIBE_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnUnsubscribeRoomGroupError, (unsigned long long)this));
		///
		///				boost::shared_ptr<IRequest> request (new UnsubscribeRoomGroupRequest("CardGames")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnUnsubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnUnsubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUnsubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueGroupId = (*ptrEventParams)["groupId"];
		///					boost::shared_ptr<string> ptrGroupId = ((boost::static_pointer_cast<string>)(ptrEventParamValueGroupId));
		///					string* message = new string("Group Removed: " +  (*ptrGroupId));
		///				}
		///
		///				void CMyClass::OnUnsubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///					string* message = new string("Unsubscribe failure: " +  (*ptrErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_GROUP_UNSUBSCRIBE"/>
		/// <seealso cref="Core.SFSEvent.ROOM_GROUP_UNSUBSCRIBE_ERROR"/>
		/// <seealso cref="SubscribeRoomGroupRequest"/>
		UnsubscribeRoomGroupRequest(string groupId);

		virtual ~UnsubscribeRoomGroupRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_GROUP_ID;
		
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
		boost::shared_ptr<string> groupId;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
