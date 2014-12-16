// ===================================================================
//
// Description		
//		Contains the definition of EventDispatcher
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __EventDispatcher__
#define __EventDispatcher__

#include "DelegateOneArgument.h"	// Delegate with one parameter
#include "../Core/BaseEvent.h"
#include "../Core/SFSEvent.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Core;

namespace Sfs2X {
namespace Util {

	typedef DelegateOneArgument<boost::shared_ptr<BaseEvent> > EventListenerDelegate;

	// -------------------------------------------------------------------
	// Class EventDispatcher
	// -------------------------------------------------------------------
	class EventDispatcher
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		EventDispatcher(boost::shared_ptr<void> target);
		void AddEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);
		void RemoveEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);
		void DispatchEvent(boost::shared_ptr<BaseEvent> evt);
		void RemoveAll();

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
		bool FilterEvent(boost::shared_ptr<BaseEvent> evt);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<void> target;
		map<string, boost::shared_ptr<EventListenerDelegate> > listeners;
		string lastDispatchedEvent;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
