// ===================================================================
//
// Description		
//		Contains the implementation of FSMState
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "FSMState.h"
#include <stddef.h>

namespace Sfs2X {
namespace FSM {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FSMState::FSMState ()
{
	transitions = boost::shared_ptr<map<long int, long int> >(new map<long int, long int>());
	transitions->clear();
	stateName = 0;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
FSMState::~FSMState()
{
	transitions->clear();
}

// -------------------------------------------------------------------
// SetStateName
// -------------------------------------------------------------------
void FSMState::SetStateName(long int newStateName)
{
	stateName = newStateName;
}

// -------------------------------------------------------------------
// GetStateName
// -------------------------------------------------------------------
long int FSMState::GetStateName()
{
	return stateName;
}

// -------------------------------------------------------------------
// AddTransition
// -------------------------------------------------------------------
void FSMState::AddTransition(long int transition, long int outputState)
{
	this->transitions->insert(pair<long int, long int> (transition, outputState));
}

// -------------------------------------------------------------------
// ApplyTransition
// -------------------------------------------------------------------
long int FSMState::ApplyTransition(long int transition)
{
	// Default to no change in state
	long int outputStateName = stateName;

	map<long int, long int>::iterator iterator = this->transitions->find(transition);
	if (iterator != this->transitions->end())
	{
		outputStateName = iterator->second;
	}

	return outputStateName;
}

}	// namespace FSM
}	// namespace Sfs2X
