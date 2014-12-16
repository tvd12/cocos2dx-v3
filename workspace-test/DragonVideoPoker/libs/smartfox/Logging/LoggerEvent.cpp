// ===================================================================
//
// Description		
//		Contains the implementation of LoggerEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "LoggerEvent.h"
#include <stdio.h>

namespace Sfs2X {
namespace Logging {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LoggerEvent::LoggerEvent(LogLevel level, boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters)
	: BaseEvent(LoggerEvent::LogEventType(level), parameters)
{
	this->level = level;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
LoggerEvent::~LoggerEvent()
{
}

// -------------------------------------------------------------------
// LogEventType
// -------------------------------------------------------------------
boost::shared_ptr<string> LoggerEvent::LogEventType(LogLevel level)
{
	char buffer[100];
	sprintf (buffer, "LOG_%d", level);

	return boost::shared_ptr<string>(new string(buffer));
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> LoggerEvent::ToString()
{
	char buffer[100];
	sprintf (buffer, "LoggerEvent %s", type->c_str());

	return boost::shared_ptr<string>(new string (buffer));
}

// -------------------------------------------------------------------
// Clone
// -------------------------------------------------------------------
boost::shared_ptr<void> LoggerEvent::Clone()
{
	return boost::shared_ptr<void>(new LoggerEvent(level, this->arguments));
}

}	// namespace Logging
}	// namespace Sfs2X
