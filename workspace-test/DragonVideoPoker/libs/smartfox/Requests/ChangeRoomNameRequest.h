// ===================================================================
//
// Description		
//		Contains the definition of ChangeRoomNameRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ChangeRoomNameRequest__
#define __ChangeRoomNameRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "BanMode.h"
#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Change the name of a Room at runtime.
	/// </summary>
	/// <remarks>
	/// This request might fail if the Room was configured not be ranamed or if the User sending the request is not the owner of the Room. 
	/// <para/>
	/// Moderators and Administrator can override this last constraint.
	/// </remarks>
	class DLLImportExport ChangeRoomNameRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="room">
		/// the Room to rename
		/// </param>
		/// <param name="newName">
		/// the new Room name (no duplicates are allowed)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_NAME_CHANGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomNameChange, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_NAME_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomNameChangeError, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<Room> theRoom = ptrSmartFox->GetRoomByName("Gonzo's Room");
		///
		/// 			// Change room name
		///				boost::shared_ptr<IRequest> request (new ChangeRoomNameRequest(theRoom, "Gonzo The Great's Room")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnRoomNameChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnRoomNameChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomNameChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room was renamed successfully
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///					boost::shared_ptr<void> ptrEventParamValueOldName = (*ptrEventParams)["oldName"];
		///					boost::shared_ptr<string> ptrOldName = ((boost::static_pointer_cast<string>)(ptrEventParamValueOldName));
		///				}
		///
		///				void CMyClass::OnRoomNameChangeError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Room name change failed
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_NAME_CHANGE"/>
		/// <seealso cref="Core.SFSEvent.ROOM_NAME_CHANGE_ERROR"/>
		/// <seealso cref="ChangeRoomCapacityRequest"/>
		/// <seealso cref="ChangeRoomPasswordStateRequest"/>
		ChangeRoomNameRequest(boost::shared_ptr<Room> room, string newName);
		virtual ~ChangeRoomNameRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_ROOM;

		static boost::shared_ptr<string> KEY_NAME;

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
		boost::shared_ptr<string> newName;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
