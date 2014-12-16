#ifndef __LogLevel__
#define __LogLevel__

namespace Sfs2X {
namespace Logging {

	// Summary:
    //     Defines log levels 
    typedef enum LogLevel 
    {
		LOGLEVEL_DEBUG = 100,
		LOGLEVEL_INFO = 200,
		LOGLEVEL_WARN = 300,
		LOGLEVEL_ERROR = 400
	};

}	// namespace Logging
}	// namespace Sfs2X

#endif
