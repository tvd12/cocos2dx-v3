// ===================================================================
//
// Description		
//		Contains the definition of an event that fires up callbacks 
//		with three parameters
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __EventThreeArguments__
#define __EventThreeArguments__

#include "DelegateThreeArguments.h"		// Delegate with three parameters

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
	template<class type1, class type2, class type3> class EventThreeArguments
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
		EventThreeArguments & operator += (DelegateThreeArguments<type1, type2, type3> const & delegate)
		{
			// Add delegate into collection of event's delegates
			delegates.push_back(&((DelegateThreeArguments<type1, type2, type3>&)delegate));

			return *this;
		}

		// Operator -=
		// Customizes the operator -= 
		//		delegate	The delegate that must be removed from the collection
		//					of callbacks to notify when event is fired up
		// Return: the event itself
		EventThreeArguments & operator -= (DelegateThreeArguments<type1, type2, type3> const & delegate)
		{
			// Enumerate all delegates to find the delegate to remove
			vector<boost::shared_ptr<DelegateThreeArguments<type1, type2, type3> > >::iterator it;

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
		//		value3	Value used as third parameter for callback
		void Fireup(type1 value1, type2 value2, type3 value3)
		{
			// Enumerate all registered delegates
			vector<boost::shared_ptr<DelegateThreeArguments<type1, type2, type3> > >::iterator it;

			for (it = delegates.begin() ; it < delegates.end(); it++)
			{
				// Invoke a delegate
				boost::shared_ptr<DelegateThreeArguments<type1, type2, type3> > delegate = (*it);
				delegate->Invoke(value1, value2, value3);
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

		vector<boost::shared_ptr<DelegateThreeArguments<type1, type2, type3> > > delegates;	// Collection of delegates registered for the event
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
