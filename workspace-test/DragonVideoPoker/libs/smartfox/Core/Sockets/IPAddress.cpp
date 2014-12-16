// ===================================================================
//
// Description		
//		Contains the implementation for the IP address entity
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "IPAddress.h"

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
IPAddress::IPAddress(IPAddressType type, string address)
{
	// Preserve input parameters into class members
	addressType = type;
	this->address = boost::shared_ptr<string>(new string(address));
}

// -------------------------------------------------------------------
// Address
// -------------------------------------------------------------------
boost::shared_ptr<string> IPAddress::Address()
{
	// Return the ip address value
	return address; 
}

// -------------------------------------------------------------------
// AddressType
// -------------------------------------------------------------------
IPAddress::IPAddressType IPAddress::AddressType()
{
	// Return the type of ip address
	return addressType;
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
