// ===================================================================
//
// Description		
//		Contains the definition for the IP address entity
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IPAddress__
#define __IPAddress__

#include "../../Util/Common.h"			// Common API items

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Core {
namespace Sockets {

	// -------------------------------------------------------------------
	// Class IPAddress
	// -------------------------------------------------------------------
	class IPAddress
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Operator =
		//		value	The ip address that must be copied into this one
		// Return: the updated ip address 
		IPAddress& operator = (IPAddress & value)
		{
			// Copy each fields of an ip address item
			addressType = value.AddressType();
			address = value.Address();

			return *this;
		}

		// Defines the types of ip addresses
		typedef enum IPAddressType 
		{
			IPADDRESSTYPE_IPV4,
			IPADDRESSTYPE_IPV6
		} IPAddressType;

		// Constructor
		//		type		the type of ip address wrapped by this class instance
		//		address		the string that contains the ip address value expressed in dotted form (xxx.xxx.xxx.xxx)
		IPAddress(IPAddressType type, string address);

		// Get the value for ip address stored into class instance
		boost::shared_ptr<string> Address();

		//	Get the type of ip address stored into class instance
		//	Return: the type of ip address 
		IPAddress::IPAddressType AddressType();

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

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		IPAddressType addressType;				// The type of ip address
		boost::shared_ptr<string> address;		// The ip address expressed in dotted form (xxx.xxx.xxx.xxx)
	};

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X

#endif
