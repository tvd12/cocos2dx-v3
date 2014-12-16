// ===================================================================
//
// Description		
//		Contains the definition of BanUserRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BanUserRequest__
#define __BanUserRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "BanMode.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Banish a User from the system (for moderators and admins only)
	/// </summary>
	/// <remarks>
	/// Allows to send a custom message and to set a delay in seconds. It also allows to choose banning by user name or user IP address
	/// </remarks>
	class DLLImportExport BanUserRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// <see cref="BanUserRequest(long int, string, BanMode, long int, long int)"/>
		/// </summary>
		BanUserRequest(long int userId);

		/// <summary>
		/// <see cref="BanUserRequest(long int, string, BanMode, long int, long int)"/>
		/// </summary>
		BanUserRequest(long int userId, string message);

		/// <summary>
		/// <see cref="BanUserRequest(long int, string, BanMode, long int, long int)"/>
		/// </summary>
		BanUserRequest(long int userId, string message, BanMode banMode);

		/// <summary>
		/// <see cref="BanUserRequest(long int, string, BanMode, long int, long int)"/>
		/// </summary>
		BanUserRequest(long int userId, string message, BanMode banMode, long int delaySeconds);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="userId">
		/// the id of the User to be banned
		/// </param>
		/// <param name="message">
		/// a custom ban message, if null the message configured on the server side will be used
		/// </param>
		/// <param name="banMode">
		/// choose between banning by Ip Address or User name, see {@link BanMode}� class
		/// </param>
		/// <param name="delaySeconds">
		/// a delay in seconds between the message (immediate) and the kick (delayed). Default is 5 seconds
		/// </param>
		/// <param name="durationHours">
		/// The duration of the banishment, expressed in hours.
		/// </param>
		/// <example>
		///		\code{.cpp}
		///			boost::shared_ptr<User> userToBan = ptrSmartFox->UserManager()->GetUserByName("Waldorf"); 
		///
		/// 		// Ban client by name, using default message configured on server side and default delay time (== 5sec)
		///			boost::shared_ptr<IRequest> request (new BanUserRequest(userToBan)); 
		///			ptrSmartFox->Send(request);
		///		\endcode
		///	</example>
		BanUserRequest(long int userId, string message, BanMode banMode, long int delaySeconds, long int durationHours);

		virtual ~BanUserRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_USER_ID;
		
		static boost::shared_ptr<string> KEY_MESSAGE;

		static boost::shared_ptr<string> KEY_DELAY;
		
		static boost::shared_ptr<string> KEY_BAN_MODE;
		
		static boost::shared_ptr<string> KEY_BAN_DURATION_HOURS;		

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
		void Init(long int userId, string message, BanMode banMode, long int delaySeconds, long int durationHours);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		long int userId;		
		boost::shared_ptr<string> message;
		long int delay;
		BanMode banMode;
		long int durationHours;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
