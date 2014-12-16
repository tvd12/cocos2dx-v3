// ===================================================================
//
// Description		
//		Contains the definition of ReservedBuddyVariables
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ReservedBuddyVariables__
#define __ReservedBuddyVariables__

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
namespace Variables {

	// -------------------------------------------------------------------
	// Class ReservedBuddyVariables
	// -------------------------------------------------------------------
	class ReservedBuddyVariables
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		/// <summary>
		/// This variable keeps track of the Online Status of the Buddy
		/// </summary>
		static boost::shared_ptr<string> BV_ONLINE;

		/// <summary>
		/// This variable stores the custom Buddy state (e.g. "Available", "Busy" etc...)
		/// </summary>
		static boost::shared_ptr<string> BV_STATE;

		/// <summary>
		/// This variable stores an optional nickname for the Buddy
		/// </summary>
		static boost::shared_ptr<string> BV_NICKNAME;

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
