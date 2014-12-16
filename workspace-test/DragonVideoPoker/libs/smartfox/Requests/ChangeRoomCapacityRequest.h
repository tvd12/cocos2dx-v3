// ===================================================================
//
// Description		
//		Contains the definition of ChangeRoomCapacityRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ChangeRoomCapacityRequest__
#define __ChangeRoomCapacityRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Room.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Change the capacity of a Room (maxUsers and maxSpectators) at runtime.
	/// </summary>
	/// <remarks>
	/// This request might fail if the Room was configured not be re-sizable or if the User sending the request
 	/// is not the owner of the Room. Moderators and Administrator can override this last constraint.
 	/// <para/>
 	/// It is possible to "shrink" the Room capacity so that maxUsers < userCount. <br/>
    /// In this case nothing will happen to the "extra" users.<br/>
 	/// As soon as clients will leave the Room the userCount will get down to the new maxUsers value.
	/// </remarks>
	class DLLImportExport ChangeRoomCapacityRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="room">
		/// the Room to resize
		/// </param>
		/// <param name="newMaxUsers">
		/// the new maxUsers value (use -1 if don't want to change the current value)
		/// </param>
		/// <param name="newMaxSpect">
		/// the new maxSpect value (use -1 if don't want to change the current value)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_CAPACITY_CHANGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomCapacityChange, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_CAPACITY_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomCapacityChangeError, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<Room> theRoom = ptrSmartFox->GetRoomByName("DeveloperChatRoom");
		///
		/// 			// Resize the room to have 100 users and zero spectators
		///				boost::shared_ptr<IRequest> request (new ChangeRoomCapacityRequest(theRoom, 100, 0)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnRoomCapacityChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnRoomCapacityChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomCapacityChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room capacity was changed successfully
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///				}
		///
		///				void CMyClass::OnRoomCapacityChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room capacity change failed
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_CAPACITY_CHANGE"/>
		/// <seealso cref="Core.SFSEvent.ROOM_CAPACITY_CHANGE_ERROR"/>
		/// <seealso cref="ChangeRoomNameRequest"/>
		/// <seealso cref="ChangeRoomPasswordStateRequest"/>
		ChangeRoomCapacityRequest(boost::shared_ptr<Room> room, long int newMaxUsers, long int newMaxSpect);
		virtual ~ChangeRoomCapacityRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<string> KEY_ROOM;
		
		static boost::shared_ptr<string> KEY_USER_SIZE;

		static boost::shared_ptr<string> KEY_SPEC_SIZE;
		
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
		boost::shared_ptr<Room> room;		
		long int newMaxUsers;
		long int newMaxSpect;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
