// ===================================================================
//
// Description		
//		Contains the definition of LogicOperator
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LogicOperator__
#define __LogicOperator__

#include "../../Util/Common.h"
#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Match {

	/// <summary>
	/// The LogicOperator is used to concatenate two MatchExpression together using a logical AND / OR operator
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport LogicOperator
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		LogicOperator(boost::shared_ptr<string> id);
		LogicOperator(string id);
		boost::shared_ptr<string> Id();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<LogicOperator> AND;
		static boost::shared_ptr<LogicOperator> OR;
		
	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<string> id;
	};

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X

#endif
