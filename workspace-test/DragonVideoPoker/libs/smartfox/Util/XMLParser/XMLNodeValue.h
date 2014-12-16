// ===================================================================
//
// Description		
//		Contains the definition of XMLNodeValue
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __XMLNodeValue__
#define __XMLNodeValue__

#if defined(_MSC_VER)
#pragma warning(disable:4786)	// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
using namespace std;			// Declare the STL namespace

#include "XMLObject.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {
	class XMLNodeValue;
}	// namespace Util
}	// namespace Sfs2X

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class XMLNodeValue
	// -------------------------------------------------------------------
	class XMLNodeValue : public std::string
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		XMLNodeValue();
		XMLNodeValue(const boost::shared_ptr<XMLNodeValue> other);
		XMLNodeValue(const boost::shared_ptr<char> other);
		XMLNodeValue(string other);

		~XMLNodeValue();

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
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
