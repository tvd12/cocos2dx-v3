// ===================================================================
//
// Description		
//		Contains the definition of XMLObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __XMLObject__
#define __XMLObject__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	typedef enum XMLObjectType
	{
		XMLObjectType_XMLNode,
		XMLObjectType_XMLNodeList,
		XMLObjectType_XMLNodeValue
	};		

	typedef struct
	{
		XMLObjectType type;
		boost::shared_ptr<void> XMLObjectInstance;
	} tagXMLObject;

}	// namespace Util
}	// namespace Sfs2X

#endif
