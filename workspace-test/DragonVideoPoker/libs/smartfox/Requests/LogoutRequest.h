// ===================================================================
//
// Description		
//		Contains the definition of LogoutRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LogoutRequest__
#define __LogoutRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Exceptions/SFSValidationError.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Log out of the current Zone
	/// </summary>
	/// <remarks>
	/// This will not shut down the connection and User will be able to login again in the same Zone or another one
	/// </remarks>
	class DLLImportExport LogoutRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::LOGOUT, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnLogout, (unsigned long long)this));
		///
		///				boost::shared_ptr<IRequest> request (new LogoutRequest()); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					// Logout done
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.LOGOUT"/>
		/// <seealso cref="LoginRequest"/>
		LogoutRequest();

		virtual ~LogoutRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_ZONE_NAME;

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

}	// namespace Requests
}	// namespace Sfs2X

#endif
