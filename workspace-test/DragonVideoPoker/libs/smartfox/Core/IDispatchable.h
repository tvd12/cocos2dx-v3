// ===================================================================
//
// Description		
//		Contains the definition of IDispatchable interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IDispatchable__
#define __IDispatchable__

#include "../Util/EventDispatcher.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {

	// -------------------------------------------------------------------
	// Interface IDispatchable
	// -------------------------------------------------------------------
	class IDispatchable
	{
	public:
		virtual boost::shared_ptr<EventDispatcher> Dispatcher() = 0;
		virtual void AddEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener) = 0;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
