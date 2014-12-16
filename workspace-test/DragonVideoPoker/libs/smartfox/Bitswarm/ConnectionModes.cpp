// ===================================================================
//
// Description		
//		Contains the implementation of ConnectionModes
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ConnectionModes.h"

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Bitswarm {

boost::shared_ptr<string> ConnectionModes::SOCKET (new string("socket"));
boost::shared_ptr<string> ConnectionModes::HTTP (new string("http"));

}	// namespace Bitswarm
}	// namespace Sfs2X
