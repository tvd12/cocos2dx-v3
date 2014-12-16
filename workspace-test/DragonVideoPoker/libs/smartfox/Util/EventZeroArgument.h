// ===================================================================
//
// Description		
//		Contains the definition of an event that fires up callbacks 
//		without parameters
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __EventZeroArgument__
#define __EventZeroArgument__

#include "DelegateZeroArgument.h"	// Delegate without parameters

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Event definition
	// -------------------------------------------------------------------
	class EventZeroArgument
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Operator +=
		// Customizes the operator += 
		//		delegate	The delegate that must be added at the collection
		//					of callbacks to notify when event is fired up
		// Return: the event itself
		// -------------------------------------------------------------------
		EventZeroArgument & operator += (DelegateZeroArgument const & delegate)
		{
			// Add delegate into collection of event's delegates
			delegates.push_back(&((DelegateZeroArgument&)delegate));

			return *this;
		}

		// Operator -=
		// Customizes the operator -= 
		//		delegate	The delegate that must be removed from the collection
		//					of callbacks to notify when event is fired up
		// Return: the event itself
		// -------------------------------------------------------------------
		EventZeroArgument & operator -= (DelegateZeroArgument const & delegate)
		{
			// Enumerate all delegates to find the delegate to remove
			vector<boost::shared_ptr<DelegateZeroArgument> >::iterator it;

			for (it = delegates.begin() ; it < delegates.end(); it++)
			{
				if ((*it) == &delegate)
				{
					// Remove required delegate
					delegates.erase(it);
					break;
				}
			}

			return *this;
		}

		// Fireup
		// Invokes all registered delegates to notify the event activation 
		void Fireup()
		{
			// Enumerate all registered delegates
			vector<boost::shared_ptr<DelegateZeroArgument> >::iterator it;

			for (it = delegates.begin() ; it < delegates.end(); it++)
			{
				// Invoke a delegate
				boost::shared_ptr<DelegateZeroArgument> delegate = (*it);
				delegate->Invoke();
			}
		}

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

		vector<boost::shared_ptr<DelegateZeroArgument> > delegates;	// Collection of delegates registered for the event
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
