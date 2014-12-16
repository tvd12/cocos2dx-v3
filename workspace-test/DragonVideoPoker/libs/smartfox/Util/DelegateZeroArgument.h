// ===================================================================
//
// Description		
//		Contains the definition of a delegate without parameters
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __DelegateZeroArgument__
#define __DelegateZeroArgument__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Delegate definition
	// -------------------------------------------------------------------
	class DelegateZeroArgument
	{
	public:
		
		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		// Creates and initializes an instance of this class
		//		A pointer to a function without parameters that returns a void
		//		It is the callback wrapped by this delegate
		//
		//		context		An optional context
		DelegateZeroArgument(void (*function)(unsigned long long), unsigned long long context)
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
		void Invoke()
		{
			function(context);
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

		void (*function)(unsigned long long);					// A pointer to a function without parameters that returns a void. It is the callback wrapped by this delegate
		unsigned long long context;								// An optional context
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
