// ===================================================================
//
// Description		
//		Contains the implementation of SmartFox
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SmartFox.h"
#include "Requests/ManualDisconnectionRequest.h"
#include "Requests/HandshakeRequest.h"
#include "Requests/JoinRoomRequest.h"
#include "Entities/Managers/SFSGlobalUserManager.h"
#include "Entities/Managers/SFSRoomManager.h"
#include "Entities/Managers/SFSBuddyManager.h"
#include "Util/SFSErrorCodes.h"
#include "Bitswarm/UDPManager.h"

namespace Sfs2X {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SmartFox::SmartFox()
{
	service = boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
	disconnectTimer = boost::shared_ptr<boost::asio::deadline_timer> (new boost::asio::deadline_timer(*service));

	dispatcher = boost::shared_ptr<EventDispatcher>();
	inited = false;

	this->debug = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SmartFox::SmartFox(bool debug)
{
	service = boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
	disconnectTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*service));

	dispatcher = boost::shared_ptr<EventDispatcher>();
	inited = false;

	this->debug = debug;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SmartFox::~SmartFox()
{
	if (eventsQueue != NULL)
	{
		eventsQueue->clear();
	}
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void SmartFox::Initialize()
{
	if (inited) return;
			
	// Current version
	majVersion = 1;
	minVersion = 1;
	subVersion = 0;

	clientDetails = boost::shared_ptr<string>(new string("C++ API"));
	useBlueBox = true;
	isJoining = false;
	threadSafeMode = true;
	isConnecting = false;
	autoConnectOnConfig = false;
	eventsLocker = boost::shared_ptr<SynchronizationObject>(new SynchronizationObject());
	eventsQueue = boost::shared_ptr<vector<boost::shared_ptr<BaseEvent> > >(new vector<boost::shared_ptr<BaseEvent> >());
	bbConnectionAttempt = 0;

	log = boost::shared_ptr<Sfs2X::Logging::Logger>(new Sfs2X::Logging::Logger(shared_from_this()));
	log->EnableEventDispatching(true);
	if (debug) log->LoggingLevel(LOGLEVEL_DEBUG);

	lagMonitor = boost::shared_ptr<Sfs2X::Util::LagMonitor>();
	config = boost::shared_ptr<ConfigData>(new ConfigData());

	if (dispatcher == NULL) 
	{
		dispatcher = boost::shared_ptr<EventDispatcher>(new EventDispatcher(shared_from_this()));
	}

	mySelf = boost::shared_ptr<User>();
	lastJoinedRoom = boost::shared_ptr<Room>();
	userManager = boost::shared_ptr<IUserManager>();
	roomManager = boost::shared_ptr<IRoomManager>();
	buddyManager = boost::shared_ptr<IBuddyManager>();
	sessionToken = boost::shared_ptr<string>();
	lastIpAddress = boost::shared_ptr<string>();
	currentZone = boost::shared_ptr<string>();

	bitSwarm = boost::shared_ptr<BitSwarmClient>(new BitSwarmClient(shared_from_this(), service));
	boost::shared_ptr<SFSIOHandler> handler (new SFSIOHandler(bitSwarm));
	handler->Initialize();
	bitSwarm->IoHandler(handler);
	bitSwarm->Init();

	boost::shared_ptr<EventListenerDelegate> listenerConnect (new EventListenerDelegate(&SmartFox::OnSocketConnect, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerDisonnect (new EventListenerDelegate(&SmartFox::OnSocketClose, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerReconnectionTry (new EventListenerDelegate(&SmartFox::OnSocketReconnectionTry, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerIOError(new EventListenerDelegate(&SmartFox::OnSocketIOError, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerSecurityError(new EventListenerDelegate(&SmartFox::OnSocketSecurityError, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerDataError(new EventListenerDelegate(&SmartFox::OnSocketDataError, (unsigned long long)this));

	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::CONNECT, listenerConnect);
	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::DISCONNECT, listenerDisonnect );
	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::RECONNECTION_TRY, listenerReconnectionTry);
	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::IO_ERROR, listenerIOError);
	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::SECURITY_ERROR, listenerSecurityError);
	bitSwarm->Dispatcher()->AddEventListener(BitSwarmEvent::DATA_ERROR, listenerDataError);
			
	inited = true;
	Reset();
}

// -------------------------------------------------------------------
// SetClientDetails
// -------------------------------------------------------------------
void SmartFox::SetClientDetails(boost::shared_ptr<string> platformId, boost::shared_ptr<string> version)
{
	if (IsConnected()) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("SetClientDetails must be called before the connection is started");
		log->Warn(logMessages);
		return;
	}

	clientDetails = boost::shared_ptr<string>(new string(platformId != NULL ? platformId->replace(platformId->begin(), platformId->end(), CLIENT_TYPE_SEPARATOR, ' ') : "")); 
	*clientDetails += CLIENT_TYPE_SEPARATOR;
	clientDetails->append(version != NULL ? version->replace(version->begin(), version->end(), CLIENT_TYPE_SEPARATOR, ' ') : "");
}

// -------------------------------------------------------------------
// BitSwarm
// -------------------------------------------------------------------
boost::shared_ptr<BitSwarmClient> SmartFox::BitSwarm()
{
	return bitSwarm;
}

// -------------------------------------------------------------------
// Log
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Logging::Logger> SmartFox::Log()
{
	return log;
}

// -------------------------------------------------------------------
// Reset
// -------------------------------------------------------------------
void SmartFox::Reset()
{
	bbConnectionAttempt = 0;

	userManager = boost::shared_ptr<IUserManager>(new SFSGlobalUserManager(shared_from_this()));
	roomManager = boost::shared_ptr<IRoomManager>(new SFSRoomManager(shared_from_this()));
	buddyManager = boost::shared_ptr<IBuddyManager>(new SFSBuddyManager(shared_from_this()));

	// Remove previous lag monitor, if any.
	if (lagMonitor != NULL)
	{
		lagMonitor->Destroy();
	}
			
	isJoining = false;
	currentZone = boost::shared_ptr<string>();
	lastJoinedRoom = boost::shared_ptr<Room>();
	sessionToken = boost::shared_ptr<string>();
	mySelf = boost::shared_ptr<User>();
}

// -------------------------------------------------------------------
// EnableLagMonitor
// -------------------------------------------------------------------
void SmartFox::EnableLagMonitor(bool enabled, long int interval, long int queueSize)
{
	if (mySelf == NULL) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Lag Monitoring requires that you are logged in a Zone!");
		log->Warn(logMessages);
	
		return;
	}
			
	if (enabled) 
	{
		lagMonitor = boost::shared_ptr<Sfs2X::Util::LagMonitor>(new Sfs2X::Util::LagMonitor(*service, shared_from_this(), interval, queueSize));
		lagMonitor->Start();
	}
	else 
	{
		lagMonitor->Stop();
	}
}

// -------------------------------------------------------------------
// EnableLagMonitor
// -------------------------------------------------------------------
void SmartFox::EnableLagMonitor(bool enabled)
{
	EnableLagMonitor(enabled, 4, 10);
}

// -------------------------------------------------------------------
// EnableLagMonitor
// -------------------------------------------------------------------
void SmartFox::EnableLagMonitor(bool enabled, long int interval)
{
	EnableLagMonitor(enabled, interval, 10);
}

// -------------------------------------------------------------------
// IsConnecting
// -------------------------------------------------------------------
bool SmartFox::IsConnecting()
{
	return isConnecting;
}

// -------------------------------------------------------------------
// GetSocketEngine
// -------------------------------------------------------------------
boost::shared_ptr<BitSwarmClient> SmartFox::GetSocketEngine()
{
	return bitSwarm;
}

// -------------------------------------------------------------------
// LagMonitor
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Util::LagMonitor> SmartFox::LagMonitor()
{
	return lagMonitor;
}

// -------------------------------------------------------------------
// IsConnected
// -------------------------------------------------------------------
bool SmartFox::IsConnected()
{
	bool connected = false;
	if (bitSwarm != NULL) 
	{
		connected = bitSwarm->Connected();
	}
	
	return connected;
}

// -------------------------------------------------------------------
// Version
// -------------------------------------------------------------------
boost::shared_ptr<string> SmartFox::Version()
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	char buffer[100];
	sprintf (buffer, "%ld.%ld.%ld", majVersion, minVersion, subVersion);

	return boost::shared_ptr<string>(new string(buffer));
}

// -------------------------------------------------------------------
// Config
// -------------------------------------------------------------------
boost::shared_ptr<ConfigData> SmartFox::Config()
{
	return config;
}

// -------------------------------------------------------------------
// UseBlueBox
// -------------------------------------------------------------------
bool SmartFox::UseBlueBox()
{
	return useBlueBox;
}

// -------------------------------------------------------------------
// UseBlueBox
// -------------------------------------------------------------------
void SmartFox::UseBlueBox(bool value)
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	useBlueBox = value;
}

// -------------------------------------------------------------------
// ConnectionMode
// -------------------------------------------------------------------
boost::shared_ptr<string> SmartFox::ConnectionMode()
{
	return bitSwarm->ConnectionMode();
}

// -------------------------------------------------------------------
// CompressionThreshold
// -------------------------------------------------------------------
long int SmartFox::CompressionThreshold()
{
	return bitSwarm->CompressionThreshold();	
}

// -------------------------------------------------------------------
// MaxMessageSize
// -------------------------------------------------------------------
long int SmartFox::MaxMessageSize()
{
	return bitSwarm->MaxMessageSize();
}

// -------------------------------------------------------------------
// GetRoomById
// -------------------------------------------------------------------
boost::shared_ptr<Room> SmartFox::GetRoomById(long int id)
{
	return roomManager->GetRoomById(id);
}

// -------------------------------------------------------------------
// GetRoomByName
// -------------------------------------------------------------------
boost::shared_ptr<Room> SmartFox::GetRoomByName(string name)
{
	return roomManager->GetRoomByName(name);
}

// -------------------------------------------------------------------
// GetRoomListFromGroup
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SmartFox::GetRoomListFromGroup(string groupId)
{
	return roomManager->GetRoomListFromGroup(groupId);
}

// -------------------------------------------------------------------
// KillConnection
// -------------------------------------------------------------------
void SmartFox::KillConnection()
{
	bitSwarm->KillConnection();
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void SmartFox::Connect(string host, long int port)
{
	if (IsConnected()) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Already connected");
		log->Warn(logMessages);

		return;
	}
			
	// Skip attempt, if already trying to connect
	if (isConnecting) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("A connection attempt is already in progress");
		log->Warn(logMessages);

		return;
	}
			
	// Attempt to use external config (if exist) for missing params
	if (config != NULL) 
	{
		if (host.size() == 0)
			host = config->Host();
					
		if (port == -1)
			port = config->Port();
	}	
			
	// Apply basic validation
	if (host.size() == 0)
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid connection host/address"))); 
	}
			
	if (port < 0 || port > 65535)
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid connection port"))); 
	}

	// Resolve hostname 
	// Note that user has provided an ip address instead of an host name, resolver returns the address itself
    tcp::resolver resolver(*service);

	boost::shared_ptr<string> portAsString (new string());
	boost::shared_ptr<string> format (new string("%d"));
	StringFormatter<long int> (portAsString, format, port);

    tcp::resolver::query query(tcp::v4(), host, *portAsString);
    tcp::resolver::iterator iterator = resolver.resolve(query);
	tcp::endpoint endpoint = *iterator;

	boost::shared_ptr<string> endpointAddress (new string(endpoint.address().to_string()));
	unsigned short int endpointPort = endpoint.port();
		
	// All fine and dandy, let's proceed with the connection
	lastIpAddress = boost::shared_ptr<string>(new string(host));
	isConnecting = true;
								
	bitSwarm->Connect(endpointAddress, endpointPort);
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void SmartFox::Connect()
{
	Connect("", -1);
}

// -------------------------------------------------------------------
// Connect
// -------------------------------------------------------------------
void SmartFox::Connect(string host)
{
	Connect(host, -1);
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void SmartFox::Disconnect()
{
	if (IsConnected()) 
	{
		// If reconnection is active we need to tell the server that we don't want to reconnect
		if (bitSwarm->ReconnectionSeconds() > 0)
		{
			boost::shared_ptr<ManualDisconnectionRequest> request (new ManualDisconnectionRequest());
			Send(request);
		}
				
		// Disconnect the socket
//		DisconnectConnection(100);  // Dont use timer (crash in Unity)
		bitSwarm->Disconnect(ClientDisconnectionReason::MANUAL);
	}
	else 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("You are not connected");
		log->Info(logMessages);
	}
}

// -------------------------------------------------------------------
// DisconnectConnection
// -------------------------------------------------------------------
void SmartFox::DisconnectConnection(long int timeout) 
{
	// Start deadline timer for tcp connection task
    disconnectTimer->expires_from_now(boost::posix_time::seconds(timeout));
	disconnectTimer->async_wait(boost::bind(&SmartFox::OnDisconnectConnectionEvent, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// OnDisconnectConnectionEvent
// -------------------------------------------------------------------
void SmartFox::OnDisconnectConnectionEvent(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Timer has been stopped
		// Nothing to do
		return;
	}

	bitSwarm->Disconnect(ClientDisconnectionReason::MANUAL);
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
bool SmartFox::Debug()
{
	return debug;
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
void SmartFox::Debug(bool value)
{
	debug = value;
}

// -------------------------------------------------------------------
// CurrentIp
// -------------------------------------------------------------------
boost::shared_ptr<string> SmartFox::CurrentIp()
{
	return bitSwarm->ConnectionIp();
}

// -------------------------------------------------------------------
// CurrentPort
// -------------------------------------------------------------------
long int SmartFox::CurrentPort()
{
	return bitSwarm->ConnectionPort();
}

// -------------------------------------------------------------------
// CurrentZone
// -------------------------------------------------------------------
boost::shared_ptr<string> SmartFox::CurrentZone()
{
	return currentZone;
}

// -------------------------------------------------------------------
// MySelf
// -------------------------------------------------------------------
boost::shared_ptr<User> SmartFox::MySelf()
{
	return mySelf;
}

// -------------------------------------------------------------------
// MySelf
// -------------------------------------------------------------------
void SmartFox::MySelf(boost::shared_ptr<User> value)
{
	mySelf = value;
}

// -------------------------------------------------------------------
// Logger
// -------------------------------------------------------------------
boost::shared_ptr<Sfs2X::Logging::Logger> SmartFox::Logger()
{
	return log;
}

// -------------------------------------------------------------------
// LastJoinedRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room> SmartFox::LastJoinedRoom()
{
	return lastJoinedRoom;
}

// -------------------------------------------------------------------
// LastJoinedRoom
// -------------------------------------------------------------------
void SmartFox::LastJoinedRoom(boost::shared_ptr<Room> value)
{
	lastJoinedRoom = value;
}

// -------------------------------------------------------------------
// JoinedRooms
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SmartFox::JoinedRooms()
{
	return roomManager->GetJoinedRooms();
}

// -------------------------------------------------------------------
// RoomList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Room> > > SmartFox::RoomList()
{
	return roomManager->GetRoomList();
}

// -------------------------------------------------------------------
// RoomManager
// -------------------------------------------------------------------
boost::shared_ptr<IRoomManager> SmartFox::RoomManager()
{
	return roomManager;
}

// -------------------------------------------------------------------
// UserManager
// -------------------------------------------------------------------
boost::shared_ptr<IUserManager> SmartFox::UserManager()
{
	return userManager;
}

// -------------------------------------------------------------------
// BuddyManager
// -------------------------------------------------------------------
boost::shared_ptr<IBuddyManager> SmartFox::BuddyManager()
{
	return buddyManager;
}

// -------------------------------------------------------------------
// UdpAvailable
// -------------------------------------------------------------------
bool SmartFox::UdpAvailable()
{
	return true;
}

// -------------------------------------------------------------------
// UdpInited
// -------------------------------------------------------------------
bool SmartFox::UdpInited()
{
	if (bitSwarm->UdpManager() != NULL) 
	{
		return bitSwarm->UdpManager()->Inited();
	} 
	else 
	{
		return false;
	}
}

// -------------------------------------------------------------------
// InitUDP
// -------------------------------------------------------------------
void SmartFox::InitUDP()
{
	InitUDP("", -1);
}

// -------------------------------------------------------------------
// InitUDP
// -------------------------------------------------------------------
void SmartFox::InitUDP(string udpHost)
{
	InitUDP(udpHost, -1);
}

// -------------------------------------------------------------------
// InitUDP
// -------------------------------------------------------------------
void SmartFox::InitUDP(string udpHost, unsigned short int udpPort)
{
	if (!IsConnected()) {
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Cannot initialize UDP protocol until the client is connected to SFS2X.");
		log->Warn(logMessages);
		return;
	}

	// Attempt to use external config (if exist) for missing params
	if (config != NULL) {
		if (udpHost == "")
			udpHost = config->UdpHost();

		if (udpPort == -1)
			udpPort = config->UdpPort();
	}

	// Apply basic validation
	if (udpHost.size() == 0)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid UDP host/address"))); 

	if (udpPort < 0 || udpPort > 65535)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid UDP port range"))); 

	// If user supplied a hostname, then lets lookup as bitclient requires IP
	// Resolve hostname 
	// Note that user has provided an ip address instead of an host name, resolver returns the address itself
	try {
		tcp::resolver resolver(*service);

		boost::shared_ptr<string> portAsString (new string());
		boost::shared_ptr<string> format (new string("%d"));
		StringFormatter<long int> (portAsString, format, udpPort);

		tcp::resolver::query query(tcp::v4(), udpHost, *portAsString);
		tcp::resolver::iterator iterator = resolver.resolve(query);
		tcp::endpoint endpoint = *iterator;

		string endpointAddress = endpoint.address().to_string();
		unsigned short int endpointPort = endpoint.port();
	}
	catch(exception ex) {

		boost::shared_ptr<string> message (new string(ex.what()));

		char buffer[512];
		sprintf (buffer, "Failed to lookup hostname %s. UDP init failed. Reason %s", udpHost.c_str(), message->c_str());
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		log->Error(logMessages);

		boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<bool> value (new bool());
		*value = false;
		evtParams->insert(pair<string, boost::shared_ptr<void> >("success", value));
		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::UDP_INIT, evtParams));
		DispatchEvent(evt);
		return;
	}

	/*
	* If it's already inited with success we don't allow re-assigning a new UDP manager
	*/
	if (bitSwarm->UdpManager() == NULL || !bitSwarm->UdpManager()->Inited()) {
		boost::shared_ptr<IUDPManager> manager (new UDPManager(*service, shared_from_this()));
		bitSwarm->UdpManager(manager);
	}

	// Attempt initialization

	try {
		bitSwarm->UdpManager()->Initialize(udpHost, udpPort);
	}
	catch (exception ex) {
		boost::shared_ptr<string> message (new string(ex.what()));

		char buffer[512];
		sprintf (buffer, "Exception initializing UDP: %s", message->c_str());
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		log->Error(logMessages);
	}
}

// -------------------------------------------------------------------
// IsJoining
// -------------------------------------------------------------------
bool SmartFox::IsJoining()
{
	return isJoining;
}

// -------------------------------------------------------------------
// IsJoining
// -------------------------------------------------------------------
void SmartFox::IsJoining(bool value)
{
	isJoining = value;
}

// -------------------------------------------------------------------
// SessionToken
// -------------------------------------------------------------------
boost::shared_ptr<string> SmartFox::SessionToken()
{
	return sessionToken;
}

// -------------------------------------------------------------------
// Dispatcher
// -------------------------------------------------------------------
boost::shared_ptr<EventDispatcher> SmartFox::Dispatcher()
{
	return dispatcher;
}

// -------------------------------------------------------------------
// ThreadSafeMode
// -------------------------------------------------------------------
bool SmartFox::ThreadSafeMode()
{
	return threadSafeMode;
}

// -------------------------------------------------------------------
// ThreadSafeMode
// -------------------------------------------------------------------
void SmartFox::ThreadSafeMode(bool value)
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	threadSafeMode = value;
}

// -------------------------------------------------------------------
// GetReconnectionSeconds
// -------------------------------------------------------------------
long int SmartFox::GetReconnectionSeconds()
{
	return bitSwarm->ReconnectionSeconds();
}

// -------------------------------------------------------------------
// SetReconnectionSeconds
// -------------------------------------------------------------------
void SmartFox::SetReconnectionSeconds(long int seconds)
{
	bitSwarm->ReconnectionSeconds(seconds);
}

// -------------------------------------------------------------------
// Send
// -------------------------------------------------------------------
void SmartFox::Send(boost::shared_ptr<IRequest> request)
{
	// Handshake is an exception, during a reconnection attempt
	if (!IsConnected()) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());

		boost::shared_ptr<string> format (new string("You are not connected. Request %d cannot be sent"));
		StringFormatter<long long> (logMessage, format, ((boost::static_pointer_cast<BaseRequest>)(request))->Type());
		
		logMessages->push_back(*logMessage);
		log->Warn(logMessages);

		return;
	}
	
	try 
	{
		// Activate joining flag
		if (dynamic_cast<JoinRoomRequest*>(request.get()) != NULL) {
			if (isJoining) {
				return;
			}		
			else {
				isJoining = true;
			}		
		}
				
		// Validate Request parameters
		request->Validate(shared_from_this());
				
		// Execute Request logic
		request->Execute(shared_from_this());
				
		// Send request to SmartFoxServer2X
		bitSwarm->Send(request->Message());
		}
		catch (SFSValidationError problem) 
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());

			logMessages->push_back(*(problem.Message()));

			list<string>::iterator iterator;
			for (iterator = problem.Errors()->begin(); iterator != problem.Errors()->end(); iterator++)
			{
				boost::shared_ptr<string> errMsg (new string ("\t" + *iterator + "\n"));
				logMessages->push_back(*errMsg);
			}
				
			log->Warn(logMessages);
		}
		catch (SFSCodecError error) 
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());

			logMessages->push_back(*(error.Message()));

			log->Warn(logMessages);
		}
}

// -------------------------------------------------------------------
// LoadConfig
// -------------------------------------------------------------------
void SmartFox::LoadConfig(string filePath, bool connectOnSuccess)
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	boost::shared_ptr<ConfigLoader> configLoader (new ConfigLoader(shared_from_this()));
	configLoader->Initialize();

	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadSuccess (new EventListenerDelegate(&SmartFox::OnConfigLoadSuccess, (unsigned long long)this));
	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadFailure (new EventListenerDelegate(&SmartFox::OnConfigLoadFailure, (unsigned long long)this));

	configLoader->Dispatcher()->AddEventListener(SFSEvent::CONFIG_LOAD_SUCCESS, listenerConfigLoadSuccess);
	configLoader->Dispatcher()->AddEventListener(SFSEvent::CONFIG_LOAD_FAILURE, listenerConfigLoadFailure);
	autoConnectOnConfig = connectOnSuccess;
	configLoader->LoadConfig(filePath);
}

// -------------------------------------------------------------------
// LoadConfig
// -------------------------------------------------------------------
void SmartFox::LoadConfig(string filePath)
{
	LoadConfig(filePath, true);
}

// -------------------------------------------------------------------
// LoadConfig
// -------------------------------------------------------------------
void SmartFox::LoadConfig(bool connectOnSuccess)
{
	LoadConfig("sfs-config.xml", connectOnSuccess);
}

// -------------------------------------------------------------------
// LoadConfig
// -------------------------------------------------------------------
void SmartFox::LoadConfig()
{
	LoadConfig("sfs-config.xml", true);
}

// -------------------------------------------------------------------
// AddLogListener
// -------------------------------------------------------------------
void SmartFox::AddLogListener(LogLevel logLevel, boost::shared_ptr<EventListenerDelegate> eventListener)
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	AddEventListener(LoggerEvent::LogEventType(logLevel), eventListener);
	log->EnableEventDispatching(true);
}

// -------------------------------------------------------------------
// AddJoinedRoom
// -------------------------------------------------------------------
void SmartFox::AddJoinedRoom(boost::shared_ptr<Room> room) 
{
	boost::shared_ptr<long int> roomId (new long int());
	*roomId = room->Id();

	if (!roomManager->ContainsRoom((boost::static_pointer_cast<void>)(roomId))) {
		roomManager->AddRoom(room);
		lastJoinedRoom = room;
	}
	else {
		// this is just for debugging
		boost::shared_ptr<string> message (new string("Unexpected: joined room already exists for this User: " + (*mySelf->Name()) + ", Room: " + (*room->Name())));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}		
}

// -------------------------------------------------------------------
// RemoveJoinedRoom
// -------------------------------------------------------------------
void SmartFox::RemoveJoinedRoom(boost::shared_ptr<Room> room) 
{
	roomManager->RemoveRoom(room);

	// remove room id
	// delete _playerIdByRoomId[room.id]

	// point to the previous room, if any
	if (JoinedRooms()->size() > 0) {
		lastJoinedRoom = (boost::shared_ptr<Room>)(JoinedRooms()->at(((JoinedRooms()->size()) - 1)));
	}	
}

// -------------------------------------------------------------------
// OnSocketConnect
// -------------------------------------------------------------------
void SmartFox::OnSocketConnect(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);

	if ((evt->Params()->find("success") != evt->Params()->end()) && ((*(boost::static_pointer_cast<bool>)(evt->Params()->find("success")->second)) == true))
	{
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > params = evt->Params();
		boost::shared_ptr<void> paramValue = (*params.get())["isReconnection"];
		instance->SendHandshakeRequest(*(boost::static_pointer_cast<bool>)(paramValue));
	}
	else
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Connection attempt failed");
		instance->log->Warn(logMessages);

		instance->HandleConnectionProblem(evt);
	}
}

// -------------------------------------------------------------------
// OnSocketClose
// -------------------------------------------------------------------
void SmartFox::OnSocketClose(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);
	instance->Reset();

	// Fire event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
	data->insert(pair<string, boost::shared_ptr<void> >("reason", (*(evt->Params()))["reason"]));
	boost::shared_ptr<BaseEvent> sfsEvt (new SFSEvent(SFSEvent::CONNECTION_LOST, data));
	instance->DispatchEvent(sfsEvt);
}

// -------------------------------------------------------------------
// OnSocketReconnectionTry
// -------------------------------------------------------------------
void SmartFox::OnSocketReconnectionTry(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;

	// Fire event
	boost::shared_ptr<BaseEvent> sfsEvt (new SFSEvent(SFSEvent::CONNECTION_RETRY));
}

// -------------------------------------------------------------------
// OnSocketDataError
// -------------------------------------------------------------------
void SmartFox::OnSocketDataError(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);

	// Fire event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
	data->insert(pair<string, boost::shared_ptr<void> >("errorMessage", (*(evt->Params()))["message"]));
	boost::shared_ptr<BaseEvent> sfsEvt (new SFSEvent(SFSEvent::SFS_SOCKET_ERROR, data));
	instance->DispatchEvent(sfsEvt);
}

// -------------------------------------------------------------------
// OnSocketIOError
// -------------------------------------------------------------------
void SmartFox::OnSocketIOError(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);
	
	if (instance->isConnecting) {
		instance->HandleConnectionProblem(evt);
	}		
}

// -------------------------------------------------------------------
// OnSocketSecurityError
// -------------------------------------------------------------------
void SmartFox::OnSocketSecurityError(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);
	
	if (instance->isConnecting) {
		instance->HandleConnectionProblem(evt);
	}		
}

// -------------------------------------------------------------------
// OnConfigLoadSuccess
// -------------------------------------------------------------------
void SmartFox::OnConfigLoadSuccess(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<SFSEvent> evt = (boost::static_pointer_cast<SFSEvent>)(e);

	boost::shared_ptr<ConfigLoader> cfgLoader = (boost::static_pointer_cast<ConfigLoader>)(evt->Target());
	boost::shared_ptr<ConfigData> cfgData = (boost::static_pointer_cast<ConfigData>)((*(evt->Params()))["cfg"]);

	// remove listeners
	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadSuccess (new EventListenerDelegate(&SmartFox::OnConfigLoadSuccess, context));
	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadFailure (new EventListenerDelegate(&SmartFox::OnConfigLoadFailure, context));

	cfgLoader->Dispatcher()->RemoveEventListener(SFSEvent::CONFIG_LOAD_SUCCESS, listenerConfigLoadSuccess);
	cfgLoader->Dispatcher()->RemoveEventListener(SFSEvent::CONFIG_LOAD_FAILURE, listenerConfigLoadFailure);
			
	// Validate mandatory params
	if (cfgData->Host().size() == 0) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid Host/IpAddress in external config file"))); 
	}		
				
	/* Always true due to declaration type
	if (cfgData->Port() < 0 || cfgData->Port() > 65535) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid TCP port in external config file"))); 
	}
	*/
				
	if (cfgData->Zone().size() == 0)
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid Zone name in external config file"))); 
	}
			
	// Store globally
	instance->config = cfgData;
			
	instance->debug = cfgData->Debug();
				
	instance->useBlueBox = cfgData->UseBlueBox();
			
	// Fire event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
	data->insert(pair<string, boost::shared_ptr<void> >("config", cfgData));
	boost::shared_ptr<BaseEvent> sfsEvt (new SFSEvent(SFSEvent::CONFIG_LOAD_SUCCESS, data));
	instance->DispatchEvent(sfsEvt);
			
	// AutoConnect?
	if (instance->autoConnectOnConfig) 
	{
		instance->Connect(instance->config->Host(), instance->config->Port());
	}		
}

// -------------------------------------------------------------------
// OnConfigLoadFailure
// -------------------------------------------------------------------
void SmartFox::OnConfigLoadFailure(unsigned long long context, boost::shared_ptr<BaseEvent> e)
{
	SmartFox* instance = (SmartFox*)context;
	boost::shared_ptr<SFSEvent> evt = (boost::static_pointer_cast<SFSEvent>)(e);

	char buffer[512];

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > params = evt->Params();
	boost::shared_ptr<void> paramValue = (*params.get())["message"];

	sprintf (buffer, "Failed to load config: %s", (boost::static_pointer_cast<string>)(paramValue)->c_str());
	string logMessage = buffer;

	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	logMessages->push_back(logMessage);
	instance->log->Error(logMessages);

	boost::shared_ptr<ConfigLoader> cfgLoader = (boost::static_pointer_cast<ConfigLoader>)(evt->Target());

	// remove listeners
	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadSuccess (new EventListenerDelegate(&SmartFox::OnConfigLoadSuccess, context));
	boost::shared_ptr<EventListenerDelegate> listenerConfigLoadFailure (new EventListenerDelegate(&SmartFox::OnConfigLoadFailure, context));

	cfgLoader->Dispatcher()->RemoveEventListener(SFSEvent::CONFIG_LOAD_SUCCESS, listenerConfigLoadSuccess);
	cfgLoader->Dispatcher()->RemoveEventListener(SFSEvent::CONFIG_LOAD_FAILURE, listenerConfigLoadFailure);
			
	// Fire event
	boost::shared_ptr<BaseEvent> sfsEvt (new SFSEvent(SFSEvent::CONFIG_LOAD_FAILURE));
	instance->DispatchEvent(sfsEvt);
}

// -------------------------------------------------------------------
// HandleHandShake
// -------------------------------------------------------------------
void SmartFox::HandleHandShake(boost::shared_ptr<BaseEvent> evt)
{
	boost::shared_ptr<ISFSObject> obj = (boost::static_pointer_cast<ISFSObject>)((*(evt->Params()))["message"]);

	// Success
	if (obj->IsNull(*BaseRequest::KEY_ERROR_CODE)) 
	{
		sessionToken = boost::shared_ptr<string>(new string(*(obj->GetUtfString(*HandshakeRequest::KEY_SESSION_TOKEN))));
		bitSwarm->CompressionThreshold(*(obj->GetInt(*HandshakeRequest::KEY_COMPRESSION_THRESHOLD)));
		bitSwarm->MaxMessageSize(*(obj->GetInt(*HandshakeRequest::KEY_MAX_MESSAGE_SIZE)));
		
		if (debug) 
		{
			char buffer[512];
			sprintf (buffer, "Handshake response: tk => %s, ct => %ld", sessionToken->c_str(), bitSwarm->CompressionThreshold());
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			log->Debug(logMessages);

//			log.Debug(String.Format("Handshake response: tk => {0}, ct => {1}", sessionToken, bitSwarm.CompressionThreshold));
		}
				
		if (bitSwarm->IsReconnecting())
		{
			bitSwarm->IsReconnecting(false);
					
			/*
			* Reconnection success
			* We can safely assume that reconnection was performed correctly at this point
			* In case of failure the server will disconnect the temp socket.
			*/
			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CONNECTION_RESUME));
			DispatchEvent(evt);
		}
		else 
		{
			/*
			* Regular connection success
			*/
			isConnecting = false; // reset flag
			boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
			boost::shared_ptr<bool> value (new bool());
			*value = true;
			data->insert(pair<string, boost::shared_ptr<void> >("success", value));

			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CONNECTION, data));
			DispatchEvent(evt);
		}
	}
	// Failure (via socket)
	else {
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<void> errorCode = (obj->GetShort(*BaseRequest::KEY_ERROR_CODE));
		boost::shared_ptr<string> errorMsg = SFSErrorCodes::GetErrorMessage(*((boost::static_pointer_cast<short int>)(errorCode)), this->Log(), obj->GetUtfStringArray(*BaseRequest::KEY_ERROR_PARAMS));
		
		boost::shared_ptr<bool> successValue (new bool());
		*successValue = false;
		evtParams->insert(pair<string, boost::shared_ptr<void> >("success", successValue));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorMessage", errorMsg));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("errorCode", errorCode));

		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CONNECTION, evtParams));
		DispatchEvent(evt);
	}
}

// -------------------------------------------------------------------
// HandleLogin
// -------------------------------------------------------------------
void SmartFox::HandleLogin(boost::shared_ptr<BaseEvent> evt)
{
	currentZone = boost::shared_ptr<string>(new string(*((boost::static_pointer_cast<string>)((*(evt->Params()))["zone"]))));
}

// -------------------------------------------------------------------
// HandleClientDisconnection
// -------------------------------------------------------------------
void SmartFox::HandleClientDisconnection(boost::shared_ptr<string> reason)
{
	// TODO: Hide with custom namespace?

	// Fire event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
	evtParams->insert(pair<string, boost::shared_ptr<void> >("reason", reason));
	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CONNECTION_LOST, evtParams));
	DispatchEvent(evt);

	// no reconnections
	bitSwarm->ReconnectionSeconds(0);
	bitSwarm->Disconnect(reason);

	Reset();
}

// -------------------------------------------------------------------
// HandleLogout
// -------------------------------------------------------------------
void SmartFox::HandleLogout()
{
	// TODO: Hide with custom namespace?
			
	if (lagMonitor != NULL && lagMonitor->IsRunning()) 
	{
		lagMonitor->Stop();
	}
					
 	userManager = boost::shared_ptr<IUserManager>(new SFSGlobalUserManager(shared_from_this()));
 	roomManager = boost::shared_ptr<IRoomManager>(new SFSRoomManager(shared_from_this()));
 	isJoining = false;
 	lastJoinedRoom = boost::shared_ptr<Room>();
 	currentZone = boost::shared_ptr<string>();
 	mySelf = boost::shared_ptr<User>();
}

// -------------------------------------------------------------------
// HttpPort
// -------------------------------------------------------------------
void SmartFox::HttpPort(unsigned short int httpPort)
{
	if (IsConnected()) {
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Trying to set HTTP port after API is connected. This value will have no effect!");
		log->Warn(logMessages);
	}
	if (config == NULL) {
		config = boost::shared_ptr<ConfigData>(new ConfigData());
	}
	config->HttpPort(httpPort);
}

// -------------------------------------------------------------------
// HandleConnectionProblem
// -------------------------------------------------------------------
void SmartFox::HandleConnectionProblem(boost::shared_ptr<BaseEvent> e)
{
	// Socket failed, attempt using the BBox if it's connection
	if (this->IsConnecting() && useBlueBox && bbConnectionAttempt < MAX_BB_CONNECT_ATTEMPTS)
	{
		bbConnectionAttempt++;
		bitSwarm->ForceBlueBox(true);
		unsigned short int bbPort = (config != NULL) ? config->HttpPort() : DEFAULT_HTTP_PORT;
		bitSwarm->Connect(lastIpAddress, bbPort);

		boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::CONNECTION_ATTEMPT_HTTP, evtParams));
		DispatchEvent(evt);
	}
	else 
	{
		bitSwarm->ForceBlueBox(false);
		bbConnectionAttempt = 0;

		boost::shared_ptr<BitSwarmEvent> evt = (boost::static_pointer_cast<BitSwarmEvent>)(e);

		boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<bool> value (new bool());
		*value = false;
		data->insert(pair<string, boost::shared_ptr<void> >("success", value));
		data->insert(pair<string, boost::shared_ptr<void> >("errorMessage", (*(evt->Params()))["message"]));
		boost::shared_ptr<SFSEvent> evtToDispatch (new SFSEvent(SFSEvent::CONNECTION, data));
		DispatchEvent(evtToDispatch);

		isConnecting = false;
		bitSwarm->Destroy();
	}
}

// -------------------------------------------------------------------
// HandleReconnectionFailure
// -------------------------------------------------------------------
void SmartFox::HandleReconnectionFailure() 
{
	// Reset reconnection seconds, this way no more reconnections will be available in this session.
	this->SetReconnectionSeconds(0);
			
	// Stop running reconnection
	this->bitSwarm->StopReconnection();
}

// -------------------------------------------------------------------
// SendHandshakeRequest
// -------------------------------------------------------------------
void SmartFox::SendHandshakeRequest(bool isReconnection)
{
	boost::shared_ptr<HandshakeRequest> req (new HandshakeRequest(*this->Version(), isReconnection ? *sessionToken : "", *clientDetails));
	Send(req);
}

// -------------------------------------------------------------------
// DispatchEvent
// -------------------------------------------------------------------
void SmartFox::DispatchEvent(boost::shared_ptr<BaseEvent> evt)
{
	if (!threadSafeMode) 
	{
		Dispatcher()->DispatchEvent(evt);

		// Cleanup
		if (evt->Params() != NULL)
		{
			evt->Params()->clear();
		}
	}
	else 
	{
		EnqueueEvent(evt);
	}
}

// -------------------------------------------------------------------
// EnqueueEvent
// -------------------------------------------------------------------
void SmartFox::EnqueueEvent(boost::shared_ptr<BaseEvent> evt)
{
	eventsLocker->lock();
	eventsQueue->push_back(evt);
	eventsLocker->unlock();
}

// -------------------------------------------------------------------
// ProcessEvents
// -------------------------------------------------------------------
void SmartFox::ProcessEvents()
{
	if (!threadSafeMode) return;

	// Copy events into a local vector
	vector<boost::shared_ptr<BaseEvent> > events;

	eventsLocker->lock();

	if (eventsQueue->size() == 0)
	{
		eventsLocker->unlock();
		return;
	}

	events.insert(events.end(), eventsQueue->begin(), eventsQueue->end());
	eventsQueue->clear();

	eventsLocker->unlock();

	// Notify events
	vector<boost::shared_ptr<BaseEvent> >::iterator iterator;
	for (iterator = events.begin() ; iterator < events.end(); iterator++)
	{
		boost::shared_ptr<BaseEvent> evt = *iterator;
		Dispatcher()->DispatchEvent(evt);

		// Cleanup
		if (evt->Params() != NULL)
		{
			map<string, boost::shared_ptr<void> >::iterator itrArguments;
			evt->Params()->clear();
		}
	}

	events.clear();
}

// -------------------------------------------------------------------
// AddEventListener
// -------------------------------------------------------------------
void SmartFox::AddEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	// Due to shared pointer the Initialize method cannot be invoked into class constructor
	// so if not yet called by API user, we invoke it in main class methods
	if (inited == false)
	{
		Initialize();
	}

	dispatcher->AddEventListener(eventType, listener);
}

// -------------------------------------------------------------------
// RemoveEventListener
// -------------------------------------------------------------------
void SmartFox::RemoveEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	dispatcher->RemoveEventListener(eventType, listener);
}

// -------------------------------------------------------------------
// RemoveAllEventListeners
// -------------------------------------------------------------------
void SmartFox::RemoveAllEventListeners()
{
	dispatcher->RemoveAll();
}

}	// namespace Sfs2X

// -------------------------------------------------------------------
// GetBoostService
// -------------------------------------------------------------------
boost::shared_ptr<boost::asio::io_service> SmartFox::GetBoostService()
{
	return service;
}
