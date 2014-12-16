// ===================================================================
//
// Description		
//		Contains the implementation of PendingPacket
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PendingPacket.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PendingPacket::PendingPacket(boost::shared_ptr<PacketHeader> header)
{
	this->header = header;
	buffer = boost::shared_ptr<ByteArray>(new ByteArray());
	buffer->Compressed(header->Compressed());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PendingPacket::~PendingPacket()
{
}

// -------------------------------------------------------------------
// Header
// -------------------------------------------------------------------
boost::shared_ptr<PacketHeader> PendingPacket::Header()
{
	return header; 
}

// -------------------------------------------------------------------
// Buffer
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> PendingPacket::Buffer()
{
	return buffer;
}

// -------------------------------------------------------------------
// Buffer
// -------------------------------------------------------------------
void PendingPacket::Buffer(boost::shared_ptr<ByteArray> value)
{
	buffer = value;
}

}	// namespace Bitswarm
}	// namespace Sfs2X
