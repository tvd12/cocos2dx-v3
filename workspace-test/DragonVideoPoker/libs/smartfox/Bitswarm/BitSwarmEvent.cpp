// ===================================================================
//
// Description		
//		Contains the implementation of BitSwarmEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BitSwarmEvent.h"

namespace Sfs2X {
namespace Bitswarm {

boost::shared_ptr<string> BitSwarmEvent::CONNECT (new string("connect"));
boost::shared_ptr<string> BitSwarmEvent::DISCONNECT (new string("disconnect"));
boost::shared_ptr<string> BitSwarmEvent::RECONNECTION_TRY (new string("reconnectionTry"));
boost::shared_ptr<string> BitSwarmEvent::IO_ERROR (new string("ioError"));
boost::shared_ptr<string> BitSwarmEvent::SECURITY_ERROR (new string("securityError"));
boost::shared_ptr<string> BitSwarmEvent::DATA_ERROR (new string("dataError"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmEvent::BitSwarmEvent(boost::shared_ptr<string> type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmEvent::BitSwarmEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments)
	: BaseEvent (type, arguments)
{
}


}	// namespace Bitswarm
}	// namespace Sfs2X
