// ===================================================================
//
// Description		
//		Contains the definition of XMLNodeList
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __XMLNodeList__
#define __XMLNodeList__

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {
	class XMLNodeList;
}	// namespace Util
}	// namespace Sfs2X

#include "XMLObject.h"
#include "XMLNode.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	class XMLNodeList : public std::list<boost::shared_ptr<XMLNode> >
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		XMLNodeList();
		virtual ~XMLNodeList();

		boost::shared_ptr<XMLNode> Pop();
		long int Push(boost::shared_ptr<XMLNode> item);

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
