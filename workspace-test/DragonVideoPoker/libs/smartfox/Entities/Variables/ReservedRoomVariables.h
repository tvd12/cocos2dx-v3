// ===================================================================
//
// Description		
//		Contains the definition of ReservedRoomVariables
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ReservedRoomVariables__
#define __ReservedRoomVariables__

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
namespace Variables {

	// -------------------------------------------------------------------
	// Class ReservedRoomVariables
	// -------------------------------------------------------------------
	class ReservedRoomVariables
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		/// <summary>
		/// Used by the SFSGame Room to notify the started/stopped status of the Game
		/// </summary>
		/// <seealso cref="Requests.Game.CreateSFSGameRequest"/>
		static boost::shared_ptr<string> RV_GAME_STARTED;

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

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
