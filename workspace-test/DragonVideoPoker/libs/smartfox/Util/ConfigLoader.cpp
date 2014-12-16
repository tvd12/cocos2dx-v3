// ===================================================================
//
// Description		
//		Contains the implementation of ConfigLoader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ConfigLoader.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ConfigLoader::ConfigLoader(boost::shared_ptr<SmartFox> smartFox)
{
	this->smartFox = smartFox;
	xmlParser = boost::shared_ptr<XMLParser>();
	rootNode = boost::shared_ptr<XMLNode>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ConfigLoader::~ConfigLoader()
{
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void ConfigLoader::Initialize()
{
	// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
	// so any initialization that need of instance shared pointer should be moved into this method that will be explicity called after constructor

	dispatcher = boost::shared_ptr<EventDispatcher>(new EventDispatcher(shared_from_this()));
}

// -------------------------------------------------------------------
// Dispatcher
// -------------------------------------------------------------------
boost::shared_ptr<EventDispatcher> ConfigLoader::Dispatcher()
{
	return dispatcher;
}

// -------------------------------------------------------------------
// LoadConfig
// -------------------------------------------------------------------
void ConfigLoader::LoadConfig(string filePath)
{
	ifstream is;
	is.open (filePath.c_str(), std::ios::binary);

	// Get length of file
	is.seekg (0, ios::end);
	unsigned long int length = (unsigned long int)(is.tellg());
	is.seekg (0, ios::beg);

	// allocate memory:
	boost::shared_ptr<char> fileText (new char [length]);
  
	// read data 
	is.read (fileText.get(), length);
	is.close();

	xmlParser = boost::shared_ptr<XMLParser>(new XMLParser());

	boost::shared_ptr<string> fileTextAsString (new string (fileText.get(), fileText.get() + length));
	rootNode = xmlParser->Parse(fileTextAsString);
	
	TryParse();
}

// -------------------------------------------------------------------
// GetNodeText
// -------------------------------------------------------------------
boost::shared_ptr<string> ConfigLoader::GetNodeText(boost::shared_ptr<XMLNode> rootNode, string nodeName)
{
	map<string, tagXMLObject>::iterator iterator = rootNode->find(nodeName);
	if (iterator == rootNode->end())
	{
		return boost::shared_ptr<string>();
	}
	else
	{
		boost::shared_ptr<XMLNodeList> xmlNodeList = (boost::static_pointer_cast<XMLNodeList>)(iterator->second.XMLObjectInstance);

		list<boost::shared_ptr<XMLNode> >::iterator iteratorNodeList = xmlNodeList->begin();
		std::advance(iteratorNodeList, 0);
		boost::shared_ptr<XMLNode> xmlNode = *iteratorNodeList;
		boost::shared_ptr<XMLNodeValue> xmlValue = (boost::static_pointer_cast<XMLNodeValue>)(xmlNode->at("_text").XMLObjectInstance);
		return (boost::shared_ptr<string>)xmlValue;
	}
}

// -------------------------------------------------------------------
// TryParse
// -------------------------------------------------------------------
void ConfigLoader::TryParse()
{
	boost::shared_ptr<ConfigData> cfgData (new ConfigData());

	try 
	{
		// Verify required nodes exist
		map<string, tagXMLObject>::iterator iterator = rootNode->find("SmartFoxConfig");
		if (iterator == rootNode->end())
		{
			boost::throw_exception(boost::enable_error_info (std::runtime_error("SmartFoxConfig tag not found")));
		}

		boost::shared_ptr<XMLNodeList> nodeList = (boost::static_pointer_cast<XMLNodeList>)(iterator->second.XMLObjectInstance);

		list<boost::shared_ptr<XMLNode> >::iterator iteratorNodeList = nodeList->begin();
		std::advance(iteratorNodeList, 0);
		boost::shared_ptr<XMLNode> configNode = *iteratorNodeList;

		if (GetNodeText(configNode, "ip") == NULL) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			string logMessage("Required config node missing: ip");
			logMessages->push_back(logMessage);
			this->smartFox->Log()->Error(logMessages);
		}
		if (GetNodeText(configNode, "port") == NULL) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			string logMessage("Required config node missing: port");
			logMessages->push_back(logMessage);
			this->smartFox->Log()->Error(logMessages);
		}
		if (GetNodeText(configNode, "udpIp") == NULL) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			string logMessage("Required config node missing: udpIp");
			logMessages->push_back(logMessage);
			this->smartFox->Log()->Error(logMessages);
		}
		if (GetNodeText(configNode, "udpPort") == NULL) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			string logMessage("Required config node missing: udpPort");
			logMessages->push_back(logMessage);
			this->smartFox->Log()->Error(logMessages);
		}
		if (GetNodeText(configNode, "zone") == NULL) {
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			string logMessage("Required config node missing: zone");
			logMessages->push_back(logMessage);
			this->smartFox->Log()->Error(logMessages);
		}

		// Read required values				
		cfgData->Host(*GetNodeText(configNode, "ip"));
		cfgData->Port(atoi(GetNodeText(configNode, "port")->c_str()));
		cfgData->UdpHost(*GetNodeText(configNode, "udpIp"));
		cfgData->UdpPort(atoi(GetNodeText(configNode, "udpPort")->c_str()));
		cfgData->Zone(*GetNodeText(configNode, "zone"));

		cfgData->Debug(false);
		if ((GetNodeText(configNode, "debug") != NULL) && ((*(GetNodeText(configNode, "debug"))) == "true")) {
			cfgData->Debug(true);
		}

		cfgData->UseBlueBox(false);
		if ((GetNodeText(configNode, "useBlueBox") != NULL) && ((*(GetNodeText(configNode, "useBlueBox"))) == "true")) {
			cfgData->UseBlueBox(true);
		}

		if ((GetNodeText(configNode, "httpPort") != NULL) && ((*(GetNodeText(configNode, "httpPort"))) != "")) {
			cfgData->HttpPort(atoi(GetNodeText(configNode, "httpPort")->c_str()));
		}

		if ((GetNodeText(configNode, "blueBoxPollingRate") != NULL) && ((*(GetNodeText(configNode, "blueBoxPollingRate"))) != "")) {
			cfgData->BlueBoxPollingRate(atoi(GetNodeText(configNode, "blueBoxPollingRate")->c_str()));
		}

	}
	catch (exception e) 
	{
		boost::shared_ptr<string> messageException (new string(e.what()));
		boost::shared_ptr<string> message (new string("Error parsing config file: " + (*messageException)));

		OnConfigLoadFailure(message);
		return;
	}

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
	data->insert(pair<string, boost::shared_ptr<void> >("cfg", cfgData));
	boost::shared_ptr<SFSEvent> sfsEvt (new SFSEvent(SFSEvent::CONFIG_LOAD_SUCCESS, data));
	dispatcher->DispatchEvent(sfsEvt);
}

// -------------------------------------------------------------------
// OnConfigLoadFailure
// -------------------------------------------------------------------
void ConfigLoader::OnConfigLoadFailure(boost::shared_ptr<string> msg)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > data (new map<string, boost::shared_ptr<void> >());
	data->insert(pair<string, boost::shared_ptr<void> >("message", msg));

	boost::shared_ptr<SFSEvent> sfsEvt (new SFSEvent(SFSEvent::CONFIG_LOAD_FAILURE, data));
	dispatcher->DispatchEvent(sfsEvt);
}

// IDispatchable implementation

// -------------------------------------------------------------------
// AddEventListener
// -------------------------------------------------------------------
void ConfigLoader::AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener)
{
	dispatcher->AddEventListener(eventType, listener);
}

}	// namespace Util
}	// namespace Sfs2X
