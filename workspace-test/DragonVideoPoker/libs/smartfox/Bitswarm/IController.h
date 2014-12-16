// ===================================================================
//
// Description		
//		Contains the definition of IController interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IController__
#define __IController__

#include "IMessage.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
	// Interface IController
	// -------------------------------------------------------------------
	class IController
	{
	public:
		virtual long int Id(void) = 0;
		virtual void Id(long int value) = 0;
		virtual void HandleMessage(boost::shared_ptr<IMessage> message) = 0;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
