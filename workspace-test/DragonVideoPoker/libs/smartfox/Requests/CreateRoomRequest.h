// ===================================================================
//
// Description		
//		Contains the definition of CreateRoomRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __CreateRoomRequest__
#define __CreateRoomRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "RoomSettings.h"
#include "../Entities/Room.h"
#include "MMO/MMORoomSettings.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Entities::Variables;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Requests::MMO;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Creates a new Room in the current Zone
	/// </summary>
	class DLLImportExport CreateRoomRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <remarks>
		/// The instance must be passed to the <see cref="Sfs2X.SmartFox.Send">SmartFox.Send</see> method for the request to be performed.
		/// </remarks>
		/// <param name="settings">
		/// the new room settings, see <see cref="RoomSettings"/> for all the details
		/// </param>
		/// <param name="autoJoin">
		/// if true the Room will be joined as soon as it is created
		/// </param>
		/// <param name="roomToLeave">
		/// indicates which Room should be left once the join has succeeded
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_ADDED, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomAdded, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_CREATION_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomCreationError, (unsigned long long)this));
		///
		/// 			boost::shared_ptr<Room> theRoom = ptrSmartFox->GetRoomByName("Gonzo's Room");
		///
		/// 			// Create a new Chat Room
		///				boost::shared_ptr<RoomSettings> settings (new RoomSettings("Animal Chat Room"));
		///				settings->GroupId("ChatGroup");
		///				settings->MaxUsers(40);
		///				boost::shared_ptr<IRequest> request (new CreateRoomRequest(settings)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnRoomAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent>> ptrEvent);
		///
		///				void CMyClass::OnRoomAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// A new Room was added
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///				}
		///
		///				void CMyClass::OnRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// An error occurred while attempting to create the Room
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="RoomSettings"/>
		/// <seealso cref="Sfs2X.Requests.Game.SFSGameSettings"/>
		/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings"/>
		CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin, boost::shared_ptr<Room> roomToLeave);

		/// <summary>
		/// <see cref="CreateRoomRequest(boost::shared_ptr<RoomSettings>, bool, boost::shared_ptr<Room>)"/>
		/// </summary>
		CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin);

		/// <summary>
		/// <see cref="CreateRoomRequest(boost::shared_ptr<RoomSettings>, bool, boost::shared_ptr<Room>)"/>
		/// </summary>
		CreateRoomRequest(boost::shared_ptr<RoomSettings> settings);

		virtual ~CreateRoomRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ROOM;
		
		static boost::shared_ptr<string> KEY_NAME;
		
		static boost::shared_ptr<string> KEY_PASSWORD;
		
		static boost::shared_ptr<string> KEY_GROUP_ID;
		
		static boost::shared_ptr<string> KEY_ISGAME;
		
		static boost::shared_ptr<string> KEY_MAXUSERS;
		
		static boost::shared_ptr<string> KEY_MAXSPECTATORS;
		
		static boost::shared_ptr<string> KEY_MAXVARS;
		
		static boost::shared_ptr<string> KEY_ROOMVARS;
		
		static boost::shared_ptr<string> KEY_PERMISSIONS;
		
		static boost::shared_ptr<string> KEY_EVENTS;
		
		static boost::shared_ptr<string> KEY_EXTID;
		
		static boost::shared_ptr<string> KEY_EXTCLASS;
		
		static boost::shared_ptr<string> KEY_EXTPROP;
		
		static boost::shared_ptr<string> KEY_AUTOJOIN;
		
		static boost::shared_ptr<string> KEY_ROOM_TO_LEAVE;

		//--- MMORoom Params --------------------------------------------------------

		static boost::shared_ptr<string> KEY_MMO_DEFAULT_AOI;
		
		static boost::shared_ptr<string> KEY_MMO_MAP_LOW_LIMIT;
		
		static boost::shared_ptr<string> KEY_MMO_MAP_HIGH_LIMIT;
		
		static boost::shared_ptr<string> KEY_MMO_USER_MAX_LIMBO_SECONDS;
		
		static boost::shared_ptr<string> KEY_MMO_PROXIMITY_UPDATE_MILLIS;
		
		static boost::shared_ptr<string> KEY_MMO_SEND_ENTRY_POINT;

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
		void Init(boost::shared_ptr<RoomSettings> settings, bool autoJoin, boost::shared_ptr<Room> roomToLeave);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<RoomSettings> settings;
		bool autoJoin;
		boost::shared_ptr<Room> roomToLeave;	
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
