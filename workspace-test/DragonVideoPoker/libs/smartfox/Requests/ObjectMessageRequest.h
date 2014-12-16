// ===================================================================
//
// Description		
//		Contains the definition of ObjectMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ObjectMessageRequest__
#define __ObjectMessageRequest__

#include "../Util/Common.h"
#include "GenericMessageRequest.h"
#include "../Entities/Room.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Send a custom data Object to all users in a Room or a sub-selection of them
	/// </summary>
	/// <remarks>
	/// (If you are familiar with SmartFoxServer 1.x this request the equivalent of sendObject)
	/// <para/>
	/// The request allow to send a custom data object to all users in the same Room. 
	/// A typical use of this request is for sending game moves to other players 
	/// </remarks>
	class DLLImportExport ObjectMessageRequest : public GenericMessageRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="obj">
		/// the custom object
		/// </param>
		/// <param name="targetRoom">
		/// an optional target room. This room must be joined and by default it is the last joined Room  
		/// </param>
		/// <param name="recipients">
		/// an optional selection of Users in the target Room (by default the message is sent to all Users)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::OBJECT_MESSAGE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnObjectMessage, (unsigned long long)this));
		///
		/// 			// The variables myCharacter and senderCharacter are local data objects
		/// 
		/// 			// Send a game move to all players
		/// 			boost::shared_ptr<ISFSObject> dataObj (new SFSObject());
		/// 			dataObj->PutInt("x", myCharacter.x);
		/// 			dataObj->PutInt("y", myCharacter.y);
		///
		///				boost::shared_ptr<IRequest> request (new ObjectMessageRequest(dataObj)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
		///					boost::shared_ptr<void> ptrEventParamValueObject = (*ptrEventParams)["message"];
		///					boost::shared_ptr<ISFSObject> ptrNotifiedObject = ((boost::static_pointer_cast<ISFSObject>)(ptrEventParamValueObject));
		/// 				senderCharacter.x = ptrNotifiedObject->GetInt("x");
		/// 				senderCharacter.y = ptrNotifiedObject->GetInt("y");
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.OBJECT_MESSAGE"/>
		ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<Room> targetRoom, boost::shared_ptr<vector<boost::shared_ptr<User> > > recipients);

		/// <summary>
		/// ObjectMessageRequest(ISFSObject obj, Room targetRoom, ICollection<User> recipients)
		/// </summary>
		ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<Room> targetRoom);

		/// <summary>
		/// ObjectMessageRequest(ISFSObject obj, Room targetRoom, ICollection<User> recipients)
		/// </summary>
		ObjectMessageRequest(boost::shared_ptr<ISFSObject> obj);

		virtual ~ObjectMessageRequest();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
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
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
