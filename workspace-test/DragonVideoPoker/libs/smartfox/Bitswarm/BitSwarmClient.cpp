// ===================================================================
//
// Description		
//		Contains the implementation of BitSwarmClient
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BitSwarmClient.h"
#include "../Controllers/ExtensionController.h"
#include "../Controllers/SystemController.h"
#include "./BBox/BBEvent.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmClient::BitSwarmClient(boost::shared_ptr<boost::asio::io_service> service) 
{
	sfs = boost::shared_ptr<SmartFox>();
	socket = boost::shared_ptr<ISocketLayer>();
	controllers.clear();
	compressionThreshold = 2000000;
	maxMessageSize = 10000;
	lastIpAddress = boost::shared_ptr<string>(new string());
	lastTcpPort = 0;
	reconnectionSeconds = 0;
	attemptingReconnection = false;
	log = boost::shared_ptr<Logger>();
	//sysController = NULL;
	//extController = NULL;
	udpManager = boost::shared_ptr<IUDPManager>();
	controllersInited = false;
	dispatcher = boost::shared_ptr<EventDispatcher>();
	bbClient = boost::shared_ptr<BBClient>();
	useBlueBox = false;
	bbConnected = false;
	threadManager = boost::shared_ptr<Sfs2X::Core::ThreadManager>(new Sfs2X::Core::ThreadManager());
	ioHandler = boost::shared_ptr<Sfs2X::Bitswarm::IoHandler>();
	manualDisconnection = false;
	retryTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*service));
}
		
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmClient::BitSwarmClient(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<boost::asio::io_service> service) 
{
	this->sfs = sfs;
	log = sfs->Log();
	socket = boost::shared_ptr<ISocketLayer>();
	controllers.clear();
	compressionThreshold = 2000000;
	maxMessageSize = 10000;
	lastIpAddress = boost::shared_ptr<string>(new string());
	lastTcpPort = 0;
	reconnectionSeconds = 0;
	attemptingReconnection = false;
	//sysController = NULL;
	//extController = NULL;
	udpManager = boost::shared_ptr<IUDPManager>();
	controllersInited = false;
	dispatcher = boost::shared_ptr<EventDispatcher>();
	bbClient = boost::shared_ptr<BBClient>();
	useBlueBox = false;
	bbConnected = false;
	connectionMode = boost::shared_ptr<string>();
	threadManager = boost::shared_ptr<Sfs2X::Core::ThreadManager>(new Sfs2X::Core::ThreadManager());
	ioHandler = boost::shared_ptr<Sfs2X::Bitswarm::IoHandler>();
	manualDisconnection = false;
	retryTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*service));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BitSwarmClient::~BitSwarmClient()
{
	controllers.clear();
}

// -------------------------------------------------------------------
// GetBoostService
// -------------------------------------------------------------------
boost::shared_ptr<boost::asio::io_service> BitSwarmClient::GetBoostService()
{
	return sfs->GetBoostService();
}

// -------------------------------------------------------------------
// ThreadManager
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Core::ThreadManager> BitSwarmClient::ThreadManager()
{
	return threadManager;
}

// -------------------------------------------------------------------
// ConnectionMode
// -------------------------------------------------------------------
boost::shared_ptr<string> BitSwarmClient::ConnectionMode()
{
	return connectionMode;
}

// -------------------------------------------------------------------
// UseBlueBox
// -------------------------------------------------------------------
bool BitSwarmClient::UseBlueBox()
{
	return useBlueBox;
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
bool BitSwarmClient::Debug()
{
	if (sfs == NULL)
	{
		return true;
	}
	return sfs->Debug();
}

// -------------------------------------------------------------------
// Sfs
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> BitSwarmClient::Sfs()
{
	return sfs;
}

// -------------------------------------------------------------------
// Connected
// -------------------------------------------------------------------
bool BitSwarmClient::Connected()
{
	if (useBlueBox)
	{
		return bbConnected;
	}

	if (socket == NULL)
	{
		return false;
	}
	else
	{
		return socket->IsConnected();
	}
}

// -------------------------------------------------------------------
// IoHandler
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Bitswarm::IoHandler> BitSwarmClient::IoHandler()
{
	return ioHandler;
}

// -------------------------------------------------------------------
// IoHandler
// -------------------------------------------------------------------
void BitSwarmClient::IoHandler(boost::shared_ptr<Sfs2X::Bitswarm::IoHandler> value)
{
	if (value == NULL)
	{
		boost::shared_ptr<string> message (new string("IOHandler is already set!"));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}

	ioHandler = value;
}

// -------------------------------------------------------------------
// CompressionThreshold
// -------------------------------------------------------------------
long int BitSwarmClient::CompressionThreshold()
{
	return compressionThreshold;
}

// -------------------------------------------------------------------
// CompressionThreshold
// -------------------------------------------------------------------
void BitSwarmClient::CompressionThreshold(long int value)
{
	/*
	* Avoid compressing data whose size is < 100 bytes
	* Ideal default value should be 300 bytes or more...
	*/

	if (value > 100) 
	{
		compressionThreshold = value;
	}
	else 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Compression threshold cannot be < 100 bytes."))); 
		//throw exception("Compression threshold cannot be < 100 bytes.");
	}		
}

// -------------------------------------------------------------------
// MaxMessageSize
// -------------------------------------------------------------------
long int BitSwarmClient::MaxMessageSize()
{
	return maxMessageSize;
}

// -------------------------------------------------------------------
// MaxMessageSize
// -------------------------------------------------------------------
void BitSwarmClient::MaxMessageSize (long int value)
{
	maxMessageSize = value;
}
/*
// -------------------------------------------------------------------
// SysController
// -------------------------------------------------------------------
Sfs2X::Controllers::SystemController* BitSwarmClient::SysController()
{
	return sysController;
}

// -------------------------------------------------------------------
// ExtController
// -------------------------------------------------------------------
Sfs2X::Controllers::ExtensionController* BitSwarmClient::ExtController()
{
	return extController;
}
*/
// -------------------------------------------------------------------
// ExtController
// -------------------------------------------------------------------
boost::shared_ptr<ISocketLayer> BitSwarmClient::Socket()
{
	return socket;
}

// -------------------------------------------------------------------
// HttpClient
// -------------------------------------------------------------------
boost::shared_ptr<BBClient> BitSwarmClient::HttpClient()
{
	return bbClient;
}

// -------------------------------------------------------------------
// IsReconnecting
// -------------------------------------------------------------------
bool BitSwarmClient::IsReconnecting()
{
	return attemptingReconnection;
}

// -------------------------------------------------------------------
// IsReconnecting
// -------------------------------------------------------------------
void BitSwarmClient::IsReconnecting(bool value)
{
	attemptingReconnection = value;
}

// -------------------------------------------------------------------
// ReconnectionSeconds
// -------------------------------------------------------------------
long int BitSwarmClient::ReconnectionSeconds()
{
	if (reconnectionSeconds < 0) 
	{
		return 0;
	}
	
	return reconnectionSeconds;
}

// -------------------------------------------------------------------
// ReconnectionSeconds
// -------------------------------------------------------------------
void BitSwarmClient::ReconnectionSeconds(long int value)
{
	reconnectionSeconds = value;
}

// -------------------------------------------------------------------
// Dispatcher
// -------------------------------------------------------------------
boost::shared_ptr<EventDispatcher> BitSwarmClient::Dispatcher()
{
	return dispatcher;
}

// -------------------------------------------------------------------
// Dispatcher
// -------------------------------------------------------------------
void BitSwarmClient::Dispatcher(boost::shared_ptr<EventDispatcher> value)
{
	dispatcher= value;
}

// -------------------------------------------------------------------
// Log
// -------------------------------------------------------------------
boost::shared_ptr<Logger> BitSwarmClient::Log()
{
	if (sfs == NULL) 
	{
		// Returning dummy logger for tests
		return boost::shared_ptr<Logger>(new Logger(boost::shared_ptr<SmartFox>()));
	}
				
	return sfs->Log();
}

// -------------------------------------------------------------------
// ForceBlueBox
// -------------------------------------------------------------------
void BitSwarmClient::ForceBlueBox(bool val)
{
	if (!bbConnected) 
	{
		useBlueBox = val;
	} 
	else 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("You can't change the BlueBox mode while the connection is running"))); 
		//throw exception("You can't change the BlueBox mode while the connection is running");
	}
}

// -------------------------------------------------------------------
// EnableBlueBoxDebug
// -------------------------------------------------------------------
void BitSwarmClient::EnableBlueBoxDebug(bool val)
{
	bbClient->IsDebug(val);
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void BitSwarmClient::Init()
{
	if (dispatcher == NULL) 
	{
		dispatcher = boost::shared_ptr<EventDispatcher>(new EventDispatcher(shared_from_this()));
	}

	// Do it once
	if (!controllersInited)	
	{
		InitControllers();
		controllersInited = true;
	}


	if (socket != NULL) return; // Don't init the socket layer if it's already initialized
		
	socket = boost::shared_ptr<ISocketLayer>(new TCPSocketLayer(shared_from_this()));

	boost::shared_ptr<ConnectionDelegate> delegateConnection (new ConnectionDelegate(&BitSwarmClient::OnSocketConnect, (unsigned long long)this));
	socket->OnConnect(delegateConnection);

	boost::shared_ptr<ConnectionDelegate> delegateDisconnection (new ConnectionDelegate(&BitSwarmClient::OnSocketClose, (unsigned long long)this));
	socket->OnDisconnect(delegateDisconnection);

	boost::shared_ptr<OnDataDelegate> delegateOnData (new OnDataDelegate(&BitSwarmClient::OnSocketData, (unsigned long long)this));
	socket->OnData(delegateOnData);

	boost::shared_ptr<OnErrorDelegate> delegateOnError (new OnErrorDelegate(&BitSwarmClient::OnSocketError, (unsigned long long)this));
	socket->OnError(delegateOnError); 

	bbClient = boost::shared_ptr<BBClient>(new BBClient(shared_from_this()));
	bbClient->Initialize();

	bbClient->AddEventListener(BBEvent::CONNECT, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(&BitSwarmClient::OnBBConnect, (unsigned long long)this)));
	bbClient->AddEventListener(BBEvent::DATA, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(&BitSwarmClient::OnBBData, (unsigned long long)this)));
	bbClient->AddEventListener(BBEvent::DISCONNECT, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(&BitSwarmClient::OnBBDisconnect, (unsigned long long)this)));
	bbClient->AddEventListener(BBEvent::IO_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(&BitSwarmClient::OnBBError, (unsigned long long)this)));
	bbClient->AddEventListener(BBEvent::SECURITY_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(&BitSwarmClient::OnBBError, (unsigned long long)this)));

	threadManager->Start();
}

// -------------------------------------------------------------------
// Destroy
// -------------------------------------------------------------------
void BitSwarmClient::Destroy()
{
	socket->OnConnect(boost::shared_ptr<ConnectionDelegate>());
	socket->OnDisconnect(boost::shared_ptr<ConnectionDelegate>());
	socket->OnData(boost::shared_ptr<OnDataDelegate>());
	socket->OnError(boost::shared_ptr<OnErrorDelegate>());
						
	if (socket->IsConnected()) 
	{
		socket->Disconnect();
	}
									
	socket = boost::shared_ptr<ISocketLayer>();
}

// -------------------------------------------------------------------
// GetController
// -------------------------------------------------------------------
boost::shared_ptr<IController> BitSwarmClient::GetController(long int id)
{
	return controllers[id];
}

// -------------------------------------------------------------------
// ConnectionIp
// -------------------------------------------------------------------
boost::shared_ptr<string> BitSwarmClient::ConnectionIp()
{
	if (!Connected())
	{
		return boost::shared_ptr<string>(new string("Not Connected"));
	}
	else
	{
		return boost::shared_ptr<string>(new string(*lastIpAddress));
	}
}

// -------------------------------------------------------------------
// ConnectionPort
// -------------------------------------------------------------------
long int BitSwarmClient::ConnectionPort()
{
	if (!Connected())
	{
		return -1;
	}
	else
	{
		return lastTcpPort;
	}
}


// -------------------------------------------------------------------
// AddController
// -------------------------------------------------------------------
void BitSwarmClient::AddController(long int id, boost::shared_ptr<IController> controller)
{
	if (controller == NULL) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Controller is null, it can't be added."))); 
		//throw exception("Controller is null, it can't be added.");
	}		

	std::map<long int, boost::shared_ptr<IController> >::iterator iterator = controllers.find(id);
			
	if (iterator != controllers.end()) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("A controller with id:  %d already exists! Controller can't be added:"));
		StringFormatter<long int> (err, format, id);

		boost::throw_exception(boost::enable_error_info (std::runtime_error(err->c_str()))); 

		//throw exception(err.c_str());
	}
				
	controllers[id] = controller;
}

/*
// -------------------------------------------------------------------
// AddCustomController
// -------------------------------------------------------------------
void BitSwarmClient::AddCustomController(long int id, Type controllerType)
{
	IController controller = Activator.CreateInstance(controllerType) as IController;
	AddController(id, controller);
}
*/
// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void BitSwarmClient::Connect()
{
	boost::shared_ptr<string> address (new string("127.0.0.1"));
	Connect(address, 9339);
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void BitSwarmClient::Connect(boost::shared_ptr<string> ip, unsigned short int port)
{
	lastIpAddress = ip;
	lastTcpPort = port;

	threadManager->Start();

	if (useBlueBox) 
	{
		connectionMode = ConnectionModes::HTTP;
		bbClient->PollSpeed((sfs->Config() != NULL) ? sfs->Config()->BlueBoxPollingRate() : 750);
		bbClient->Connect(ip, port);
	} 
	else 
	{
		boost::shared_ptr<IPAddress> address (new IPAddress(IPAddress::IPADDRESSTYPE_IPV4, *lastIpAddress));
		socket->Connect(address, lastTcpPort);	
		connectionMode = ConnectionModes::SOCKET;
	}
}

// -------------------------------------------------------------------
// Send
// -------------------------------------------------------------------
void BitSwarmClient::Send(boost::shared_ptr<IMessage> message)
{
	ioHandler->Codec()->OnPacketWrite(message);
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void BitSwarmClient::Disconnect()
{
	Disconnect(boost::shared_ptr<string>());
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void BitSwarmClient::Disconnect(boost::shared_ptr<string> reason)
{
	// Using dirty flag for manual disconnection
	if ((reason != NULL) && (*reason == (*ClientDisconnectionReason::MANUAL))) 
	{
		manualDisconnection = true;
	}
									
	if (useBlueBox) 
	{
		bbClient->Close();
	}
	else 
	{
		socket->Disconnect();
		if (udpManager != NULL) 
		{
			udpManager->Disconnect();
		}
	}
}

// -------------------------------------------------------------------
// InitControllers
// -------------------------------------------------------------------
void BitSwarmClient::InitControllers()
{
	boost::shared_ptr<Sfs2X::Controllers::SystemController> sysController (new Sfs2X::Controllers::SystemController(shared_from_this()));
	sysController->Initialize();

	boost::shared_ptr<Sfs2X::Controllers::ExtensionController> extController (new Sfs2X::Controllers::ExtensionController(shared_from_this()));

	AddController(0, sysController);
	AddController(1, extController);
}

// Socket handlers

// -------------------------------------------------------------------
// KillConnection
// -------------------------------------------------------------------
void BitSwarmClient::KillConnection()
{
	socket->Kill();
	BitSwarmClient::OnSocketClose((unsigned long long)this);
}

// -------------------------------------------------------------------
// OnSocketConnect
// -------------------------------------------------------------------
void BitSwarmClient::OnSocketConnect(unsigned long long context)
{
	BitSwarmClient* instance = (BitSwarmClient*)context;
	boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::CONNECT));
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<bool> valueSuccess (new bool());
	*valueSuccess = true;
	args->insert(pair<string, boost::shared_ptr<void> >("success", valueSuccess));
	boost::shared_ptr<bool> valueIsReconnection (new bool());
	*valueIsReconnection = instance->attemptingReconnection;					// 2nd argument not publicly documented, used internally
	args->insert(pair<string, boost::shared_ptr<void> >("isReconnection", valueIsReconnection));	
	evt->Params(args);
	instance->DispatchEvent(evt);
}

// -------------------------------------------------------------------
// OnSocketClose
// -------------------------------------------------------------------
void BitSwarmClient::OnSocketClose(unsigned long long context)
{
	BitSwarmClient* instance = (BitSwarmClient*)context;
	bool isRegularDisconnection = instance->sfs==NULL || (!instance->attemptingReconnection && instance->sfs->GetReconnectionSeconds() == 0);
	//bool isManualDisconnection = (evt!=null) && (string)evt.Params["reason"] == ClientDisconnectionReason.MANUAL;
	bool isManualDisconnection = instance->manualDisconnection;

	/*
	* There are three cases in which we need to acknowledge the disconnection
	* 
	* 	1. 	We're in the middle of Reconnection Attempt:
	*		In this case a disconnection means that there's no way we can reconnect, so end of story.
	*
	*	2.	It is Regular Disconnection (no reconnection feature available)
	*
	*	3.	It is a voluntary (Manual) disconnection, initiated on the client
	*
	*/
	if (instance->attemptingReconnection || isRegularDisconnection || isManualDisconnection) {
		// Reset UDP Manager
		if (instance->udpManager!=NULL) {
			instance->udpManager->Reset();
		}

					
		/*
		* Disconnection at socket level
		* Dispatching the event here only in the case of manual disconnection. If it's disconnection from server 
		* This will be dispatched from the server disconnection event handler
		*/

		if (isManualDisconnection) {
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());
			args->insert(pair<string, boost::shared_ptr<void> >("reason", (boost::static_pointer_cast<void>)(ClientDisconnectionReason::MANUAL)));

			boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::DISCONNECT, args));
			instance->sfs->DispatchEvent(evt);

			// Don't resetting manualDisconnection flag here as there will be OnSocketError event
		}

		return;
	}

	char buffer[512];
	sprintf (buffer, "Attempting reconnection in %ld sec", instance->ReconnectionSeconds());
	string logMessage = buffer;

	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	logMessages->push_back(logMessage);
	instance->log->Debug(logMessages);

	//--- Attempt a reconnection to the server --------------------------------------------------------

	/*
	* If we aren't in any of the above three cases then it's time to attempt a
	* reconnection to the server.
	*/
	instance->attemptingReconnection = true;

	// Fire event and retry
	boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::RECONNECTION_TRY));
	instance->sfs->DispatchEvent(evt);

	// Retry connection: pause n seconds and retry
	instance->RetryConnection(instance->ReconnectionSeconds()/**1000*/);
}

// -------------------------------------------------------------------
// StopReconnection
// -------------------------------------------------------------------
void BitSwarmClient::StopReconnection() 
{
	attemptingReconnection = false;
	//firstReconnAttempt = DateTime.MinValue;
			
	if (socket->IsConnected()) 
	{
		socket->Disconnect();
	}
		
	ExecuteDisconnection();
}

// -------------------------------------------------------------------
// ExecuteDisconnection
// -------------------------------------------------------------------
void BitSwarmClient::ExecuteDisconnection() 
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());
	args->insert(pair<string, boost::shared_ptr<void> >("reason", (boost::static_pointer_cast<void>)(ClientDisconnectionReason::UNKNOWN)));

	boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::DISCONNECT, args));
	sfs->DispatchEvent(evt);

	/*
	 * --==|| Clear resources ||==--
	 * 
	 * Without this all thread will remain active even if the API are done with the Session
	 * 
	 * @since 1.0.8
	 * @by Lapo
	 */
	ReleaseResources ();
}

// -------------------------------------------------------------------
// ReleaseResources
// -------------------------------------------------------------------
void BitSwarmClient::ReleaseResources()
{
	//threadManager->Stop();

	if (udpManager != NULL && udpManager->Inited())
		udpManager->Disconnect ();
}

// -------------------------------------------------------------------
// RetryConnection
// -------------------------------------------------------------------
void BitSwarmClient::RetryConnection(long int timeout)
{
	// Start deadline timer for tcp connection task
    retryTimer->expires_from_now(boost::posix_time::seconds(timeout));
	retryTimer->async_wait(boost::bind(&BitSwarmClient::OnRetryConnectionEvent, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// OnRetryConnectionEvent
// -------------------------------------------------------------------
void BitSwarmClient::OnRetryConnectionEvent(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Timer has been stopped
		// Nothing to do
		return;
	}

	boost::shared_ptr<IPAddress> address (new IPAddress(IPAddress::IPADDRESSTYPE_IPV4, *lastIpAddress));
	socket->Connect(address, lastTcpPort);	
}

// -------------------------------------------------------------------
// OnSocketData
// -------------------------------------------------------------------
void BitSwarmClient::OnSocketData(unsigned long long context, boost::shared_ptr<vector<unsigned char> > data)
{
	BitSwarmClient* instance = (BitSwarmClient*)context;

	/*
	* Catches possible data errors... we have seen a few
	* http://www.smartfoxserver.com/forums/viewtopic.php?t=10314
	*/
	try 
	{
		boost::shared_ptr<ByteArray> buffer (new ByteArray(data));
		instance->ioHandler->OnDataRead(buffer);
	}
	catch (exception e) 
	{
		boost::shared_ptr<string> message (new string(e.what()));

		char buffer[512];
		sprintf (buffer, "## SocketDataError: %s", message->c_str());
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		instance->log->Error(logMessages);

		boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::DATA_ERROR));
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());

		args->insert(pair<string, boost::shared_ptr<void> >("message", message));
		evt->Params(args);
		instance->DispatchEvent(evt);
	}
}

// -------------------------------------------------------------------
// OnSocketError
// -------------------------------------------------------------------
void BitSwarmClient::OnSocketError(unsigned long long context, boost::shared_ptr<string> message, SocketErrors se)
{
	BitSwarmClient* instance = (BitSwarmClient*)context;

	boost::shared_ptr<BitSwarmEvent> evt = boost::shared_ptr<BitSwarmEvent>();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());

	char buffer[1024];
	if (se != SocketErrors_NotSocket)
	{
		sprintf (buffer, "%s [%ld]", message->c_str(), se);
	}
	else
	{
		sprintf (buffer, "%s", message->c_str());
	}

	boost::shared_ptr<string> messageFormatted (new string(buffer));

	data->insert(pair<string, boost::shared_ptr<void> >("reason", (boost::static_pointer_cast<void>)(messageFormatted)));

	if (se != SocketErrors_AccessDenied)
	{
		if (!instance->attemptingReconnection && !instance->sfs->IsConnecting() && !instance->manualDisconnection) 
		{
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > disconnectData (new map<string, boost::shared_ptr<void> >());
			disconnectData->insert(pair<string, boost::shared_ptr<void> >("reason", (boost::shared_ptr<string>)(new string(*ClientDisconnectionReason::UNKNOWN))));
			evt = boost::shared_ptr<BitSwarmEvent>(new BitSwarmEvent(BitSwarmEvent::DISCONNECT));
			evt->Params(disconnectData);
			instance->DispatchEvent(evt);
		}
			
		evt = boost::shared_ptr<BitSwarmEvent>(new BitSwarmEvent(BitSwarmEvent::IO_ERROR));
		evt->Params(data);
	}
	else
	{
		evt = boost::shared_ptr<BitSwarmEvent>(new BitSwarmEvent(BitSwarmEvent::SECURITY_ERROR));
		evt->Params(data);
	}

	instance->manualDisconnection = false;
	instance->DispatchEvent(evt);
}

// UDP

// -------------------------------------------------------------------
// UdpManager
// -------------------------------------------------------------------
boost::shared_ptr<IUDPManager> BitSwarmClient::UdpManager()
{
	return udpManager;
}

// -------------------------------------------------------------------
// UdpManager
// -------------------------------------------------------------------
void BitSwarmClient::UdpManager(boost::shared_ptr<IUDPManager> value)
{
	udpManager = value;
}

// IDispatchable implementation

// -------------------------------------------------------------------
// AddEventListener 
// -------------------------------------------------------------------
void BitSwarmClient::AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	dispatcher->AddEventListener(eventType, listener);
}
		
// -------------------------------------------------------------------
// DispatchEvent 
// -------------------------------------------------------------------
void BitSwarmClient::DispatchEvent(boost::shared_ptr<BitSwarmEvent> evt)
{
	dispatcher->DispatchEvent(evt);

	// Cleanup
	if (evt->Params() != NULL)
	{
		map<string, boost::shared_ptr<void> >::iterator itrArguments;
		for (itrArguments = evt->Params()->begin(); itrArguments != evt->Params()->end(); itrArguments++)
		{
			if ((itrArguments->first == "success") || (itrArguments->first == "message") || (itrArguments->first == "reason"))
			{
				continue;
			}

			if (itrArguments->first == "isReconnection")
			{
				continue;
			}
		}

		evt->Params()->clear();
		evt->Params(boost::shared_ptr<map<string, boost::shared_ptr<void> > >());
	}
}

long long BitSwarmClient::NextUdpPacketId()
{
	return udpManager->NextUdpPacketId();
}
		
// region BB
		
// -------------------------------------------------------------------
// OnBBConnect 
// -------------------------------------------------------------------
void BitSwarmClient::OnBBConnect(unsigned long long context, boost::shared_ptr<BaseEvent> e) {

	BitSwarmClient* instance = (BitSwarmClient*)context;

	instance->bbConnected = true;

	boost::shared_ptr<BitSwarmEvent> evt (new BitSwarmEvent(BitSwarmEvent::CONNECT));
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());

	boost::shared_ptr<bool> valueSuccess (new bool());
	*valueSuccess = true;
	args->insert(pair<string, boost::shared_ptr<void> >("success", valueSuccess));
	boost::shared_ptr<bool> valueIsReconnection (new bool());
	*valueIsReconnection = false;
	args->insert(pair<string, boost::shared_ptr<void> >("isReconnection", valueIsReconnection));	
	evt->Params(args);
	instance->DispatchEvent(evt);
}
		
// -------------------------------------------------------------------
// OnBBData 
// -------------------------------------------------------------------
void BitSwarmClient::OnBBData(unsigned long long context, boost::shared_ptr<BaseEvent> e) {

	BitSwarmClient* instance = (BitSwarmClient*)context;

	boost::shared_ptr<BBEvent> evt = (boost::static_pointer_cast<BBEvent>)(e);
	boost::shared_ptr<ByteArray> buffer = (boost::static_pointer_cast<ByteArray>)((*(evt->Params()))["data"]);

	instance->ioHandler->OnDataRead(buffer);
}
		
// -------------------------------------------------------------------
// OnBBDisconnect 
// -------------------------------------------------------------------
void BitSwarmClient::OnBBDisconnect(unsigned long long context, boost::shared_ptr<BaseEvent> e) {

	BitSwarmClient* instance = (BitSwarmClient*)context;

	// Connection is off
	instance->bbConnected = false;
	instance->useBlueBox = false;

	if (instance->manualDisconnection) 
	{
		instance->manualDisconnection = false;
		instance->ExecuteDisconnection();
	}
}
		
// -------------------------------------------------------------------
// OnBBError 
// -------------------------------------------------------------------
void BitSwarmClient::OnBBError(unsigned long long context, boost::shared_ptr<BaseEvent> e) {

	BitSwarmClient* instance = (BitSwarmClient*)context;

	boost::shared_ptr<BBEvent> evt = (boost::static_pointer_cast<BBEvent>)(e);

	boost::shared_ptr<string> evtMessage = (boost::static_pointer_cast<string>)((*(evt->Params()))["message"]);

	char buffer[512];
	sprintf (buffer, "## BlueBox Error:  %s", evtMessage->c_str());
	string logMessage = buffer;

	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	logMessages->push_back(logMessage);
	instance->log->Error(logMessages);

	boost::shared_ptr<BitSwarmEvent> bevt (new BitSwarmEvent(BitSwarmEvent::IO_ERROR));
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());

	args->insert(pair<string, boost::shared_ptr<void> >("message", evtMessage));
	bevt->Params(args);
	instance->DispatchEvent(bevt);
}
		
}	// namespace Bitswarm
}	// namespace Sfs2X

