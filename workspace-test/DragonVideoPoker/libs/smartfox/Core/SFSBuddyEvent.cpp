// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddyEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddyEvent.h"

namespace Sfs2X {
namespace Core {

boost::shared_ptr<string> SFSBuddyEvent::BUDDY_LIST_INIT (new string("buddyListInit"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_ADD (new string("buddyAdd"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_REMOVE (new string("buddyRemove"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_BLOCK (new string("buddyBlock"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_ERROR (new string("buddyError"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_ONLINE_STATE_UPDATE (new string("buddyOnlineStateChange"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_VARIABLES_UPDATE (new string("buddyVariablesUpdate"));
boost::shared_ptr<string> SFSBuddyEvent::BUDDY_MESSAGE (new string("buddyMessage"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyEvent::SFSBuddyEvent(boost::shared_ptr<string> type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyEvent::SFSBuddyEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > args)
	: BaseEvent (type, args)
{
}

}	// namespace Core
}	// namespace Sfs2X

