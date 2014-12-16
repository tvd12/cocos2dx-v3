// ===================================================================
//
// Description		
//		Contains the definition of FSMState 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __FSMState__
#define __FSMState__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

// STL library settings
#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

namespace Sfs2X {
namespace FSM {

	// -------------------------------------------------------------------
	// Class FSMState
	// -------------------------------------------------------------------
	class FSMState
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// Constructor
		FSMState();

		// Destructor
		~FSMState();

		void SetStateName(long int newStateName);
		long int GetStateName();
		void AddTransition(long int transition, long int outputState);
		long int ApplyTransition(long int transition);

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

		long int stateName;
		boost::shared_ptr<map<long int, long int> > transitions;
	};

}	// namespace FSM
}	// namespace Sfs2X

#endif
