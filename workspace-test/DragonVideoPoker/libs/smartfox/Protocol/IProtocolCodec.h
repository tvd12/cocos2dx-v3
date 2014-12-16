// ===================================================================
//
// Description		
//		Contains the definition of IProtocolCodec interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IProtocolCodec__
#define __IProtocolCodec__

namespace Sfs2X {
namespace Protocol {
	class IProtocolCodec;
}	// namespace Protocol
}	// namespace Sfs2X

#include "../Bitswarm/IMessage.h"
#include "../Bitswarm/IoHandler.h"
#include "../Util/ByteArray.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Util;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Protocol {

	class IProtocolCodec
	{
	public:
		virtual void OnPacketRead(boost::shared_ptr<ISFSObject> packet) = 0;
		virtual void OnPacketRead(boost::shared_ptr<ByteArray> packet) = 0;
		virtual void OnPacketWrite(boost::shared_ptr<IMessage> message) = 0;
		
		virtual boost::shared_ptr<IoHandler> IOHandler() = 0;
		virtual void IOHandler(boost::shared_ptr<IoHandler> value) = 0;
	};

}	// namespace Protocol
}	// namespace Sfs2X

#endif
