// ===================================================================
//
// Description		
//		Contains the definition of ChangeRoomPasswordStateRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ChangeRoomPasswordStateRequest__
#define __ChangeRoomPasswordStateRequest__

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
	/// Changes the password of a Room at runtime.
	/// </summary>
	/// <remarks>
	/// The request not only changes the password of a Room but also its "password state", which indicates if a Room is password protected or not.<br/>
	/// This request might fail if the Room was configured to deny password runtime changes or if the User sending the request is not the owner of the Room. 
	/// <para/>
	/// Moderators and Administrator can override this last constraint.
	/// </remarks>
	class DLLImportExport ChangeRoomPasswordStateRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="room">
		/// the Room 
		/// </param>
		/// <param name="newPass">
		/// the new password (null or empty string means no password)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomPasswordStateChange, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomPasswordStateChangeError, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<Room> theRoom = ptrSmartFox->GetRoomByName("DeveloperChatRoom");
		///
		/// 			// Change room password
		///				boost::shared_ptr<IRequest> request (new ChangeRoomPasswordStateRequest(theRoom, "forloop")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnRoomPasswordStateChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnRoomPasswordStateChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomPasswordStateChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room password change success
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///				}
		///
		///				void CMyClass::OnRoomPasswordStateChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room password change failed
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_PASSWORD_STATE_CHANGE"/>
		/// <seealso cref="Core.SFSEvent.ROOM_PASSWORD_STATE_CHANGE_ERROR"/>
		/// <seealso cref="ChangeRoomNameRequest"/>
		/// <seealso cref="ChangeRoomPasswordStateRequest"/>
		ChangeRoomPasswordStateRequest(boost::shared_ptr<Room> room, string newPass);
		virtual ~ChangeRoomPasswordStateRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ROOM;
		
		static boost::shared_ptr<string> KEY_PASS;

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
		boost::shared_ptr<string> newPass;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
