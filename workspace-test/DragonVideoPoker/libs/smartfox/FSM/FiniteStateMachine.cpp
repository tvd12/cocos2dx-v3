// ===================================================================
//
// Description		
//		Contains the implementation of FiniteStateMachine
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "FiniteStateMachine.h"
#include "../Core/Sockets/TCPSocketLayer.h"

using namespace Sfs2X::Core::Sockets;

namespace Sfs2X {
namespace FSM {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FiniteStateMachine::FiniteStateMachine ()
{
	currentStateName = 0;
	onStateChange = boost::shared_ptr<OnStateChangeDelegate>();
	states = boost::shared_ptr<list<boost::shared_ptr<FSMState> > >(new list<boost::shared_ptr<FSMState> >());
	locker = boost::shared_ptr<SynchronizationObject>(new SynchronizationObject());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
FiniteStateMachine::~FiniteStateMachine()
{
	if (states != NULL)
	{
		states->clear();
	}
}

// -------------------------------------------------------------------
// AddState
// -------------------------------------------------------------------
void FiniteStateMachine::AddState(long int st)
{
	boost::shared_ptr<FSMState> state (new FSMState());
	state->SetStateName(st);
	states->push_back(state);
}

// -------------------------------------------------------------------
// AddAllStates
// -------------------------------------------------------------------
void FiniteStateMachine::AddAllStates (std::vector<long int>& states)
{
	vector<long int>::iterator it;

	for (it = states.begin() ; it < states.end(); it++)
	{
		AddState(*it);
	}
}

// -------------------------------------------------------------------
// AddStateTransition
// -------------------------------------------------------------------
void FiniteStateMachine::AddStateTransition (long int from, long int to, long int tr)
{
	boost::shared_ptr<FSMState> state = FindStateObjByName (from);
	state->AddTransition (tr, to);
}

// -------------------------------------------------------------------
// ApplyTransition
// -------------------------------------------------------------------
long int FiniteStateMachine::ApplyTransition (long int tr)
{
	locker->lock();
					
	long int startStateName = currentStateName;
	currentStateName = FindStateObjByName(currentStateName)->ApplyTransition (tr);

	if (startStateName != currentStateName) 
	{
		if (onStateChange != NULL) 
		{
			onStateChange->Invoke(startStateName, currentStateName);
		}
	}

	locker->unlock();

	return currentStateName;
}

// -------------------------------------------------------------------
// GetCurrentState
// -------------------------------------------------------------------
long int FiniteStateMachine::GetCurrentState()
{
	locker->lock();

	long int valueToReturn = currentStateName;

	locker->unlock();

	return valueToReturn;
}

// -------------------------------------------------------------------
// SetCurrentState
// -------------------------------------------------------------------
void FiniteStateMachine::SetCurrentState (long int state)
{
	if (onStateChange != NULL) 
	{
		onStateChange->Invoke(currentStateName, state);
	}
	
	currentStateName = state;
}

// -------------------------------------------------------------------
// SetCurrentState
// -------------------------------------------------------------------
boost::shared_ptr<FSMState> FiniteStateMachine::FindStateObjByName (long int st)
{
	list<boost::shared_ptr<FSMState> >::iterator iterator;

	for (iterator = states->begin(); iterator != states->end(); iterator++)
	{
		boost::shared_ptr<FSMState> state = (*iterator);
		if (st == state->GetStateName())
		{
			return state;
		}
	}

	return boost::shared_ptr<FSMState>();
}

}	// namespace FSM
}	// namespace Sfs2X
