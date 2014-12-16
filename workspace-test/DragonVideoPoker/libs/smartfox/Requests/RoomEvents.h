// ===================================================================
//
// Description		
//		Contains the definition of RoomEvents
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomEvents__
#define __RoomEvents__

#include "../Util/Common.h"

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This class provides Room event settings that can be specified when creating a new Room via the <see cref="CreateRoomRequest"/>
	/// </summary>
	/// <remarks>
	/// You can configure which events the Room will fire in the Zone:
	/// <ul>
	/// 		<li><b>allowUserEnter</b>: fire an event each time a User enters/joins the Room</li>
	/// 		<li><b>allowUserExit</b>: fire an event each time a User exits/leaves the Room</li>
	/// 		<li><b>allowUserCountChange</b>: fire an event each time the user count/spectator count changes in the Room</li>
	/// 		<li><b>allowUserVariablesUpdate</b>: fire an event each time a user in the Room has updated his/her UserVariables</li>
	/// </ul>
	/// 
	/// Each of these events can be turned ON (true) or OFF (false)
	/// </remarks>
	/// <seealso cref="RoomSettings"/>
	/// <seealso cref="CreateRoomRequest"/>
	class DLLImportExport RoomEvents
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		RoomEvents();
		bool AllowUserEnter();
		void AllowUserEnter(bool value);
		bool AllowUserExit();
		void AllowUserExit(bool value);
		bool AllowUserCountChange();
		void AllowUserCountChange(bool value);
		bool AllowUserVariablesUpdate();
		void AllowUserVariablesUpdate(bool value);

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
		bool allowUserEnter;
		bool allowUserExit;
		bool allowUserCountChange;
		bool allowUserVariablesUpdate;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
