// ===================================================================
//
// Description		
//		Contains the definition of QuickJoinGameRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __QuickJoinGameRequest__
#define __QuickJoinGameRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Entities/Room.h"
#include "../../Entities/Match/MatchExpression.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Entities::Match;

namespace Sfs2X {
namespace Requests {
namespace Game {

	/// <summary>
	/// Quick join a User in a public game.
	/// </summary>
	/// <remarks>
	/// By providing a MatchExpression and a list of Rooms or Groups the system can search for matching Rooms and immediately teleport the player in the game action.
	/// </remarks>
	class DLLImportExport QuickJoinGameRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// <see cref=" QuickJoinGameRequest(boost::shared_ptr<MatchExpression>, vector<boost::shared_ptr<string>>, boost::shared_ptr<Room>)"/>
		/// </summary>
		QuickJoinGameRequest(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<string> > > whereToSearch);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="matchExpression">
		/// a MatchExpression to filter Rooms
		/// </param>
		/// <param name="whereToSearch">
		/// this parameter accepts a List of Room objects or a List of Strings representing valid Room Group names
		/// </param>
		/// <param name="roomToLeave">
		/// an optional Room that the User will leave after joining the game
		/// </param>
		/// <example>
		///		\code{.cpp}
		/// 		// Add event listener for the Invitation reply event
		///			ptrSmartFox->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnRoomJoin, (unsigned long long)this)));
		///
		///			boost::shared_ptr<string> value (new string("Darts"));
		///			boost::shared_ptr<long int> value1 (new long int());
		///			*value1 = 400;
		///			boost::shared_ptr<MatchExpression> exp (new MatchExpression("type", StringMatch::EQUALS, value, MatchExpression::MatchExpressionValueType::MatchExpression_ValueString))->And(new MatchExpression("bestScore", NumberMatch::LESS_THAN, value1, MatchExpression::MatchExpressionValueType::MatchExpression_ValueOther));
		///
		/// 		// Search the "games" Group for a free public game of Darts with a bestScore variable < 400 
		///			boost::shared_ptr<vector<boost::shared_ptr<string>>> whereToSearch (new vector<boost::shared_ptr<string>>);
		///			whereToSearch->push_back("[""games""]");
		///			boost::shared_ptr<IRequest> request (new QuickJoinGameRequest(exp), whereToSearch, ptrSmartFox->MySelf()->LastJoinedRoom());
		///			ptrSmartFox->Send(request);
		///			ptrSmartFox->Send(request);
		///
		///			static void OnRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		/// 		// Handle responses from invited users
		///			void CMyClass::OnRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///			{
		///				// Get the pointer to my class
		///				CMyClass* instance = (CMyClass*)ptrContext;
		///
		///				// Successfully joined in Room
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///				boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///			}
		/// 
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.ROOM_JOIN"/>
		/// <seealso cref="MatchExpression"/>
		QuickJoinGameRequest(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<string> > > whereToSearch, boost::shared_ptr<Room> roomToLeave);

		/// <summary>
		/// <see cref=" QuickJoinGameRequest(boost::shared_ptr<MatchExpression>, vector<boost::shared_ptr<string>>, boost::shared_ptr<Room>)"/>
		/// </summary>
		QuickJoinGameRequest(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<Room> > > whereToSearch);

		/// <summary>
		/// <see cref=" QuickJoinGameRequest(boost::shared_ptr<MatchExpression>, vector<boost::shared_ptr<string>>, boost::shared_ptr<Room>)"/>
		/// </summary>
		QuickJoinGameRequest(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<Room> > > whereToSearch, boost::shared_ptr<Room> roomToLeave);

		virtual ~QuickJoinGameRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static const long int MAX_ROOMS;
		
		static boost::shared_ptr<string> KEY_ROOM_LIST;
		
		static boost::shared_ptr<string> KEY_GROUP_LIST;
		
		static boost::shared_ptr<string> KEY_ROOM_TO_LEAVE;
		
		static boost::shared_ptr<string> KEY_MATCH_EXPRESSION;

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
		void Init(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<string> > > whereToSearch, boost::shared_ptr<Room> roomToLeave);
		void Init(boost::shared_ptr<MatchExpression> matchExpression, boost::shared_ptr<vector<boost::shared_ptr<Room> > > whereToSearch, boost::shared_ptr<Room> roomToLeave);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > whereToSearchRoom;
		boost::shared_ptr<vector<boost::shared_ptr<string> > > whereToSearchString;
		boost::shared_ptr<MatchExpression> matchExpression;
		boost::shared_ptr<Room> roomToLeave;
		
		bool isSearchListString;
		bool isSearchListRoom;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
