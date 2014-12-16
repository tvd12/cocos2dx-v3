// ===================================================================
//
// Description		
//		Contains the definition of BaseController
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BaseController__
#define __BaseController__

#include "IController.h"				// IController interface
#include "BitSwarmClient.h"				// BitSwarmClient class
#include "../SmartFox.h"				// SmartFox class
#include "../Logging/Logger.h"			// Logging service
#include "IMessage.h"					// IMessage interface
#include "../Exceptions/SFSError.h"		// SFS error class

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X;
using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Logging;

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class BaseController
	// -------------------------------------------------------------------
	class BaseController : public IController
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		BaseController ();
		BaseController (boost::shared_ptr<BitSwarmClient> bitSwarm);

		virtual ~BaseController();

		virtual void HandleMessage(boost::shared_ptr<IMessage> message) = 0;
		long int Id();
		void Id(long int value);

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

		long int id;
		boost::shared_ptr<SmartFox> sfs;
		boost::shared_ptr<BitSwarmClient> bitSwarm;
		boost::shared_ptr<Logger> log;

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
