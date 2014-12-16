// ===================================================================
//
// Description		
//		Contains the definition of SetUserPositionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __SetUserPositionRequest__
#define __SetUserPositionRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Entities/MMORoom.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;

namespace Sfs2X {
namespace Requests {
namespace MMO {

	/// <summary>
	/// Updates the User position inside an MMORoom.
	/// </summary>
	/// 
	/// <remarks>
	/// MMORooms represent virtual environments and can host any number of users. Based on their position, the system allows users within a certain range
	/// from each other (Area of Interest, or AoI) to interact.
	/// <para/>
	/// This request allows the current user to update his position inside the MMORoom, which in turn will trigger a
	/// <see cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE">PROXIMITY_LIST_UPDATE</see> event for all users that fall within his AoI.
	/// </remarks>
	/// 
	/// <example>
	/// The following example changes the position of the user in a 2D coordinates space and handles the related event:
	///	\code{.cpp}
	/// private void UpdatePlayerPosition(int px, int py)
	/// {
	///		boost::shared_ptr<Vec3D> newPos (new Vec3D(px, py));
	///		boost::shared_ptr<IRequest> request (new SetUserPositionRequest(newPos));
	///		ptrSmartFox->Send(request);
	/// }
	///
	///	static void OnProximityListUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	///
	/// void CMyClass::OnProximityListUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
	/// {
	///		// Get the pointer to my class
	///		CMyClass* instance = (CMyClass*)ptrContext;
	///
	///		boost::shared_ptr<vector<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	///		boost::shared_ptr<void> ptrEventParamValueAddedUsers = (*ptrEventParams)["addedUsers"];
	///		boost::shared_ptr<vector<boost::shared_ptr<User>> ptrNotifiedAddedUsers = ((boost::static_pointer_cast<vector<boost::shared_ptr<User>>)(ptrEventParamValueAddedUsers));
	///		boost::shared_ptr<void> ptrEventParamValueRemovedUsers = (*ptrEventParams)["removedUsers"];
	///		boost::shared_ptr<vector<boost::shared_ptr<User>> ptrNotifiedRemovedUsers = ((boost::static_pointer_cast<vector<boost::shared_ptr<User>>)(ptrEventParamValueRemovedUsers));
    ///
	/// 	// Add users that entered the proximity list
	/// 	for (long int i = 0; i < ptrNotifiedAddedUsers->Size(); i++) 
	/// 	{
	/// 		// Obtain the coordinates at which the user "appeared" in our range
	/// 		boost::shared_ptr<Vec3D> entryPoint = ptrNotifiedAddedUsers->at(i)->AoiEntryPoint;
    ///
	/// 		// Add new avatar in the scene
	/// 		boost::shared_ptr<AvatarSprite> avatarSprite = boost::shared_ptr<AvatarSprite>(new AvatarSprite());
	/// 		avatarSprite->x = entryPoint->px;
	/// 		avatarSprite->y = entryPoint->py;
	/// 		...
	/// 	}
    ///
	/// 	// Remove users that left the proximity list
	/// 	for each (User user in removed)
	/// 	{
	/// 		// Remove the avatar from the scene
	/// 		...
	/// 	}
	/// }
	/// \endcode
	/// </example>
	/// 
	/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	class DLLImportExport SetUserPositionRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new SetUserPositionRequest instance.
		/// </summary>
		/// 
		/// <remarks>
		/// The instance must be passed to the <see cref="Sfs2X.SmartFox.Send">SmartFox.Send</see> method for the request to be performed.
		/// </remarks>
		/// 
		/// <param name="position">The user position.</param>
		/// <param name="room">The <em>MMORoom</em> object corresponding to the Room where the position should be set; if <c>null</c>, the last Room joined by the user is used.</param>
		SetUserPositionRequest (boost::shared_ptr<Vec3D> position, boost::shared_ptr<Room> room);

		/// <summary>
		/// See <em>SetUserPositionRequest(Vec3D, Room)</em> constructor.
		/// </summary>
		SetUserPositionRequest (boost::shared_ptr<Vec3D> position);

		virtual ~SetUserPositionRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		/// <exclude/>
		static boost::shared_ptr<string> KEY_ROOM;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_VEC3D;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_PLUS_USER_LIST;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_MINUS_USER_LIST;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_PLUS_ITEM_LIST;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_MINUS_ITEM_LIST;

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

		boost::shared_ptr<Vec3D> pos;
		boost::shared_ptr<Room> room;
	};

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X

#endif
