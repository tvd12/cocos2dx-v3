// ===================================================================
//
// Description		
//		Contains the definition of PlayerToSpectatorRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PlayerToSpectatorRequest__
#define __PlayerToSpectatorRequest__

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

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Attempt to turn the current User from Player to a Spectator (in a Game Room)
	/// </summary>
	/// <remarks>
	/// This could fail if no Spectator slots are available in the Room at the time of the request
	/// </remarks>
	class DLLImportExport PlayerToSpectatorRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		/// <summary>
		/// <see cref="PlayerToSpectatorRequest(Room*)"/>
		/// </summary>
		PlayerToSpectatorRequest();

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="targetRoom">
		/// the Room where the change has to be performed, a null value indicates the last joined Room (default)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::PLAYER_TO_SPECTATOR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnSpectatorOk, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::PLAYER_TO_SPECTATOR_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnSpectatorError, (unsigned long long)this));
		///
		///				boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest()); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnSpectatorOk(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnSpectatorOk(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					// Success! I am now a spectator in this Game!
		///				}
		///
		///				void CMyClass::OnSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					// I was not able to become spectator in the Game
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.PLAYER_TO_SPECTATOR"/>
		/// <seealso cref="Core.SFSEvent.PLAYER_TO_SPECTATOR_ERROR"/>
		/// <seealso cref="SpectatorToPlayerRequest"/>
		PlayerToSpectatorRequest(boost::shared_ptr<Room> targetRoom);

		virtual ~PlayerToSpectatorRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ROOM_ID;

		static boost::shared_ptr<string> KEY_USER_ID;

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
