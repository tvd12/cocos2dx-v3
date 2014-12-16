// ===================================================================
//
// Description		
//		Contains the definition of ISFSDataSerializer interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ISFSDataSerializer__
#define __ISFSDataSerializer__

#include "../../Util/ByteArray.h"
#include "../../Entities/Data/ISFSArray.h"
#include "../../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	class ISFSDataSerializer
	{
	public:
		virtual boost::shared_ptr<ByteArray> Object2Binary(boost::shared_ptr<ISFSObject> obj) = 0;
		virtual boost::shared_ptr<ByteArray> Array2Binary(boost::shared_ptr<ISFSArray> array) = 0;
		virtual boost::shared_ptr<ISFSObject> Binary2Object(boost::shared_ptr<ByteArray> data) = 0;
		virtual boost::shared_ptr<ISFSArray> Binary2Array(boost::shared_ptr<ByteArray> data) = 0;
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X

#endif
