// ===================================================================
//
// Description		
//		Contains the definition of IMatcher interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IMatcher__
#define __IMatcher__

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
    /// 
    /// </summary>
	class DLLImportExport IMatcher
	{
	public:
		/// <summary>
		/// Get the condition symbol of this matcher
		/// </summary>
		virtual boost::shared_ptr<string> Symbol() = 0;

		/// <summary>
		/// Get the type of this matcher
		/// </summary>
		virtual long int Type() = 0;
	};

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X

#endif
