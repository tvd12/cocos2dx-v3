// ===================================================================
//
// Description		
//		Contains the definition of LoginRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LoginRequest__
#define __LoginRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Join one of the Zones in the Server.
	/// </summary>
	/// <remarks>
	/// Each Zone represents a different application running independently<br/>
	/// In order to join a Zone a user name and password are usually required.<br/>
	/// If the Zone allows guest users, user name and password are not needed and a guest name will be created on the server side<br/>
	/// If the Zone uses a server side extension to handle the login, you can also send a custom SFSObject with any extra parameters.<br/>
	/// </remarks>
	class DLLImportExport LoginRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="userName">
		/// the user name (optional)
		/// </param>
		/// <param name="password">
		/// the password (optional)
		/// </param>
		/// <param name="zoneName">
		/// the name of an existing Zone in the server (case sensitive, 'SimpleChat' != 'simplechat'). If no Zone is specified the SmartFox.Config.Zone parameter will be used.
		/// </param>
		/// <param name="parameters">
		/// the custom parameters (optional, if you use an Extension on server side to handle the login)
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGIN, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnLogin, (unsigned long long)this));
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGIN_ERROR, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnLoginError, (unsigned long long)this));
		///
		/// 			// Login passing only the user name, no password and the zone name is obtained
		/// 			// from the previously loaded configuration
		///				boost::shared_ptr<IRequest> request (new LoginRequest("FozzieTheBear")); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				static void OnLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					// Login success
		///				}
		///
		///				void CMyClass::OnLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
		///					boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
		///					string* message = new string("Login failure: " +  (*ptrErrorMessage));
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.LOGIN"/>
		/// <seealso cref="Core.SFSEvent.LOGIN_ERROR"/>
		/// <seealso cref="SmartFox.LoadConfig(string, bool)"/>
		LoginRequest(string userName, string password, string zoneName, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// <see cref="LoginRequest(string, string, string, boost::shared_ptr<ISFSObject>"/>
		/// </summary>
		LoginRequest(string userName, string password, string zoneName);

		/// <summary>
		/// <see cref="LoginRequest(string, string, string, boost::shared_ptr<ISFSObject>)"/>
		/// </summary>
		LoginRequest(string userName, string password);

		/// <summary>
		/// <see cref="LoginRequest(string, string, string, boost::shared_ptr<ISFSObject>)"/>
		/// </summary>
		LoginRequest(string userName);

		virtual ~LoginRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_ZONE_NAME;
		
		static boost::shared_ptr<string> KEY_USER_NAME;
		
		static boost::shared_ptr<string> KEY_PASSWORD;
		
		static boost::shared_ptr<string> KEY_PARAMS;
		
		static boost::shared_ptr<string> KEY_PRIVILEGE_ID;

		static boost::shared_ptr<string> KEY_ID;
		
		static boost::shared_ptr<string> KEY_ROOMLIST;
		
		static boost::shared_ptr<string> KEY_RECONNECTION_SECONDS;

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

		void Init(string userName, string password, string zoneName, boost::shared_ptr<ISFSObject> parameters);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<string> zoneName;
		boost::shared_ptr<string> userName;
		boost::shared_ptr<string> password;
		boost::shared_ptr<ISFSObject> parameters;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
