// ===================================================================
//
// Description		
//		Contains the definition of a delegate that accepts three parameters
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#ifndef __DelegateThreeArguments__
#define __DelegateThreeArguments__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Delegate definition
	// -------------------------------------------------------------------
	template<class type1, class type2, class type3> class DelegateThreeArguments
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		// Creates and initializes an instance of this class
		//		A pointer to a function that accepts three parameters and returns a void
		//		It is the callback wrapped by this delegate
		//
		//		context		An optional context
		DelegateThreeArguments(void (*function)(unsigned long long, type1, type2, type3), unsigned long long context)
		{
			// Preserve input parameter as delegate function 
			this->function = function;

			// Preserve optional context
			this->context = context;
		}

		// Invoke
		// Invoke delegate
		//		value1	delegate first parameter
		//		value2	delegate second parameter
		//		value3	delegate third parameter
		//
		void Invoke(type1 value1, type2 value2, type3 value3)
		{
			function(context, value1, value2, value3);
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

		void (*function)(unsigned long long, type1, type2, type3);				// A pointer to a function that accepts three parameters and returns a void. It is the callback wrapped by this delegate
		unsigned long long context;												// An optional context
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
