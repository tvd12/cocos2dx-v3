// ===================================================================
//
// Description		
//		Contains the implementation of MapLimits
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MapLimits.h"

#include <boost/system/error_code.hpp> 

namespace Sfs2X {
namespace Requests {
namespace MMO {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MapLimits::MapLimits (boost::shared_ptr<Vec3D> lowerLimit, boost::shared_ptr<Vec3D> higherLimit)
{
	if (lowerLimit == NULL || higherLimit == NULL)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Map limits arguments must be both non null!"))); 

	this->lowerLimit = lowerLimit;
	this->higherLimit = higherLimit;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MapLimits::~MapLimits()
{
}

// -------------------------------------------------------------------
// LowerLimit
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MapLimits::LowerLimit()
{
	return lowerLimit;
}

// -------------------------------------------------------------------
// HigherLimit
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> MapLimits::HigherLimit()
{
	return higherLimit;
}

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X


