// ===================================================================
//
// Description		
//		Contains the definition of an event that fires up callbacks 
//		with two parameters
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __EventTwoArguments__
#define __EventTwoArguments__

#include "DelegateTwoArguments.h"		// Delegate with two parameters

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
	template<class type1, class type2> class EventTwoArguments
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
		EventTwoArguments & operator += (DelegateTwoArguments<type1, type2> const & delegate)
		{
			// Add delegate into collection of event's delegates
			delegates.push_back(&((DelegateTwoArguments<type1, type2>&)delegate));

			return *this;
		}

		// Operator -=
		// Customizes the operator -= 
		//		delegate	The delegate that must be removed from the collection
		//					of callbacks to notify when event is fired up
		// Return: the event itself
		EventTwoArguments & operator -= (DelegateTwoArguments<type1, type2> const & delegate)
		{
			// Enumerate all delegates to find the delegate to remove
			vector<boost::shared_ptr<DelegateTwoArguments<type1, type2> > >::iterator it;

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
		//		value1	Value used as first parameter for callback
		//		value2	Value used as second parameter for callback
		void Fireup(type1 value1, type2 value2)
		{
			// Enumerate all registered delegates
			vector<boost::shared_ptr<DelegateTwoArguments<type1, type2> > >::iterator it;

			for (it = delegates.begin() ; it < delegates.end(); it++)
			{
				// Invoke a delegate
				boost::shared_ptr<DelegateTwoArguments<type1, type2> > delegate = (*it);
				delegate->Invoke(value1, value2);
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

		boost::shared_ptr<vector<DelegateTwoArguments<type1, type2> > > delegates;	// Collection of delegates registered for the event
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
