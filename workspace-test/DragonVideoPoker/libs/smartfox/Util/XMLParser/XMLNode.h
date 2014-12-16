// ===================================================================
//
// Description		
//		Contains the definition of XMLNode
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __XMLNode__
#define __XMLNode__

#if defined(_MSC_VER)
#pragma warning(disable:4786)	// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <map>					// STL library: map object
#include <vector>				// STL library: vector object
using namespace std;			// Declare the STL namespace

namespace Sfs2X {
namespace Util {
	class XMLNode;
}	// namespace Util
}	// namespace Sfs2X

#include "XMLObject.h"
#include "XMLNodeList.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class XMLNode
	// -------------------------------------------------------------------
	class XMLNode : public std::map<string, tagXMLObject>, public boost::enable_shared_from_this<XMLNode>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		XMLNode();
		~XMLNode();

		boost::shared_ptr<XMLNodeList> GetNodeList(boost::shared_ptr<string> path);
		boost::shared_ptr<XMLNode> GetNode(boost::shared_ptr<string> path);
		boost::shared_ptr<string> GetValue(boost::shared_ptr<string> path);

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
		boost::shared_ptr<void> GetObject(boost::shared_ptr<string> path);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
