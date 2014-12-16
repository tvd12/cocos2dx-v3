// ===================================================================
//
// Description		
//		Contains the implementation of Logger
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "Logger.h"

namespace Sfs2X {
namespace Logging {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Logger::Logger(boost::shared_ptr<SmartFox> smartFox) 
{
	enableConsoleTrace = true;
	enableEventDispatching = true; 
	this->smartFox = smartFox;
	loggingLevel = LOGLEVEL_INFO;
}

// -------------------------------------------------------------------
// EnableConsoleTrace
// -------------------------------------------------------------------
bool Logger::EnableConsoleTrace()
{
	return enableConsoleTrace;
}

// -------------------------------------------------------------------
// EnableConsoleTrace
// -------------------------------------------------------------------
void Logger::EnableConsoleTrace(bool value)
{
	enableConsoleTrace = value;
}

// -------------------------------------------------------------------
// EnableEventDispatching
// -------------------------------------------------------------------
bool Logger::EnableEventDispatching()
{
	return enableEventDispatching;
}

// -------------------------------------------------------------------
// EnableEventDispatching
// -------------------------------------------------------------------
void Logger::EnableEventDispatching(bool value)
{
	enableEventDispatching = value;
}

// -------------------------------------------------------------------
// LoggingLevel
// -------------------------------------------------------------------
LogLevel Logger::LoggingLevel()
{
	return loggingLevel;
}

// -------------------------------------------------------------------
// LoggingLevel
// -------------------------------------------------------------------
void Logger::LoggingLevel(LogLevel value)
{
	loggingLevel = value;
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
void Logger::Debug(boost::shared_ptr<std::vector<string> > messages) 
{ 
	boost::shared_ptr<std::string> log (new string());

	// Concatenate messages
    std::vector<string>::const_iterator iterator;    
	for(iterator = messages->begin(); iterator != messages->end(); ++iterator)
	{   
		if (log->size() > 0)
		{
			log->append(" ");
		}

		log->append(*iterator);
	}

	Log (LOGLEVEL_DEBUG, log);
}

// -------------------------------------------------------------------
// Info
// -------------------------------------------------------------------
void Logger::Info(boost::shared_ptr<std::vector<string> > messages) 
{ 
	boost::shared_ptr<std::string> log (new string());

	// Concatenate messages
    std::vector<string>::const_iterator iterator;    
	for(iterator = messages->begin(); iterator != messages->end(); ++iterator)
	{   
		if (log->size() > 0)
		{
			log->append(" ");
		}

		log->append(*iterator);
	}

	Log (LOGLEVEL_INFO, log);
}

// -------------------------------------------------------------------
// Warn
// -------------------------------------------------------------------
void Logger::Warn(boost::shared_ptr<std::vector<string> > messages) 
{ 
	boost::shared_ptr<std::string> log (new string());

	// Concatenate messages
    std::vector<string>::const_iterator iterator;    
	for(iterator = messages->begin(); iterator != messages->end(); ++iterator)
	{   
		if (log->size() > 0)
		{
			log->append(" ");
		}

		log->append(*iterator);
	}

	Log (LOGLEVEL_WARN, log);
}

// -------------------------------------------------------------------
// Error
// -------------------------------------------------------------------
void Logger::Error(boost::shared_ptr<std::vector<string> > messages) 
{
	boost::shared_ptr<std::string> log (new string());

	// Concatenate messages
    std::vector<string>::const_iterator iterator;    
	for(iterator = messages->begin(); iterator != messages->end(); ++iterator)
	{   
		if (log->size() > 0)
		{
			log->append(" ");
		}

		log->append(*iterator);
	}

	Log (LOGLEVEL_ERROR, log);
}

// -------------------------------------------------------------------
// Log
// -------------------------------------------------------------------
void Logger::Log(LogLevel level, boost::shared_ptr<string> message)
{
	if ((int)level < (int)loggingLevel) 
	{
		return; 
	}

	if (enableConsoleTrace) 
	{
	//	Console.WriteLine("[SFS - " + level + "] "+message);
	}

	// Dispatch event
	if (enableEventDispatching && smartFox != NULL) 
	{
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > parameters (new map<string, boost::shared_ptr<void> >());
		parameters->insert(std::pair<string, boost::shared_ptr<void> >("message", message));
		boost::shared_ptr<LoggerEvent> evt (new LoggerEvent(loggingLevel, parameters));
		smartFox->DispatchEvent(evt);
	}
}

// -------------------------------------------------------------------
// AddEventListener
// -------------------------------------------------------------------
void Logger::AddEventListener(LogLevel level, boost::shared_ptr<EventListenerDelegate> listener)
{
	if (smartFox == NULL) return;
	smartFox->AddEventListener(LoggerEvent::LogEventType(level), listener);
}

}	// namespace Logging
}	// namespace Sfs2X
