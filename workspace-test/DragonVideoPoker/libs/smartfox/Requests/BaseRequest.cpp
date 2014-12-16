// ===================================================================
//
// Description		
//		Contains the implementation of BaseRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BaseRequest.h"
#include "ExtensionRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> BaseRequest::KEY_ERROR_CODE (new string("ec"));
boost::shared_ptr<string> BaseRequest::KEY_ERROR_PARAMS (new string("ep"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseRequest::BaseRequest()
{
	sfso = (boost::shared_ptr<ISFSObject>)SFSObject::NewInstance();
	targetController = 0;
	isEncrypted = false;
	id = 0;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseRequest::BaseRequest(RequestType tp)
{
	sfso = (boost::shared_ptr<ISFSObject>)SFSObject::NewInstance();
	targetController = 0;
	isEncrypted = false;
	id = tp;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseRequest::BaseRequest(long int id)
{
	sfso = (boost::shared_ptr<ISFSObject>)SFSObject::NewInstance();
	targetController = 0;
	isEncrypted = false;
	this->id = id;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BaseRequest::~BaseRequest()
{
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int BaseRequest::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void BaseRequest::Id(long int value)
{
	id = value;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
RequestType BaseRequest::Type()
{
	return (RequestType)id;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
void BaseRequest::Type(RequestType value)
{
	id = value;
}

// IRequest implementation

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void BaseRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	// Override in child class
	// Throws exception if invalid request.
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void BaseRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	// Override in child class
}
		
// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
long int BaseRequest::TargetController()
{
	return targetController;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
void BaseRequest::TargetController(long int value)
{
	targetController = value;
}
		
// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
bool BaseRequest::IsEncrypted()
{
	return isEncrypted;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
void BaseRequest::IsEncrypted(bool value)
{
	isEncrypted = value;
}
		
// -------------------------------------------------------------------
// Message
// -------------------------------------------------------------------
boost::shared_ptr<IMessage> BaseRequest::Message()
{
	boost::shared_ptr<IMessage> message (new Sfs2X::Bitswarm::Message());
	message->Id(id);
	message->IsEncrypted(isEncrypted);
	message->TargetController(targetController);
	message->Content(sfso);

	/*
	* An extension request carries the UseUDP flag
	* Check if this is the case and set the flag on the message object
	* This will tell the bitswarm engine how to handle the socket write (TCP vs UDP)
	*/
	if (dynamic_cast<ExtensionRequest*>(this) != NULL) 
	{
		message->IsUDP((dynamic_cast<ExtensionRequest*>(this))->UseUDP());
	}

	return message;
}



}	// namespace Requests
}	// namespace Sfs2X
