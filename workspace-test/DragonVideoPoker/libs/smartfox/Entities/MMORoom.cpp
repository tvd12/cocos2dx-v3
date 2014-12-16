// ===================================================================
//
// Description		
//		Contains the implementation of MMORoom
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MMORoom.h"

namespace Sfs2X {
namespace Entities {


// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMORoom::MMORoom (long int id, string name, string groupId)
	: SFSRoom(id, name, groupId)
{
	this->defaultAOI = boost::shared_ptr<Vec3D>();
	this->lowerMapLimit = boost::shared_ptr<Vec3D>();
	this->higherMapLimit = boost::shared_ptr<Vec3D>();

	this->itemsById = boost::shared_ptr<map<long int, boost::shared_ptr<IMMOItem> > >(new map<long int, boost::shared_ptr<IMMOItem> >());
	this->itemsById->clear();
}
		

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMORoom::MMORoom (long int id, string name)
	: SFSRoom(id, name)
{
	this->defaultAOI = boost::shared_ptr<Vec3D>();
	this->lowerMapLimit = boost::shared_ptr<Vec3D>();
	this->higherMapLimit = boost::shared_ptr<Vec3D>();

	this->itemsById = boost::shared_ptr<map<long int, boost::shared_ptr<IMMOItem> > >(new map<long int, boost::shared_ptr<IMMOItem> >());
	this->itemsById->clear();
}
		
// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMORoom::~MMORoom()
{
	itemsById->clear();
}

// -------------------------------------------------------------------
// DefaultAOI
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MMORoom::DefaultAOI()
{
	return defaultAOI;
}

// -------------------------------------------------------------------
// DefaultAOI
// -------------------------------------------------------------------
void MMORoom::DefaultAOI(boost::shared_ptr<Vec3D> value)
{
	defaultAOI = value;
}

		
// -------------------------------------------------------------------
// LowerMapLimit
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MMORoom::LowerMapLimit()
{
	return lowerMapLimit;
}

// -------------------------------------------------------------------
// LowerMapLimit
// -------------------------------------------------------------------
void MMORoom::LowerMapLimit(boost::shared_ptr<Vec3D> value)
{
	lowerMapLimit = value;
}
		
// -------------------------------------------------------------------
// HigherMapLimit
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MMORoom::HigherMapLimit()
{
	return higherMapLimit;
}

// -------------------------------------------------------------------
// HigherMapLimit
// -------------------------------------------------------------------
void MMORoom::HigherMapLimit(boost::shared_ptr<Vec3D> value)
{
	higherMapLimit = value;
}
		
// -------------------------------------------------------------------
// GetMMOItem
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItem> MMORoom::GetMMOItem(long int id)
{
	map<long int, boost::shared_ptr<IMMOItem> >::iterator iterator;
	iterator = itemsById->find(id);
	if (iterator == itemsById->end())
	{
		return boost::shared_ptr<IMMOItem>();
	}

	return iterator->second;
}

// -------------------------------------------------------------------
// GetMMOItems
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<IMMOItem> > > MMORoom::GetMMOItems()
{
	boost::shared_ptr<vector<boost::shared_ptr<IMMOItem> > > result (new vector<boost::shared_ptr<IMMOItem> >());
	
	map<long int, boost::shared_ptr<IMMOItem> >::iterator iterator;
	for (iterator = itemsById->begin(); iterator != itemsById->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	return result;
}

// -------------------------------------------------------------------
// AddMMOItem
// -------------------------------------------------------------------
void MMORoom::AddMMOItem(boost::shared_ptr<IMMOItem> item)
{
	map<long int, boost::shared_ptr<IMMOItem> >::iterator iterator;
	iterator = itemsById->find(item->Id());
	if (iterator != itemsById->end())
	{
		iterator->second = item;
	}
	else
	{
		itemsById->insert(pair<long int, boost::shared_ptr<IMMOItem> >(item->Id(), item));
	}
}

// -------------------------------------------------------------------
// RemoveItem
// -------------------------------------------------------------------
void MMORoom::RemoveItem(long int id)
{
	map<long int, boost::shared_ptr<IMMOItem> >::iterator iterator;
	iterator = itemsById->find(id);
	if (iterator != itemsById->end())
	{
		itemsById->erase(iterator);
	}
}

}	// namespace Entities
}	// namespace Sfs2X
		
		
