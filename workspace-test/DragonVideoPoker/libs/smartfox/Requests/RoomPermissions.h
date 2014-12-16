// ===================================================================
//
// Description		
//		Contains the definition of RoomPermissions
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomPermissions__
#define __RoomPermissions__

#include "../Util/Common.h"

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This object is part of the RoomSettings parameters used for creating a new Room. 
	/// </summary>
	/// <remarks>
	/// It describes the permission settings of a new Room
	/// </remarks>
	/// <seealso cref="RoomSettings"/>
	/// <seealso cref="CreateRoomRequest"/>
	class DLLImportExport RoomPermissions
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		RoomPermissions();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		bool AllowNameChange();
		void AllowNameChange(bool value);
		bool AllowPasswordStateChange();
		void AllowPasswordStateChange(bool value);
		bool AllowPublicMessages();
		void AllowPublicMessages(bool value);
		bool AllowResizing();
		void AllowResizing(bool value);

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
		bool allowNameChange;
		bool allowPasswordStateChange;
		bool allowPublicMessages;
		bool allowResizing;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
