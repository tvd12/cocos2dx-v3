// ===================================================================
//
// Description		
//		Contains the definition of a delegate that accepts one parameter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __DelegateOneArgument__
#define __DelegateOneArgument__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Delegate definition
	// -------------------------------------------------------------------
	template<class type> class DelegateOneArgument
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		// Creates and initializes an instance of this class
		//		A pointer to a function that accepts one parameter and returns a void
		//		It is the callback wrapped by this delegate
		//
		//		context		An optional context
		DelegateOneArgument(void (*function)(unsigned long long, type), unsigned long long context)
		{
			// Preserve input parameter as delegate function 
			this->function = function;

			// Preserve optional context
			this->context = context;
		}

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		// Invoke
		// Invoke delegate
		//		value	delegate parameter
		void Invoke(type value)
		{
			function(context, value);
		}

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

		void (*function)(unsigned long long, type);					// A pointer to a function that accepts one parameter and returns a void. It is the callback wrapped by this delegate
		unsigned long long context;									// An optional context
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
