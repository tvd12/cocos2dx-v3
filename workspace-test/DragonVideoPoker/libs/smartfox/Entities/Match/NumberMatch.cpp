// ===================================================================
//
// Description		
//		Contains the implementation of NumberMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "NumberMatch.h"

namespace Sfs2X {
namespace Entities {
namespace Match {

const long int NumberMatch::TYPE_ID = 1;
boost::shared_ptr<NumberMatch> NumberMatch::EQUALS (new NumberMatch(boost::shared_ptr<string>(new string("=="))));
boost::shared_ptr<NumberMatch> NumberMatch::NOT_EQUALS (new NumberMatch(boost::shared_ptr<string>(new string("!="))));
boost::shared_ptr<NumberMatch> NumberMatch::GREATER_THAN (new NumberMatch(boost::shared_ptr<string>(new string(">"))));
boost::shared_ptr<NumberMatch> NumberMatch::GREATER_OR_EQUAL_THAN (new NumberMatch(boost::shared_ptr<string>(new string(">="))));
boost::shared_ptr<NumberMatch> NumberMatch::LESS_THAN (new NumberMatch(boost::shared_ptr<string>(new string("<"))));
boost::shared_ptr<NumberMatch> NumberMatch::LESS_OR_EQUAL_THAN (new NumberMatch(boost::shared_ptr<string>(new string("<="))));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
NumberMatch::NumberMatch(boost::shared_ptr<string> symbol)
{
	this->symbol = symbol;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
NumberMatch::NumberMatch(string symbol)
{
	this->symbol = boost::shared_ptr<string>(new string(symbol));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
NumberMatch::~NumberMatch()
{
	// delete symbol;			Do not delete because it is a static string (one-time allocated string)
}

// -------------------------------------------------------------------
// Symbol
// -------------------------------------------------------------------
boost::shared_ptr<string> NumberMatch::Symbol()
{
	return symbol;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
long int NumberMatch::Type()
{
	return TYPE_ID;
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


