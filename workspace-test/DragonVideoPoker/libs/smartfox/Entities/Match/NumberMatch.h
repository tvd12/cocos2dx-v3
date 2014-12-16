// ===================================================================
//
// Description		
//		Contains the definition of NumberMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __NumberMatch__
#define __NumberMatch__

#include "IMatcher.h"
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
	/// This matcher is used in MatchExpressions to check numeric conditions
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport NumberMatch : public IMatcher
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		NumberMatch(boost::shared_ptr<string> symbol);
		NumberMatch(string symbol);
		virtual ~NumberMatch();
		boost::shared_ptr<string> Symbol();
		long int Type();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static const long int TYPE_ID;
		
		/// <summary>
		/// Checks that Num1 == Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> EQUALS;
		
		/// <summary>
		/// Checks that Num1 != Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> NOT_EQUALS;
		
		/// <summary>
		/// Checks that Num1 > Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> GREATER_THAN;
		
		/// <summary>
		/// Checks that Num1 >= Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> GREATER_OR_EQUAL_THAN;
		
		/// <summary>
		/// Checks that Num1 < Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> LESS_THAN;
		
		/// <summary>
		/// Checks that Num1 <= Num2
		/// </summary>
		static boost::shared_ptr<NumberMatch> LESS_OR_EQUAL_THAN;

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
		boost::shared_ptr<string> symbol;
	};

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X

#endif
