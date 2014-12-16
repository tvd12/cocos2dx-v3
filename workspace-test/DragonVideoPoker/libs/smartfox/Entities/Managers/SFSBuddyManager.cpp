// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddyManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddyManager.h"
#include "../Variables/ReservedBuddyVariables.h"
#include "../Variables/SFSBuddyVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyManager::SFSBuddyManager(boost::shared_ptr<SmartFox> sfs)
{
	this->sfs = sfs;
	buddiesByName = boost::shared_ptr<map<string, boost::shared_ptr<Buddy> > >(new map<string, boost::shared_ptr<Buddy> >());
	myVariables = boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > >(new map<string, boost::shared_ptr<BuddyVariable> >());
	inited = false;
	buddyStates = boost::shared_ptr<vector<string> >();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSBuddyManager::~SFSBuddyManager()
{
	buddiesByName->clear();
	myVariables->clear();
}

// -------------------------------------------------------------------
// Inited
// -------------------------------------------------------------------
bool SFSBuddyManager::Inited()
{
	return inited;
}

// -------------------------------------------------------------------
// Inited
// -------------------------------------------------------------------
void SFSBuddyManager::Inited(bool value)
{
	inited = value;
}

// -------------------------------------------------------------------
// AddBuddy
// -------------------------------------------------------------------
void SFSBuddyManager::AddBuddy(boost::shared_ptr<Buddy> buddy)
{
	buddiesByName->insert(pair<string, boost::shared_ptr<Buddy> >(*buddy->Name(), buddy));
}

// -------------------------------------------------------------------
// ClearAll
// -------------------------------------------------------------------
void SFSBuddyManager::ClearAll()
{
	buddiesByName->clear();
}

// -------------------------------------------------------------------
// RemoveBuddyById
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::RemoveBuddyById(long int id)
{
	boost::shared_ptr<Buddy> buddy = GetBuddyById(id);

	if (buddy != NULL) {
		map<string, boost::shared_ptr<Buddy> >::iterator itrBuddy = buddiesByName->find(*buddy->Name());
		if (itrBuddy != buddiesByName->end())
		{
			buddiesByName->erase(itrBuddy);
		}
	}

	return buddy;
}

// -------------------------------------------------------------------
// RemoveBuddyByName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::RemoveBuddyByName(string name)
{
	boost::shared_ptr<Buddy> buddy = GetBuddyByName(name);

	if (buddy != NULL) {
		map<string, boost::shared_ptr<Buddy> >::iterator itrBuddy = buddiesByName->find(name);
		if (itrBuddy != buddiesByName->end())
		{
			buddiesByName->erase(itrBuddy);
		}
	}

	return buddy;			
}

// -------------------------------------------------------------------
// GetBuddyById
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::GetBuddyById(long int id)
{
	if (id > -1) {	
		std::map<string, boost::shared_ptr<Buddy> >::iterator iteratorBuddies;
		for (iteratorBuddies = buddiesByName->begin(); iteratorBuddies != buddiesByName->end(); iteratorBuddies++)
		{
			boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
			if (buddy->Id() == id)
				return buddy;
		}
	}

	return boost::shared_ptr<Buddy>();			
}

// -------------------------------------------------------------------
// ContainsBuddy
// -------------------------------------------------------------------
bool SFSBuddyManager::ContainsBuddy(string name)
{
	std::map<string, boost::shared_ptr<Buddy> >::iterator iterator = buddiesByName->find(name);

	if (iterator != buddiesByName->end())
	{
		return true;
	}

	return false;
}

// -------------------------------------------------------------------
// GetBuddyByName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::GetBuddyByName(string name)
{
	std::map<string, boost::shared_ptr<Buddy> >::iterator iterator = buddiesByName->find(name);

	if (iterator != buddiesByName->end())
	{
		return iterator->second;
	}

	return boost::shared_ptr<Buddy>();
}

// -------------------------------------------------------------------
// GetBuddyByNickName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::GetBuddyByNickName(string nickName)
{
	std::map<string, boost::shared_ptr<Buddy> >::iterator iteratorBuddies;
	for (iteratorBuddies = buddiesByName->begin(); iteratorBuddies != buddiesByName->end(); iteratorBuddies++)
	{
		boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;

		if (*(buddy->NickName()) == nickName)
			return buddy;
	}			
			
	return boost::shared_ptr<Buddy>();
}

// -------------------------------------------------------------------
// OfflineBuddies
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > SFSBuddyManager::OfflineBuddies()
{
	boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > buddies (new vector<boost::shared_ptr<Buddy> >());

	std::map<string, boost::shared_ptr<Buddy> >::iterator iteratorBuddies;
	for (iteratorBuddies = buddiesByName->begin(); iteratorBuddies != buddiesByName->end(); iteratorBuddies++)
	{
		boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
		if (!buddy->IsOnline())
			buddies->push_back(buddy);
	}

	return buddies;
}

// -------------------------------------------------------------------
// OnlineBuddies
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > SFSBuddyManager::OnlineBuddies()
{
	boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > buddies (new vector<boost::shared_ptr<Buddy> >());

	std::map<string, boost::shared_ptr<Buddy> >::iterator iteratorBuddies;
	for (iteratorBuddies = buddiesByName->begin(); iteratorBuddies != buddiesByName->end(); iteratorBuddies++)
	{
		boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
		if (buddy->IsOnline())
			buddies->push_back(buddy);
	}

	return buddies;
}

// -------------------------------------------------------------------
// BuddyList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > SFSBuddyManager::BuddyList()
{
	boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > buddies (new vector<boost::shared_ptr<Buddy> >());

	std::map<string, boost::shared_ptr<Buddy> >::iterator iteratorBuddies;
	for (iteratorBuddies = buddiesByName->begin(); iteratorBuddies != buddiesByName->end(); iteratorBuddies++)
	{
		boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
		buddies->push_back(buddy);
	}

	return buddies;
}

// -------------------------------------------------------------------
// GetMyVariable
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable> SFSBuddyManager::GetMyVariable(string varName)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator = myVariables->find(varName);

	if (iterator != myVariables->end())
	{
		return iterator->second;
	}

	return boost::shared_ptr<BuddyVariable>();
}

// -------------------------------------------------------------------
// GetMyVariable
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable> SFSBuddyManager::GetMyVariable(boost::shared_ptr<string> varName)
{
	return SFSBuddyManager::GetMyVariable(*varName);
}

// -------------------------------------------------------------------
// MyVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > SFSBuddyManager::MyVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > variables (new vector<boost::shared_ptr<BuddyVariable> >());

	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = myVariables->begin(); iterator != myVariables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> variable = iterator->second;
		variables->push_back(variable);
	}

	return variables;
}

// -------------------------------------------------------------------
// MyVariables
// -------------------------------------------------------------------
void SFSBuddyManager::MyVariables(boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > value)
{
	std::vector<boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = value->begin(); iterator != value->end(); iterator++)
	{
		SetMyVariable(*iterator);
	}
}

// -------------------------------------------------------------------
// MyOnlineState
// -------------------------------------------------------------------
bool SFSBuddyManager::MyOnlineState()
{
	// Manager not inited, we're offline
	if (!inited)
		return false;

	// If the online var is not defined we take it as online=true (default)
	bool onlineState = true;
	boost::shared_ptr<BuddyVariable> onlineVar = GetMyVariable(ReservedBuddyVariables::BV_ONLINE);

	if (onlineVar != NULL)
		onlineState = *(onlineVar->GetBoolValue());

	return onlineState;
}

// -------------------------------------------------------------------
// MyOnlineState
// -------------------------------------------------------------------
void SFSBuddyManager::MyOnlineState(bool value)
{
	boost::shared_ptr<bool> pvalue (new bool());
	*pvalue = value;
	boost::shared_ptr<BuddyVariable> variable(new SFSBuddyVariable(ReservedBuddyVariables::BV_ONLINE, pvalue, VARIABLETYPE_BOOL));
	SetMyVariable (variable);
}

// -------------------------------------------------------------------
// MyNickName
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyManager::MyNickName()
{
	boost::shared_ptr<BuddyVariable> nickNameVar = GetMyVariable(ReservedBuddyVariables::BV_NICKNAME);
	return (nickNameVar != NULL) ? nickNameVar->GetStringValue() : boost::shared_ptr<string>();
}

// -------------------------------------------------------------------
// MyNickName
// -------------------------------------------------------------------
void SFSBuddyManager::MyNickName(string value)
{
	boost::shared_ptr<string> variableValue (new string(value));
	boost::shared_ptr<BuddyVariable> variable(new SFSBuddyVariable(ReservedBuddyVariables::BV_NICKNAME, variableValue, VARIABLETYPE_STRING));
	SetMyVariable(variable);
}

// -------------------------------------------------------------------
// MyState
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyManager::MyState()
{
	boost::shared_ptr<BuddyVariable> stateVar = GetMyVariable(ReservedBuddyVariables::BV_STATE);
	return (stateVar != NULL) ? stateVar->GetStringValue() : boost::shared_ptr<string>();
}

// -------------------------------------------------------------------
// MyState
// -------------------------------------------------------------------
void SFSBuddyManager::MyState(string value)
{
	boost::shared_ptr<string> variableValue (new string(value));
	boost::shared_ptr<BuddyVariable> variable(new SFSBuddyVariable(ReservedBuddyVariables::BV_STATE, variableValue, VARIABLETYPE_STRING)),
	SetMyVariable(variable);
}

// -------------------------------------------------------------------
// BuddyStates
// -------------------------------------------------------------------
boost::shared_ptr<vector<string> > SFSBuddyManager::BuddyStates()
{
	return buddyStates;
}

// -------------------------------------------------------------------
// BuddyStates
// -------------------------------------------------------------------
void SFSBuddyManager::BuddyStates(boost::shared_ptr<vector<string> > value)
{
	buddyStates = value;
}

// -------------------------------------------------------------------
// SetMyVariable
// -------------------------------------------------------------------
void SFSBuddyManager::SetMyVariable(boost::shared_ptr<BuddyVariable> bVar)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator = myVariables->find(*bVar->Name());

	if (iterator != myVariables->end())
	{
		iterator->second = bVar;
	}
	else
	{
        myVariables->insert(std::make_pair(*bVar->Name(), bVar));
	}
}


}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X
