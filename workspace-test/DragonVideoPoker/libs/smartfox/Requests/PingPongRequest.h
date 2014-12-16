// ===================================================================
//
// Description		
//		Contains the definition of PingPongRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PingPongRequest__
#define __PingPongRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Sends a ping-pong request in order to measure the current lag
	/// </summary>
	class DLLImportExport PingPongRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		PingPongRequest ();
		virtual ~PingPongRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

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

}	// namespace Requests
}	// namespace Sfs2X

#endif

