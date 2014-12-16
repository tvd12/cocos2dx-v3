// ===================================================================
//
// Description		
//		Contains the definition of BoolMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BoolMatch__
#define __BoolMatch__

#include "IMatcher.h"
#include "../../Util/Common.h"

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Match {

	/// <summary>
	/// This matcher is used in MatchExpressions to check boolean conditions
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport BoolMatch : public IMatcher
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		BoolMatch(boost::shared_ptr<string> symbol);
		BoolMatch(string symbol);
		virtual ~BoolMatch();

		boost::shared_ptr<string> Symbol();
		long int Type();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static const long int TYPE_ID;

		/// <summary>
		/// Checks that Bool1 == Bool2
		/// </summary>
		static boost::shared_ptr<BoolMatch> EQUALS;
		
		/// <summary>
		/// Checks that Bool1 != Bool2
		/// </summary>
		static boost::shared_ptr<BoolMatch> NOT_EQUALS;
		
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
