// ===================================================================
//
// Description		
//		Contains the definition of SpectatorToPlayerRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SpectatorToPlayerRequest__
#define __SpectatorToPlayerRequest__

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
	/// Attempt to turn the current User from Spectator into a Player (in a Game Room)
	/// </summary>
	/// <remarks>
	/// This could fail if no Player slots are available in the Room at the time of the request
	/// </remarks>
	class DLLImportExport SpectatorToPlayerRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// <see cref="SpectatorToPlayerRequest(Room*)"/>
		/// </summary>
		SpectatorToPlayerRequest();

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="targetRoom">
		/// the Room where the change has to be performed, a null value indicates the last joined Room (default)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::SPECTATOR_TO_PLAYER, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnPlayerOk, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::SPECTATOR_TO_PLAYER_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnPlayerError, (unsigned long long)this));
		///
		///				boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest()); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnPlayerOk(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnPlayerOk(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					// Success! I am now a Player in this Game!
		///				}
		///
		///				void CMyClass::OnPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					// I was not able to become Player in the Game
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.SPECTATOR_TO_PLAYER"/>
		/// <seealso cref="Core.SFSEvent.SPECTATOR_TO_PLAYER_ERROR"/>
		/// <seealso cref="PlayerToSpectatorRequest"/>
		SpectatorToPlayerRequest(boost::shared_ptr<Room> targetRoom);

		virtual ~SpectatorToPlayerRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ROOM_ID;
		
		static boost::shared_ptr<string> KEY_USER_ID;

		static boost::shared_ptr<string> KEY_PLAYER_ID;

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
		void Init(boost::shared_ptr<Room> targetRoom);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<Room> room;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
