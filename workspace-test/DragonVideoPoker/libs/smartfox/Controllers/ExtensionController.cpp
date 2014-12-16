// ===================================================================
//
// Description		
//		Contains the implementation of ExtensionController
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ExtensionController.h"

namespace Sfs2X {
namespace Controllers {

boost::shared_ptr<string> ExtensionController::KEY_CMD (new string("c"));
boost::shared_ptr<string> ExtensionController::KEY_PARAMS (new string("p"));
boost::shared_ptr<string> ExtensionController::KEY_ROOM (new string("r"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ExtensionController::ExtensionController(boost::shared_ptr<BitSwarmClient> bitSwarm)
	: BaseController (bitSwarm)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ExtensionController::~ExtensionController()
{
}

// -------------------------------------------------------------------
// HandleMessage
// -------------------------------------------------------------------
void ExtensionController::HandleMessage(boost::shared_ptr<IMessage> message)
{
	if (sfs->Debug()) 
	{
		boost::shared_ptr<string> err (new string());
		boost::shared_ptr<string> format (new string("Message: %d"));
		StringFormatter<long int> (err, format, message->Id());
		
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(*err);
		log->Info(logMessages);
	}
					
	boost::shared_ptr<ISFSObject> obj = message->Content();
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
			
	boost::shared_ptr<string> cmd = obj->GetUtfString(*KEY_CMD);
	evtParams->insert(pair<string, boost::shared_ptr<void> >("cmd", cmd));
	boost::shared_ptr<ISFSObject> params = obj->GetSFSObject(*KEY_PARAMS);
	evtParams->insert(pair<string, boost::shared_ptr<void> >("params", params));
			
	if (obj->ContainsKey(*KEY_ROOM)) 
	{
		boost::shared_ptr<long int> sourceRoom (new long int());
		*sourceRoom = *(obj->GetInt(*KEY_ROOM));
		evtParams->insert(pair<string, boost::shared_ptr<void> >("sourceRoom", sourceRoom));
	}

	if (message->IsUDP())
	{
		boost::shared_ptr<long long> packetId (new long long());
		*packetId = message->PacketId();
		evtParams->insert(pair<string, boost::shared_ptr<void> >("packetId", packetId));
	}

	boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::EXTENSION_RESPONSE, evtParams));
	sfs->DispatchEvent(evt);
}

}	// namespace Controllers
}	// namespace Sfs2X
