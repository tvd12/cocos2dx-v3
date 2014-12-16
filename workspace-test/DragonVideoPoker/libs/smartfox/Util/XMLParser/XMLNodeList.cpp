// ===================================================================
//
// Description		
//		Contains the implementation of XMLNodeList
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "XMLNodeList.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNodeList::XMLNodeList()
{
	this->clear();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
XMLNodeList::~XMLNodeList()
{
	this->clear();
}

// -------------------------------------------------------------------
// Pop
// -------------------------------------------------------------------
boost::shared_ptr<XMLNode> XMLNodeList::Pop()
{
	boost::shared_ptr<XMLNode> item = boost::shared_ptr<XMLNode>();

	if (this->empty() == false)
	{
		item = this->back();
		this->pop_back();
	}

	return item;
}

// -------------------------------------------------------------------
// Push
// -------------------------------------------------------------------
long int XMLNodeList::Push(boost::shared_ptr<XMLNode> item)
{
	this->push_back(item);
	return this->size();
}

}	// namespace Util
}	// namespace Sfs2X

