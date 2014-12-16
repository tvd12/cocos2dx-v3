// ===================================================================
//
// Description		
//		Contains the definition of ManualDisconnectionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ManualDisconnectionRequest__
#define __ManualDisconnectionRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../SmartFox.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

using namespace Sfs2X;
//using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This is used by the system. Never send this directly.
	/// </summary>
	class DLLImportExport ManualDisconnectionRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		ManualDisconnectionRequest();
		virtual ~ManualDisconnectionRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);
		void Execute(boost::shared_ptr<SmartFox> sfs);

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
