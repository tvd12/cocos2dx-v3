// ===================================================================
//
// Description		
//		Contains the definition of an event that fires up callbacks 
//		with one parameter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __EventOneArgument__
#define __EventOneArgument__

#include "DelegateOneArgument.h"		// Delegate with one parameter

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
	template<class type> class EventOneArgument
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
		EventOneArgument & operator += (DelegateOneArgument<type> const & delegate)
		{
			// Add delegate into collection of event's delegates
			delegates.push_back(&((DelegateOneArgument<type>&)delegate));

			return *this;
		}

		// Operator -=
		// Customizes the operator -= 
		//		delegate	The delegate that must be removed from the collection
		//					of callbacks to notify when event is fired up
		// Return: the event itself
		EventOneArgument & operator -= (DelegateOneArgument<type> const & delegate)
		{
			// Enumerate all delegates to find the delegate to remove
			vector<boost::shared_ptr<DelegateOneArgument<type> > >::iterator it;

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
		//		value	Value used as parameter for callback
		void Fireup(type value)
		{
			// Enumerate all registered delegates
			vector<boost::shared_ptr<DelegateOneArgument<type> > >::iterator it;

			for (it = delegates.begin() ; it < delegates.end(); it++)
			{
				// Invoke a delegate
				boost::shared_ptr<DelegateOneArgument<type> > delegate = (*it);
				delegate->Invoke(value);
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

		vector<boost::shared_ptr<DelegateOneArgument<type> > > delegates;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
