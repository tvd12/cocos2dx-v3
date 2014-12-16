// ===================================================================
//
// Description		
//		Contains the definition of SFSEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSEvent__
#define __SFSEvent__

#include "../Util/Common.h"
#include "../Core/BaseEvent.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Core {
	
	/// <summary>
	/// This is the main SmartFox Event class. All major system events are found here.
	/// </summary>
	/// 
	/// <seealso cref="SFSBuddyEvent"/>
	class DLLImportExport SFSEvent : public BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		SFSEvent(boost::shared_ptr<string> type);
		SFSEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > data);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<string> HANDSHAKE;

		/// <summary>
		/// The Event notifies the result of the initial UDP handshake. 
		/// </summary>
		/// <remarks>
		/// The handshake is sent in order to establish a channel of communication between client and server.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>success</term>
		///     <description>(<b>bool</b>) true if a connection was established, false otherwise.</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how initialize the UDP channel
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
        /// <seealso cref="SmartFox.InitUDP(string, int)"/>
		static boost::shared_ptr<string> UDP_INIT;

		/// <summary>
		/// The Event notifies the result of a connection attempt.
		/// </summary>
		/// 
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>success</term>
		///     <description>(<b>bool</b>) true if a connection was established, false otherwise</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to start a connection
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
		/// 
		/// <seealso cref="CONNECTION_RETRY"/>
		/// <seealso cref="CONNECTION_RESUME"/>
		/// <seealso cref="CONNECTION_LOST"/>
		static boost::shared_ptr<string> CONNECTION;

		/**
		 * The <em>SFSEvent.PING_PONG</em> constant defines the value of the <em>type</em> property of the event object for a <em>pingPong</em> event.
		 * <p>The event is fired when measuring the lag between client and server</p>
		 * 
		 * <p>The properties of the <em>params</em> object contained in the event object have the following values:</p>
		 * <table class="innertable">
		 * <tr><th>Property</th><th>Type</th><th>Description</th></tr>
		 * <tr><td>lagValue</td><td><em>int</em></td><td>an average of the last 10 lag values, expressed in milliseconds</td></tr>
		 * </table>
		 */
		static boost::shared_ptr<string> PING_PONG;

		/**
		 * The <em>SFSEvent.SOCKET_ERROR</em> constant defines the value of the <em>type</em> property of the event object for a <em>socketError</em> event.
		 * <p>The event is fired when an unexpected socket error occurs, typically a data error.</p>
		 * 
		 * <p>The properties of the <em>params</em> object contained in the event object have the following values:</p>
		 * <table class="innertable">
		 * <tr><th>Property</th><th>Type</th><th>Description</th></tr>
		 * <tr><td>errorMessage</td><td><em>int</em></td><td>the description of the problem</td></tr>
		 * </table>
		 */
		static boost::shared_ptr<string> SFS_SOCKET_ERROR;

		/// <summary>
		/// The Event notifies the disconnection from the Server.
		/// </summary>
		/// 
		/// <remarks>
		/// When possible the API will also provide a reason for the disconnection:
		/// <ul>
		/// <li><b>Idle</b>: the connection was dropped because the User was inactive for too long</li>
		/// <li><b>Manual</b>: the User requested the disconnection</li>
		/// <li><b>Kick</b>: the connection was dropped because the User was kicked</li>
		/// <li><b>Ban</b>: the connection was dropped because the User was banned</li>
		/// <li><b>Unknown</b>: the connection was lost for reasons outside of the API (slow or bad connection, network problems etc...)</li>
		/// </ul>
        /// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>reason</term>
		///     <description>(<b>String</b>) the reason of the disconnection.</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a disconnection
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox;
		///		ptrSmartFox =  boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox());
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_LOST, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionLost, (unsigned long long)this)));
		///
		///		static void OnConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///		void CMyClass::OnConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///			boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///			boost::shared_ptr<void> ptrEventParamValueReason = (*ptrEventParams)["reason"];
		///			boost::shared_ptr<string> message (new string("Connection was lost, Reason: " +  *((boost::static_pointer_cast<string>)(ptrEventParamValueReason))));
		///		}
		/// \endcode
		/// </example>
		/// 
		/// <seealso cref="CONNECTION_RETRY"/>
		/// <seealso cref="CONNECTION_RESUME"/>
		/// <seealso cref="CONNECTION"/>
		static boost::shared_ptr<string> CONNECTION_LOST;

		/// <summary>
		/// The Event notifies the disconnection from the Server.
		/// </summary>
		/// 
		/// <remarks>
		/// SmartFoxServer 2X provides a powerful new feature that allows a broken connection to be re-established transparently
		/// without loosing any of the current application state. This allows any player to get back in the game without fear of loosing 
		/// the match because of a sloppy internet connection. 
		/// <para/>
		/// When this event is dispatched the API enter a "freeze" mode where no new requests can be sent until the reconnection is 
		/// successfully performed. It is highly recommended to handle this event and freeze your application interface accordingly until the
		/// <see cref="CONNECTION_RESUME"/> event is fired.
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a reconnection
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox;
		///		ptrSmartFox =  boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox());
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_RETRY, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionRetry, (unsigned long long)this)));
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_RESUME, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionResumed, (unsigned long long)this)));
		///
		///		static void OnConnectionRetry(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///		static void OnConnectionResumed(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///		void CMyClass::OnConnectionRetry(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			// Freeze your GUI and provide some feedback to the Player
		///		}
		///
		///		void CMyClass::OnConnectionResumed(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			// Unfreeze the GUI and let the player continue with the game...
		///		}
		/// \endcode
		/// </example>
		/// 
		/// <seealso cref="CONNECTION_LOST"/>
		/// <seealso cref="CONNECTION_RESUME"/>
		/// <seealso cref="CONNECTION"/>
		static boost::shared_ptr<string> CONNECTION_RETRY;

		/// <summary>
		/// The Event is dispatched after a temporary disconnection, when the connection to the Server has been re-establisehd.
		/// </summary>
		/// 
		/// <remarks>
		/// SmartFoxServer 2X provides a powerful new feature that allows a broken connection to be re-established transparently
		/// without loosing any of the current application state. This allows any player to get back in the game without fear of loosing 
		/// the match because of a sloppy internet connection or a sudden disconnection. 
		/// <para/>
		/// In case the re-connection attempts fails an <see cref="CONNECTION_LOST"/> event will be fired.
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a reconnection
		///	\code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox;
		///		ptrSmartFox =  boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox());
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_RETRY, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionRetry, (unsigned long long)this)));
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_RESUME, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionResumed, (unsigned long long)this)));
		///		ptrSmartFox->AddEventListener(SFSEvent::CONNECTION_LOST, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConnectionLost, (unsigned long long)this)));
		///
		///		static void OnConnectionRetry(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///		static void OnConnectionResumed(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///		static void OnConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///		void CMyClass::OnConnectionRetry(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			// Freeze your GUI and provide some feedback to the Player
		///		}
		///
		///		void CMyClass::OnConnectionResumed(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			// Unfreeze the GUI and let the player continue with the game...
		///		}
		///
		///		void CMyClass::OnConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///			boost::shared_ptr<void> ptrEventParamValueReason = (*ptrEventParams)["reason"];
		///			boost::shared_ptr<string> message (new string("Connection was lost, Reason: " +  *((boost::static_pointer_cast<string>)(ptrEventParamValueReason))));
		///		}
		///	\endcode
		/// </example>
		/// 
		/// <seealso cref="CONNECTION_LOST"/>
		/// <seealso cref="CONNECTION_RESUME"/>
		/// <seealso cref="CONNECTION"/>
		static boost::shared_ptr<string> CONNECTION_RESUME;

		/*
		 * The <em>SFSEvent.CONNECTION_ATTEMPT_HTTP</em> constant defines the value of the <em>type</em> property of the event object for a <em>connectionAttemptHttp</em> event.
		 * 
		 * <p>No parameters are available for this event object.</p>
		 * 
		 * @example	See the example provided in the <em>CONNECTION_ATTEMPT_HTTP</em> constant description.
		 * 
		 * @eventType	connectionAttemptHttp
		 * 
		 * @see		#CONNECTION
		 * @see		#CONNECTION_LOST
		 */	
		static boost::shared_ptr<string> CONNECTION_ATTEMPT_HTTP;

		/// <summary>
		/// Dispatched when the external SmartFox configuration file has been loaded successfully.
		/// </summary>
		/// <remarks>
		/// This event is dispatched only if the <i>connectOnSuccess</i> parameter of the <see cref="SmartFox.LoadConfig(string*, bool)"/> method is set to <c>false</c> otherwise the connection is made and the related <see cref="CONNECTION"/> event is fired.
		/// <para/>
		/// No parameters are provided.
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a successful configuration loading.
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::CONFIG_LOAD_SUCCESS, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConfigLoadSuccess, (unsigned long long)this)));
		///				ptrSmartFox->LoadConfig(".\\Configuration\\testEnvironmentConfig.xml", true);
		///
		///				static void OnConfigLoadSuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnConfigLoadSuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///				
		///					// Config file loaded, connection in progress
		///				}
		/// 		\endcode
		/// 
		/// </example>
		/// 
		/// <seealso cref="CONFIG_LOAD_FAILURE"/>
		/// <seealso cref="SmartFox.LoadConfig(string, bool)"/>
		static boost::shared_ptr<string> CONFIG_LOAD_SUCCESS;

		/// <summary>
		/// Dispatched when an error occurs while loading the external SmartFox configuration file.
		/// </summary>
		/// <remarks>
		/// Typically this event is received when the configuration is not found or its not accessible (no read permissions)
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a potential error in configuration loading.
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::CONFIG_LOAD_FAILURE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnConfigLoadFailure, (unsigned long long)this)));
		///				ptrSmartFox->LoadConfig(".\\Configuration\\testEnvironmentConfig.xml", true);
		///
		///				static void OnConfigLoadFailure(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnConfigLoadFailure(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///				
		///					// Failed loading config file.
		///				}
		/// 		\endcode
		/// </example>
		/// 
		/// <seealso cref="CONFIG_LOAD_SUCCESS"/>
		/// <seealso cref="SmartFox.LoadConfig(string, bool)"/>
		static boost::shared_ptr<string> CONFIG_LOAD_FAILURE;

		/// <summary>
		/// The Event is dispatched in response to a login request.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User object</description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>SFSObject</b>) a custom object with extra params (if you have added custom server side logic)</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle a login event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGIN, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnLogin, (unsigned long long)this)));
		///
		///				static void OnLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<void> ptrEventParamValueUser= (*ptrEventParams)["user"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
		///
		///					boost::shared_ptr<string> message (new string("Hi, I have just logged in as: " +  ptrNotifiedUser->Name()));
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="LOGIN_ERROR"/>
        /// <seealso cref="Requests.LoginRequest"/>
		static boost::shared_ptr<string> LOGIN;

		/// <summary>
		/// The Event is dispatched in response to a failed login request.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle a login failure event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGIN_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnLoginError, (unsigned long long)this)));
		///
		///				static void OnLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///
		///					boost::shared_ptr<string> message (new string("Login Failed. Reason: " +  *ptrNotifiedMessage));
		///				}
		/// 		\endcode
		/// </example> 
		/// <seealso cref="LOGIN"/>
        /// <seealso cref="Requests.LoginRequest"/>
		static boost::shared_ptr<string> LOGIN_ERROR;

		/// <summary>
		/// The Event is dispatched in response to a logout request.
		/// </summary>
		/// <remarks>
		/// Usually this event needs to be handled when you want to logout from the current Zone and join another one.
		/// <para/>
        /// In order to perform the operation correctly you need to do as follows:
		/// <ul>
		/// 	<li>Send a LogoutRequest to the Server</li>
		/// 	<li>Handle the OnLogout event on the client</li>
		/// 	<li>Perform a new login in the new Zone</li>
		/// </ul>
		/// <para/>
		/// No parameters are passed for this event
		/// </remarks>
		/// <example>
		/// The following example shows how to handle a logout event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGOUT, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnLogout, (unsigned long long)this)));
		///
		///				static void OnLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Logout was successful
		/// 				// Proceed with more logic here...
		///				}
		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.LogoutRequest"/>
        /// <seealso cref="Requests.LoginRequest"/>
		static boost::shared_ptr<string> LOGOUT;

		/// <summary>
		/// The Event is dispatched when a new Room was created inside the Zone under any of the Room Groups that the User is listening for.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the room object</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_ADD, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnRoomAdded, (unsigned long long)this)));
		///
		///				static void OnRoomAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomAdded(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// A new Room was added
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="ROOM_REMOVE"/>
        /// <seealso cref="Requests.CreateRoomRequest"/>
		static boost::shared_ptr<string> ROOM_ADD;

		/// <summary>
		/// The Event is dispatched whenever a Room is removed from the Zone, under any of the Room Groups that the User is listening for.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the room object</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_REMOVE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnRoomRemoved, (unsigned long long)this)));
		///
		///				static void OnRoomRemoved(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomRemoved(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// A Room was removed
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="ROOM_ADD"/>
		static boost::shared_ptr<string> ROOM_REMOVE;

		/// <summary>
		/// The Event is dispatched in response to a failed create room request.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_CREATION_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnRoomCreationError, (unsigned long long)this)));
		///
		///				static void OnRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptrvstring> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
		///					boost::shared_ptr<string> message (new string("Room Creation Error: " +  *ptrErrorMessage));
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="ROOM_ADD"/>
        /// <seealso cref="Requests.CreateRoomRequest"/>
		static boost::shared_ptr<string> ROOM_CREATION_ERROR;

		/// <summary>
		/// The Event is dispatched in response to a JoinRoomRequest.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the joined Room </description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnJoinRoom, (unsigned long long)this)));
		///
		///				static void OnJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Room joined
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="ROOM_JOIN_ERROR"/>
        /// <seealso cref="Requests.JoinRoomRequest"/>
		static boost::shared_ptr<string> ROOM_JOIN;

		/// <summary>
		/// The Event is dispatched in response to a failed JoinRoomRequest.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ROOM_JOIN_ERROR, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnJoinRoomError, (unsigned long long)this)));
		///
		///				static void OnJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
		///					boost::shared_ptr<string> message (new string("Join Room Failure: " +  *ptrErrorMessage));
		///				}
		/// 		\endcode
		/// </example>
		/// <seealso cref="ROOM_JOIN"/>
        /// <seealso cref="Requests.JoinRoomRequest"/>
		static boost::shared_ptr<string> ROOM_JOIN_ERROR;

		/// <summary>
		/// The Event is fired whenever a User enters one of the Rooms where the current User is joined.
		/// </summary>
		/// <remarks>
		/// <b>NOTE</b>: if the Room is of type <see cref="Sfs2X.Entities.MMORoom">MMORoom</see>, this event is never fired and it is substituted by the <see cref="PROXIMITY_LIST_UPDATE"/> event.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User object</description>
		///   </item>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room object</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_ENTER_ROOM, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnUserEnterRoom, (unsigned long long)this)));
		///
		///				static void OnUserEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the user parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
		///
		///					// Get the room parameter of the event
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///				}
		/// 		\endcode
		/// </example>	
		/// <seealso cref="USER_EXIT_ROOM"/>
		/// <seealso cref="ROOM_JOIN"/>
        /// <seealso cref="Requests.JoinRoomRequest"/>
		static boost::shared_ptr<string> USER_ENTER_ROOM;

		/// <summary>
		/// The Event is fired whenever a User leaves one of the Rooms where the current User is joined.
		/// </summary>
		/// <remarks>
		/// <b>NOTE</b>: if the Room is of type <see cref="Sfs2X.Entities.MMORoom">MMORoom</see>, this event is never fired and it is substituted by the <see cref="PROXIMITY_LIST_UPDATE"/> event.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User object</description>
		///   </item>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room object</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_EXIT_ROOM, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnUserExitRoom, (unsigned long long)this)));
		///
		///				static void OnUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the user parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
		///
		///					// Get the room parameter of the event
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///				}
		/// 		\endcode
		/// </example>	
		/// <seealso cref="USER_ENTER_ROOM"/>
		/// <seealso cref="ROOM_JOIN"/>
        /// <seealso cref="Requests.LeaveRoomRequest"/> 
		static boost::shared_ptr<string> USER_EXIT_ROOM;

		/// <summary>
		/// The Event is fired whenever the number of users/spectators in a Room changes.
		/// </summary>
		/// <remarks>
		/// The client receives updates for all Rooms inside the Room Groups that he is listening to.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room  </description>
		///   </item>
		///   <item>
		///     <term>uCount</term>
		///     <description>(<b>int</b>) the new user count</description>
		///   </item>
		///   <item>
		///     <term>sCount</term>
		///     <description>(<b>int</b>) the new spectator count</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_COUNT_CHANGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnUserCountChange, (unsigned long long)this)));
		///
		///				static void OnUserCountChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserCountChange(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the room parameter of the event
		///					// Get the users counter parameter of the event
		///					// Get the spectators counter parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		///					boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);
		///
		///					boost::shared_ptr<void> ptrEventParamValueUCount = (*ptrEventParams)["uCount"];
		///					int notifiedCounterUsers = *(((boost::static_pointer_cast<int>))(ptrEventParamValueUCount));
		///
		///					boost::shared_ptr<void> ptrEventParamValueSCount = (*ptrEventParams)["sCount"];
		///					int notifiedCounterSpectators = *(((boost::static_pointer_cast<int>))(ptrEventParamValueSCount));
		///				}
		/// 		\endcode
		/// </example>
		static boost::shared_ptr<string> USER_COUNT_CHANGE;

		/// <summary>
		/// The Event is fired when a User sends a public message.
		/// </summary>
		/// <remarks>
		/// Also the User receives this event every time he sends a public message. 
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the target Room</description>
		///   </item>
		///   <item>
		///     <term>sender</term>
		///     <description>(<b>User</b>) the sender</description>
		///   </item>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>String</b>) the message</description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>ISFSObject</b>) an object with custom data</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::PUBLIC_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnPublicMessage, (unsigned long long)this)));
		///
		///				static void OnPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the sender parameter of the event
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
		///
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///				}
		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.PublicMessageRequest"/>
		static boost::shared_ptr<string> PUBLIC_MESSAGE;

		/// <summary>
		/// The Event is fired when a User receives a private message.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>sender</term>
		///     <description>(<b>User</b>) the sender of the message </description>
		///   </item>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>String</b>) the message </description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>ISFSObject</b>) an object with custom data </description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::PRIVATE_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnPrivateMessage, (unsigned long long)this)));
		///
		///				static void OnPrivateMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnPrivateMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the sender parameter of the event
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
		///
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///				}
		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.PrivateMessageRequest"/>
		static boost::shared_ptr<string> PRIVATE_MESSAGE;

		/// <summary>
		/// The Event is fired when a User receives a Moderator message.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>sender</term>
		///     <description>(<b>User</b>) the sender of the message </description>
		///   </item>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>String</b>) the message </description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>ISFSObject</b>) an object with custom data</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::MODERATOR_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnModeratorMessage, (unsigned long long)this)));
		///
		///				static void OnModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the sender parameter of the event
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
		///					boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
		///
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///				}
		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.ModeratorMessageRequest"/>
		static boost::shared_ptr<string> MODERATOR_MESSAGE;

		/// <summary>
		/// The Event is fired when a User receives an Admin message.
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>sender</term>
		///     <description>(<b>User</b>) the sender of the message  </description>
		///   </item>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>String</b>) the message</description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>ISFSObject</b>) an object with custom data </description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::ADMIN_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnAdminMessage, (unsigned long long)this)));
		///
		///				static void OnAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///				}
		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.AdminMessageRequest"/>
		static boost::shared_ptr<string> ADMIN_MESSAGE;

		/// <summary>
		/// This Event is received when a User has sent an ObjectMessage request
		/// </summary>
		/// <remarks>
		/// The object sent by the sender can contain custom data, such as a game move etc...
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>sender</term>
		///     <description>(<b>User</b>) the sender of the message  </description>
		///   </item>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>ISFSObject</b>) the object data </description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// The following example shows how to handle the event
		///			\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::OBJECT_MESSAGE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnObjectMessage, (unsigned long long)this)));
		///
		///				static void OnObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<ISFSObject> ptrNotifiedMessage = ((boost::static_pointer_cast<ISFSObject>))(ptrEventParamValueMessage);
		///
		/// 				// dumps the data object
		///					virtual boost::shared_ptr<string> dump = obj->GetDump();
		///				}
 		/// 		\endcode
		/// </example>
        /// <seealso cref="Requests.ObjectMessageRequest"/>
 		static boost::shared_ptr<string> OBJECT_MESSAGE;

		/// <summary>
		/// The Event is fired every time a server-side Extension sends a message, usually in response to an ExtensionRequest. 
		/// </summary>
		/// <remarks>
		/// A server Extension can send messages at any moment, not just in response to a specific client request
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>cmd</term>
		///     <description>(<b>String</b>) the name of the "command" (or "action id") associated with the message </description>
		///   </item>
		///   <item>
		///     <term>sourceRoom</term>
		///     <description>(<b>int</b>) The id of the room where the server extension is attached to.</description>
		///   </item>
		///   <item>
		///     <term>params</term>
		///     <description>(<b>ISFSObject</b>) custom parameters</description>
		///   </item>
		///   <item>
		///     <term>packetId</term>
		///     <description>(<b>long</b>) (optional) the id of the packet for an UDP message, the id is an auto increment value sent by the server. It can be used to detect out of order UDP packets.</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ExtensionRequest"/>
		/// <seealso cref="Entities.Data.SFSObject"/>
		static boost::shared_ptr<string> EXTENSION_RESPONSE;

		/// <summary>
		/// The Event is fired in response to a SetRoomVariablesRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room in which the event occurred</description>
		///   </item>
		///   <item>
		///     <term>changedVars</term>
		///     <description>(<b>Array</b>) the list of variable names that where modified or created</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <seealso cref="Requests.SetRoomVariablesRequest"/>
		/// <seealso cref="Entities.Variables.SFSRoomVariable"/>
		static boost::shared_ptr<string> ROOM_VARIABLES_UPDATE;

		/// <summary>
		/// The Event is fired in response to a SetUserVariablesRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User that created or modified the Variables</description>
		///   </item>
		///   <item>
		///     <term>changedVars</term>
		///     <description>(<b>Array</b>) the list of variable names that where modified or created</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.SetUserVariablesRequest"/>
        /// <seealso cref="Entities.Variables.SFSUserVariable"/>
		static boost::shared_ptr<string> USER_VARIABLES_UPDATE;

		/// <summary>
		/// The Event is fired in response to a SubscribeRoomGroupRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>groupId</term>
		///     <description>(<b>String</b>) the name of the group that was subscribed</description>
		///   </item>
		///   <item>
		///     <term>newRooms</term>
		///     <description>(<b>Array</b>) the list of rooms contained in the new group </description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
		static boost::shared_ptr<string> ROOM_GROUP_SUBSCRIBE;

		/// <summary>
		/// The Event is fired in response to an UnsubscribeRoomGroupRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>groupId</term>
		///     <description>(<b>String</b>) the name of thr group that was unsubscribed</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
		static boost::shared_ptr<string> ROOM_GROUP_UNSUBSCRIBE;

		/// <summary>
		/// The Event is fired in response to a failed SubscribeRoomGroupRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
		static boost::shared_ptr<string> ROOM_GROUP_SUBSCRIBE_ERROR;

		/// <summary>
		/// The Event is fired in response to a failed UnsubscribeRoomGroupRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
		static boost::shared_ptr<string> ROOM_GROUP_UNSUBSCRIBE_ERROR;

		/// <summary>
		/// The Event is fired in response to a successful SpectatorToPlayerRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room where the spectator became a player</description>
		///   </item>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User who became a player</description>
		///   </item>
		///   <item>
		///     <term>playerId</term>
		///     <description>(<b>int</b>) the new playerId of the User</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.SpectatorToPlayerRequest"/>
		static boost::shared_ptr<string> SPECTATOR_TO_PLAYER;

		/// <summary>
		/// The Event is fired in response to a failed PlayerToSpectatorRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room where the player became a spectator</description>
		///   </item>
		///   <item>
		///     <term>user</term>
		///     <description>(<b>User</b>) the User who became a spectator</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.PlayerToSpectatorRequest"/>
        static boost::shared_ptr<string> PLAYER_TO_SPECTATOR;

		/// <summary>
		/// The Event is fired in response to a failed SpectatorToPlayerRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.SpectatorToPlayerRequest"/>
		static boost::shared_ptr<string> SPECTATOR_TO_PLAYER_ERROR;

		/// <summary>
		/// The Event is fired in response to a failed UnsubscribeRoomGroupRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.PlayerToSpectatorRequest"/>
		static boost::shared_ptr<string> PLAYER_TO_SPECTATOR_ERROR;

		/// <summary>
		/// The Event is fired in response to a ChangeRoomNameRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room where the change occurred</description>
		///   </item>
		///   <item>
		///     <term>oldName</term>
		///     <description>(<b>String</b>) the old Room name</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomNameRequest"/>
		static boost::shared_ptr<string> ROOM_NAME_CHANGE;

		/// <summary>
		/// The Event is fired in response to a failed ChangeRoomNameRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomNameRequest"/>
		static boost::shared_ptr<string> ROOM_NAME_CHANGE_ERROR;

		/// <summary>
		/// The Event is fired in response to a ChangeRoomPasswordStateRequest.
		/// </summary>
		/// <remarks>
		/// In particular this event when the <b>password state</b> is changed. For example when a non-password protected Room is assigned a password, or vice-versa 
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room where the change occurred</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomPasswordStateRequest"/>
		static boost::shared_ptr<string> ROOM_PASSWORD_STATE_CHANGE;

		/// <summary>
		/// The Event is fired in response to a failed ChangeRoomPasswordStateRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomPasswordStateRequest"/>
		static boost::shared_ptr<string> ROOM_PASSWORD_STATE_CHANGE_ERROR;

		/// <summary>
		/// The Event is fired in response to a ChangeRoomCapacityRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>Room</b>) the Room where the change occurred</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomCapacityRequest"/>
		static boost::shared_ptr<string> ROOM_CAPACITY_CHANGE;

		/// <summary>
		/// The Event is fired in response to a failed ChangeRoomCapacityRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.ChangeRoomCapacityRequest"/>
		static boost::shared_ptr<string> ROOM_CAPACITY_CHANGE_ERROR;

		/// <summary>
		/// The Event is fired in response to a FindRoomsRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>rooms</term>
		///     <description>(<b>List<Room></b>) a list of Rooms matching the request criteria. If no Room was found the list will be empty.</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.FindRoomsRequest"/>
		static boost::shared_ptr<string> ROOM_FIND_RESULT;

		/// <summary>
		/// The Event is fired in response to a FindUsersRequest
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>rooms</term>
		///     <description>(<b>Array</b>) a list of Users matching the request criteria. If no User was found the list will be empty.</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.FindUsersRequest"/>
		static boost::shared_ptr<string> USER_FIND_RESULT;

		/// <summary>
		/// The Event is fired when another User has sent you an Invitation
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>invitation</term>
		///     <description>(<b>Invitation</b>) the invitation object</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Requests.Game.InviteUsersRequest"/>
		/// <seealso cref="Entities.Invitation.SFSInvitation"/>
		static boost::shared_ptr<string> INVITATION;

		/// <summary>
		/// The Event is fired when a User sends a reply to your Invitation
		/// </summary>
		/// <remarks>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>invitee</term>
		///     <description>(<b>User</b>) the User that was invited</description>
		///   </item>
		///   <item>
		///     <term>reply</term>
		///     <description>(<b>int</b>) the <i>reply code</i>. It can be either InvitationReply.ACCEPT or InvitationReply.REFUSE</description>
		///   </item>
		///   <item>
		///     <term>data</term>
		///     <description>(<b>ISFSObject</b>) additional custom paramters (e.g. a reason for the refusal, a message etc...)</description>
		///   </item>
		/// </list>
		/// </remarks>
        /// <seealso cref="Entities.Invitation.InvitationReply"/>
        /// <seealso cref="Requests.Game.InviteUsersRequest"/>
		static boost::shared_ptr<string> INVITATION_REPLY;

		/// <summary>
		/// The Event is fired in response to a failed InvitationReplyRequest
		/// </summary>
		/// <remarks>
		/// The failure is usually caused by a late reply which doesn't make it to the server within the expected time
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>errorMessage</term>
		///     <description>(<b>string</b>) the error message</description>
		///   </item>
		///   <item>
		///     <term>errorCode</term>
		///     <description>(<b>short</b>) the error code</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
        /// <seealso cref="Requests.Game.InvitationReplyRequest"/>
		/// <seealso cref="Requests.Game.InviteUsersRequest"/>
		static boost::shared_ptr<string> INVITATION_REPLY_ERROR;

		/// <summary>
		/// Event fired for all log messages 
		/// </summary>
		/// <remarks>
		/// Unity API only
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters.
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>message</term>
		///     <description>(<b>String</b>) the log message</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// <example>
		/// \code{.cpp}
		///				ptrSmartFox->AddEventListener(LogLevel::LOGLEVEL_DEBUG, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnDebugMessage, (unsigned long long)this)));
		///
		///				static void OnDebugMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnDebugMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///				{
		///					// Get the pointer to my class
		///					CMyClass* instance = (CMyClass*)ptrContext;
		///
		///					// Get the message parameter of the event
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
		///					boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
		///				}
		/// \endcode
		/// </example>
		static boost::shared_ptr<string> DEBUG_MESSAGE;

		/// <summary>
		/// Dispatched when one more users or one or more MMOItem objects enter/leave the current user's Area of Interest in MMORooms.
		/// </summary>
		/// <remarks>
		/// This event is fired after an MMORoom is joined and the <see cref="Sfs2X.Requests.MMO.SetUserPositionRequest"/> request is sent at least one time.
		/// <para/>
		/// <b>NOTE</b>: this event substitutes the default <see cref="USER_ENTER_ROOM"/> and <see cref="USER_EXIT_ROOM"/> events available in regular Rooms.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters:
		/// <list type="table">
		///   <listheader>
		///     <term>parameter</term>
		///     <description>description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b>boost::shared_ptr&lt;Room&gt;</b>) The Room where the event occurred</description>
		///   </item>
		///   <item>
		///     <term>addedUsers</term>
		///     <description>(<b>boost::shared_ptr&lt;vector&lt;boost::shared_ptr&lt;User&gt; &gt; &gt;</b>) A list of User objects representing the users who entered the current user's Area of Interest.</description>
		///   </item>
		///   <item>
		///     <term>removedUsers</term>
		///     <description>(<b>boost::shared_ptr&lt;vector&lt;boost::shared_ptr&lt;User&gt; &gt; &gt;</b>) A list of User objects representing the users who left the current user's Area of Interest.</description>
		///   </item>
		///   <item>
		///     <term>addedItems</term>
		///     <description>(<b>boost::shared_ptr&lt;vector&lt;boost::shared_ptr&lt;IMMOItem&gt; &gt; &gt;</b>) A list of MMOItem objects which entered the current user's Area of Interest.</description>
		///   </item>
		///   <item>
		///     <term>removedItems</term>
		///     <description>(<b>boost::shared_ptr&lt;vector&lt;boost::shared_ptr&lt;IMMOItem&gt; &gt; &gt;</b>) A list of MMOItem objects which left the current user's Area of Interest.</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
		/// <example>See the <see cref="Sfs2X.Requests.MMO.SetUserPositionRequest"/> example.</example>
		/// 
		/// <seealso cref="Sfs2X.Requests.MMO.SetUserPositionRequest"/>
        /// <seealso cref="Sfs2X.Entities.MMORoom"/>
		/// <seealso cref="Sfs2X.Entities.MMOItem"/>
		static boost::shared_ptr<string> PROXIMITY_LIST_UPDATE;
		
		/// <summary>
		/// Dispatched when an MMOItem Variable is updated in an MMORoom.
		/// </summary>
		/// <remarks>
		/// This event is caused by an MMOItem Variable being set, updated or deleted in a server side Extension, and it is received only if the current user has the related MMOItem in his Area of Interest.
		/// <para/>
		/// The <see cref="BaseEvent.Params"/> object contains the following parameters:
		/// <list type="table">
		///   <listheader>
		///     <term>Parameter</term>
		///     <description>Description</description>
		///   </listheader>
		///   <item>
		///     <term>room</term>
		///     <description>(<b><see cref="Sfs2X.Entities.MMORoom"/></b>) The MMORoom where the MMOItem whose Variables have been updated is located.</description>
		///   </item>
		///   <item>
		///     <term>mmoItem</term>
		///     <description>(<b><see cref="Sfs2X.Entities.MMOItem"/></b>) The MMOItem whose variables have been updated.</description>
		///   </item>
		///   <item>
		///     <term>changedVars</term>
		///     <description>(<b>boost::shared_ptr&lt;vector&lt;boost::shared_ptr&lt;string&gt; &gt; &gt;</b>) The list of names of the MMOItem Variables that were changed (or created for the first time).</description>
		///   </item>
		/// </list>
		/// </remarks>
		/// 
		/// <example>
		/// The following example shows how to handle the MMOItem Variable update:
		/// \code{.cpp}
		///		boost::shared_ptr<Sfs2X::SmartFox> ptrSmartFox;
		///		ptrSmartFox =  boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox());
		///		ptrSmartFox->AddEventListener(SFSEvent::MMOITEM_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::OnMMOItemVarsUpdate, (unsigned long long)this)));
		///
		///		static void OnMMOItemVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///		void CMyClass::OnMMOItemVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
		///		{
		///			// Get the pointer to my class
		///			CMyClass* instance = (CMyClass*)ptrContext;
		///
		///			boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///			boost::shared_ptr<vector <boost::shared_ptr<string> > > ptrEventParamValueChangedVars = (*ptrEventParams)["changedVars"];
		///			boost::shared_ptr<IMMOItem> ptrEventParamValueMMOItem = (*ptrEventParams)["mmoItem"];
		///
		/// 		// Check if the MMOItem was moved
		///			if ((std::find(changedVars->begin(), changedVars->end(), "x") != changedVars->end()) || (std::find(changedVars->begin(), changedVars->end(), "y") != changedVars->end()))
		/// 		{
		/// 			// Move the sprite representing the MMOItem
		/// 			...
		/// 		}
		///		}
		/// 
		/// \endcode
		/// </example>
		/// 
		/// <seealso cref="Sfs2X.Entities.Variables.MMOItemVariable"/>
		/// <seealso cref="Sfs2X.Entities.MMOItem"/>
		/// <seealso cref="Sfs2X.Entities.MMORoom"/>
		static boost::shared_ptr<string> MMOITEM_VARIABLES_UPDATE;

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

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
