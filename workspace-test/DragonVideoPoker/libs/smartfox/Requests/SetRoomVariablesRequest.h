// ===================================================================
//
// Description		
//		Contains the definition of SetRoomVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SetRoomVariablesRequest__
#define __SetRoomVariablesRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Data/ISFSArray.h"
#include "../Entities/Data/SFSArray.h"
#include "../Entities/Room.h"
#include "../Entities/Variables/RoomVariable.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Set custom Room Variables in a Room
	/// </summary>
	/// <seealso cref="SFSRoomVariable"/>
	class DLLImportExport SetRoomVariablesRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="roomVariables">
		/// a vector of RoomVariables
		/// </param>
		/// <param name="room">
		/// the target Room
		/// </param>
		/// <example>
		/// <b>Example #1</b>
		///		\code{.cpp}
		///			boost::shared_ptr<vector<boost::shared_ptr<RoomVariable>>> collectionRoomVariables (new vector<boost::shared_ptrvRoomVariable>>());
		///
		///			boost::shared_ptr<RoomVariable> variable (new RoomVariable ("gameStarted", false, VARIABLETYPE_BOOL));
		///			collectionRoomVariables->push_back(variable);
		///
		///			boost::shared_ptr<RoomVariable> variable1 (new RoomVariable ("gameType", "Snooker", VARIABLETYPE_STRING));
		///			collectionRoomVariables->push_back(variable1);
		///
		///			boost::shared_ptr<RoomVariable> variable2 (new RoomVariable ("minRank", 10, VARIABLETYPE_INT));
		///			collectionRoomVariables->push_back(variable2);
		///
		///			collectionUserVariable->push_back(variable3);
		/// 
		///			boost::shared_ptr<IRequest> request (new SetRoomVariablesRequest(collectionRoomVariables, ptrSmartFox->MySelf()->LastJoinedRoom())); 
		///			ptrSmartFox->Send(request);
		/// 	\endcode
		/// <b>Example #2</b>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomVarsUpdate, (unsigned long long)this));
		///
		///				static void OnRoomVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
		///					boost::shared_ptr<vector<boost::shared_ptr<string>>> changedVars = ((boost::static_pointer_cast<vector<boost::shared_ptr<string>>>)(ptrEventParamValueVars));
		///
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> room = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
		///					boost::shared_ptr<RoomVariable> variable = room->GetVariable("gameStarted");
		///					if (variable != NULL)
		///					{
		///						if (variable->GetBoolValue() == true)
		///						{
		///							// Game Starts!
		///						}
		///						else
		///						{
		///							// Game was Stopped!
		///						}
		///					}
		///				}
		/// 	\endcode
		/// </example>
		SetRoomVariablesRequest (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables, boost::shared_ptr<Room> room);

		/// <summary>
		/// <see cref="SetRoomVariablesRequest(vector<RoomVariable*>*, Room*)"/>
		/// </summary>
		SetRoomVariablesRequest (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables);

		virtual ~SetRoomVariablesRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_VAR_ROOM;

		static boost::shared_ptr<string> KEY_VAR_LIST;

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
		void Init (boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables, boost::shared_ptr<Room> room);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > roomVariables;
		boost::shared_ptr<Room> room;

	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
