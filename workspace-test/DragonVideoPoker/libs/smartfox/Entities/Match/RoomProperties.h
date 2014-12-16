// ===================================================================
//
// Description		
//		Contains the definition of RoomProperties
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomProperties__
#define __RoomProperties__

#include "../../Util/Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Match {

	/// <summary>
	/// A list of additional properties that can be used in MatchExpressions for Room objects
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport RoomProperties
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		RoomProperties();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		/// <summary>
		/// The Room name
		/// </summary>
		static boost::shared_ptr<string> NAME;
		
		/// <summary>
		/// The Room group id
		/// </summary>
		static boost::shared_ptr<string> GROUP_ID;
		
		/// <summary>
		/// The Room max users
		/// </summary>
		static boost::shared_ptr<string> MAX_USERS;
		
		/// <summary>
		/// The Room max spectators
		/// </summary>
		static boost::shared_ptr<string> MAX_SPECTATORS;
		
		/// <summary>
		/// The Room user count
		/// </summary>
		static boost::shared_ptr<string> USER_COUNT;
		
		/// <summary>
		/// The Room spectator count
		/// </summary>
		static boost::shared_ptr<string> SPECTATOR_COUNT;
		
		/// <summary>
		/// The Room isGame flag
		/// </summary>
		static boost::shared_ptr<string> IS_GAME;
		
		/// <summary>
		/// The Room isPrivate flag
		/// </summary>
		static boost::shared_ptr<string> IS_PRIVATE;
		
		/// <summary>
		/// Check if the Room has at least 1 free player slot
		/// </summary>
		static boost::shared_ptr<string> HAS_FREE_PLAYER_SLOTS;
		
		/// <summary>
		/// Check if the Room is of type SFSGame
		/// </summary>
		static boost::shared_ptr<string> IS_TYPE_SFSGAME;
		
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

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X

#endif
