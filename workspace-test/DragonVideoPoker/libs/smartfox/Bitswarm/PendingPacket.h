// ===================================================================
//
// Description		
//		Contains the definition of PendingPacket
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PendingPacket__
#define __PendingPacket__

#include "../Core/PacketHeader.h"
#include "../Util/ByteArray.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Core;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class PendingPacket
	// -------------------------------------------------------------------
	class PendingPacket
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		PendingPacket(boost::shared_ptr<PacketHeader> header);
		~PendingPacket();

		boost::shared_ptr<PacketHeader> Header();
		boost::shared_ptr<ByteArray> Buffer();
		void Buffer(boost::shared_ptr<ByteArray> value);

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

		boost::shared_ptr<PacketHeader> header;
		boost::shared_ptr<ByteArray> buffer;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
