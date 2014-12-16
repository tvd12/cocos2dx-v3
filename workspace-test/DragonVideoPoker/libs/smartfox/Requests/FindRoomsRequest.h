// ===================================================================
//
// Description		
//		Contains the definition of FindRoomsRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __FindRoomsRequest__
#define __FindRoomsRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Room.h"
#include "../Entities/Match/MatchExpression.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Match;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Search Rooms in the system by matching their variables and properties against a MatchExpression
	/// </summary>
	class DLLImportExport FindRoomsRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// <see cref="FindRoomsRequest(boost::shared_ptr<MatchExpression>, string, long int) "/>
		/// </summary>
		FindRoomsRequest(boost::shared_ptr<MatchExpression> expr);

		/// <summary>
		/// <see cref="FindRoomsRequest(boost::shared_ptr<MatchExpression>, string, long int) "/>
		/// </summary>
		FindRoomsRequest(boost::shared_ptr<MatchExpression> expr, string groupId);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="expr">
		/// the match expression 
		/// </param>
		/// <param name="groupId">
		/// the id of the Room Group where to perform the search, if null the search will be Zone-wide (default)
		/// </param>
		/// <param name="limit">
		/// the number of results wanted. Zero means no limit, we will get all results (default)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_FIND_RESULT, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnRoomFindResult, (unsigned long long)this));
		///
		/// 			// Search for all Rooms whose 'country' Room Variable == 'Sweden'
		/// 			boost::shared_ptr<MatchExpression> expr (new MatchExpression("country", NumberMatch::EQUALS, "Sweden"));
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new FindRoomRequest(expr)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnRoomFindResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomFindResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Rooms found
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRooms = (*ptrEventParams)["rooms"];
		///					boost::shared_ptr<vector<boost::shared_ptr<Room>> ptrNotifiedRooms = ((boost::static_pointer_cast<vector<boost::shared_ptr<Room>>)(ptrEventParamValueRooms));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_FIND_RESULT"/>
		/// <seealso cref="MatchExpression"/>
		/// <seealso cref="RoomProperties"/>
		FindRoomsRequest(boost::shared_ptr<MatchExpression> expr, string groupId, long int limit);

		virtual ~FindRoomsRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_EXPRESSION;

		static boost::shared_ptr<string> KEY_GROUP;

		static boost::shared_ptr<string> KEY_LIMIT;

		static boost::shared_ptr<string> KEY_FILTERED_ROOMS;

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
		void Init(boost::shared_ptr<MatchExpression> expr, string groupId, long int limit);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<MatchExpression> matchExpr;
		boost::shared_ptr<string> groupId;
		long int limit;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
