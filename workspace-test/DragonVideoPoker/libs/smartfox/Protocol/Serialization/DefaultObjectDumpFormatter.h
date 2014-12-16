// ===================================================================
//
// Description		
//		Contains the definition of DefaultObjectDumpFormatter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __DefaultObjectDumpFormatter__
#define __DefaultObjectDumpFormatter__

#include "../../Exceptions/SFSError.h"
#include "../../Util/ByteArray.h"
#include "../../Util/StringFormatter.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	// -------------------------------------------------------------------
	// Class DefaultObjectDumpFormatter
	// -------------------------------------------------------------------
	class DefaultObjectDumpFormatter
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		virtual ~DefaultObjectDumpFormatter();

		static boost::shared_ptr<string> PrettyPrintDump(boost::shared_ptr<string> rawDump);
		static boost::shared_ptr<string> HexDump(boost::shared_ptr<ByteArray> ba);
		static boost::shared_ptr<string> HexDump(boost::shared_ptr<ByteArray> ba, long int bytesPerLine);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static const char TOKEN_INDENT_OPEN = '{'; //(char) 0x01;
		static const char TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
		static const char TOKEN_DIVIDER = ';'; //(char) 0x03;
		static const char NEW_LINE = '\n';
		static const char TAB = '\t';
		static const char DOT = '.';
		
		static const int HEX_BYTES_PER_LINE = 16;

		static const int MAX_DUMP_LENGTH = 1024;

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

		static boost::shared_ptr<string> GetFormatTabs(long int howMany);
		static boost::shared_ptr<string> StrFill(char ch, long int howMany);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X

#endif
