// ===================================================================
//
// Description		
//		Contains the definition of ClientDisconnectionReason
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ClientDisconnectionReason__
#define __ClientDisconnectionReason__

#include "../Util/Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class ClientDisconnectionReason
	// -------------------------------------------------------------------
	/* static */ class DLLImportExport ClientDisconnectionReason
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> GetReason(long int reasonId);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		/// <summary>
		/// Client was disconnected because he was idle for too long (depends on server settings)
		/// </summary>
		static boost::shared_ptr<string> IDLE;
		
		/// <summary>
		/// Client was kicked out of the server
		/// </summary>
		static boost::shared_ptr<string> KICK; 
		
		/// <summary>
		/// Client was banished from the server
		/// </summary>
		static boost::shared_ptr<string> BAN; 
		
		/// <summary>
		/// The client manually disconnected from the server
		/// </summary>
		static boost::shared_ptr<string> MANUAL; 
		
		/// <summary>
		/// A generic network error occurred, it's not possible to determine the cause of the disconnection
		/// </summary>
		static boost::shared_ptr<string> UNKNOWN;
		
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
		static string* reasons[];
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
