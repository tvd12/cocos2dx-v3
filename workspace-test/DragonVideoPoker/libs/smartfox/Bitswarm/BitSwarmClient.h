// ===================================================================
//
// Description		
//		Contains the definition of BitSwarmClient
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BitSwarmClient__
#define __BitSwarmClient__

// Forward class declaration
namespace Sfs2X {
namespace Bitswarm {
	class BitSwarmClient;
}	// namespace Bitswarm
}	// namespace Sfs2X

#include "BitSwarmEvent.h"
#include "IUDPManager.h"
#include "IoHandler.h"
#include "IController.h"
#include "ConnectionModes.h"
#include "./BBox/BBClient.h"
#include "../Logging/Logger.h"
#include "../Core/IDispatchable.h"
#include "../Core/ThreadManager.h"
#include "../Util/EventDispatcher.h"
#include "../Core/Sockets/TCPSocketLayer.h"
#include "../Core/Sockets/SocketErrors.h"
#include "../SmartFox.h"
#include "../Util/ClientDisconnectionReason.h"
#include "../Exceptions/SFSError.h"

#include <boost/asio/deadline_timer.hpp>		// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <map>							// STL library: map object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Logging;
using namespace Sfs2X::Util;

using namespace Sfs2X::Core;
using namespace Sfs2X::Core::Sockets;
using namespace Sfs2X::Bitswarm::BBox;

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
	// Class BitSwarmClient
	// -------------------------------------------------------------------
	class BitSwarmClient : public IDispatchable, public boost::enable_shared_from_this<BitSwarmClient>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		BitSwarmClient(boost::shared_ptr<boost::asio::io_service> service);
		BitSwarmClient(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<boost::asio::io_service> service);
		virtual ~BitSwarmClient();

		boost::shared_ptr<boost::asio::io_service> GetBoostService();
		boost::shared_ptr<Sfs2X::Core::ThreadManager> ThreadManager();
		boost::shared_ptr<string> ConnectionMode();
		bool UseBlueBox();
		bool Debug();
		boost::shared_ptr<SmartFox> Sfs();
		bool Connected();
		boost::shared_ptr<Sfs2X::Bitswarm::IoHandler> IoHandler();
		void IoHandler(boost::shared_ptr<Sfs2X::Bitswarm::IoHandler> value);
		long int CompressionThreshold();
		void CompressionThreshold(long int value);
		long int MaxMessageSize();
		void MaxMessageSize (long int value);
		boost::shared_ptr<ISocketLayer> Socket();
		boost::shared_ptr<BBClient> HttpClient();
		bool IsReconnecting();
		void IsReconnecting(bool value);
		long int ReconnectionSeconds();
		void ReconnectionSeconds(long int value);
		void Dispatcher(boost::shared_ptr<EventDispatcher> value);
		boost::shared_ptr<Logger> Log();
		void ForceBlueBox(bool val);
		void EnableBlueBoxDebug(bool val);
		void Init();
		void Destroy();
		boost::shared_ptr<IController> GetController(long int id);
		boost::shared_ptr<string> ConnectionIp();
		long int ConnectionPort();
		void Connect();
		void Connect(boost::shared_ptr<string> ip, unsigned short int port);
		void Send(boost::shared_ptr<IMessage> message);
		void Disconnect();
		void Disconnect(boost::shared_ptr<string> reason);
		void StopReconnection();

		// IDispatchable implementation

		void AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);
		boost::shared_ptr<EventDispatcher> Dispatcher();
		void DispatchEvent(boost::shared_ptr<BitSwarmEvent> evt);

		// Socket handlers

		void KillConnection();

		// UDP

		boost::shared_ptr<IUDPManager> UdpManager();
		void UdpManager(boost::shared_ptr<IUDPManager> value);
		long long NextUdpPacketId();

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

		void AddController(long int id, boost::shared_ptr<IController> controller);
		void InitControllers();
		void RetryConnection(long int timeout);
		void OnRetryConnectionEvent(const boost::system::error_code& code);

		void ExecuteDisconnection();
		void ReleaseResources();

		static void OnBBConnect(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnBBData(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnBBDisconnect(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnBBError(unsigned long long context, boost::shared_ptr<BaseEvent> e);

		// Socket handlers

		static void OnSocketConnect(unsigned long long context);
		static void OnSocketClose(unsigned long long context);
		static void OnSocketData(unsigned long long context, boost::shared_ptr<vector<unsigned char> > data);
		static void OnSocketError(unsigned long long context, boost::shared_ptr<string> message, SocketErrors se);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<ISocketLayer> socket;
		std::map<long int, boost::shared_ptr<IController> > controllers;
		long int compressionThreshold; 
		long int maxMessageSize;
		boost::shared_ptr<SmartFox> sfs;						
		boost::shared_ptr<string> lastIpAddress; 
		unsigned short int lastTcpPort; 
		long int reconnectionSeconds;
		bool attemptingReconnection;  
		boost::shared_ptr<Logger> log;						
		boost::shared_ptr<IUDPManager> udpManager;
		bool controllersInited;
		boost::shared_ptr<EventDispatcher> dispatcher;
		boost::shared_ptr<BBClient> bbClient;
		volatile bool useBlueBox;
		bool bbConnected;
		boost::shared_ptr<string> connectionMode;
		boost::shared_ptr<Sfs2X::Core::ThreadManager> threadManager;		
		boost::shared_ptr<Sfs2X::Bitswarm::IoHandler> ioHandler;
		bool manualDisconnection;

		boost::shared_ptr<boost::asio::deadline_timer> retryTimer;			// Boost Asio deadline timer
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
