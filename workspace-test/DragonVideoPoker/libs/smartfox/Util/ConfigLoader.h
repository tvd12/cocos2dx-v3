// ===================================================================
//
// Description		
//		Contains the definition of ConfigLoader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ConfigLoader__
#define __ConfigLoader__

#include "../SmartFox.h"
#include "./EventDispatcher.h"
#include "XMLParser/XMLParser.h"
#include "XMLParser/XMLNode.h"
#include "../Core/IDispatchable.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <istream>						// STL library: stream object
#include <fstream>						// STL library:	file stream object
#include <map>							// STL library: map object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Core;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class ConfigLoader
	// -------------------------------------------------------------------
	class ConfigLoader : public IDispatchable, public boost::enable_shared_from_this<ConfigLoader>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		ConfigLoader(boost::shared_ptr<SmartFox> smartFox);
		virtual ~ConfigLoader();

		void Initialize();

		/// <summary>
		/// By default load a file called sfs-config.xml located in the same folder of the application
		/// </summary>
		/// <param name="filePath">
		/// Path to config file
		/// </param>
		void LoadConfig(string filePath);

		boost::shared_ptr<EventDispatcher> Dispatcher();

		// IDispatchable implementation
		void AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);

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
		void TryParse();
		boost::shared_ptr<string> GetNodeText(boost::shared_ptr<XMLNode> rootNode, string nodeName);
		void OnConfigLoadFailure(boost::shared_ptr<string> msg);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<SmartFox> smartFox;
		boost::shared_ptr<EventDispatcher> dispatcher;
		boost::shared_ptr<XMLParser> xmlParser;
		boost::shared_ptr<XMLNode> rootNode;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
