// ===================================================================
//
// Description		
//		Helper class for logging in with a pre-hashed password
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PasswordUtil__
#define __PasswordUtil__

#include "./Common.h"

#include <stdio.h>
#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {
	
	/// <summary>
	/// Helper class for logging in with a pre-hashed password
	/// </summary>
	/// <remarks>
	/// This is needed if your server-side database stores User passwords hashed with MD5.
	/// For more information see the <see href="http://docs2x.smartfoxserver.com/DevelopmentBasics/signup-assistant-basics" target="_blank">Sign Up Assistant component tutorial</see> (<b>Password Mode</b> section).
	/// </remarks>
	class DLLImportExport PasswordUtil
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Generates the MD5 hash of the user password.
		/// </summary>
		/// 
		/// <param name="pass">The plain text password.</param>
		/// 
		/// <returns>The hashed password.</returns>
		/// 
		/// <example>
		///			\code{.cpp}
		///				string userName = "testName";
		///				string userPass = "testPass";
		///				
		///				boost::shared_ptr<string> md5Pass = PasswordUtil.MD5Password(userPass);
		///				boost::shared_ptr<IRequest> request (new LoginRequest(userName, *md5Pass)); 
		///				ptrSmartFox->Send(request);
		/// 		\endcode
		/// </example>
		static boost::shared_ptr<string> MD5Password(string pass);

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

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
