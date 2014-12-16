// ===================================================================
//
// Description		
//		Contains the definition of UDPManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UDPManager__
#define __UDPManager__

#include "IUDPManager.h"					// IUDPManager interface
#include "../Core/Sockets/ISocketLayer.h"	// ISocketLayer interface
#include "../SmartFox.h"					// SmartFox class
#include "../Logging/Logger.h"				// Logging service

#include <boost/bind.hpp>						// Boost Asio header
#include <boost/asio.hpp>						// Boost Asio header
#include <boost/asio/deadline_timer.hpp>		// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

using namespace Sfs2X;
using namespace Sfs2X::Logging;

using boost::asio::ip::tcp;					// Boost Asio namespace

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class UDPManager
	// -------------------------------------------------------------------
	class UDPManager : public IUDPManager, public boost::enable_shared_from_this<UDPManager>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		UDPManager(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs);
		virtual ~UDPManager();

		void Initialize(string udpAddr, unsigned short int udpPort);
		long long NextUdpPacketId();
		void Send(boost::shared_ptr<ByteArray> binaryData);
		bool Inited();
		bool isConnected();
		void Reset();
		void Disconnect(); 

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
		static void OnUDPData(unsigned long long context, boost::shared_ptr<vector<unsigned char> > bt);
		static void OnUDPError(unsigned long long context, boost::shared_ptr<string> msg, SocketErrors se); 
		void SendInitializationRequest();
		void OnTimeout(const boost::system::error_code& code);
		void StartTimer();
		void StopTimer();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<SmartFox> sfs;
		long long packetId;
		boost::shared_ptr<ISocketLayer> udpSocket;
		bool inited;
		boost::shared_ptr<Logger> log;
		bool locked;  
		bool initSuccess;
		
		// Init transaction variables
		const static long int MAX_RETRY = 3;				// Retry max 3 times
		const static long int RESPONSE_TIMEOUT = 3000;		// Wait response for max 3 seconds
			
		boost::asio::io_service& boostIoService;			// Boost Asio IO service		
		boost::asio::deadline_timer initThread;		
	
		long int currentAttempt;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
