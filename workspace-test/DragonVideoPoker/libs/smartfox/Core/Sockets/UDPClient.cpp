// ===================================================================
//
// Description		
//		Contains the implementation of an handler for a Udp client 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// =================================================================== 
#include "UDPClient.h"

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
#include <boost/detail/interlocked.hpp>			// Boost Asio header
#endif

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
UDPClient::UDPClient (boost::asio::io_service& io_service)
	: boostIoService(io_service),
	  boostUdpResolver(io_service),
      boostUdpSocket(io_service),
	  boostTimerTaskDeadline(io_service)
{
	callbackUDPConnection = boost::shared_ptr<UDPConnectionDelegate>();
	callbackUDPDataRead = boost::shared_ptr<UDPDataReadDelegate>();
	callbackUDPDataWrite = boost::shared_ptr<UDPDataWriteDelegate>();
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
UDPClient::~UDPClient()
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
void UDPClient::Connect (boost::shared_ptr<IPAddress> ipAddress, unsigned short int ipPort, long int timeout, boost::shared_ptr<UDPConnectionDelegate> callback)
{
	// Preserve callback that will be used to notify udp connection result
	callbackUDPConnection = callback;

	// Start deadline timer for udp connection task
    boostTimerTaskDeadline.expires_from_now(boost::posix_time::seconds(timeout));
	boostTimerTaskDeadline.async_wait(boost::bind(&UDPClient::OnBoostAsioConnectTimedout, this, boost::asio::placeholders::error));

	// Attempt to establish a udp connection
	char buffer[512];
	sprintf (buffer, "%ld", ipPort);
	boost::shared_ptr<string> ipPortAsString (new string(buffer));

    udp::resolver::query query(udp::v4(), *(ipAddress->Address()), *ipPortAsString); 
    udp::resolver::iterator itr = boostUdpResolver.resolve(query);
    boostUdpEndpoint = *itr; 

	string endpointAddress = boostUdpEndpoint.address().to_string();
	unsigned short int endpointPort = boostUdpEndpoint.port();

	boostUdpSocket.async_connect(boostUdpEndpoint,  boost::bind(&UDPClient::OnBoostAsioConnect, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// Shutdown
// -------------------------------------------------------------------
void UDPClient::Shutdown()
{
	// Cancel all asynchronous operations associated with the socket
    boostUdpSocket.close();
    boostIoService.stop();
}

// -------------------------------------------------------------------
// OnBoostAsioConnect
// -------------------------------------------------------------------
void UDPClient::OnBoostAsioConnect(const boost::system::error_code& code)
{
	// Stop deadline timer for udp connection task
	boostTimerTaskDeadline.cancel();

	// Notify the establishment of the udp connection
	callbackUDPConnection->Invoke((SocketErrors)(code.value()));
}

// -------------------------------------------------------------------
// OnBoostAsioConnectTimedout
// -------------------------------------------------------------------
void UDPClient::OnBoostAsioConnectTimedout(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Deadline timer for udp connection task has been stopped
		// Nothing to do
		return;
	}

	// Deadline timer for udp connection task is expired

	// Notify the establishment of the tco connection
	callbackUDPConnection->Invoke((SocketErrors)(code.value()));
}

// -------------------------------------------------------------------
// AsynchRead
// -------------------------------------------------------------------
void UDPClient::AsynchRead (boost::shared_ptr<UDPDataReadDelegate> callback)
{
	// Preserve callback that will be used to notify udp received data
	
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackUDPDataRead = callback;

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Schedule asyncronous read
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncReadOperationsInProgress);
	#else
		counterAsyncReadOperationsInProgress++;
	#endif
	boostUdpSocket.async_receive_from(boost::asio::buffer(boostUdpInputBuffer), boostUdpEndpoint, boost::bind(&UDPClient::OnBoostAsioDataReceived, this, _1, _2));
}

// -------------------------------------------------------------------
// AsynchWrite
// -------------------------------------------------------------------
void UDPClient::AsynchWrite (boost::shared_ptr<vector<unsigned char> > data, boost::shared_ptr<UDPDataWriteDelegate> callback)
{
	// Preserve callback that will be used to notify the completion of udp write data

	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	callbackUDPDataWrite = callback;

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

	// Schedule an asynchronous write to dispatch outgoing data over Udp socket
	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )
		BOOST_INTERLOCKED_INCREMENT(&counterAsyncWriteOperationsInProgress);
	#else
		counterAsyncWriteOperationsInProgress++;	
	#endif
	boostUdpSocket.async_send_to(boost::asio::buffer((void*)bufferOutput.get(), (size_t)data->size()), boostUdpEndpoint, boost::bind(&UDPClient::OnBoostAsioDataSent, this, bufferOutput, data->size(), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// OnBoostAsioDataSent
// -------------------------------------------------------------------
void UDPClient::OnBoostAsioDataSent(boost::shared_ptr<unsigned char> bufferOutput, size_t length, size_t transferred, const boost::system::error_code& error)
{
	// Notify operation status
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackUDPDataWrite != NULL)
	{
		callbackUDPDataWrite->Invoke((SocketErrors)error.value());
	}

	boost::lock_guard<boost::recursive_mutex> unlock(mtxDisconnection);

	// Check if all output data have been transmitted
	if (transferred != length)
	{
		// Not all data have been transmitted

		// Allocate a smart pointer to a vector where take place outgoing data
		boost::shared_ptr<unsigned char> bufferNextOutput(new unsigned char[length - transferred]);
		memcpy ((void*)(bufferNextOutput.get()), bufferOutput.get() + transferred, length - transferred);

		// Schedule an asynchronous write to dispatch outgoing data over Udp socket
		boostUdpSocket.async_send_to(boost::asio::buffer((void*)bufferNextOutput.get(), (length - transferred)), boostUdpEndpoint, boost::bind(&UDPClient::OnBoostAsioDataSent, this, bufferNextOutput, (length - transferred), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));

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
void UDPClient::OnBoostAsioDataReceived(const boost::system::error_code& error, long int length)
{
	boost::shared_ptr<vector<unsigned char> > data;
	if (length > 0)
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
		data->assign((unsigned char*)(boostUdpInputBuffer.data()), (unsigned char*)(boostUdpInputBuffer.data() + length));
	}
	else
	{
		data = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	}

	// Notify received data
	// Note that data length could be 0 when socket closure has been detected
	 
	boost::lock_guard<boost::recursive_mutex> lock(mtxDisconnection);

	if (callbackUDPDataRead != NULL)
	{
		callbackUDPDataRead->Invoke(data);
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
