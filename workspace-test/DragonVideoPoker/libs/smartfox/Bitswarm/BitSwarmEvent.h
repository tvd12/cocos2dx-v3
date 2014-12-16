// ===================================================================
//
// Description		
//		Contains the definition of BitSwarmEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BitSwarmEvent__
#define __BitSwarmEvent__

#include "../Core/BaseEvent.h"
#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Core;

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class BitSwarmEvent
	// -------------------------------------------------------------------
	class DLLImportExport BitSwarmEvent : public BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		BitSwarmEvent(boost::shared_ptr<string> type);
		BitSwarmEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> CONNECT;
		static boost::shared_ptr<string> DISCONNECT;
		static boost::shared_ptr<string> RECONNECTION_TRY;
		static boost::shared_ptr<string> IO_ERROR;
		static boost::shared_ptr<string> SECURITY_ERROR;
		static boost::shared_ptr<string> DATA_ERROR;

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

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
