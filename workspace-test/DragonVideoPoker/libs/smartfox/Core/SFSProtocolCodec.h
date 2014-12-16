// ===================================================================
//
// Description		
//		Contains the definition of SFSProtocolCodec
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSProtocolCodec__
#define __SFSProtocolCodec__

#include "../Bitswarm/IoHandler.h"
#include "../Bitswarm/IMessage.h"
#include "../Bitswarm/Message.h"
#include "../Bitswarm/BitSwarmClient.h"
#include "../Protocol/IProtocolCodec.h"
#include "../Exceptions/SFSCodecError.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Entities/Data/SFSObject.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Protocol;
using namespace Sfs2X::Logging;

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Core {
	
	// -------------------------------------------------------------------
	// Class SFSProtocolCodec
	// -------------------------------------------------------------------
	class SFSProtocolCodec : public IProtocolCodec
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		SFSProtocolCodec(boost::shared_ptr<IoHandler> ioHandler, boost::shared_ptr<BitSwarmClient> bitSwarm); 
		virtual ~SFSProtocolCodec();

		boost::shared_ptr<IoHandler> IOHandler();
		void IOHandler(boost::shared_ptr<IoHandler> value);

		/*
		* TCP Data provides a ByteArray
		*/
		void OnPacketRead(boost::shared_ptr<ByteArray> packet);
		void OnPacketRead(boost::shared_ptr<ISFSObject> packet);
		void OnPacketWrite(boost::shared_ptr<IMessage> message);
		
		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> CONTROLLER_ID;
		static boost::shared_ptr<string> ACTION_ID;
		static boost::shared_ptr<string> PARAM_ID;
		static boost::shared_ptr<string> USER_ID;				// UDP Only
		static boost::shared_ptr<string> UDP_PACKET_ID;			// UDP Only

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

		boost::shared_ptr<ISFSObject> PrepareTCPPacket(boost::shared_ptr<IMessage> message);
		boost::shared_ptr<ISFSObject> PrepareUDPPacket(boost::shared_ptr<IMessage> message);
		void DispatchRequest(boost::shared_ptr<ISFSObject> requestObject);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<IoHandler> ioHandler;
		boost::shared_ptr<Logger> log;
		boost::shared_ptr<BitSwarmClient> bitSwarm;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
