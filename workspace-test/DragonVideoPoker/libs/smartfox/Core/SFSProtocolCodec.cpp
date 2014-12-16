// ===================================================================
//
// Description		
//		Contains the implementation of SFSProtocolCodec
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSProtocolCodec.h"

namespace Sfs2X {
namespace Core {
	
boost::shared_ptr<string> SFSProtocolCodec::CONTROLLER_ID (new string("c"));
boost::shared_ptr<string> SFSProtocolCodec::ACTION_ID (new string("a"));
boost::shared_ptr<string> SFSProtocolCodec::PARAM_ID (new string("p"));
boost::shared_ptr<string> SFSProtocolCodec::USER_ID (new string("u"));				// UDP Only
boost::shared_ptr<string> SFSProtocolCodec::UDP_PACKET_ID (new string("i"));		// UDP Only

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSProtocolCodec::SFSProtocolCodec(boost::shared_ptr<IoHandler> ioHandler, boost::shared_ptr<BitSwarmClient> bitSwarm)
{
	this->ioHandler = ioHandler;
	this->log = bitSwarm->Log();
	this->bitSwarm = bitSwarm;

}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSProtocolCodec::~SFSProtocolCodec()
{
}

// -------------------------------------------------------------------
// IOHandler
// -------------------------------------------------------------------
boost::shared_ptr<IoHandler> SFSProtocolCodec::IOHandler()
{
	return ioHandler;
}

// -------------------------------------------------------------------
// IOHandler
// -------------------------------------------------------------------
void SFSProtocolCodec::IOHandler(boost::shared_ptr<IoHandler> value)
{
	if (ioHandler != NULL)
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("IOHandler is already defined for thir ProtocolHandler instance: 0x%x"));
		StringFormatter<void*> (err, format, this);
		
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}

	ioHandler = value;
}

// -------------------------------------------------------------------
// OnPacketRead
// -------------------------------------------------------------------
void SFSProtocolCodec::OnPacketRead(boost::shared_ptr<ISFSObject> packet)
{
	// Create a Request and dispatch to ProtocolCodec
	DispatchRequest(packet);
}

// -------------------------------------------------------------------
// OnPacketRead
// -------------------------------------------------------------------
void SFSProtocolCodec::OnPacketRead(boost::shared_ptr<ByteArray> packet)
{
	boost::shared_ptr<ISFSObject> sfsObj = SFSObject::NewFromBinaryData(packet);
									
	// Create a Request and dispatch to ProtocolCodec
	DispatchRequest(sfsObj);
}

// -------------------------------------------------------------------
// OnPacketRead
// -------------------------------------------------------------------
void SFSProtocolCodec::OnPacketWrite(boost::shared_ptr<IMessage> message)
{
	if (bitSwarm->Debug()) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("Writing message");
		logMessages->push_back(*(message->Content()->GetHexDump()));
		log->Warn(logMessages);
	}
			
	boost::shared_ptr<ISFSObject> sfsObj = boost::shared_ptr<ISFSObject>();
			
	if (message->IsUDP())
		sfsObj = PrepareUDPPacket(message);
	else
		sfsObj = PrepareTCPPacket(message);
			
	// Now the SFSObj is wrapped by its header object
	message->Content(sfsObj);
									
	// Hand it to the IOHandler
	ioHandler->OnDataWrite(message);
}

// -------------------------------------------------------------------
// PrepareTCPPacket
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSProtocolCodec::PrepareTCPPacket(boost::shared_ptr<IMessage> message)
{
	boost::shared_ptr<ISFSObject> sfsObj (new SFSObject());
			
	// Target controller
	boost::shared_ptr<unsigned char> valueTargetController (new unsigned char());
	*valueTargetController = (unsigned char)(message->TargetController());
	sfsObj->PutByte(CONTROLLER_ID, valueTargetController);
			
	// Action id
	boost::shared_ptr<short int> valueActionId (new short int());
	*valueActionId = (short int)message->Id();
	sfsObj->PutShort(ACTION_ID, valueActionId);
			
	// Params
	sfsObj->PutSFSObject(PARAM_ID, message->Content());
			
	return sfsObj;
}

// -------------------------------------------------------------------
// PrepareUDPPacket
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSProtocolCodec::PrepareUDPPacket(boost::shared_ptr<IMessage> message)
{
	boost::shared_ptr<ISFSObject> sfsObj (new SFSObject());
				
	// Target controller
	boost::shared_ptr<unsigned char> valueTargetController (new unsigned char());
	*valueTargetController = (unsigned char)(message->TargetController());
	sfsObj->PutByte(CONTROLLER_ID, valueTargetController);
			
	// User id: in case we're not logged in the packet will sent with UID = -1, and the server will refuse it
	boost::shared_ptr<long int> valueUserId (new long int());
	*valueUserId = bitSwarm->Sfs()->MySelf() != NULL ? bitSwarm->Sfs()->MySelf()->Id() : -1;
	sfsObj->PutInt(USER_ID, valueUserId);
			
	// Packet id	
	boost::shared_ptr<long long> valuePacketId (new long long());
	*valuePacketId = bitSwarm->NextUdpPacketId();
	sfsObj->PutLong(UDP_PACKET_ID, valuePacketId);
				
	// Params
	sfsObj->PutSFSObject(PARAM_ID, message->Content());
			
	return sfsObj;
}
		
// -------------------------------------------------------------------
// DispatchRequest
// -------------------------------------------------------------------
void SFSProtocolCodec::DispatchRequest(boost::shared_ptr<ISFSObject> requestObject)
{
	boost::shared_ptr<IMessage> message (new Message());
			
	// Check controller ID
	if (requestObject->IsNull(CONTROLLER_ID)) 
	{
		boost::shared_ptr<string> message (new string("Request rejected: No Controller ID in request!"));
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(message));
		throw exception;
	}
			
	// Check if action ID exist 
	if (requestObject->IsNull(ACTION_ID)) 
	{
		boost::shared_ptr<string> message (new string("Request rejected: No Action ID in request!"));
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(message));
		throw exception;
	}
			
			
	message->Id((long int)(*(requestObject->GetShort(ACTION_ID))));
	message->Content(requestObject->GetSFSObject(PARAM_ID));
	message->IsUDP(requestObject->ContainsKey(UDP_PACKET_ID));
			
	if (message->IsUDP())
		message->PacketId(*(requestObject->GetLong(UDP_PACKET_ID)));
			
	int controllerId = *(requestObject->GetByte(CONTROLLER_ID));
	boost::shared_ptr<IController> controller = bitSwarm->GetController(controllerId);
			
	if (controller == NULL) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Cannot handle server response. Unknown controller, id: %d"));
		StringFormatter<long int> (err, format, controllerId);
		
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	// Dispatch to controller
	controller->HandleMessage(message);
}


}	// namespace Core
}	// namespace Sfs2X
