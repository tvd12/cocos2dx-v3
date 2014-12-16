// ===================================================================
//
// Description		
//		Contains the definition of UserProperties
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UserProperties__
#define __UserProperties__

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
	/// A list of additional properties that can be used in MatchExpressions for User objects
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport UserProperties
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		UserProperties();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		/// <summary>
		/// The user name
		/// </summary>
		static boost::shared_ptr<string> NAME;
		
		/// <summary>
		/// The isPlayer flag
		/// </summary>
		static boost::shared_ptr<string> IS_PLAYER;
		
		/// <summary>
		/// The isSpectator flag
		/// </summary>
		static boost::shared_ptr<string> IS_SPECTATOR;
		
		/// <summary>
		/// The isNPC flag
		/// </summary>
		static boost::shared_ptr<string> IS_NPC;
		
		/// <summary>
		/// The User privilege Id
		/// </summary>
		static boost::shared_ptr<string> PRIVILEGE_ID;
		
		/// <summary>
		/// Checks if User.lastJoinedRoom == null, in other words the User is not joined in any Room
		/// </summary>
		static boost::shared_ptr<string> IS_IN_ANY_ROOM;

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
