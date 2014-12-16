// ===================================================================
//
// Description		
//		Contains the implementation of PacketHeader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PacketHeader.h"
#include <stdio.h>

namespace Sfs2X {
namespace Core {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PacketHeader::PacketHeader(bool encrypted, bool compressed, bool blueBoxed, bool bigSized)
{
	binary = true;
	expectedLength = -1;
	this->compressed = compressed;
	this->encrypted = encrypted;
	this->blueBoxed = blueBoxed;
	this->bigSized = bigSized;
}

// -------------------------------------------------------------------
// ExpectedLength
// -------------------------------------------------------------------
long int PacketHeader::ExpectedLength()
{
	return expectedLength;
}

// -------------------------------------------------------------------
// ExpectedLength
// -------------------------------------------------------------------
void PacketHeader::ExpectedLength(long int value)
{
	expectedLength = value;
}

// -------------------------------------------------------------------
// Encrypted
// -------------------------------------------------------------------
bool PacketHeader::Encrypted()
{
	return encrypted;
}

// -------------------------------------------------------------------
// Encrypted
// -------------------------------------------------------------------
void PacketHeader::Encrypted(bool value)
{
	encrypted = value;
}

// -------------------------------------------------------------------
// Compressed
// -------------------------------------------------------------------
bool PacketHeader::Compressed()
{
	return compressed;
}

// -------------------------------------------------------------------
// Compressed
// -------------------------------------------------------------------
void PacketHeader::Compressed(bool value)
{
	compressed = value;
}

// -------------------------------------------------------------------
// BlueBoxed
// -------------------------------------------------------------------
bool PacketHeader::BlueBoxed()
{
	return blueBoxed;
}

// -------------------------------------------------------------------
// BlueBoxed
// -------------------------------------------------------------------
void PacketHeader::BlueBoxed(bool value)
{
	blueBoxed = value;
}

// -------------------------------------------------------------------
// Binary
// -------------------------------------------------------------------
bool PacketHeader::Binary()
{
	return binary;
}

// -------------------------------------------------------------------
// Binary
// -------------------------------------------------------------------
void PacketHeader::Binary(bool value)
{
	binary = value;
}

// -------------------------------------------------------------------
// BigSized
// -------------------------------------------------------------------
bool PacketHeader::BigSized()
{
	return bigSized;
}

// -------------------------------------------------------------------
// BigSized
// -------------------------------------------------------------------
void PacketHeader::BigSized(bool value)
{
	bigSized = value;
}

// -------------------------------------------------------------------
// FromBinary
// -------------------------------------------------------------------
boost::shared_ptr<PacketHeader> PacketHeader::FromBinary(long int headerByte)
{
	return boost::shared_ptr<PacketHeader>(new PacketHeader((headerByte & 0x40) > 0, 
							 (headerByte & 0x20) > 0,
							 (headerByte & 0x10) > 0,
							 (headerByte & 0x8) > 0));
}

// -------------------------------------------------------------------
// Encode
// -------------------------------------------------------------------
unsigned char PacketHeader::Encode()
{
	unsigned char headerByte = 0;
			
	if (binary)	headerByte |= 0x80;
	if (encrypted) headerByte |= 0x40;
	if (compressed)	headerByte |= 0x20;
	if (blueBoxed) headerByte |= 0x10;
	if (bigSized) headerByte |= 0x08;
				
	return headerByte;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> PacketHeader::ToString()
{
	boost::shared_ptr<string> buf (new string());
	string temporary;
	char tmpbuffer[100];

	buf->append("---------------------------------------------\n");

	temporary.clear();
	sprintf (tmpbuffer, "Binary:  \t %d \n", binary);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "Compressed:\t %d \n", compressed);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "Encrypted:\t %d \n", encrypted);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "BlueBoxed:\t %d \n", blueBoxed);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "BigSized:\t %d \n", bigSized);
	temporary = tmpbuffer;
	buf->append(temporary);

	buf->append("---------------------------------------------\n");

	return buf;
}


}	// namespace Core
}	// namespace Sfs2X
