// ===================================================================
//
// Description		
//		Contains the definition of BBEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BBEvent__
#define __BBEvent__

#include "../../Core/BaseEvent.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Core;

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

	// -------------------------------------------------------------------
	// Class BBEvent
	// -------------------------------------------------------------------
	class BBEvent : public BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		BBEvent(boost::shared_ptr<string> type);
		BBEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> CONNECT;
		static boost::shared_ptr<string> DISCONNECT;
		static boost::shared_ptr<string> DATA;
		static boost::shared_ptr<string> IO_ERROR;
		static boost::shared_ptr<string> SECURITY_ERROR;

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

}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
