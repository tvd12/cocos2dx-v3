// ===================================================================
//
// Description		
//		Contains the definition of HandshakeRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __HandshakeRequest__
#define __HandshakeRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This request is used by the API sub-system at connection time. It's not intended for other uses.
	/// </summary>
	class DLLImportExport HandshakeRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		HandshakeRequest(string apiVersion, string reconnectionToken, string clientDetails);
		virtual ~HandshakeRequest();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_SESSION_TOKEN;
		static boost::shared_ptr<string> KEY_API;
		static boost::shared_ptr<string> KEY_COMPRESSION_THRESHOLD;
		static boost::shared_ptr<string> KEY_RECONNECTION_TOKEN;
		static boost::shared_ptr<string> KEY_CLIENT_TYPE;
		static boost::shared_ptr<string> KEY_MAX_MESSAGE_SIZE;

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
