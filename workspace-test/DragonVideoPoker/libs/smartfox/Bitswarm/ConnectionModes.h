// ===================================================================
//
// Description		
//		Contains the definition of ConnectionModes
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ConnectionModes__
#define __ConnectionModes__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
using namespace std;			// Declare the STL namespace

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class ConnectionModes
	// -------------------------------------------------------------------
	class ConnectionModes
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> SOCKET;
		static boost::shared_ptr<string> HTTP;

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

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
