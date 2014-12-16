// ===================================================================
//
// Description		
//		Contains the definition of KickUserRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __KickUserRequest__
#define __KickUserRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Kicks a User out of the server (for moderators and admins only)
	/// </summary>
	/// <remarks>
	/// Allows to send a custom message and to set a delay in seconds.
	/// </remarks>
	class DLLImportExport KickUserRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		/// <summary>
		/// <see cref="KickUserRequest(long int, string, long int)"/>
		/// </summary>
		KickUserRequest(long int userId);

		/// <summary>
		/// <see cref="KickUserRequest(long int, string, long int)"/>
		/// </summary>
		KickUserRequest(long int userId, string message);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="userId">
		/// the id of the User to be kicked out of the server
		/// </param>
		/// <param name="message">
		/// a custom kick message, if null the message configured on the server side will be used
		/// </param>
		/// <param name="delaySeconds">
		/// a delay in seconds between the message (immediate) and the kick (delayed). Default is 5 seconds
		/// </param>
		/// <example>
		///		\code{.cpp}
		/// 			boost::shared_ptr<User> userToKick new (ptrSmartFox->UserManager()->GetUserByName("Swedish Cook")); 
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new KickUserRequest(userToKick)); 
		///				ptrSmartFox->Send(request);
		/// 	\endcode
		/// </example>
		/// <seealso cref="BanUserRequest"/>
		KickUserRequest(long int userId, string message, long int delaySeconds);

		virtual ~KickUserRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);
		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_USER_ID;
		
		static boost::shared_ptr<string> KEY_MESSAGE;

		static boost::shared_ptr<string> KEY_DELAY;

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
		void Init(long int userId, string message, long int delaySeconds);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		long int userId;		
		boost::shared_ptr<string> message;
		long int delay;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
