// ===================================================================
//
// Description		
//		Contains the definition of SFSErrorCodes
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSErrorCodes__
#define __SFSErrorCodes__

#include "./Common.h"
#include "../Logging/Logger.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Logging;

namespace Sfs2X {
namespace Util {

	/// <summary>
	/// Provides a mean of translation between Server error codes and their relative error messages.
	/// </summary>
	/// <remarks>
	/// Error messages are provided by default in the English language but they can be localized and substituted in any other language.
    /// <para/>
	/// The error messages contain special placeholders that are processed at runtime and substituted with runtime data. They are in the form of a number enclosed in curly brackets such as: {0}, {1} etc... 
    /// <para/>
    /// Please be sure to maintain these placeholders while translating the messages. 
	/// </remarks>
	/* static */ class DLLImportExport SFSErrorCodes
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> GetErrorMessage(long int code, boost::shared_ptr<Logger> log, boost::shared_ptr<vector<string> > args); 
		static void SetErrorMessage(long int code, string message);

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
		static string* errorsByCode[];
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
