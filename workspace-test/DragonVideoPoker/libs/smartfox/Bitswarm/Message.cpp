// ===================================================================
//
// Description		
//		Contains the implementation of Message
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "Message.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Message::Message()
{
	id = 0;
	content = boost::shared_ptr<ISFSObject>();
	targetController = 0;
	isEncrypted = false;
	isUDP = false;
	packetId = 0;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Message::~Message()
{
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int Message::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void Message::Id(long int value)
{
	id = value;
}
		
// -------------------------------------------------------------------
// Content
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> Message::Content()
{
	return content;
}

// -------------------------------------------------------------------
// Content
// -------------------------------------------------------------------
void Message::Content(boost::shared_ptr<ISFSObject> value)
{
	content = value;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
long int Message::TargetController()
{
	return targetController;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
void Message::TargetController(long int value)
{
	targetController = value;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
bool Message::IsEncrypted()
{
	return isEncrypted;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
void Message::IsEncrypted(bool value)
{
	isEncrypted = value;
}

// -------------------------------------------------------------------
// IsUDP
// -------------------------------------------------------------------
bool Message::IsUDP()
{
	return isUDP;
}

// -------------------------------------------------------------------
// IsUDP
// -------------------------------------------------------------------
void Message::IsUDP(bool value)
{
	isUDP = value;
}

// -------------------------------------------------------------------
// PacketId
// -------------------------------------------------------------------
long long Message::PacketId()
{
	return packetId;
}

// -------------------------------------------------------------------
// PacketId
// -------------------------------------------------------------------
void Message::PacketId(long long value)
{
	packetId = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> Message::ToString()
{
	char buffer[512];
	sprintf (buffer, "{ Message id: %ld  }\n", id);

	boost::shared_ptr<string> str (new string(buffer));
	str->append("{ Dump: }\n");
	str->append(*(content->GetDump()));

	return str;
}

}	// namespace Bitswarm
}	// namespace Sfs2X
