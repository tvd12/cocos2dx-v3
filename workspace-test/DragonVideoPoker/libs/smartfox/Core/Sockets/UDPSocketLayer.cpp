// ===================================================================
//
// Description		
//		Contains the implementation of an handler for a Udp socket 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "UDPSocketLayer.h"
#include "../../Util/StringFormatter.h"
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
UDPSocketLayer::UDPSocketLayer (boost::shared_ptr<SmartFox> sfs) 
{
	socketNumber = 0;
	connection = boost::shared_ptr<UDPClient>();
	ipAddress = boost::shared_ptr<IPAddress>();
	onError = boost::shared_ptr<OnErrorDelegate>();
	onData = boost::shared_ptr<OnDataDelegate>();

	socketPollSleep = 0;
	isDisconnecting = false;
	connected = false;

	log = boost::shared_ptr<Logger>();
	bitSwarm = boost::shared_ptr<BitSwarmClient>();

	if (sfs != NULL) {
		log = sfs->Log();
		bitSwarm = sfs->BitSwarm();
	}
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
UDPSocketLayer::~UDPSocketLayer()
{
}

// -------------------------------------------------------------------
// LogWarn
// -------------------------------------------------------------------
void UDPSocketLayer::LogWarn(boost::shared_ptr<string> msg) 
{
	if (log == NULL) return;
	
	boost::shared_ptr<std::vector<string> > messages (new std::vector<string>());
	messages->push_back("UDPSocketLayer: ");
	messages->push_back(*msg);

	log->Warn(messages);
}
		
// -------------------------------------------------------------------
// LogError
// -------------------------------------------------------------------
void UDPSocketLayer::LogError(boost::shared_ptr<string> msg) 
{
	if (log == NULL) return;

	boost::shared_ptr<std::vector<string> > messages (new std::vector<string>());
	messages->push_back("UDPSocketLayer: ");
	messages->push_back(*msg);

	log->Error(messages);
}

// -------------------------------------------------------------------
// HandleError
// -------------------------------------------------------------------
void UDPSocketLayer::HandleError(boost::shared_ptr<string> err) 
{
	HandleError(err, SocketErrors_NotSocket);
}

// -------------------------------------------------------------------
// HandleError
// -------------------------------------------------------------------
void UDPSocketLayer::HandleError(boost::shared_ptr<string> err, SocketErrors se) 
{
	boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data (new std::map<string, boost::shared_ptr<void> >());
	data->insert(std::pair<string, boost::shared_ptr<void> >("err", err));
	
	stringstream converterIntToString;
	converterIntToString << (long int)se;
	boost::shared_ptr<string> convertedString (new string(converterIntToString.str()));
	data->insert(std::pair<string, boost::shared_ptr<void> >("se", convertedString));

	boost::shared_ptr<ParameterizedThreadStart> callback (new ParameterizedThreadStart(&UDPSocketLayer::HandleErrorCallback, (unsigned long long)this));
	boost::shared_ptr<ThreadManager> manager = bitSwarm->ThreadManager(); 
	manager->EnqueueCustom(callback, data);
}

// -------------------------------------------------------------------
// HandleErrorCallback
// -------------------------------------------------------------------
void UDPSocketLayer::HandleErrorCallback(unsigned long long context, boost::shared_ptr<void> state) 
{
	// Map context
	UDPSocketLayer* instance = (UDPSocketLayer*)context;

	boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data = (boost::static_pointer_cast<std::map<string, boost::shared_ptr<void> > >)(state);
	boost::shared_ptr<string> err = (boost::static_pointer_cast<string>)((*data)["err"]);

	long int errAsInteger = 0;
	
	boost::shared_ptr<string> format (new string("%d"));
	StringFormatter<long int> ((boost::static_pointer_cast<string>)((*data)["se"]), format, errAsInteger);
		
	SocketErrors se = (SocketErrors)errAsInteger;
			
	// Dont spam errors when disconnecting
	if (!instance->isDisconnecting) 
	{
		instance->CloseConnection();
		instance->LogError(err);
		instance->CallOnError(err, se);
	}
}

// -------------------------------------------------------------------
// WriteSocket
// -------------------------------------------------------------------
void UDPSocketLayer::WriteSocket(boost::shared_ptr<vector<unsigned char> > data)
{
	try
	{
		boost::shared_ptr<UDPDataWriteDelegate> callback (new UDPDataWriteDelegate(&UDPSocketLayer::OnSocketDataSent, (unsigned long long)this));
		connection->AsynchWrite(data, callback);
	}
	catch (...)
	{
		data->clear();

		boost::shared_ptr<string> message (new string("General error writing to socket: "));
		HandleError(message);
	}
}

// -------------------------------------------------------------------
// HandleBinaryData
// -------------------------------------------------------------------
void UDPSocketLayer::HandleBinaryData(boost::shared_ptr<vector<unsigned char> > data) 
{
	CallOnData(data);
}

// -------------------------------------------------------------------
// CallOnError
// -------------------------------------------------------------------
void UDPSocketLayer::CallOnError(boost::shared_ptr<string> msg, SocketErrors se) 
{
	if (onError != NULL) 
	{
		onError->Invoke(msg, se);
	}
}

// -------------------------------------------------------------------
// CallOnData
// -------------------------------------------------------------------
void UDPSocketLayer::CallOnData(boost::shared_ptr<vector<unsigned char> > data) 
{
	if (onData != NULL) 
	{
		boost::shared_ptr<ThreadManager> manager = bitSwarm->ThreadManager(); 
		manager->EnqueueDataCall(onData, data);
	}
}

// -------------------------------------------------------------------
// OnSocketConnection
// -------------------------------------------------------------------
void UDPSocketLayer::OnSocketConnection(unsigned long long context, SocketErrors code)
{
	// Map context
	UDPSocketLayer* instance = (UDPSocketLayer*)context;

	if (code == SocketErrors_Success)
	{
		// Connection established
		instance->connected = true;

		// Schedule an asynchronous read
		boost::shared_ptr<UDPDataReadDelegate> callback (new UDPDataReadDelegate(&UDPSocketLayer::OnSocketDataReceived, context));
		instance->connection->AsynchRead(callback);
	}
	else
	{
		boost::shared_ptr<string> message (new string("Connection error: "));
		instance->HandleError(message, code);	
	}
}


// -------------------------------------------------------------------
// OnSocketDataSent
// -------------------------------------------------------------------
void UDPSocketLayer::OnSocketDataSent(unsigned long long context, SocketErrors code)
{
	// Map context
	UDPSocketLayer* instance = (UDPSocketLayer*)context;

	if (code != SocketErrors_Success) 
	{
		boost::shared_ptr<string> message (new string("Error sending data to remote side over the established connection"));
		instance->HandleError(message, code);	
    }
}

// -------------------------------------------------------------------
// OnSocketDataReceived
// -------------------------------------------------------------------
void UDPSocketLayer::OnSocketDataReceived(unsigned long long context, boost::shared_ptr<vector<unsigned char> > data)
{
	// Map context
	UDPSocketLayer* instance = (UDPSocketLayer*)context;

	if (data->size() < 1) 
	{
		return;
    }

	instance->HandleBinaryData(data);

	// Schedule an asynchronous read
	boost::shared_ptr<UDPDataReadDelegate> callback (new UDPDataReadDelegate(&UDPSocketLayer::OnSocketDataReceived, context));
	instance->connection->AsynchRead(callback);
}

// -------------------------------------------------------------------
// SocketPollSleep
// -------------------------------------------------------------------
void UDPSocketLayer::SocketPollSleep (long int value)
{
	socketPollSleep = value;
}

// -------------------------------------------------------------------
// SocketPollSleep
// -------------------------------------------------------------------
long int UDPSocketLayer::SocketPollSleep()
{
	return socketPollSleep;
}

// ISocketLayer implementation

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void UDPSocketLayer::Connect(boost::shared_ptr<IPAddress> address, unsigned short int port)
{
	socketNumber = port;
	ipAddress = address;
			
	try
	{
		connection = boost::shared_ptr<UDPClient>(new UDPClient(*(bitSwarm->GetBoostService())));
		boost::shared_ptr<UDPConnectionDelegate> callback (new UDPConnectionDelegate(&UDPSocketLayer::OnSocketConnection, (unsigned long long)this));
		connection->Connect(ipAddress, socketNumber, Const_TimeoutConnect, callback);
		boost::thread bt(boost::bind(static_cast<size_t (boost::asio::io_service::*)()>(&boost::asio::io_service::run), bitSwarm->GetBoostService()));
	}
	catch (...)
	{
		boost::shared_ptr<string> message (new string("General exception on connection: "));
		HandleError(message);
	}
}

// -------------------------------------------------------------------
// IsConnected
// -------------------------------------------------------------------
bool UDPSocketLayer::IsConnected()
{
	return connected;
}

// -------------------------------------------------------------------
// RequiresConnection
// -------------------------------------------------------------------
bool UDPSocketLayer::RequiresConnection()
{
	return false;
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void UDPSocketLayer::Disconnect()
{
	isDisconnecting = true;
	CloseConnection();
			
	isDisconnecting = false;
}

// -------------------------------------------------------------------
// CloseConnection
// -------------------------------------------------------------------
void UDPSocketLayer::CloseConnection()
{
	try 
	{
		connection->Shutdown();
	}
	catch (...)
	{
	}

	connected = false;
}

// -------------------------------------------------------------------
// OnConnect
// -------------------------------------------------------------------
boost::shared_ptr<ConnectionDelegate> UDPSocketLayer::OnConnect()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not supported"))); 
}

// -------------------------------------------------------------------
// OnConnect
// -------------------------------------------------------------------
void UDPSocketLayer::OnConnect(boost::shared_ptr<ConnectionDelegate> onConnect)
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not supported"))); 
}

// -------------------------------------------------------------------
// OnDisconnect
// -------------------------------------------------------------------
boost::shared_ptr<ConnectionDelegate> UDPSocketLayer::OnDisconnect()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not supported"))); 
}

// -------------------------------------------------------------------
// OnDisconnect
// -------------------------------------------------------------------
void UDPSocketLayer::OnDisconnect(boost::shared_ptr<ConnectionDelegate> onDisconnect)
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not supported"))); 
}

// -------------------------------------------------------------------
// Write
// -------------------------------------------------------------------
void UDPSocketLayer::Write(boost::shared_ptr<vector<unsigned char> > data)
{
	WriteSocket(data);
}

// -------------------------------------------------------------------
// OnData
// -------------------------------------------------------------------
boost::shared_ptr<OnDataDelegate> UDPSocketLayer::OnData()
{
	return onData;
}

// -------------------------------------------------------------------
// OnData
// -------------------------------------------------------------------
void UDPSocketLayer::OnData(boost::shared_ptr<OnDataDelegate> onData)
{
	this->onData = onData;
}

// -------------------------------------------------------------------
// OnError
// -------------------------------------------------------------------
boost::shared_ptr<OnErrorDelegate> UDPSocketLayer::OnError()
{
	return onError;
}

// -------------------------------------------------------------------
// OnError
// -------------------------------------------------------------------
void UDPSocketLayer::OnError(boost::shared_ptr<OnErrorDelegate> onError)
{
		this->onError = onError;
}

// -------------------------------------------------------------------
// Kill
// -------------------------------------------------------------------
void UDPSocketLayer::Kill()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not supported"))); 
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
