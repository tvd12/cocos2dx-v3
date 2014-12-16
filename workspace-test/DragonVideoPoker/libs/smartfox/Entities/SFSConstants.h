// ===================================================================
//
// Description		
//		Contains the definition of SFSConstants
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSConstants__
#define __SFSConstants__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

namespace Sfs2X {
namespace Entities {

	// ------------------------------------------------------------------- 
	// Class SFSConstants
	// -------------------------------------------------------------------
	/*static*/ class SFSConstants
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<string> DEFAULT_GROUP_ID;
		static boost::shared_ptr<string> REQUEST_UDP_PACKET_ID;
		
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

}	// namespace Entities
}	// namespace Sfs2X

#endif
