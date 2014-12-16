// ===================================================================
//
// Description		
//		Contains the definition of an handler for a Udp client 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UDPClient__
#define __UDPClient__

#include "../../Util/Common.h"					// Common API items
#include "IPAddress.h"							// Ip address item
#include "../../Util/DelegateOneArgument.h"		// Delegate with one parameter
#include "SocketErrors.h"						// Socket errors

#include <boost/bind.hpp>						// Boost Asio header
#include <boost/asio.hpp>						// Boost Asio header
#include <boost/asio/deadline_timer.hpp>		// Boost Asio header
#include <boost/array.hpp>						// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost Asio shared from this
#include <boost/thread/recursive_mutex.hpp>		// Boost Asio header

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using boost::asio::ip::udp;					// Boost Asio namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
namespace Sockets {

	// -------------------------------------------------------------------
	// Definition of delegates specific for the Udp client handler
	// -------------------------------------------------------------------
	typedef DelegateOneArgument<SocketErrors> UDPConnectionDelegate;
	typedef DelegateOneArgument<boost::shared_ptr<vector<unsigned char> > > UDPDataReadDelegate;
	typedef DelegateOneArgument<SocketErrors> UDPDataWriteDelegate;

	// -------------------------------------------------------------------
	// Class UDPClient
	// -------------------------------------------------------------------
	class UDPClient : public boost::enable_shared_from_this<UDPClient>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		//		io_service		Boost Asio service
		UDPClient (boost::asio::io_service& io_service);

		// Destructor
		~UDPClient();

		// Connect
		// Attemps to establish a udp client connection
		//		ipAddress		Server ip address expressed in dotted form
		//		ipPort			Server ip port
		//		timeout			Connection timeout expressed in seconds
		//		callback		Callback to notify operation result
		void Connect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort, long int timeout, boost::shared_ptr<UDPConnectionDelegate> callback);
		
		// Shutdown
		// Terminate an established udp client connection
		void Shutdown();

		// AsynchRead
		// Begin an asynchronous read task over an established socket
		//		callback		Callback to notify operation result
		void AsynchRead (boost::shared_ptr<UDPDataReadDelegate> callback);

		// AsynchWrite
		// Asynchronous write data on the underlying socket
		//		data		Buffer that contains data to write
		//		callback	Callback to notify the completion of sent task
		void AsynchWrite (boost::shared_ptr<vector<unsigned char> > data, boost::shared_ptr<UDPDataWriteDelegate> callback);

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

		// OnBoostAsioConnect
		// Callback to receive Boost Asio notification regarding connect task
		//		code		Error code
	    void OnBoostAsioConnect(const boost::system::error_code& code);

		// OnBoostAsioConnectTimedout
		// Callback to receive Boost Asio notification regarding timedout connect task
		//		code		Error code
		void OnBoostAsioConnectTimedout(const boost::system::error_code& code);

		// OnBoostAsioDataReceived
		// Callback to receive Boost Asio notification regarding timedout connect task
		//		error		Error code
		//		length		Length received data
		void OnBoostAsioDataReceived(const boost::system::error_code& error, long int length);

		// OnBoostAsioDataSent
		// Callback to notify the completion of asynchronous write over the socket
		//		bufferOutput		Output data
		//		length				Quantity of bytes into output data
		//		transferred			Quantity of transferred bytes
		//		error				Error code
		void OnBoostAsioDataSent(boost::shared_ptr<unsigned char> bufferOutput, size_t length, size_t transferred, const boost::system::error_code& error);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		const static long int READ_BUFFER_SIZE = 4096;

		boost::asio::io_service& boostIoService;					// Boost Asio IO service		
		udp::resolver boostUdpResolver;								// Boost Asio Udp resolver
		udp::socket boostUdpSocket;									// Boost Asio Udp socket
		udp::endpoint boostUdpEndpoint;								// Boost Asio Udp endpoint
		boost::asio::deadline_timer boostTimerTaskDeadline;			// Boost Asio deadline timer
		boost::array<char, READ_BUFFER_SIZE> boostUdpInputBuffer;	// Boost Asio Udp input buffer

		boost::shared_ptr<UDPConnectionDelegate> callbackUDPConnection;		// Callback to notify udp connection result
		boost::shared_ptr<UDPDataReadDelegate> callbackUDPDataRead;			// Callback to notify udp received data
		boost::shared_ptr<UDPDataWriteDelegate> callbackUDPDataWrite;		// Callback to notify the completion of udp write data

		boost::recursive_mutex mtxDisconnection;			// Mutex to synchronize Udp disconnection tasks 

		long int counterAsyncReadOperationsInProgress;		// Counter of asynchronous read operations that are in progress
		long int counterAsyncWriteOperationsInProgress;		// Counter of asynchronous write operations that are in progress
	};

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X

#endif



