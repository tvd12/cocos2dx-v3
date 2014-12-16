// ===================================================================
//
// Description		
//		Contains the implementation of SFSErrorCodes
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSErrorCodes.h"
#include <boost/format.hpp>

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace std;
using boost::format;
using boost::io::group;

namespace Sfs2X {
namespace Util {

string* SFSErrorCodes::errorsByCode[] = 
{
			new string("Client API version is obsolete: %s; required version: %s"), 										// 0
			new string("Requested Zone %s does not exist"),							
			new string("User name %s is not recognized"),
			new string("Wrong password for user %s"),
			new string("User %s is banned"),
			new string("Zone %s is full"),																					// 5
			new string("User %s is already logged in Zone %s"),
			new string("The server is full"),
			new string("Zone %s is currently inactive"),
			new string("User name %s contains bad words; filtered: %s"),
			new string("Guest users not allowed in Zone %s"),																// 10
			new string("IP address %s is banned"),
			new string("A Room with the same name already exists: %s"),
			new string("Requested Group is not available - Room: %s; Group: %s"),
			new string("Bad Room name length -  Min: %s; max: %s; passed name length: %s"),
			new string("Room name contains bad words: %s"),																	// 15
			new string("Zone is full; can't add Rooms anymore"),
			new string("You have exceeded the number of Rooms that you can create per session: %s"),
			new string("Room creation failed, wrong parameter: %s"),
			new string("User %s already joined in Room"),
			new string("Room %s is full"),																					// 20
			new string("Wrong password for Room %s"),
			new string("Requested Room does not exist"),
			new string("Room %s is locked"),
			new string("Group %s is already subscribed"),
			new string("Group %s does not exist"),																			// 25
			new string("Group %s is not subscribed"), 
			new string("Group %s does not exist"),
			new string("%s"),
 			new string("Room permission error; Room %s cannot be renamed"),
 			new string("Room permission error; Room %s cannot change password statee"),										// 30 
 			new string("Room permission error; Room %s cannot change capacity"),
			new string("Switch user error; no player slots available in Room %s"),
			new string("Switch user error; no spectator slots available in Room %s"),
			new string("Switch user error; Room %s is not a Game Room"),
			new string("Switch user error; you are not joined in Room %s"),													// 35
			new string("Buddy Manager initialization error, could not load buddy list: %s"),
			new string("Buddy Manager error, your buddy list is full; size is %s"),
			new string("Buddy Manager error, was not able to block buddy %s because offline"),
			new string("Buddy Manager error, you are attempting to set too many Buddy Variables; limit is %s"),
			new string("Game %s access denied, user does not match access criteria"),										// 40
			new string("QuickJoinGame action failed: no matching Rooms were found"),
			new string("Your previous invitation reply was invalid or arrived too late")
};

// -------------------------------------------------------------------
// SetErrorMessage
// -------------------------------------------------------------------
void SFSErrorCodes::SetErrorMessage(long int code, string message)
{
	errorsByCode[code] = new string(message);
}

// -------------------------------------------------------------------
// GetErrorMessage
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSErrorCodes::GetErrorMessage(long int code, boost::shared_ptr<Logger> log, boost::shared_ptr<vector<string> > args) 
{
    format f(*errorsByCode[code]);
    for (std::vector<std::string>::const_iterator it = args->begin(); it != args->end(); ++it) 
	{
        f % *it;
    }
    return boost::shared_ptr<string>(new string(f.str()));
}

}	// namespace Util
}	// namespace Sfs2X
