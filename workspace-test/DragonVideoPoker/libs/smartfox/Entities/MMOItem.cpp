// ===================================================================
//
// Description		
//		Contains the implementation of MMOItem
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MMOItem.h"
#include "Variables/MMOItemVariable.h"

namespace Sfs2X {
namespace Entities {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItem> MMOItem::FromSFSArray(boost::shared_ptr<ISFSArray> encodedItem)
{
	// Create the MMO Item with the server side ID (Index = 0 of the SFSArray)
	boost::shared_ptr<IMMOItem> item (new MMOItem(encodedItem->GetInt(0)));

	// Decode ItemVariables (Index = 1 of the SFSArray)
	boost::shared_ptr<ISFSArray> encodedVars = encodedItem->GetSFSArray(1);
			
	for (long int i = 0; i < encodedVars->Size(); i++)
	{
		item->SetVariable(MMOItemVariable::FromSFSArray(encodedVars->GetSFSArray(i)));
	}
			
	return item;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMOItem::MMOItem (long int id)
{
	this->id = id;
	this->aoiEntryPoint = boost::shared_ptr<Vec3D>();

	this->variables = boost::shared_ptr<map<string, boost::shared_ptr<IMMOItemVariable> > >(new map<string, boost::shared_ptr<IMMOItemVariable> >());
	this->variables->clear();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMOItem::~MMOItem()
{
	variables->clear();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int MMOItem::Id()
{
	return id;
}

// -------------------------------------------------------------------
// GetVariables
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<IMMOItemVariable> > > MMOItem::GetVariables()
{
	boost::shared_ptr<vector<boost::shared_ptr<IMMOItemVariable> > > result (new vector<boost::shared_ptr<IMMOItemVariable> >());
	
	map<string, boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	return result;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItemVariable> MMOItem::GetVariable(string name)
{
	map<string, boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
	iterator = variables->find(name);
	if (iterator == variables->end())
	{
		return boost::shared_ptr<IMMOItemVariable>();
	}

	return iterator->second;
}
		
// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void MMOItem::SetVariable(boost::shared_ptr<IMMOItemVariable> variable)
{
	// Remove if variables was null-ified
	if (variable->IsNull()) 
	{
		map<string, boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
		iterator = variables->find(*variable->Name());
		if (iterator != variables->end())
		{
			variables->erase(iterator);
		}
	}
	else
	{
		map<string, boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
		iterator = variables->find(*variable->Name());
		if (iterator != variables->end())
		{
			iterator->second = variable;
		}
		else
		{
			variables->insert(pair<string, boost::shared_ptr<IMMOItemVariable> >(*variable->Name(), variable));
		}
	}
}
		
// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void MMOItem::SetVariables(boost::shared_ptr<vector<boost::shared_ptr<IMMOItemVariable> > > variables)
{
	vector<boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
	for (iterator = variables->begin(); iterator != variables->end(); iterator++)
	{
		SetVariable(*iterator);
	}
}
		
// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool MMOItem::ContainsVariable(string name)
{
	map<string, boost::shared_ptr<IMMOItemVariable> >::iterator iterator;
	iterator = variables->find(name);
	if (iterator == variables->end())
	{
		return false;
	}

	return true;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MMOItem::AOIEntryPoint()
{
	return aoiEntryPoint;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
void MMOItem::AOIEntryPoint(boost::shared_ptr<Vec3D> value)
{
	aoiEntryPoint = value;
}

}	// namespace Entities
}	// namespace Sfs2X
		
		
