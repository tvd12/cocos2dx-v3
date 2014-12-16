// ===================================================================
//
// Description		
//		Contains the definition of IUDPManager interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IUDPManager__
#define __IUDPManager__

#include "../Util/ByteArray.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
	// Interface IUDPManager
	// -------------------------------------------------------------------
	class IUDPManager
	{
	public:
		virtual void Initialize(string udpAddr, unsigned short int udpPort) = 0;
		virtual bool Inited() = 0;
		virtual long long NextUdpPacketId() = 0;
		virtual void Send(boost::shared_ptr<ByteArray> binaryData) = 0;
		virtual void Reset() = 0;
		virtual void Disconnect() = 0;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
