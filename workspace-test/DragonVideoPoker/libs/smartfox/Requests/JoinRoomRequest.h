// ===================================================================
//
// Description		
//		Contains the definition of JoinRoomRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __JoinRoomRequest__
#define __JoinRoomRequest__

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
	/// Join the current User in a Room.
	/// </summary>
	class DLLImportExport JoinRoomRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="id">
		/// you can use the numeric ID of the Room or its name
		/// </param>
		/// <param name="pass">
		/// needed only if the Room is password protected
		/// </param>
		/// <param name="roomIdToLeave">
		/// the id of a previously joined Room that you want to leave once joined in the new Room (optional). The default behavior is to leave the previous Room. You can pass a negative ID to avoid leaving any Room
		/// </param>
		/// <param name="asSpectator">
		/// if true it indicates that you want to join the room as spectator (optional, for game Rooms only)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnJoinRoom, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_JOIN_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnJoinRoomError, (unsigned long long)this));
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new JoinRoomRequest("Lobby")); 
		///				ptrSmartFox->Send(request);
		///
		///			static void OnJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			static void OnJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				// Room joined successfully
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///				boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///				// Buddy was removed
		///			}
		///
		///			void CMyClass::OnJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///			{
		///				CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///				boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///				string* message = new string("Join Room failure:" +  (*ptrErrorMessage));
		///			}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_JOIN"/>
		/// <seealso cref="Core.SFSEvent.ROOM_JOIN_ERROR"/>
		/// <seealso cref="LeaveRoomRequest"/>
		JoinRoomRequest(boost::shared_ptr<Room> id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);
		JoinRoomRequest(string id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);
		JoinRoomRequest(long int id, string pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);

		/// <summary>
		/// <see cref="JoinRoomRequest(boost::shared_ptr<Room>, string, long int, bool)"/>
		/// </summary>
		JoinRoomRequest(boost::shared_ptr<Room> id, string pass, boost::shared_ptr<long int> roomIdToLeave);
		JoinRoomRequest(string id, string pass, boost::shared_ptr<long int> roomIdToLeave);
		JoinRoomRequest(long int id, string pass, boost::shared_ptr<long int> roomIdToLeave);

		/// <summary>
		/// <see cref="JoinRoomRequest(boost::shared_ptr<Room>, string, long int, bool)"/>
		/// </summary>
		JoinRoomRequest(boost::shared_ptr<Room> id, string pass);
		JoinRoomRequest(string id, string pass);
		JoinRoomRequest(long int id, string pass);

		/// <summary>
		/// <see cref="JoinRoomRequest(boost::shared_ptr<Room>, string, long int, bool)"/>
		/// </summary>
		JoinRoomRequest(boost::shared_ptr<Room> id);
		JoinRoomRequest(string id);
		JoinRoomRequest(long int id);

		virtual ~JoinRoomRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<string> KEY_ROOM;
		
		static boost::shared_ptr<string> KEY_USER_LIST;
		
		static boost::shared_ptr<string> KEY_ROOM_NAME;
		
		static boost::shared_ptr<string> KEY_ROOM_ID;
		
		static boost::shared_ptr<string> KEY_PASS;
		
		static boost::shared_ptr<string> KEY_ROOM_TO_LEAVE;
		
		static boost::shared_ptr<string> KEY_AS_SPECTATOR;

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
		void Init(boost::shared_ptr<Room> id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);
		void Init(string id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);
		void Init(long int id, boost::shared_ptr<string> pass, boost::shared_ptr<long int> roomIdToLeave, bool asSpectator);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		long int id;
		boost::shared_ptr<string> name;
		boost::shared_ptr<string> pass;
		boost::shared_ptr<long int> roomIdToLeave;
		bool asSpectator;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
