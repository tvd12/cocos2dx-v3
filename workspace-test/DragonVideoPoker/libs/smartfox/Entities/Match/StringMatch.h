// ===================================================================
//
// Description		
//		Contains the definition of StringMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __StringMatch__
#define __StringMatch__

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
	/// This matcher is used in MatchExpressions to check String conditions
	/// </summary>
	/// <seealso cref="MatchExpression"/>
	class DLLImportExport StringMatch : public IMatcher
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		StringMatch(string symbol);
		StringMatch(boost::shared_ptr<string> symbol);
		virtual ~StringMatch();
		boost::shared_ptr<string> Symbol();
		long int Type();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static const long int TYPE_ID;

		/// <summary>
		/// Checks that Str1 == Str2
		/// </summary>
		static boost::shared_ptr<StringMatch> EQUALS;
		
		/// <summary>
		/// Checks that Str1 != Str2
		/// </summary>
		static boost::shared_ptr<StringMatch> NOT_EQUALS;
		
		/// <summary>
		/// Checks that Str1.indexOf(Str2) != -1
		/// </summary>
		static boost::shared_ptr<StringMatch> CONTAINS;
		
		/// <summary>
		/// Checks that Str1 starts with characters contained in Str2
		/// </summary>
		static boost::shared_ptr<StringMatch> STARTS_WITH;
		
		/// <summary>
		/// Checks that Str1 end with characters contained in Str2
		/// </summary>
		static boost::shared_ptr<StringMatch> ENDS_WITH;

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
