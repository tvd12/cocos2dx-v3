// ===================================================================
//
// Description		
//		Contains the implementation of LogicOperator
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "LogicOperator.h"

namespace Sfs2X {
namespace Entities {
namespace Match {

boost::shared_ptr<LogicOperator> LogicOperator::AND (new LogicOperator(boost::shared_ptr<string>(new string("AND"))));
boost::shared_ptr<LogicOperator> LogicOperator::OR (new LogicOperator(boost::shared_ptr<string> (new string ("OR"))));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LogicOperator::LogicOperator(boost::shared_ptr<string> id)
{
	this->id = id;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LogicOperator::LogicOperator(string id)
{
	this->id = boost::shared_ptr<string>(new string(id));
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
boost::shared_ptr<string> LogicOperator::Id()
{
	return id;
}


}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


