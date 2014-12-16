// ===================================================================
//
// Description		
//		Contains the definition of LoggerEvent 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LoggerEvent__
#define __LoggerEvent__

#include "../Core/BaseEvent.h"
#include "LogLevel.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

// STL library settings
#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Core;

namespace Sfs2X {
namespace Logging {

	// -------------------------------------------------------------------
	// Class LoggerEvent
	// -------------------------------------------------------------------
	class DLLImportExport LoggerEvent : public BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		LoggerEvent(LogLevel level, boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters);
		~LoggerEvent();
		static boost::shared_ptr<string> LogEventType(LogLevel level);
		boost::shared_ptr<string> ToString();
		boost::shared_ptr<void> Clone();

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
		LogLevel level;
	};

}	// namespace Logging
}	// namespace Sfs2X

#endif
