// ===================================================================
//
// Description		
//		Contains the implementation of ClientDisconnectionReason
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#include "ClientDisconnectionReason.h"

using namespace std;

namespace Sfs2X {
namespace Util {

boost::shared_ptr<string> ClientDisconnectionReason::IDLE (new string("idle"));
boost::shared_ptr<string> ClientDisconnectionReason::KICK (new string("kick")); 
boost::shared_ptr<string> ClientDisconnectionReason::BAN (new string("ban")); 
boost::shared_ptr<string> ClientDisconnectionReason::MANUAL (new string("manual")); 
boost::shared_ptr<string> ClientDisconnectionReason::UNKNOWN (new string("unknown"));

string* ClientDisconnectionReason::reasons[] = 
{
	new string("idle"), 
	new string("kick"), 
	new string("ban")
};

// -------------------------------------------------------------------
// GetReason
// -------------------------------------------------------------------
boost::shared_ptr<string> ClientDisconnectionReason::GetReason(long int reasonId)
{
	return boost::shared_ptr<string>(new string(*(reasons[reasonId])));
}

}	// namespace Util
}	// namespace Sfs2X
