// ===================================================================
//
// Description		
//		Contains the definition of SFSIOHandler
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSIOHandler__
#define __SFSIOHandler__

#include "../FSM/FiniteStateMachine.h"
#include "../Bitswarm/BitSwarmClient.h"
#include "../Bitswarm/PendingPacket.h"
#include "../Bitswarm/PacketReadState.h"
#include "../Bitswarm/PacketReadTransition.h"
#include "../Bitswarm/IoHandler.h"
#include "../Protocol/IProtocolCodec.h"
#include "../Protocol/Serialization/DefaultObjectDumpFormatter.h"
#include "../Exceptions/SFSError.h"
#include "../Core/SFSProtocolCodec.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

using namespace Sfs2X::Logging;
using namespace Sfs2X::FSM;
using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Protocol;
using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Exceptions;

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
	
	// -------------------------------------------------------------------
	// Class SFSIOHandler
	// -------------------------------------------------------------------
	class SFSIOHandler : public IoHandler, public boost::enable_shared_from_this<SFSIOHandler>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSIOHandler(boost::shared_ptr<BitSwarmClient> bitSwarm);
		virtual ~SFSIOHandler();

		void Initialize();

		boost::shared_ptr<IProtocolCodec> Codec();
		void InitStates();

		/*
		 * STATE_MACHINE:
		 * Advances its job in aggregating the packet data through five possible states:
		 * 
		 * 1. WAIT_NEW_PACKET: start a brand new packet constructions
		 * 2. WAIT_DATA_SIZE: waiting for the DATA_SIZE field to come next
		 * 3. WAIT_DATA_SIZE_FRAGMENT: handle DATA_SIZE field fragmentation, if it didn't come through all at once
		 * 4. WAIT_DATA: handle the DATA field until DATA_SIZE (or more) is reached.
		 * 
		*/
		void OnDataRead(boost::shared_ptr<ByteArray> data);
		void OnDataWrite(boost::shared_ptr<IMessage> message);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static const long int SHORT_BYTE_SIZE;
		static const long int INT_BYTE_SIZE;

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

		PacketReadState ReadState();
		boost::shared_ptr<ByteArray> HandleNewPacket(boost::shared_ptr<ByteArray> data);
		boost::shared_ptr<ByteArray> HandleDataSize(boost::shared_ptr<ByteArray> data);
		boost::shared_ptr<ByteArray> HandleDataSizeFragment(boost::shared_ptr<ByteArray> data);
		boost::shared_ptr<ByteArray> HandlePacketData(boost::shared_ptr<ByteArray> data);
		boost::shared_ptr<ByteArray> HandleInvalidData(boost::shared_ptr<ByteArray> data);
		boost::shared_ptr<ByteArray> ResizeByteArray(boost::shared_ptr<ByteArray> arrayobj, long int pos, long int len);
		static void WriteBinaryData(unsigned long long context, boost::shared_ptr<PacketHeader> header, boost::shared_ptr<ByteArray> binData, bool udp);
		void WriteTCP(boost::shared_ptr<ByteArray> writeBuffer);
		void WriteUDP(boost::shared_ptr<ByteArray> writeBuffer);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<ByteArray> EMPTY_BUFFER;
		boost::shared_ptr<BitSwarmClient> bitSwarm;
		boost::shared_ptr<Logger> log;
		boost::shared_ptr<PendingPacket> pendingPacket;
		boost::shared_ptr<IProtocolCodec> protocolCodec; 
		long int skipBytes;
		boost::shared_ptr<FiniteStateMachine> fsm;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
