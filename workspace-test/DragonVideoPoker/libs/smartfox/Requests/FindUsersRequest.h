// ===================================================================
//
// Description		
//		Contains the definition of FindUsersRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __FindUsersRequest__
#define __FindUsersRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/User.h"
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
	/// Search Users in the system by matching their variables and properties against a MatchExpression
	/// </summary>
	class DLLImportExport FindUsersRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		void Init(boost::shared_ptr<MatchExpression> expr);
		void Init(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target, long int limit);
		void Init(boost::shared_ptr<MatchExpression> expr, string target, long int limit);

		/// <summary>
		/// <see cref="FindUsersRequest(boost::shared_ptr<MatchExpression>, string, long int)"/>
		/// </summary>
		FindUsersRequest(boost::shared_ptr<MatchExpression> expr);

		/// <summary>
		/// <see cref="FindUsersRequest(boost::shared_ptr<MatchExpression>, string, long int)"/>
		/// </summary>
		FindUsersRequest(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target);

		/// <summary>
		/// <see cref="FindUsersRequest(boost::shared_ptr<MatchExpression>, string, long int)"/>
		/// </summary>
		FindUsersRequest(boost::shared_ptr<MatchExpression> expr, boost::shared_ptr<Room> target, long int limit);

		/// <summary>
		/// <see cref="FindUsersRequest(boost::shared_ptr<MatchExpression>, string, long int)"/>
		/// </summary>
		FindUsersRequest(boost::shared_ptr<MatchExpression> expr, string target);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="expr">
		/// the match expression 
		/// </param>
		/// <param name="target">
		/// it can be a Room or String (the Group Id), if null the search will done in the whole Zone (default)
		/// </param>
		/// <param name="limit">
		/// the number of results wanted. Zero means no limit, we will get all results (default)
		/// </param>
		/// <remarks>
		/// target can be 
		/// --> Room: search in that room
		/// --> String: a valid groupId
		/// --> null: search the whole zone
		/// </remarks>
		/// 
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_FIND_RESULT, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnUserFindResult, (unsigned long long)this));
		///
		/// 			// Search for all Users whose 'age' User Variable is 29
		/// 			boost::shared_ptr<MatchExpression> expr (new MatchExpression("age", NumberMatch::EQUALS, 29));
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new FindUserRequest(expr)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnUserFindResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserFindResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Show the array of Users
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueUsers = (*ptrEventParams)["users"];
		///					boost::shared_ptr<vector<boost::shared_ptr<User>>> ptrNotifiedUsers = ((boost::static_pointer_cast<vector<boost::shared_ptr<User>>>)(ptrEventParamValueUsers));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.USER_FIND_RESULT"/>
		/// <seealso cref="UserProperties"/>
		/// <seealso cref="MatchExpression"/>
		FindUsersRequest(boost::shared_ptr<MatchExpression> expr, string target, long int limit);

		virtual ~FindUsersRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_EXPRESSION;
		
		static boost::shared_ptr<string> KEY_GROUP;
		
		static boost::shared_ptr<string> KEY_ROOM;
			
		static boost::shared_ptr<string> KEY_LIMIT;
		
		static boost::shared_ptr<string> KEY_FILTERED_USERS;

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
		boost::shared_ptr<MatchExpression> matchExpr;
		boost::shared_ptr<Room> targetRoom;
		boost::shared_ptr<string> targetString;
		long int limit;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
