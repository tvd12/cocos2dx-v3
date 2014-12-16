// ===================================================================
//
// Description		
//		Contains the definition of GoOnlineRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __GoOnlineRequest__
#define __GoOnlineRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Exceptions/SFSValidationError.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {
namespace Buddylist {

	/// <summary>
	/// Toggles the Buddy ONLINE status of the User.
	/// </summary>
	/// <remarks>
	/// All clients who have the current User as their Buddy in the BuddyList, will see his status change accordingly.
	/// Going online/offline as Buddy doesn't affect the User connection,the currently joined Zone/Rooms etc... 
	/// 
	/// The ONLINE status is maintained by a reserved and persistent BuddyVariable.
	/// </remarks>
	/// 
	/// <seealso cref="Entities.Variables.SFSBuddyVariable"/>
    /// <seealso cref="Entities.Variables.ReservedBuddyVariables"/>
	class DLLImportExport GoOnlineRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="online">
		/// the Buddy Online status
		/// </param>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ONLINE_STATE_UPDATE"/>
		/// <seealso cref="Core.SFSBuddyEvent.BUDDY_ERROR"/>
		GoOnlineRequest(bool online);

		virtual ~GoOnlineRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute(boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_ONLINE;

		static boost::shared_ptr<string> KEY_BUDDY_NAME;

		static boost::shared_ptr<string> KEY_BUDDY_ID;

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
		bool online;
	};

}	// namespace Buddylist
}	// namespace Requests
}	// namespace Sfs2X

#endif
