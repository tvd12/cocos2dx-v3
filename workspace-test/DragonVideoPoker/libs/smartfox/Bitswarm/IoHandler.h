// ===================================================================
//
// Description		
//		Contains the definition of IoHandler interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IoHandler__
#define __IoHandler__

// Forward class declaration
namespace Sfs2X {
namespace Bitswarm {
	class IoHandler;
}	// namespace Bitswarm
}	// namespace Sfs2X

#include "IMessage.h"
#include "../Util/ByteArray.h"
#include "../Protocol/IProtocolCodec.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Protocol;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
	// Interface IoHandler
	// -------------------------------------------------------------------
	class IoHandler
	{
	public:
		virtual void OnDataRead(boost::shared_ptr<ByteArray> buffer) = 0;
		virtual void OnDataWrite(boost::shared_ptr<IMessage> message) = 0;
		virtual boost::shared_ptr<IProtocolCodec> Codec() = 0;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif

