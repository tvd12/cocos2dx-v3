// ===================================================================
//
// Description		
//		Contains the definition of SetMMOItemVariables
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __SetMMOItemVariables__
#define __SetMMOItemVariables__

#include "../../Util/Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {
namespace MMO {

	// -------------------------------------------------------------------
	// Class SetMMOItemVariables
	// -------------------------------------------------------------------
	class DLLImportExport SetMMOItemVariables
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SetMMOItemVariables();
		virtual ~SetMMOItemVariables();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_ROOM_ID;
		static boost::shared_ptr<string> KEY_ITEM_ID;
		static boost::shared_ptr<string> KEY_VAR_LIST;

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

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X

#endif
