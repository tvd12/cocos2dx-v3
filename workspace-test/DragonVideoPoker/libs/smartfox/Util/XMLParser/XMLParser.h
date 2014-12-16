// ===================================================================
//
// Description		
//		Contains the definition of XMLParser
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __XMLParser__
#define __XMLParser__

#if defined(_MSC_VER)
#pragma warning(disable:4786)	// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
using namespace std;			// Declare the STL namespace

#include "XMLNode.h"
#include "XMLNodeValue.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

namespace Sfs2X {
namespace Util {

	/*
	 * UnityScript Lightweight XML Parser
	 * by Fraser McCormick (unityscripts@roguishness.com)
	 * http://twitter.com/flimgoblin
	 * http://www.roguishness.com/unity/
	 *
	 * You may use this script under the terms of either the MIT License 
	 * or the Gnu Lesser General Public License (LGPL) Version 3. 
	 * See:
	 * http://www.roguishness.com/unity/lgpl-3.0-standalone.html
	 * http://www.roguishness.com/unity/gpl-3.0-standalone.html
	 * or
	 * http://www.roguishness.com/unity/MIT-license.txt
	 */

	/* Usage:
	 * parser=new XMLParser();
	 * var node=parser.Parse("<example><value type=\"String\">Foobar</value><value type=\"Int\">3</value></example>");
	 * 
	 * Nodes are Boo.Lang.Hash values with text content in "_text" field, other attributes
	 * in "@attribute" and any child nodes listed in an array of their nodename.
	 * 
	 * any XML meta tags <? .. ?> are ignored as are comments <!-- ... -->
	 * any CDATA is bundled into the "_text" attribute of its containing node.
	 *
	 * e.g. the above XML is parsed to:
	 * node={ "example": 
	 *			[ 
	 *			   { "_text":"", 
	 *				  "value": [ { "_text":"Foobar", "@type":"String"}, {"_text":"3", "@type":"Int"}]
	 *			   } 
	 *			],
	 *		  "_text":""
	 *     }
	 *		  
	 */
	class XMLParser
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		XMLParser();
		~XMLParser();

		boost::shared_ptr<XMLNode> Parse(boost::shared_ptr<string> content);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
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
		static char LT;
		static char GT;
		static char SPACE;
		static char QUOTE;
		static char QUOTE2;
		static char SLASH;
		static char QMARK;
		static char EQUALS;
		static char EXCLAMATION;
		static char DASH;
		//static char SQL;
		static char SQR;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
