// ===================================================================
//
// Description		
//		Contains the implementation of an handler for a Tcp client 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// =================================================================== 
#include "TCPClient.h"

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
#include <boost/detail/interlocked.hpp>			// Boost Asio header
#endif

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
TCPClient::TCPClient (boost::asio::io_service& io_service)
	: boostIoService(io_service),
	  boostTcpResolver(io_service),
      boostTcpSocket(io_service),
	  boostTimerTaskDeadline(io_service)
{
	callbackTCPConnection = boost::shared_ptr<TCPConnectionDelegate>();
	callbackTCPDataRead = boost::shared_ptr<TCPDataReadDelegate>();
	callbackTCPDataWrite = boost::shared_ptr<TCPDataWriteDelegate>();
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_EXCHANGE(&counterAsyncReadOperationsInProgress, 0);
		BOOST_INTERLOCKED_EXCHANGE(&counterAsyncWriteOperationsInProgress, 0);
	#else
		counterAsyncReadOperationsInProgress = 0;
		counterAsyncWriteOperationsInProgress = 0;
	#endif
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
TCPClient::~TCPClient()
{
	// Wait for completion of asynchronous operations 
	long int counterInProgressAsyncRead = counterAsyncReadOperationsInProgress = 0;
	long int counterInProgressAsyncWrite = counterAsyncWriteOperationsInProgress = 0;
	do
	{
		counterInProgressAsyncRead = counterAsyncReadOperationsInProgress;
		counterInProgressAsyncWrite = counterAsyncWriteOperationsInProgress;
	} while ((counterInProgressAsyncRead > 0) || (counterInProgressAsyncWrite > 0));
	//MAX while ((counterAsyncReadOperationsInProgress > 0) || (counterAsyncWriteOperationsInProgress > 0));
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void TCPClient::Connect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort, long int timeout, boost::shared_ptr<TCPConnectionDelegate> callback)
{
	// Preserve callback that will be used to notify tcp connection result
	callbackTCPConnection = callback;

	// Start deadline timer for tcp connection task
    boostTimerTaskDeadline.expires_from_now(boost::posix_time::seconds(timeout));
	boostTimerTaskDeadline.async_wait(boost::bind(&TCPClient::OnBoostAsioConnectTimedout, this, boost::asio::placeholders::error));

	// Attempt to establish a tcp connection
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(*(ipAddress->Address())), ipPort);
	boostTcpSocket.async_connect(endpoint,  boost::bind(&TCPClient::OnBoostAsioConnect, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void TCPClient::SynchConnect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort)
{
	boost::system::error_code error;

	// Attempt to establish a tcp connection
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(*(ipAddress->Address())), ipPort);
	boostTcpSocket.connect(endpoint, error);
}

// -------------------------------------------------------------------
// Shutdown
// -------------------------------------------------------------------
void TCPClient::Shutdown()
{
	// Cancel all asynchronous operations associated with the socket
    boostTcpSocket.close();
    boostIoService.stop();
}

// -------------------------------------------------------------------
// OnBoostAsioConnect
// -------------------------------------------------------------------
void TCPClient::OnBoostAsioConnect(const boost::system::error_code& code)
{
	// Stop deadline timer for tcp connection task
	boostTimerTaskDeadline.cancel();

	// Notify the establishment of the tcp connection
	callbackTCPConnection->Invoke((SocketErrors)(code.value()));
}

// -------------------------------------------------------------------
// OnBoostAsioConnectTimedout
// -------------------------------------------------------------------
void TCPClient::OnBoostAsioConnectTimedout(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Deadline timer for tcp connection task has been stopped
		// Nothing to do
		return;
	}

	// Deadline timer for tcp connection task is expired

	// Notify the establishment of the tco connection
	callbackTCPConnection->Invoke((SocketErrors)(code.value()));
}

// -------------------------------------------------------------------
// AsynchRead
// -------------------------------------------------------------------
void TCPClient::AsynchRead (boost::shared_ptr<TCPDataReadDelegate> callback)
{
	// Preserve callback that will be used to notify tcp received data
	
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackTCPDataRead = callback;

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Schedule asyncronous read
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncReadOperationsInProgress);
	#else
		counterAsyncReadOperationsInProgress++;
	#endif
	boostTcpSocket.async_read_some(boost::asio::buffer(boostTcpInputBuffer), boost::bind(&TCPClient::OnBoostAsioDataReceived, this, _1, _2));
}

// -------------------------------------------------------------------
// SynchRead
// -------------------------------------------------------------------
boost::shared_ptr<vector<unsigned char> > TCPClient::SynchRead ()
{
	size_t length = 0;
	boost::system::error_code error;
	
	length = boostTcpSocket.read_some(boost::asio::buffer(boostTcpInputBuffer), error);

	if (error == boost::asio::error::eof)
	{
		return boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());			// Connection closed cleanly by peer
	}
	else if (error)
	{
		throw boost::system::system_error(error);	// Some other error.
	}

	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>());
	if (length > 0)
	{
		data->assign((unsigned char*)(boostTcpInputBuffer.data()), (unsigned char*)(boostTcpInputBuffer.data() + length));
	}

	return data;
}

// -------------------------------------------------------------------
// AsynchWrite
// -------------------------------------------------------------------
void TCPClient::AsynchWrite (boost::shared_ptr<vector<unsigned char> > data, boost::shared_ptr<TCPDataWriteDelegate> callback)
{
	// Preserve callback that will be used to notify the completion of tcp write data

	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackTCPDataWrite = callback;

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Allocate a smart pointer to a vector where take place outgoing data
	boost::shared_ptr<unsigned char> bufferOutput(new unsigned char[data->size()]);

	unsigned char* writerBufferOutput = bufferOutput.get();
	long int offsetBufferOutput = 0;
	vector<unsigned char>::iterator iterator;
	for(iterator = data->begin(); iterator != data->end(); ++iterator)
	{
		*(writerBufferOutput + offsetBufferOutput) = (*iterator);
		offsetBufferOutput++;
	}
	//memcpy ((void*)(bufferOutput.get()), data->data(), data->size());

	// Schedule an asynchronous write to dispatch outgoing data over Tcp socket
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncWriteOperationsInProgress);
	#else
		counterAsyncWriteOperationsInProgress++;	
	#endif
	boostTcpSocket.async_write_some(boost::asio::buffer((void*)bufferOutput.get(), (size_t)data->size()), boost::bind(&TCPClient::OnBoostAsioDataSent, this, bufferOutput, data->size(), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// SynchWrite
// -------------------------------------------------------------------
void TCPClient::SynchWrite (boost::shared_ptr<vector<unsigned char> > data)
{
	// Allocate a smart pointer to a vector where take place outgoing data
	boost::shared_ptr<unsigned char> bufferOutput(new unsigned char[data->size()]);

	unsigned char* writerBufferOutput = bufferOutput.get();
	long int offsetBufferOutput = 0;
	vector<unsigned char>::iterator iterator;
	for(iterator = data->begin(); iterator != data->end(); ++iterator)
	{
		*(writerBufferOutput + offsetBufferOutput) = (*iterator);
		offsetBufferOutput++;
	}

	// Dispatch outgoing data over Tcp socket
	boostTcpSocket.write_some (boost::asio::buffer((void*)bufferOutput.get(), (size_t)data->size()));
}

// -------------------------------------------------------------------
// OnBoostAsioDataSent
// -------------------------------------------------------------------
void TCPClient::OnBoostAsioDataSent(boost::shared_ptr<unsigned char> bufferOutput, size_t length, size_t transferred, const boost::system::error_code& error)
{
	// Notify operation status
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackTCPDataWrite != NULL)
	{
		callbackTCPDataWrite->Invoke((SocketErrors)error.value());
	}

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Check if all output data have been transmitted
	if (transferred != length)
	{
		// Not all data have been transmitted

		// Allocate a smart pointer to a vector where take place outgoing data
		boost::shared_ptr<unsigned char> bufferNextOutput(new unsigned char[length - transferred]);
		memcpy ((void*)(bufferNextOutput.get()), bufferOutput.get() + transferred, length - transferred);

		// Schedule an asynchronous write to dispatch outgoing data over Tcp socket
		boostTcpSocket.async_write_some(boost::asio::buffer((void*)bufferNextOutput.get(), (length - transferred)), boost::bind(&TCPClient::OnBoostAsioDataSent, this, bufferNextOutput, (length - transferred), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));

		return;
	}

	// Decrease counter of asynchronous write that are in progress
	if (counterAsyncWriteOperationsInProgress > 0)
	{
		#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
			BOOST_INTERLOCKED_DECREMENT(&counterAsyncWriteOperationsInProgress);
		#else
			counterAsyncWriteOperationsInProgress--;
		#endif
	}
}

// -------------------------------------------------------------------
// OnBoostAsioDataReceived
// -------------------------------------------------------------------
void TCPClient::OnBoostAsioDataReceived(const boost::system::error_code& error, long int length)
{
	boost::shared_ptr<vector<unsigned char> > data;
	if (length > 0)
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
		data->assign((unsigned char*)(boostTcpInputBuffer.data()), (unsigned char*)(boostTcpInputBuffer.data() + length));
	}
	else
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	}

	// Notify received data
	// Note that data length could be 0 when socket closure has been detected
	 
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackTCPDataRead != NULL)
	{
		callbackTCPDataRead->Invoke(data);
	}

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Decrease counter of asynchronous read that are in progress
	if (counterAsyncReadOperationsInProgress > 0)
	{
		#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
			BOOST_INTERLOCKED_DECREMENT(&counterAsyncReadOperationsInProgress);
		#else
			counterAsyncReadOperationsInProgress--;
		#endif
	}
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
