// ===================================================================
//
// Description		
//		Contains the implemenetation of EventDispatcher
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "EventDispatcher.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
EventDispatcher::EventDispatcher(boost::shared_ptr<void> target)
{
	this->target = target;
	this->lastDispatchedEvent = "";
}

// -------------------------------------------------------------------
// AddEventListener
// -------------------------------------------------------------------
void EventDispatcher::AddEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	listeners.insert(std::pair<string, boost::shared_ptr<EventListenerDelegate> >(*eventType, listener));
}

// -------------------------------------------------------------------
// RemoveEventListener
// -------------------------------------------------------------------
void EventDispatcher::RemoveEventListener(boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	map<string, boost::shared_ptr<EventListenerDelegate> >::iterator iterator;
	iterator = listeners.find(*eventType);
	if (iterator != listeners.end())
	{
		listeners.erase (iterator); 
	}
}

// -------------------------------------------------------------------
// DispatchEvent
// -------------------------------------------------------------------
void EventDispatcher::DispatchEvent(boost::shared_ptr<BaseEvent> evt)
{
	map<string, boost::shared_ptr<EventListenerDelegate> >::iterator iterator;
	iterator = listeners.find(*(evt->Type()));

	if (iterator != listeners.end())
	{
		if (FilterEvent(evt) == true)
		{
			return;
		}

		evt->Target(target);
		(*iterator).second->Invoke(evt);

		lastDispatchedEvent = *(evt->Type());
	}
}

// -------------------------------------------------------------------
// FilterEvent
// -------------------------------------------------------------------
bool EventDispatcher::FilterEvent(boost::shared_ptr<BaseEvent> evt)
{
	if (*evt->Type() != lastDispatchedEvent)
	{
		return false;
	}

	// Filter duplicated "connection lost" events 
	// (for instance when connection is idle, this event is triggered from both server application message and socket falldown)
	if (evt->Type() == SFSEvent::CONNECTION_LOST)
	{
		return true;
	}

	return false;
}

// -------------------------------------------------------------------
// RemoveAll
// -------------------------------------------------------------------
void EventDispatcher::RemoveAll()
{
	listeners.clear();
}


}	// namespace Util
}	// namespace Sfs2X
