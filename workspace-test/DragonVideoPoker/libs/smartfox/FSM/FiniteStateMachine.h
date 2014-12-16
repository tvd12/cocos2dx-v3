// ===================================================================
//
// Description		
//		Contains the definition of FiniteStateMachine 
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __FiniteStateMachine__
#define __FiniteStateMachine__

#include "FSMState.h"
#include "../Core/SynchronizationObject.h"
#include "../Util/DelegateTwoArguments.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

// STL library settings
#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>					// STL library: list object
#include <vector>				// STL library: vector object
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Core;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace FSM {

	// -------------------------------------------------------------------
	// Class FiniteStateMachine
	// -------------------------------------------------------------------
	class FiniteStateMachine
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Definition of delegates 
		// -------------------------------------------------------------------
		typedef DelegateTwoArguments<long int, long int> OnStateChangeDelegate;

		// Constructor
		FiniteStateMachine();

		// Destructor
		~FiniteStateMachine();

		void AddState(long int st);
		void AddAllStates(std::vector<long int>& states);
		void AddStateTransition (long int from, long int to, long int tr);
		long int ApplyTransition (long int tr);
		long int GetCurrentState();
		void SetCurrentState (long int state);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		boost::shared_ptr<OnStateChangeDelegate> onStateChange;

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

		boost::shared_ptr<FSMState> FindStateObjByName (long int st);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<list<boost::shared_ptr<FSMState> > > states;
		volatile long int currentStateName;
		boost::shared_ptr<SynchronizationObject> locker;
	};

}	// namespace FSM
}	// namespace Sfs2X

#endif
