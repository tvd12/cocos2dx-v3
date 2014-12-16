// ===================================================================
//
// Description		
//		Contains the definition of SmartFox
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SmartFox__
#define __SmartFox__

// Forward class declaration
namespace Sfs2X {
	class SmartFox;
}	// namespace Sfs2X

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

#include "Bitswarm/BitSwarmClient.h"
#include "Bitswarm/BitSwarmEvent.h"
#include "Util/EventDispatcher.h"
#include "Core/SFSIOHandler.h"
#include "Core/BaseEvent.h"
#include "Core/SFSEvent.h"
#include "Core/IDispatchable.h"
#include "Util/Common.h"
#include "Entities/Managers/IUserManager.h"
#include "Entities/Room.h"
#include "Entities/User.h"
#include "Entities/Managers/IBuddyManager.h"
#include "Entities/Managers/IRoomManager.h"
#include "Exceptions/SFSValidationError.h"
#include "FSM/FiniteStateMachine.h"
#include "Logging/Logger.h"
#include "Requests/IRequest.h"
#include "Util/ConfigData.h"
#include "Util/ConfigLoader.h"
#include "Util/LagMonitor.h"

#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/asio.hpp>						// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

using namespace Sfs2X::Bitswarm;
using namespace Sfs2X::Util;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Requests;
using namespace Sfs2X::Core;
using namespace Sfs2X::Logging;
using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Entities::Managers;

namespace Sfs2X {

	/// <summary>
	/// SmartFox is the main class of the SmartFoxServer 2X API.
	/// </summary>
	/// <remarks>
	/// This class is responsible for connecting the client to a SmartFoxServer instance and for dispatching all asynchronous events. Developers always interact with SmartFoxServer through this class.
	/// <para/>
	/// <b>NOTE</b>: in the provided examples, <c>sfs</c> always indicates a SmartFox instance.
    /// <para/>
 	/// Author: The gotoAndPlay() Team<br/>
	/// http://www.smartfoxserver.com<br/>
	/// http://www.gotoandplay.it<br/>
	/// </remarks>
	class DLLImportExport SmartFox : public IDispatchable, public boost::enable_shared_from_this<SmartFox>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new SmartFox instance.
		/// </summary>
		/// 
		/// <example>
		/// The following example instantiates the <b>SmartFox</b> class without enabling the debug messages:
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox (new Sfs2X::SmartFox());
		/// \endcode
		/// </example>
		SmartFox();

		/// <overloads>
		/// <summary>
		/// Creates a new SmartFox instance.
		/// </summary>
		/// 
		/// <example>
		/// The following example instantiates the <b>SmartFox</b> class while enabling the debug messages:
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox (new Sfs2X::SmartFox(true));
		/// \endcode
		/// </example>
		/// </overloads>		
		/// 
		/// <param name="debug">
		/// If \code{.cpp} true \endcode, the SmartFoxServer API debug messages are logged.
		/// </param>
		SmartFox(bool debug);

		virtual ~SmartFox();

		/// <summary>
		/// Allows to specify custom client details that will be used to gather statistics about the client platform 
		/// via the SFS2X Analytics Module. By default the generic "Unity" label is used as platform, without specifying the version.
		/// </summary>
		/// 
		/// <remark>
		/// This method must be called before the connection is started. <br/>
		/// The length of the two strings combined must be < 512 characters.  
		/// </remark>
		/// 
		/// <param name='platformId'>
		/// The id of the runtime platform: for example "Unity WebPlayer" or "iOS".
		/// </param>
		/// <param name='version'>
		/// An optional version of the runtime platform: for example "2.0.0".
		/// </param>
		/// 
		void SetClientDetails(boost::shared_ptr<string> platformId, boost::shared_ptr<string> version);

		boost::shared_ptr<BitSwarmClient> BitSwarm();
		boost::shared_ptr<Sfs2X::Logging::Logger> Log();

		/// <summary>
		/// Enables the automatic realtime monitoring of the lag between the client and the server (round robin). <br/>
		/// When turned on, the <b>SFSEvent.PING_PONG</b> event type is dispatched continuously, providing the average of the last ten measured lag values.
		/// </summary>
		/// 
		/// <remark>
		/// The lag monitoring is automatically halted when the user logs out of a Zone or gets disconnected.
		/// <p><b>NOTE</b>: the lag monitoring can be enabled after the login has been performed successfully only.</p>
		/// </remark>
		/// 
		/// <param name='enabled'>
		/// The lag monitoring status: \code{.cpp} true \endcode to start the monitoring, \code{.cpp} false \endcode to stop it.
		/// </param>
		/// <param name='interval'>
		/// An optional amount of seconds to pause between each query (recommended 3-4s)
		/// </param>
		/// <param name='queueSize'>
		/// The amount of values stored temporarily and used to calculate the average lag
		/// </param>
		/// 
		/// <seealso cref="SFSEvent"/>
		void EnableLagMonitor(bool enabled, long int interval, long int queueSize);

        /// <summary>
        /// <see cref="EnableLagMonitor(bool, long int, long int)"/>
        /// </summary>
		void EnableLagMonitor(bool enabled);

        /// <summary>
        /// <see cref="EnableLagMonitor(bool, long int, long int)"/>
        /// </summary>
		void EnableLagMonitor(bool enabled, long int interval);

		bool IsConnecting();

		boost::shared_ptr<BitSwarmClient> GetSocketEngine();

		boost::shared_ptr<Sfs2X::Util::LagMonitor> LagMonitor();

		/// <summary>
		/// Indicates whether the client is connected to the server or not.
		/// </summary>
		/// <example>
		/// The following example checks the connection status:
		/// \code{.cpp}
		///		string status = ptrSmartFox->IsConnected() == true ? "yes" : "no";
		///		string message = "Am I connected? " + status;
		/// \endcode
		/// </example>
		bool IsConnected();

		/// <summary>
		/// Return the API current version
		/// </summary>
		boost::shared_ptr<string> Version();

		/// <summary>
		/// Get the current client configuration. It can return null if the configuration was not loaded
		/// </summary>
		/// 
		/// <seealso cref="LoadConfig(string, bool)"/>
		boost::shared_ptr<ConfigData> Config();

		/// <summary>
		/// Indicates whether the client should attempt a tunnelled http connection through the BlueBox in case a socket connection can't be established.
		/// </summary>
		/// <remarks>
		/// <p><b>NOTE</b>: this property must be set <b>before</b> the <b>connect()</b> method is called.<br/>
		/// Also, after a connection is established, this property does not return the current connection mode (socket or http); for this purpose use the <b>ConnectionMode</b> property.</p>
		/// </remarks>
		/// <seealso cref="ConnectionMode"/>
		/// <seealso cref="LoadConfig(string*, bool)"/>
		bool UseBlueBox();
		void UseBlueBox(bool value);

		/// <summary>
		/// Return the current connection mode which can be <b>socket</b> or <b>http</b>.
		/// </summary>
		/// <value>
		/// The connection mode.
		/// </value>
		/// <example>
		/// The following example shows the connection mode:
		/// \code{.cpp}
		///		string message = "Connection mode: " + *(ptrSmartFox->ConnectionMode());
		/// \endcode
		/// </example>
		boost::shared_ptr<string> ConnectionMode();

		/// <summary>
		/// Returns the current compression threshold.
		/// </summary>
		/// <remarks>
		/// This value represents the maximum message size (in bytes) before the protocol compression is activated.<br/>
		/// It is determined by the server configuration.
		/// </remarks>
		long int CompressionThreshold();

		/// <summary>
		/// Returns the maximum size of messages allowed by the server.
		/// </summary>
		/// <remarks>
		/// Any request exceeding this size will not be sent.<br/>
		/// The value is determined by the server configuration.
		/// </remarks>
		long int MaxMessageSize();

		/// <summary>
		/// Retrieves a <em>Room</em> object from its id.
		/// </summary>
		/// <remarks>
		/// <p><b>NOTE</b>: the same object is returned by the <b>IRoomManager.GetRoomById()</b> method, accessible through the <b>RoomManager</b> getter;
		/// this was replicated on the <b>SmartFox</b> class for handy access due to its usually frequent usage.</p>
		/// </remarks>
		/// <param name="id">
		/// The id of the Room.
		/// </param>
		/// <returns>
		/// An object representing the requested Room; \code{.cpp}  NULL \endcode if no <b>Room</b> object with the passed id exists in the Rooms list.
		/// </returns>
		/// <example>
		/// The following example retrieves a <b>Room</b> object and writes its name:
		/// \code{.cpp}
		///		long int roomId = 3;
		///		boost::shared_ptr<Room> room = ptrSmartFox->GetRoomById(roomId);
		///		string message = "The name of Room is " + *(room->Name());
		/// \endcode
		/// </example>
		/// 
		/// <seealso cref="GetRoomByName(string)"/>
		/// <seealso cref="RoomList"/>
        /// <seealso cref="Entities.Managers.SFSRoomManager"/>
		boost::shared_ptr<Room> GetRoomById(long int id);

		/// <summary>
		/// Retrieves a <b>Room</b> object from its name.
		/// </summary>
		/// <remarks>
		/// <p><b>NOTE</b>: the same object is returned by the <b>IRoomManager.GetRoomByName()</b> method, accessible through the <b>RoomManager</b> getter;
		/// this was replicated on the <b>SmartFox</b> class for handy access due to its usually frequent usage.</p>
		/// </remarks>
		/// <param name="name">
		/// The name of the Room.
		/// </param>
		/// <returns>
		/// An object representing the requested Room; \code{.cpp}  NULL \endcode if no <b>Room</b> object with the passed name exists in the Rooms list.
		/// </returns>
		/// <example>
		/// The following example retrieves a <b>Room</b> object and writes its id:
		/// \code{.cpp}
		///		string roomName = "The Lobby";
		///		boost::shared_ptr<Room> room = ptrSmartFox->GetRoomByName(roomName);
		///
		///		char buffer[512];
		///		sprintf (buffer, "%ld", room->Id());
		///
		///		string message = "The ID of Room " + roomName + " is " + *(new string(buffer));
		/// \endcode
		/// </example>
		/// 
        /// <seealso cref="Entities.Managers.SFSRoomManager"/>
        /// <seealso cref="RoomList"/>
		/// <seealso cref="SFSRoom"/>
		boost::shared_ptr<Room> GetRoomByName(string name);

		/// <summary>
		/// Retrieves the list of Rooms which are part of the specified Room Group.
		/// </summary>
		/// <remarks>
		/// <p><b>NOTE</b>: the same list is returned by the <b>IRoomManager.GetRoomListFromGroup()</b> method, accessible through the <b>RoomManager</b> getter;
		/// this was replicated on the <b>SmartFox</b> class for handy access due to its usually frequent usage.</p>
		/// </remarks>
		/// <param name="groupId">
		/// The name of the Group.
		/// </param>
		/// <returns>
		/// The list of <em>Room</em> objects belonging to the passed Group.
		/// </returns>
		/// 
        /// <seealso cref="Entities.Managers.SFSRoomManager"/>
        /// <seealso cref="SFSRoom"/>
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > GetRoomListFromGroup(string groupId);

		/// <summary>
		/// Simulates an abrupt disconnection from the server.<br/>
		/// This method should be used for testing and simulations only, otherwise use the <b>Disconnect()</b> method.
		/// </summary>
		/// <seealso cref="Disconnect"/>
		void KillConnection();

		/// <summary>
		/// Establishes a connection between the client and a SmartFoxServer 2X instance.
		/// </summary>
		/// <remarks>
		/// If no argument is passed, the client will use the settings loaded via <b>loadConfig()</b> method.
		/// <p>
		/// The client usually connects to a SmartFoxServer instance through a socket connection. In case a socket connection can't be established,
		/// and the <b>UseBlueBox</b> property is set to \code{.cpp} true \endcode, a tunnelled http connection through the BlueBox module is attempted.
		/// When a successful connection is established, the <b>ConnectionMode</b> property can be used to check the current connection mode.
		///	</p>
		/// </remarks>
		/// 
		/// <param name="host">
		/// The address of the server to connect to.
		/// </param>
		/// <param name="port">
		/// The TCP port to connect to.
		/// </param>
        /// <exception cref="ArgumentException">If an invalid host/address or port is passed, and it can't be found in the loaded settings.</exception>
		/// 
		/// <example>
		/// The following example connects to a local SmartFoxServer 2X instance:
		/// \code{.cpp}
		///		ptrSmartFox->Connect("127.0.0.1", 9933);
		/// \endcode
		/// </example>
		/// 
		/// <seealso cref="LoadConfig(string,bool)"/>
		/// <seealso cref="UseBlueBox"/>
		/// <seealso cref="ConnectionMode"/>
		/// <seealso cref="Disconnect()"/>
		void Connect(string host, long int port);

        /// <summary>
        /// <see cref="Connect(string*, long int)"/>
        /// </summary>
		void Connect();

        /// <summary>
        /// <see cref="Connect(string*, long int)"/>
        /// </summary>
        void Connect(string host);

		/// <summary>
		/// Closes the connection between the client and the SmartFoxServer 2X instance.
		/// </summary>
		/// <seealso cref="Connect(string*, long int)"/>
		void Disconnect();

		/// <summary>
		/// Indicates whether the client-server messages debug is enabled or not.<br/>
		/// If set to \code{.cpp} true \endcode, detailed debugging informations for all the incoming and outgoing messages are provided.
		///	<p>Debugging can be enabled when instantiating the <b>SmartFox</b> class too.</p>
		/// </summary>
		/// <value>
		/// <c>true</c> if debug; otherwise, <c>false</c>.
		/// </value>
		bool Debug();
		void Debug(bool value);

		/// <summary>
		/// Returns the IP address of the SmartFoxServer 2X instance to which the client is connected.
		/// </summary>
		/// 
		/// <seealso cref="Connect(string, int)"/>
		/// <seealso cref="LoadConfig(string, bool)"/>
		boost::shared_ptr<string> CurrentIp();

		/// <summary>
		/// Returns the TCP port of the SmartFoxServer 2X instance to which the client is connected.
		/// </summary>
		/// 
        /// <seealso cref="Connect(string, int)"/>
        /// <seealso cref="LoadConfig(string, bool)"/>
        long int CurrentPort();

		/// <summary>
		/// Returns the Zone currently in use, if the user is already logged in.
		/// </summary>
		/// 
		/// <seealso cref="LoadConfig(string, bool)"/>
		/// <seealso cref="LoginRequest"/>
		boost::shared_ptr<string> CurrentZone();

		/// <summary>
		/// Returns the <b>User</b> object representing the client when connected to a SmartFoxServer 2X instance.
		/// </summary>
		/// <remarks>
		/// This object is generated upon successful login only, so it is \code{.cpp}  NULL \endcode if login was not performed yet.
		/// <p><b>NOTE</b>: setting the <em>MySelf</em> property manually can disrupt the API functioning.</p>
		/// </remarks>
		/// <seealso cref="Sfs2X.Entities.User.IsItMe"/>
		/// <seealso cref="LoginRequest"/>
		boost::shared_ptr<User> MySelf();
		void MySelf(boost::shared_ptr<User> value);

		/// <summary>
		/// Returns a reference to the internal <b>Logger</b> instance used by SmartFoxServer 2X.
		/// </summary>
		boost::shared_ptr<Sfs2X::Logging::Logger> Logger();

		/// <summary>
		/// Returns the object representing the last Room joined by the client, if any.
		/// </summary>
		/// <remarks>
		/// This property is \code{.cpp}  NULL \endcode if no Room was joined.
		/// <p><b>NOTE</b>: setting the <b>LastJoinedRoom</b> property manually can disrupt the API functioning.
		/// Use the <b>JoinRoomRequest</b> request to join a new Room instead.</p>
		/// </remarks>
		/// 
		/// <seealso cref="JoinRoomRequest"/>
		boost::shared_ptr<Room> LastJoinedRoom();
		void LastJoinedRoom(boost::shared_ptr<Room> value);

		/// <summary>
		/// Returns a list of <b>Room</b> objects representing the Rooms currently joined by the client.
		/// </summary>
		/// <remarks>
		/// <p><b>NOTE</b>: the same list is returned by the <b>IRoomManager.GetJoinedRooms()</b> method, accessible through the <b>RoomManager</b> getter;
		/// this was replicated on the <b>SmartFox</b> class for handy access due to its usually frequent usage.</p>
		/// </remarks>
		/// <seealso cref="JoinRoomRequest"/>
		/// <seealso cref="RoomManager"/>
		/// <seealso cref="Room"/>
		/// <seealso cref="LastJoinedRoom"/>
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > JoinedRooms();

		/// <summary>
		/// Returns a list of <b>Room</b> objects representing the Rooms currently "watched" by the client.
		/// </summary>
		/// <remarks>
		/// The list contains all the Rooms that are currently joined and all the Rooms belonging to the Room Groups that have been subscribed.
		/// <p><b>NOTE 1</b>: at login time, the client automatically subscribes all the Room Groups specified in the Zone's <b>Default Room Groups</b> setting.</p>
		/// <p><b>NOTE 2</b>: the same list is returned by the <b>IRoomManager.GetRoomList()</b> method, accessible through the <b>RoomManager</b> getter;
		/// this was replicated on the <b>SmartFox</b> class for handy access due to its usually frequent usage.</p>
		/// </remarks>
		/// <seealso cref="RoomManager"/>
		/// <seealso cref="JoinRoomRequest"/>
		/// <seealso cref="SubscribeRoomGroupRequest"/>
		/// <seealso cref="UnsubscribeRoomGroupRequest"/>
		boost::shared_ptr<vector<boost::shared_ptr<Room> > > RoomList();

		/// <summary>
		/// Returns a reference to the Room Manager.
		/// </summary>
		/// <remarks>
		/// This manager is used internally by the SmartFoxServer 2X API; the reference returned by this property
		/// gives access to the Rooms list and Groups, allowing interaction with <b>Room</b> objects.
		/// </remarks>
		/// <seealso cref="SFSRoomManager"/>
		boost::shared_ptr<IRoomManager> RoomManager();

		/// <summary>
		/// Returns a reference to the User Manager.
		/// </summary>
		/// <remarks>
		/// This manager is used internally by the SmartFoxServer 2X API; the reference returned by this property
		/// gives access to the users list, allowing interaction with <b>User</b> objects.
		/// </remarks>
		/// <seealso cref="SFSUserManager"/>
		boost::shared_ptr<IUserManager> UserManager();

		/// <summary>
		/// Returns a reference to the Buddy Manager.
		/// </summary>
		/// <remarks>
		/// This manager is used internally by the SmartFoxServer 2X API; the reference returned by this property
		/// gives access to the buddies list, allowing interaction with <b>Buddy</b> and <b>BuddyVariable</b> objects and access to user properties in the <b>Buddy List</b> system.
		/// </remarks>
		/// <seealso cref="SFSBuddyManager"/>
		boost::shared_ptr<IBuddyManager> BuddyManager();

		/// <summary>
		/// Indicates whether the UPD protocol is available or not in the current runtime.
		/// </summary>
		/// <remarks>
		/// UPD Protocol is available for Unity always and will always return true. Added for compatibility reasons with other APIs
		/// <para/>
		/// Using the UDP protocol in an application requires that a handshake is performed between client and server.
		/// By default This is NOT done by the API to avoid allocating resources that might never be used
		/// <para/>
		/// In order to activate the UDP support, the <b>InitUDP()</b> method must be invoked explicitly.
		/// </remarks>
		/// <seealso cref="InitUDP(string, int)"/>
		bool UdpAvailable();

		/// <summary>
		/// Indicates whether the UDP handshake has been performed successfully or not.
		/// </summary>
        /// <seealso cref="InitUDP(string, int)"/>
		bool UdpInited();

		/// <summary>
		/// <see cref="InitUDP(string*, long int)"/> 
		/// </summary>
		void InitUDP();

		/// <summary>
		/// <see cref="InitUDP(string*, long int)"/> 
		/// </summary>
		void InitUDP(string udpHost);

		/// <summary>
		/// IInitializes the UDP protocol by performing an handshake with the server.
		/// </summary>
		/// <remarks>
		/// This method needs to be called only once. It can be executed at any moment provided that you already started connection to the server.<br/>
		/// After a successful initialization you can send UDP extension request at any moment.
		/// <para/>
		/// If <em>udpHost</em> or <em>udpPort</em> arguments are not passed, the client will use the settings loaded via <b>LoadConfig()</b> method.
		/// <para/>
		/// <h3>MTU Note:</h3>
		/// The <b>MTU</b> or Maximum Transmission Unit, represents the largest amount of bytes that can be sent at once before packet fragmentation occurs.<br/>
		/// Since the UDP protocol uses a "nothing-or-all" appraoch to the transmission, it is important to keep in mind that on average a size of 1100-1200 bytes is probably the maximum you can reach.
		/// If you exceed the MTU size the data will be "lost in hyperspace" (the internet).
		///  
		/// Another interesting matter is that there's no fixed size for the MTU, each operating system uses a slighlty different size. <br/>
		/// Because of this we suggest a conservative data size of 1000-1200 bytes per packet to avoid packet loss.<br/>
		/// The SFS2X protocol compression allows to send 2-3KBytes of uncompressed data which usually is squeezed down to a size of ~1000 bytes.<br/>
		/// <para/>
		/// If you have larger data to send we suggest to organize it in smaller chunks so that they don't exceed the suggested MTU size.
		/// <para/>
		/// More details about the MTU are found here: http://en.wikipedia.org/wiki/Maximum_transmission_unit
		/// </remarks>
		/// <example>
		/// The following example initializes the UDP communication, sends a request to an Extension and handles the related events:
		/// \code{.cpp}
		///			ptrSmartFox->AddEventListener(SFSEvent::UPD_INIT, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnUDPInit, (unsigned long long)this)));
		///			ptrSmartFox->InitUDP();
		///
		///			static void OnUDPInit(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///			void CMyClass::OnUDPInit(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///			{
		///				// Get the pointer to my class
		///				CMyClass* instance = (CMyClass*)ptrContext;
		///			
		///				boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///				boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
		///
		///				if ((*((boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess))) == true)
		///				{
		/// 				// Init OK: Execute an extension call via UDP
		///					boost::shared_ptr<ISFSObject> parameters (new SFSObject());
		///					boost::shared_ptr<IRequest> request (new ExtensionRequest("udpTest", parameters, boost::shared_ptr<Room>(), true));
		///					ptrSmartFox->Send(request);
		///				}
		///				else
		///				{
		///					// Sorry, UDP is not available. Initialization failed
		///				}
		/// 		}
		/// \endcode
		/// </example>
		/// <param name="udpHost">
		/// The IP address of the server to connect to.
		/// </param>
		/// <param name="udpPort">
		/// The UDP port to connect to.
		/// </param>
		/// <seealso cref="SFSEvent.UDP_INIT"/>
		void InitUDP(string udpHost, unsigned short int udpPort);

		bool IsJoining();
		void IsJoining(bool value);

		/// <summary>
		/// Return the unique session token.
		/// </summary>
		/// <remarks>
		/// The Session token is a String sent by the server to the client after the initial handshake
		/// </remarks>
		boost::shared_ptr<string> SessionToken();

        /// <summary>
        /// Dispatch an event
        /// </summary>
		void DispatchEvent(boost::shared_ptr<BaseEvent> evt);

        /// <summary>
        /// When true (default) sets the API to be run with an event queue that needs to be processed from the client
        /// </summary>
        /// <remarks>
        /// When run in Unity, this <b>has</b> to be true. Otherwise you will get random crashes.
        /// </remarks>
        /// <seealso cref="ProcessEvents"/>
		bool ThreadSafeMode();
		void ThreadSafeMode(bool value);

		// No public docs for this, we use it internally for starting a reconnection
		long int GetReconnectionSeconds();
		
		// No public docs for this, we use it internally for starting a reconnection
		void SetReconnectionSeconds(long int seconds);

		/// <summary>
		/// Sends a request to the server.  
		/// </summary>
		/// <remarks>
		/// All the available request objects can be found in the <b>requests</b> namespace. 
		/// </remarks>
		/// <param name="request">
		/// a request object
		/// </param>
		/// 
		/// <example>
		/// The following example sends a login request:
		///			\code{.cpp}
		///				boost::shared_ptr<IRequest> request (new LoginRequest("FozzieTheBear", "KermitPass", "TheMuppetZone"));
		///				ptrSmartFox->Send(request);
		///			\endcode
		/// </example>
		/// 
		/// <example>
		/// The following example sends a login request:
		///			\code{.cpp}
		///				boost::shared_ptr<IRequest> request (new JoinRoomRequest("Lobby"));
		///				ptrSmartFox->Send(request);
		///			\endcode
		/// </example>
		/// 
		/// <example>
		/// The following example creates an object containing some parameters and sends it to the server-side Extension.
		///			\code{.cpp}
		///				boost::shared_ptr<ISFSObject> parameters = SFSObject.NewInstance();
		///
		///				boost::shared_ptr<long int> value (new long int());
		///				*value = 10;
		///				parameters->SetInt("x", value);
		///
		///				value = boost::shared_ptr<long int>(new long int());
		///				*value = 10;
		///				parameters->SetInt("y", value);
		///
		///				boost::shared_ptr<IRequest> request (new ExtensionRequest("setPosition", parameters));
		///				ptrSmartFox->Send(request);
		///			\endcode
		/// </example>
		/// 
		void Send(boost::shared_ptr<IRequest> request);

		/// <summary>
		/// Loads the client configuration file.
		/// </summary>
		/// 
		/// <remarks>
		/// The SmartFox instance can be configured through an external xml configuration file loaded at run-time.<br/>
        /// By default, the <b>loadConfig</b> method loads a file named "sfs-config.xml", placed in the same folder of the application file.<br/>
        /// If the <i>AutoConnect</i> parameter is set to <c>true</c>, On loading completion the <see cref="Connect(string*, long int)"/> method is automatically called by the API, otherwise the <see cref="SFSEvent.CONFIG_LOAD_SUCCESS"/> event is dispatched.<br/>
		/// In case of loading error, the <see cref="SFSEvent.CONFIG_LOAD_FAILURE"/> event id fired.
		/// <para/>
		/// <b>NOTE</b>: the SmartFoxClient configuration file (client-side) should not be confused with the SmartFoxServer configuration file (server-side).
		/// <para/>
		/// The external xml configuration file has the following structure; ip, port, udpIp, udpPort and zone parameters are mandatory, all other parameters are optional.
		///			\code{.cpp}
		///				<SmartFoxConfig>
		///					<ip>127.0.0.1</ip>
		///					<port>9933</port>
		///					<udpIp>127.0.0.1</ip>
		///					<udpPort>9933</port>
		///					<zone>simpleChat</zone>
		///					<debug>true</debug>
		///					<blueBoxIpAddress>127.0.0.1</blueBoxIpAddress>
		///					<blueBoxPort>9933</blueBoxPort>
		///					<smartConnect>true</smartConnect>
		///					<httpPort>8080</httpPort>
		///					<httpPollSpeed>750</httpPollSpeed>
		///					<rawProtocolSeparator>%</rawProtocolSeparator>
		///				</SmartFoxConfig>
		///			\endcode
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to load an external configuration file.
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::CONFIG_LOAD_SUCCESS, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConfigLoadSuccess, (unsigned long long)this)));
		///				ptrSmartFox->AddEventListener(SFSEvent::CONFIG_LOAD_FAILURE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConfigLoadFailure, (unsigned long long)this)));
		///				ptrSmartFox->LoadConfig(".\\Configuration\\testEnvironmentConfig.xml", true);
		///
		///				static void OnConfigLoadSuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnConfigLoadFailure(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnConfigLoadSuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Config file loaded, connection in progress
		///				}
		///
		///				void CMyClass::OnConfigLoadFailure(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Failed loading config file
		///				}
		///			\endcode
		/// </example>
		/// 
		/// <param name="filePath">
		/// Filename of the external XML configuration, including its path relative to the folder of the application file.
		/// </param>
		/// <param name="connectOnSuccess">
		/// A flag indicating if the connection to SmartFoxServer must be attempted upon configuration loading completion.
		/// </param>
		/// 
		/// <seealso cref="SFSEvent.CONFIG_LOAD_SUCCESS"/>
		/// <seealso cref="SFSEvent.CONFIG_LOAD_FAILURE"/>
		void LoadConfig(string filePath, bool connectOnSuccess);

		/// <summary>
        /// <see cref="LoadConfig(string*, bool)"/>
        /// </summary>
		void LoadConfig(string filePath);

		/// <summary>
        /// <see cref="LoadConfig(string*, bool)"/>
        /// </summary>
        void LoadConfig(bool connectOnSuccess);

        /// <summary>
        /// <see cref="LoadConfig(string*, bool)"/>
        /// </summary>
        void LoadConfig();

		/// <summary>
		/// Register delegate method for log message callbacks
		/// </summary>
		/// <remarks>
		/// Calling this method is just like calling the <see cref="Sfs2X.Logging.Logger.AddEventListener">Logger.AddEventListener</see> method directly,
		/// but in addition the <see cref="Sfs2X.Logging.Logger.EnableEventDispatching">Logger.EnableEventDispatching</see> property is automatically set to <c>true</c>. 
		///
		/// C# API only
		/// </remarks>
		/// 
		/// <param name="logLevel">
		/// A <see cref="LogLevel"/>
		/// </param>
		/// <param name="eventListener">
		/// A <see cref="EventListenerDelegate"/>
		/// </param>
		/// <seealso cref="Sfs2X.Logging.Logger.AddEventListener"/>
		void AddLogListener(LogLevel logLevel, boost::shared_ptr<EventListenerDelegate> eventListener);

		void AddJoinedRoom(boost::shared_ptr<Room> room);
		void RemoveJoinedRoom(boost::shared_ptr<Room> room);

		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Public handlers methods (used by SystemController)
		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		void HandleHandShake(boost::shared_ptr<BaseEvent> evt);

        void HandleLogin(boost::shared_ptr<BaseEvent> evt);

		void HandleClientDisconnection(boost::shared_ptr<string> reason);

		void HandleLogout();

		/// <summary>
		/// Sets the http port to use for BlueBox connections  
		/// </summary>
		/// <remarks>
		/// Can only be set prior to connecting. Once connected this value has no effect
		/// </remarks>
		/// 
		/// <example>
		/// This example shows how to set the HTTP Port
		///		\code{.cpp}
		///				ptrSmartFox->HttpPort(80);
		///				ptrSmartFox->Connect(ip, port);
		///		\endcode
		/// </example>
		/// 
		void HttpPort(unsigned short int httpPort);

        /// <summary>
        /// Tells the API to process all event queues and execute the delegate callbacks
        /// </summary>
        /// <remarks>
        /// This has to be done from the client to maintain thread safety
        /// </remarks>
        /// <example>
		///		\code{.cpp}
        /// 	void FixedUpdate() {
        /// 		ptrSmartFox->ProcessEvents();
        ///	}
        ///		\endcode
        /// </example>
		void ProcessEvents();

		// IDispatchable implementation

        /// <summary>
        /// Adds a delegate to a given API event type that will be used for callbacks
        /// </summary>
        /// <param name="eventType">The SFSEvent event to get callbacks on</param>
        /// <param name="listener">The delegate method to register</param>
        /// <example>
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox;
		///		ptrSmartFox =  boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox());
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnection, (unsigned long long)this)));
		///
		///		static void OnConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///		void CMyClass::OnConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///			boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///			boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
		///			boost::shared_ptr<bool> ptrValue = (boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess);
		///
		///			if (*ptrValue == true) 
		///			{
		///				// Connection was established
		///			}
		///			else
		///			{
		///				// Connection failed
		///			}
		///		}
        /// \endcode
        /// </example>
        /// <seealso cref="SFSEvent"/>
        void AddEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);

		/// <summary>
		/// Removes a delegate registration from a given registered event
		/// </summary>
		/// <param name="eventType"></param>
		/// <param name="listener"></param>
		void RemoveEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);

        /// <summary>
        /// Removed all event listeners
        /// </summary>
        /// <remarks>
        /// Note: log delegates need to be removed separately
        /// </remarks>
		void RemoveAllEventListeners();

		boost::shared_ptr<boost::asio::io_service> GetBoostService();

        /// <exclude/>
		void HandleReconnectionFailure();

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

		void Initialize();
		void Reset();
		void DisconnectConnection(long int timeout);

		void HandleConnectionProblem(boost::shared_ptr<BaseEvent> e);
		void SendHandshakeRequest(bool isReconnection);
		void EnqueueEvent(boost::shared_ptr<BaseEvent> evt);
		void OnDisconnectConnectionEvent(const boost::system::error_code& code);

        /// <summary>
        /// Returns the event dispatcher
        /// </summary>
		boost::shared_ptr<EventDispatcher> Dispatcher();

		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Event handlers
		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		static void OnSocketConnect(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnSocketClose(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnSocketReconnectionTry(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnSocketDataError(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnSocketIOError(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnSocketSecurityError(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnConfigLoadSuccess(unsigned long long context, boost::shared_ptr<BaseEvent> e);
		static void OnConfigLoadFailure(unsigned long long context, boost::shared_ptr<BaseEvent> e);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		const static long int DEFAULT_HTTP_PORT = 8080;
		const static long int MAX_BB_CONNECT_ATTEMPTS = 3;
		const static char CLIENT_TYPE_SEPARATOR = ':';

		// Current version
		long int majVersion;
		long int minVersion;
		long int subVersion;

		boost::shared_ptr<BitSwarmClient> bitSwarm;

		// Stores the custom client details about the runtime platform
		boost::shared_ptr<string> clientDetails;

		boost::shared_ptr<Sfs2X::Util::LagMonitor> lagMonitor;

		// If true the client will fall back to BlueBox if no socket connection is available
		bool useBlueBox;
			
		// If true the client is in the middle of a join transaction
		bool isJoining;  
		
		// References the client's User object
		boost::shared_ptr<User> mySelf; 
		
		// A unique session token, sent by the server during the handshake
		boost::shared_ptr<string> sessionToken;
		
		// Last joined room
		boost::shared_ptr<Room> lastJoinedRoom;
		
		// The logger
		boost::shared_ptr<Sfs2X::Logging::Logger> log;
		
		// API initialization flag
		bool inited;
		
		// Protocol debug flag
		bool debug;
		
		// Thread safe mode. Once enabled, you have to run ProcessEvents manually to process the queued events in your thread.
		bool threadSafeMode;
		
		// Connection attempt flag
		bool isConnecting; 
		
		// The global user manager
		boost::shared_ptr<IUserManager> userManager; 
		
		// The global room manager
		boost::shared_ptr<IRoomManager> roomManager;
		
		// The global buddy manager
		boost::shared_ptr<IBuddyManager> buddyManager;
		
		boost::shared_ptr<ConfigData> config;
		
		// The name of the currently joined Zone
		boost::shared_ptr<string> currentZone;
		
		// When true -> starts the connection right after successful config loading
		bool autoConnectOnConfig;
		
		// Last ip address used for connection, used when falling back to BlueBox
		boost::shared_ptr<string> lastIpAddress;
		
		boost::shared_ptr<EventDispatcher> dispatcher;
		
		boost::shared_ptr<SynchronizationObject> eventsLocker;
		
		boost::shared_ptr<vector<boost::shared_ptr<BaseEvent> > > eventsQueue;
		
		long int bbConnectionAttempt;

		boost::shared_ptr<boost::asio::io_service> service;
		boost::shared_ptr<boost::asio::deadline_timer> disconnectTimer;			// Boost Asio deadline timer
	};

}	// namespace Sfs2X

#endif
