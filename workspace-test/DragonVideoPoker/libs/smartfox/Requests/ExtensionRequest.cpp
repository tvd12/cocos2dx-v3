// ===================================================================
//
// Description		
//		Contains the implementation of ExtensionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ExtensionRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> ExtensionRequest::KEY_CMD (new string("c"));
boost::shared_ptr<string> ExtensionRequest::KEY_PARAMS (new string("p"));
boost::shared_ptr<string> ExtensionRequest::KEY_ROOM (new string("r"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ExtensionRequest::ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room, bool useUDP)
	: BaseRequest(RequestType_CallExtension)
{
	Init(extCmd, parameters, room, useUDP);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ExtensionRequest::ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room)
	: BaseRequest(RequestType_CallExtension)
{
	Init(extCmd, parameters, room, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ExtensionRequest::ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters)
	: BaseRequest(RequestType_CallExtension)
{
	Init(extCmd, parameters, boost::shared_ptr<Room>(), false);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ExtensionRequest::~ExtensionRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void ExtensionRequest::Init(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room, bool useUDP)
{
	targetController = 1;
			
	this->extCmd = boost::shared_ptr<string>(new string(extCmd));
	this->parameters = parameters;
	this->room = room;
	this->useUDP = useUDP;
			
	// New since 0.9.6
	if (parameters == NULL)
 		this->parameters = boost::shared_ptr<ISFSObject>(new SFSObject());
}

// -------------------------------------------------------------------
// UseUDP
// -------------------------------------------------------------------
bool ExtensionRequest::UseUDP()
{
	return useUDP;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ExtensionRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (extCmd == NULL || extCmd->size() == 0)
		errors->push_back("Missing extension command");
				
	if (parameters == NULL)
		errors->push_back("Missing extension parameters");
					
	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("ExtensionCall request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ExtensionRequest::Execute (boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_CMD, extCmd);

	boost::shared_ptr<long> valueId (new long());
	*valueId = room == NULL ? -1 : room->Id();
	sfso->PutInt(KEY_ROOM, valueId);
	sfso->PutSFSObject(KEY_PARAMS, parameters);
}

}	// namespace Requests
}	// namespace Sfs2X


