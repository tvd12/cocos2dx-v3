// ===================================================================
//
// Description		
//		Contains the definition of SubscribeRoomGroupRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SubscribeRoomGroupRequest__
#define __SubscribeRoomGroupRequest__

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
	/// Subscribe to the events of a Room Group
	/// </summary>
	class DLLImportExport SubscribeRoomGroupRequest : public BaseRequest
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
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_GROUP_SUBSCRIBE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnSubscribeRoomGroup, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_GROUP_SUBSCRIBE_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnSubscribeRoomGroupError, (unsigned long long)this));
		///
		///				boost::shared_ptr<IRequest> request (new SubscribeRoomGroupRequest("CardGames")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnSubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnSubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnSubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRooms = (*ptrEventParams)["newRooms"];
		///					boost::shared_ptr<vector<boost::shared_ptr<Room>>> ptrRooms = ((boost::static_pointer_cast<vectorboost::shared_ptr<Room>>>)(ptrEventParamValueRooms));
		///					string* message = new string("Subscription done");
		///				}
		///
		///				void CMyClass::OnSubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
		///					string* message = new string("Subscription failure: " +  (*ptrErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_GROUP_SUBSCRIBE"/>
		/// <seealso cref="Core.SFSEvent.ROOM_GROUP_SUBSCRIBE_ERROR"/>
		/// <seealso cref="UnsubscribeRoomGroupRequest"/>
		SubscribeRoomGroupRequest(string groupId);

		virtual ~SubscribeRoomGroupRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_GROUP_ID;

		static boost::shared_ptr<string> KEY_ROOM_LIST;

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
