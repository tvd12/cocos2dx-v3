// ===================================================================
//
// Description		
//		Contains the implementation of BoolMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BoolMatch.h"

namespace Sfs2X {
namespace Entities {
namespace Match {

const long int BoolMatch::TYPE_ID = 0;
boost::shared_ptr<BoolMatch> BoolMatch::EQUALS (new BoolMatch(boost::shared_ptr<string>(new string("=="))));
boost::shared_ptr<BoolMatch> BoolMatch::NOT_EQUALS (new BoolMatch(boost::shared_ptr<string>(new string("!="))));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BoolMatch::BoolMatch(boost::shared_ptr<string> symbol)
{
	this->symbol = symbol;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BoolMatch::BoolMatch(string symbol)
{
	this->symbol = boost::shared_ptr<string>(new string(symbol));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BoolMatch::~BoolMatch()
{
	// delete symbol;		Do not delete because it is a static string (one-time allocated string)
}

// -------------------------------------------------------------------
// Symbol
// -------------------------------------------------------------------
boost::shared_ptr<string> BoolMatch::Symbol()
{
	return symbol;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
long int BoolMatch::Type()
{
	return TYPE_ID;
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


