// ===================================================================
//
// Description		
//		Contains the definition of RoomVariable interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomVariable__
#define __RoomVariable__

#include "../../Util/Common.h"
#include "UserVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

	class DLLImportExport RoomVariable : public UserVariable
	{
	public:
		/// <summary>
		/// Checks if the variable is private. 
		/// </summary>
		/// <remarks>
		/// A private RoomVariable is only modifiable by its owner (the user that created it)
		/// </remarks>
		virtual bool IsPrivate() = 0;

		/// <summary>
		/// Checks if the variable is private. 
		/// </summary>
		/// <remarks>
		/// A private RoomVariable is only modifiable by its owner (the user that created it)
		/// </remarks>
		virtual void IsPrivate(bool value) = 0;

		/// <summary>
		/// Checks if the variable is persistent. 
		/// </summary>
		/// <remarks>
		/// A persistent RoomVariable continues to exist in a Room after the User has left it and until he disconnects
		/// </remarks>
		virtual bool IsPersistent() = 0;

		/// <summary>
		/// Checks if the variable is persistent. 
		/// </summary>
		/// <remarks>
		/// A persistent RoomVariable continues to exist in a Room after the User has left it and until he disconnects
		/// </remarks>
		virtual void IsPersistent(bool value) = 0;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
