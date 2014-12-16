// ===================================================================
//
// Description		
//		Contains the definition of LeaveRoomRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LeaveRoomRequest__
#define __LeaveRoomRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Room.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Leaves a currently joined Room
	/// </summary>
	class DLLImportExport LeaveRoomRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="room">
		/// any joined Room that you want to leave, if null the last joined Room will be left
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_EXIT_ROOM, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnUserExitRoom, (unsigned long long)this));
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new LeaveRoomRequest()); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room was left
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.USER_EXIT_ROOM"/>
		/// <seealso cref="JoinRoomRequest"/>
		LeaveRoomRequest(boost::shared_ptr<Room> room);

        /// <summary>
        /// <see cref="LeaveRoomRequest(Room*)"/>
        /// </summary>
		LeaveRoomRequest();

		virtual ~LeaveRoomRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ROOM_ID;

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
		void Init(boost::shared_ptr<Room> room);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<Room> room;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
