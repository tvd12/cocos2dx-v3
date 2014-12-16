// ===================================================================
//
// Description		
//		Contains the definition of an handler for a Tcp socket 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __TCPSocketLayer__
#define __TCPSocketLayer__

#include "ISocketLayer.h"						// ISocketLayer interface
#include "../../Logging/Logger.h"				// Logging service
#include "../../Bitswarm/BitSwarmClient.h"		// Bitswarm
#include "../../FSM/FiniteStateMachine.h"		// State machine
#include "TCPClient.h"							// TCP client handler
#include "../../Util/Common.h"					// Common API items

#include <boost/asio.hpp>						// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this
using boost::asio::ip::tcp;						// Boost Asio namespace

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Logging;
using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::FSM;

// -------------------------------------------------------------------
// Defines
// -------------------------------------------------------------------
#define Const_TimeoutConnect 10		// Timeout Tcp connect [sec.]

namespace Sfs2X {
namespace Core {
namespace Sockets {

	// -------------------------------------------------------------------
	// Class TCPSocketLayer
	// -------------------------------------------------------------------
	class TCPSocketLayer : public ISocketLayer, public boost::enable_shared_from_this<TCPSocketLayer>
	{
	public:

		// -------------------------------------------------------------------
		// Public types
		// -------------------------------------------------------------------

		typedef enum States
		{
			States_Disconnected,
			States_Connecting,
			States_Connected
		};
		
		typedef enum Transitions
		{
			Transitions_StartConnect,
			Transitions_ConnectionSuccess,
			Transitions_ConnectionFailure,
			Transitions_Disconnect
		};

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		// Creates and initializes an instance of this class
		//		bs		Bitswarm client
		TCPSocketLayer (boost::shared_ptr<BitSwarmClient> bs);

		// Destructor
		// Destroy an instance of this class
		virtual ~TCPSocketLayer();

		// State
		// Returns the state
		States State();

		void SocketPollSleep (long int value);
		long int SocketPollSleep();

		// ISocketLayer implementation

		virtual void Connect(boost::shared_ptr<IPAddress> address, unsigned short int port);
		virtual bool IsConnected();
		virtual bool RequiresConnection();
		virtual void Disconnect();

		virtual boost::shared_ptr<ConnectionDelegate> OnConnect();						// Get delegate
		virtual void OnConnect(boost::shared_ptr<ConnectionDelegate> onConnect);			// Set delegate

		virtual boost::shared_ptr<ConnectionDelegate> OnDisconnect();						// Get delegate
		virtual void OnDisconnect(boost::shared_ptr<ConnectionDelegate> onDisconnect);	// Set delegate

		virtual void Write(boost::shared_ptr<vector<unsigned char> >);

		virtual boost::shared_ptr<OnDataDelegate> OnData();								// Get delegate
		virtual void OnData(boost::shared_ptr<OnDataDelegate> onData);					// Set delegate

		virtual boost::shared_ptr<OnErrorDelegate> OnError();								// Get delegate
		virtual void OnError(boost::shared_ptr<OnErrorDelegate> onError);					// Set delegate

		virtual void Kill();

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

		void InitStates();
		void LogWarn(boost::shared_ptr<string> msg);
		void LogError(boost::shared_ptr<string> msg);
		void HandleError(boost::shared_ptr<string> err);
		void HandleError(boost::shared_ptr<string> err, SocketErrors se);
		static void HandleErrorCallback(unsigned long long context, boost::shared_ptr<void> state);
		void CallOnConnect();
		void CallOnDisconnect();
		void CallOnData(boost::shared_ptr<vector<unsigned char> > data);
		void CallOnError(boost::shared_ptr<string> msg, SocketErrors se);
		void HandleDisconnection();
		void HandleBinaryData(boost::shared_ptr<vector<unsigned char> > data);
		void WriteSocket(boost::shared_ptr<vector<unsigned char> > data);

		// Connection	

		// OnSocketConnection
		// Notifies the result of a network connection task
		//		context		Optional context
		//		code		Error code for connection task
		static void OnSocketConnection(unsigned long long context, SocketErrors code);

		// OnSocketDataReceived
		// Notifies the receiving of data from network connection 
		//		context		Optional context
		//		data		Received data
		static void OnSocketDataReceived(unsigned long long context, boost::shared_ptr<vector<unsigned char> > data);

		// OnSocketDataSent
		// Notifies the completion of data transmission over network connection
		//		context		Optional context
		//		code		Error code for data send task
		static void OnSocketDataSent(unsigned long long context, SocketErrors code);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		const static long int READ_BUFFER_SIZE = 4096;
		boost::shared_ptr<Logger> log;
		boost::shared_ptr<BitSwarmClient> bitSwarm;
		boost::shared_ptr<FiniteStateMachine> fsm;
		volatile bool isDisconnecting;
		long int socketPollSleep;

		// Connection	

		boost::shared_ptr<TCPClient> connection;
		unsigned short int socketNumber;
		boost::shared_ptr<IPAddress> ipAddress;

		boost::shared_ptr<ConnectionDelegate> onConnect;		// Callback to notify tcp connection result
		boost::shared_ptr<ConnectionDelegate> onDisconnect;		// Callback to notify tcp disconnection result
		boost::shared_ptr<OnErrorDelegate> onError;				// Callback to notify errors
		boost::shared_ptr<OnDataDelegate> onData;				// Callback to notify data


		// Socket reading

		unsigned char byteBuffer[READ_BUFFER_SIZE];


		boost::shared_ptr<TCPSocketLayer> me;
	};

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X

#endif
