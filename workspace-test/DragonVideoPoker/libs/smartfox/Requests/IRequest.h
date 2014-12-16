// ===================================================================
//
// Description		
//		Contains the definition of IRequest interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __IRequest__
#define __IRequest__

namespace Sfs2X {
namespace Requests {
	class IRequest;
}	// namespace Requests
}	// namespace Sfs2X

#include "../Util/Common.h"
#include "../Bitswarm/IMessage.h"
#include "../SmartFox.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X;
using namespace Sfs2X::Bitswarm;

namespace Sfs2X {
namespace Requests {

	class DLLImportExport IRequest
	{
	public:
		virtual void Validate(boost::shared_ptr<SmartFox> sfs) = 0;
		virtual void Execute(boost::shared_ptr<SmartFox> sfs) = 0;
		
		virtual long int TargetController() = 0;
		virtual void TargetController(long int value) = 0;
		
		virtual bool IsEncrypted() = 0;
		virtual void IsEncrypted(bool value) = 0;
		
		virtual boost::shared_ptr<IMessage> Message() = 0;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
