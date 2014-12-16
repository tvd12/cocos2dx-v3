// ===================================================================
//
// Description		
//		Contains the definition of Logger 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Logger__
#define __Logger__

namespace Sfs2X {
namespace Logging {
	class Logger;
}	// namespace Logging
}	// namespace Sfs2X

#include "LogLevel.h"
#include "LoggerEvent.h"
#include "../SmartFox.h"
#include "../Util/EventDispatcher.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

// STL library settings
#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <vector>				// STL library: vector object
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Logging {

	// -------------------------------------------------------------------
	// Class Logger
	// -------------------------------------------------------------------
	class Logger
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		Logger(boost::shared_ptr<SmartFox> smartFox);

		bool EnableConsoleTrace();
		void EnableConsoleTrace(bool value);

		bool EnableEventDispatching();
		void EnableEventDispatching(bool value);

		LogLevel LoggingLevel();
		void LoggingLevel(LogLevel value);

		void Debug(boost::shared_ptr<std::vector<string> > messages);
		void Info(boost::shared_ptr<std::vector<string> > messages);
		void Warn(boost::shared_ptr<std::vector<string> > messages);
		void Error(boost::shared_ptr<std::vector<string> > messages);

		void AddEventListener(LogLevel level, boost::shared_ptr<EventListenerDelegate> listener);

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

		void Log(LogLevel level, boost::shared_ptr<string> message);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<SmartFox> smartFox;
		LogLevel loggingLevel;
		bool enableConsoleTrace;
		bool enableEventDispatching; 
	};
}	// namespace Logging
}	// namespace Sfs2X

#endif
