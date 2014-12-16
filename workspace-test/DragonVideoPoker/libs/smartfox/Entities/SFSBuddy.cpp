// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddy
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddy.h"
#include "./Variables/SFSBuddyVariable.h"
#include "./Variables/ReservedBuddyVariables.h"

namespace Sfs2X {
namespace Entities {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddy::FromSFSArray(boost::shared_ptr<ISFSArray> arr)
{
	boost::shared_ptr<Buddy> buddy (new SFSBuddy (
		arr->GetInt(0), 									// id
		*(arr->GetUtfString(1)), 							// name
		arr->GetBool(2),									// blocked
		arr->Size() > 4 ? arr->GetBool(4) : false			// isTemp is optional, we have to check
		));

	boost::shared_ptr<ISFSArray> bVarsData = arr->GetSFSArray(3); // variables data array

	for (int j = 0; j < bVarsData->Size(); j++) {
		boost::shared_ptr<BuddyVariable> bv = SFSBuddyVariable::FromSFSArray(bVarsData->GetSFSArray(j)); 
		buddy->SetVariable(bv);
	}

	return buddy;
}

// -------------------------------------------------------------------
// SFSBuddy
// -------------------------------------------------------------------
SFSBuddy::SFSBuddy(long int id, string name)
{
	this->id = id;
	this->name = boost::shared_ptr<string>(new string(name));
	this->isBlocked = false;
	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > >(new map<string, boost::shared_ptr<BuddyVariable> >());
	this->variables->clear();
	this->isTemp = false;
}

// -------------------------------------------------------------------
// SFSBuddy
// -------------------------------------------------------------------
SFSBuddy::SFSBuddy(long int id, string name, bool isBlocked)
{
	this->id = id;
	this->name = boost::shared_ptr<string>(new string(name));
	this->isBlocked = isBlocked;
	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > >(new map<string, boost::shared_ptr<BuddyVariable> >());
	this->variables->clear();
	this->isTemp = false;
}

// -------------------------------------------------------------------
// SFSBuddy
// -------------------------------------------------------------------
SFSBuddy::SFSBuddy(long int id, string name, bool isBlocked, bool isTemp)
{
	this->id = id;
	this->name = boost::shared_ptr<string>(new string(name));
	this->isBlocked = isBlocked;
	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > >(new map<string, boost::shared_ptr<BuddyVariable> >());
	this->variables->clear();
	this->isTemp = isTemp;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSBuddy::~SFSBuddy()
{
	variables->clear();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int SFSBuddy::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void SFSBuddy::Id(long int value)
{
	id = value;
}

// -------------------------------------------------------------------
// IsBlocked
// -------------------------------------------------------------------
bool SFSBuddy::IsBlocked()
{
	return isBlocked;
}

// -------------------------------------------------------------------
// IsBlocked
// -------------------------------------------------------------------
void SFSBuddy::IsBlocked(bool value)
{
	isBlocked = value;
}

// -------------------------------------------------------------------
// IsTemp
// -------------------------------------------------------------------
bool SFSBuddy::IsTemp()
{
	return isTemp;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddy::Name()
{
	return name;
}

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
bool SFSBuddy::IsOnline()
{
	boost::shared_ptr<BuddyVariable> bv = GetVariable(*ReservedBuddyVariables::BV_ONLINE);

	// An non-inited ONLINE state == online
	bool onlineStateVar = (bv == NULL)? true : *(bv->GetBoolValue());

	/* The buddy is considered ONLINE if 
	* 	1. he is connectected in the system
	*	2. his online variable is set to true
	*/			
	return onlineStateVar && id > -1;
}

// -------------------------------------------------------------------
// State
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddy::State()
{
	/*
	* TODO: what if state was not inited yet?
	* Do we return null or a default state?
	*/
	boost::shared_ptr<BuddyVariable> bv = GetVariable(*ReservedBuddyVariables::BV_STATE);
	return (bv == NULL) ? boost::shared_ptr<string>() : bv->GetStringValue();
}

// -------------------------------------------------------------------
// NickName
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddy::NickName()
{
	boost::shared_ptr<BuddyVariable> bv = GetVariable(*ReservedBuddyVariables::BV_NICKNAME);
	return (bv == NULL) ? boost::shared_ptr<string>() : bv->GetStringValue();
}

// -------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > SFSBuddy::Variables()
{
	boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > variables (new vector<boost::shared_ptr<BuddyVariable> >());

	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = this->variables->begin(); iterator != this->variables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> variable = iterator->second;
		variables->push_back(variable);
	}

	return variables;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable> SFSBuddy::GetVariable(string varName)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator = variables->find(varName);

	if (iterator != variables->end())
	{
		return iterator->second;
	}

	return boost::shared_ptr<BuddyVariable>();
}

// -------------------------------------------------------------------
// GetOfflineVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > SFSBuddy::GetOfflineVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > offlineVars (new vector<boost::shared_ptr<BuddyVariable> >());

	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> item = iterator->second;

		if (item->Name()->find(*SFSBuddyVariable::OFFLINE_PREFIX) == 0) {
			offlineVars->push_back(item);
		}
	}

	return offlineVars;
}

// -------------------------------------------------------------------
// GetOnlineVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > SFSBuddy::GetOnlineVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > onlineVars (new vector<boost::shared_ptr<BuddyVariable> >());

	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> item = iterator->second;

		if (item->Name()->find(*SFSBuddyVariable::OFFLINE_PREFIX) != 0) {
			onlineVars->push_back(item);
		}
	}

	return onlineVars;
}

// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool SFSBuddy::ContainsVariable(string varName)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator = variables->find(varName);

	if (iterator != variables->end())
	{
		return true;
	}

	return false;
}

// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void SFSBuddy::SetVariable(boost::shared_ptr<BuddyVariable> bVar)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator = variables->find(*bVar->Name());

	if (iterator != variables->end())
	{
		iterator->second = bVar;
	}
	else
	{
		variables->insert(pair<string, boost::shared_ptr<BuddyVariable> >(*bVar->Name(), bVar));
	}
}

// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void SFSBuddy::SetVariables(boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > variables)
{
	std::vector<boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		SetVariable(*iterator);
	}
}

// -------------------------------------------------------------------
// RemoveVariable
// -------------------------------------------------------------------
void SFSBuddy::RemoveVariable(string varName)
{
	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	iterator = variables->find(varName);

	if (iterator != variables->end())
	{
		variables->erase(iterator);
	}
}

// -------------------------------------------------------------------
// ClearVolatileVariables
// -------------------------------------------------------------------
void SFSBuddy::ClearVolatileVariables()
{
	list<string> listNamesToRemove;

	std::map<string, boost::shared_ptr<BuddyVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		boost::shared_ptr<BuddyVariable> bVar = iterator->second;
		if (bVar->Name()->find(*SFSBuddyVariable::OFFLINE_PREFIX) != 0) {
			listNamesToRemove.push_back(*(bVar->Name()));
		}
	}

	list<string>::iterator iteratorNamesToRemove;
	for (iteratorNamesToRemove = listNamesToRemove.begin(); iteratorNamesToRemove != listNamesToRemove.end(); iteratorNamesToRemove++)
	{
		RemoveVariable(*iteratorNamesToRemove);
	}
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddy::ToString()
{
	char buffer[512];
	sprintf (buffer, "[Buddy: %s, id: %ld]", name->c_str(), id);

	return boost::shared_ptr<string>(new string(buffer));
}

}	// namespace Entities
}	// namespace Sfs2X

