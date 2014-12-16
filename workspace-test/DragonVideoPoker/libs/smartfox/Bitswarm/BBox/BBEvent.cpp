// ===================================================================
//
// Description		
//		Contains the implementation of BBEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BBEvent.h"

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

boost::shared_ptr<string> BBEvent::CONNECT (new string("bb-connect"));
boost::shared_ptr<string> BBEvent::DISCONNECT (new string("bb-disconnect"));
boost::shared_ptr<string> BBEvent::DATA (new string("bb-data"));
boost::shared_ptr<string> BBEvent::IO_ERROR (new string("bb-ioError"));
boost::shared_ptr<string> BBEvent::SECURITY_ERROR (new string("bb-securityError"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BBEvent::BBEvent(boost::shared_ptr<string> type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BBEvent::BBEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments)
	: BaseEvent (type, arguments)
{
}

}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X


