#include "SFSIOHandler.h"

namespace Sfs2X {
namespace Core {

const long int SFSIOHandler::SHORT_BYTE_SIZE = 2;
const long int SFSIOHandler::INT_BYTE_SIZE = 4;

// ------------------------------------------------------------------- 
// Constructor
// -------------------------------------------------------------------
SFSIOHandler::SFSIOHandler(boost::shared_ptr<BitSwarmClient> bitSwarm)
{
	skipBytes = 0;
	EMPTY_BUFFER = boost::shared_ptr<ByteArray>(new ByteArray());
	this->bitSwarm = bitSwarm;
	log = bitSwarm->Log();
	pendingPacket = boost::shared_ptr<PendingPacket>();
	InitStates();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSIOHandler::~SFSIOHandler()
{
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void SFSIOHandler::Initialize()
{
	// Note: shared pointer for class instance (shared_from_this()) is not available up to the class constructor is completed
	// so any initialization that need of instance shared pointer should be moved into this method that will be explicity called after constructor

	protocolCodec = boost::shared_ptr<IProtocolCodec> (new SFSProtocolCodec(shared_from_this(), bitSwarm));
}

// -------------------------------------------------------------------
// Codec
// -------------------------------------------------------------------
boost::shared_ptr<IProtocolCodec> SFSIOHandler::Codec()
{
	return  protocolCodec;
}

// -------------------------------------------------------------------
// ReadState
// -------------------------------------------------------------------
PacketReadState SFSIOHandler::ReadState()
{
	return (PacketReadState)fsm->GetCurrentState();
}

// -------------------------------------------------------------------
// InitStates
// -------------------------------------------------------------------
void SFSIOHandler::InitStates()
{
	fsm = boost::shared_ptr<FiniteStateMachine>(new FiniteStateMachine());

	std::vector<long int> states;
	for (long int enumerator = PACKETREADSTATE_WAIT_NEW_PACKET; enumerator <= PACKETREADSTATE_INVALID_DATA; enumerator++)
	{
		states.push_back(enumerator);
	}
	fsm->AddAllStates(states);
						
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_NEW_PACKET, PACKETREADSTATE_WAIT_DATA_SIZE, PacketReadTransition_HeaderReceived);
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_DATA_SIZE, PACKETREADSTATE_WAIT_DATA, PacketReadTransition_SizeReceived);
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_DATA_SIZE, PACKETREADSTATE_WAIT_DATA_SIZE_FRAGMENT, PacketReadTransition_IncompleteSize);
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_DATA_SIZE_FRAGMENT, PACKETREADSTATE_WAIT_DATA, PacketReadTransition_WholeSizeReceived);
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_DATA, PACKETREADSTATE_WAIT_NEW_PACKET, PacketReadTransition_PacketFinished);
			
	fsm->AddStateTransition(PACKETREADSTATE_WAIT_DATA, PACKETREADSTATE_INVALID_DATA, PacketReadTransition_InvalidData);
	fsm->AddStateTransition(PACKETREADSTATE_INVALID_DATA, PACKETREADSTATE_WAIT_NEW_PACKET, PacketReadTransition_InvalidDataFinished);
		
	fsm->SetCurrentState(PACKETREADSTATE_WAIT_NEW_PACKET);
}

// -------------------------------------------------------------------
// OnDataRead
// -------------------------------------------------------------------
void SFSIOHandler::OnDataRead(boost::shared_ptr<ByteArray> data)
{
	if (data->Length() == 0) 
	{
		boost::shared_ptr<string> message (new string("Unexpected empty packet data: no readable bytes available!"));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
			
	if (bitSwarm != NULL && bitSwarm->Sfs()->Debug()) 
	{
		if (data->Length() > 1024) 
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("Data Read: Size > 1024, dump omitted");
			log->Info(logMessages);
		} 
		else 
		{
			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back("Data Read: ");
			logMessages->push_back(*(DefaultObjectDumpFormatter::HexDump(data)));
			log->Info(logMessages);
		}
	}		
			
	data->Position(0);
								
	while (data->Length() > 0)
	{
		if (ReadState() == PACKETREADSTATE_WAIT_NEW_PACKET) 
		{
			data = HandleNewPacket(data);
		}
		else if (ReadState() == PACKETREADSTATE_WAIT_DATA_SIZE) 
		{
			data = HandleDataSize(data);
		} 
		else if (ReadState() == PACKETREADSTATE_WAIT_DATA_SIZE_FRAGMENT) 
		{
			data = HandleDataSizeFragment(data);
		}
		else if (ReadState() == PACKETREADSTATE_WAIT_DATA)
		{
			data = HandlePacketData(data);
		}
		else if (ReadState() == PACKETREADSTATE_INVALID_DATA) 
		{
			data = HandleInvalidData(data);
		}
	}			
}

// -------------------------------------------------------------------
// HandleNewPacket
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::HandleNewPacket(boost::shared_ptr<ByteArray> data)
{
	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	boost::shared_ptr<string> logMessage (new string());

	boost::shared_ptr<string> format (new string("Handling New Packet of size %d"));
	StringFormatter<long long> (logMessage, format, data->Length());
		
	logMessages->push_back(*logMessage);
	log->Debug(logMessages);

	// Decode the header byte
	unsigned char headerByte;
	data->ReadByte(headerByte);
			
	if (~(headerByte & 128) > 0) 
	{
		// NOTE: Added extra debug info, for unexpected packets
		boost::shared_ptr<string> logMessage (new string());

		boost::shared_ptr<string> format (new string("Unexpected header byte: %d\n%s"));
		StringFormatter<unsigned char, const char*> (logMessage, format, headerByte, DefaultObjectDumpFormatter::HexDump(data)->c_str());
		
		boost::shared_ptr<SFSError> exception(new SFSError(logMessage));
		throw exception;
	}
				
	boost::shared_ptr<PacketHeader> header = PacketHeader::FromBinary(headerByte);
							
	// Store the pending packet
	pendingPacket = boost::shared_ptr<PendingPacket>(new PendingPacket(header));
			
	// Change state
	fsm->ApplyTransition(PacketReadTransition_HeaderReceived);
			
	// Resize the array
	return ResizeByteArray(data, 1, data->Length()-1);
}

// -------------------------------------------------------------------
// HandleDataSize
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::HandleDataSize(boost::shared_ptr<ByteArray> data)
{
	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	boost::shared_ptr<string> logMessage (new string());
	
	boost::shared_ptr<string> format (new string("Handling Header Size. Length: %d (%s)"));
	StringFormatter<long long, const char*> (logMessage, format, data->Length(), (pendingPacket->Header()->BigSized() ? "big" : "small"));
			
	logMessages->push_back(*logMessage);
	log->Debug(logMessages);
	
	long int dataSize = -1;
	long int sizeBytes = SHORT_BYTE_SIZE; // default == 2 bytes
			
	// Size is expressed in 4 bytes (signed int)
	if (pendingPacket->Header()->BigSized())
	{
		// Check if we have the full header
		if (data->Length() >= INT_BYTE_SIZE) 
		{
			data->ReadInt(dataSize);
		}
				
		sizeBytes = 4;
	}
	// Size is expressed in 2 bytes (unsigned short)
	else 
	{
		if (data->Length() >= SHORT_BYTE_SIZE) 
		{
			unsigned short int dataSizeUShort;
			data->ReadUShort(dataSizeUShort);
			dataSize = dataSizeUShort;
		}
	}

	logMessages->clear();
	logMessage->clear();

	format = boost::shared_ptr<string>(new string("Data size is %d"));
	StringFormatter<long int> (logMessage, format, dataSize);
		
	logMessages->push_back(*logMessage);
	log->Debug(logMessages);

	if (dataSize != -1) 
	{
		// Store expected packet size
		pendingPacket->Header()->ExpectedLength(dataSize);
		data = ResizeByteArray(data, sizeBytes, data->Length() - sizeBytes);
				
		fsm->ApplyTransition(PacketReadTransition_SizeReceived);
	}
	// We didn't decode the whole size
	else
	{
		fsm->ApplyTransition(PacketReadTransition_IncompleteSize);
		// Store the data we have
		pendingPacket->Buffer()->WriteBytes(data->Bytes());
				
		// An empty data will signal that we need to wait the next fragment
		data = EMPTY_BUFFER; 
	}
			
	return data;
}

// -------------------------------------------------------------------
// HandleDataSizeFragment
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::HandleDataSizeFragment(boost::shared_ptr<ByteArray> data)
{
	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	boost::shared_ptr<string> logMessage (new string());

	boost::shared_ptr<string> format (new string("Handling Size fragment. Data: %d"));
	StringFormatter<long int> (logMessage, format, data->Length());
		
	logMessages->push_back(*logMessage);
	log->Debug(logMessages);
			
	long int remaining = pendingPacket->Header()->BigSized() ? (INT_BYTE_SIZE - pendingPacket->Buffer()->Length()):(SHORT_BYTE_SIZE - pendingPacket->Buffer()->Length());
						
	// Ok, we have enough data to finish
	if (data->Length() >= remaining)
	{
		pendingPacket->Buffer()->WriteBytes(data->Bytes(), 0, remaining);
								
		long int neededLength = pendingPacket->Header()->BigSized() ? 4 : 2;
		boost::shared_ptr<ByteArray> size (new ByteArray());
		size->WriteBytes(pendingPacket->Buffer()->Bytes(), 0, neededLength);
		size->Position(0);
		long int dataSize;
		if (pendingPacket->Header()->BigSized())
		{
			size->ReadInt(dataSize);
		}
		else
		{
			short int dataSizeShort;
			size->ReadShort(dataSizeShort);
			dataSize = dataSizeShort;
		}

		logMessages->clear();
		logMessage->clear();

		boost::shared_ptr<string> logMessage (new string());
		boost::shared_ptr<string> format (new string("DataSize is ready: %d bytes"));
		StringFormatter<long int> (logMessage, format, dataSize);
		
		logMessages->push_back(*logMessage);
		log->Debug(logMessages);
		
		pendingPacket->Header()->ExpectedLength(dataSize);
		boost::shared_ptr<ByteArray> value (new ByteArray());
		pendingPacket->Buffer(value);
								
		// Next state
		fsm->ApplyTransition(PacketReadTransition_WholeSizeReceived);
				
		// Remove bytes that were analyzed
		if (data->Length() > remaining) 
		{
			data = ResizeByteArray(data, remaining, data->Length() - remaining);
		}
		else 
		{
			data = EMPTY_BUFFER;
		}
	}
	// Nope, we're not done yet
	else 	
	{
		pendingPacket->Buffer()->WriteBytes(data->Bytes());
		data = EMPTY_BUFFER;
	}
		
	return data;
}

// -------------------------------------------------------------------
// HandlePacketData
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::HandlePacketData(boost::shared_ptr<ByteArray> data)
{
	// is there more data for the next incoming packet?
	long int remaining = pendingPacket->Header()->ExpectedLength ()- pendingPacket->Buffer()->Length();
	bool isThereMore = (data->Length() > remaining);
			
	// Saving the copy of received array for the case of failure
	boost::shared_ptr<ByteArray> currentData (new ByteArray(data->Bytes()));
									
	try 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());

		boost::shared_ptr<string> format (new string("Handling Data: %d, previous state: %d/%d"));
		StringFormatter<long int, long int, long int> (logMessage, format, data->Length(), pendingPacket->Buffer()->Length(), pendingPacket->Header()->ExpectedLength());
		
		logMessages->push_back(*logMessage);
		log->Debug(logMessages);
					
		if (data->Length() >= remaining)
		{
			pendingPacket->Buffer()->WriteBytes(data->Bytes(), 0, remaining);

			logMessages->clear();
			logMessage->clear();
			logMessages->push_back("<<< Packet Complete >>>");
			log->Debug(logMessages);

			/*
			* Encryption handling code goes here TODO
			*/
					
			// Handle compression
			if (pendingPacket->Header()->Compressed())
			{
				pendingPacket->Buffer()->Uncompress();
			}
					
			// Send to protocol codec
			protocolCodec->OnPacketRead(pendingPacket->Buffer());
					
			fsm->ApplyTransition(PacketReadTransition_PacketFinished);
		}
				
		// Not enough data to complete the packet
		else
		{
			// Add bytes to buffer and let's wait for the rest to come over the network
			pendingPacket->Buffer()->WriteBytes(data->Bytes());
		}
				
		if (isThereMore) 
		{
			data = ResizeByteArray(data, remaining, data->Length() - remaining);
		}		
		else 
		{
			data = EMPTY_BUFFER;
		}	
	}
	catch (exception ex) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());

		boost::shared_ptr<string> format (new string("Error handling data: %s"));
		StringFormatter<const char*> (logMessage, format, ex.what());
		
		logMessages->push_back(*logMessage);
		log->Error(logMessages);
		
		// Save how many bytes we should skip
		skipBytes = remaining;				
		fsm->ApplyTransition(PacketReadTransition_InvalidData);
		return currentData;
	}
			
	return data;
}

// -------------------------------------------------------------------
// HandlePacketData
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::HandleInvalidData(boost::shared_ptr<ByteArray> data)
{
	if (skipBytes == 0) 
	{
		fsm->ApplyTransition(PacketReadTransition_InvalidDataFinished);
		return data;
	}
			
	// Removing the minimum (data.Length, skipBytes) from data
	long int bytesToRemove = data->Length() <  skipBytes ? data->Length() : skipBytes;
						
	data = ResizeByteArray(data, bytesToRemove, data->Length() - bytesToRemove);
			
	skipBytes -= bytesToRemove;
	return data;
}

// -------------------------------------------------------------------
// ResizeByteArray
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSIOHandler::ResizeByteArray(boost::shared_ptr<ByteArray> arrayobj, long int pos, long int len)
{
	vector<unsigned char>::iterator iteratorOldArray = arrayobj->Bytes()->begin();
	iteratorOldArray += pos;
	boost::shared_ptr<vector<unsigned char> > newArray (new vector<unsigned char>());
	newArray->insert(newArray->begin(), iteratorOldArray, arrayobj->Bytes()->end());
		
	return boost::shared_ptr<ByteArray>(new ByteArray(newArray));
}

// -------------------------------------------------------------------
// WriteBinaryData
// -------------------------------------------------------------------
void SFSIOHandler::WriteBinaryData(unsigned long long context, boost::shared_ptr<PacketHeader> header, boost::shared_ptr<ByteArray> binData, bool udp)
{
	SFSIOHandler* instance = (SFSIOHandler*)context;

	boost::shared_ptr<ByteArray> writeBuffer (new ByteArray());
							
	// 1. Handle Compression
	if (header->Compressed())	
	{
		binData->Compress();
	}	
			
	// 1. Write packet header byte
	writeBuffer->WriteByte(header->Encode());
			
	// 2. Write packet size
	if (header->BigSized()) 
	{
		writeBuffer->WriteInt(binData->Length());
	}		
	else 
	{
		writeBuffer->WriteUShort((unsigned short int)(binData->Length()));
	}
			
	// 3. Write actual packet data
	writeBuffer->WriteBytes(binData->Bytes());
				
	// 4. Send in hyperspace!
	if (instance->bitSwarm->UseBlueBox()) 
	{
		instance->bitSwarm->HttpClient()->Send(writeBuffer);
	}
	else if (instance->bitSwarm->Socket()->IsConnected()) 
	{
		if (udp) 
		{
			instance->WriteUDP(writeBuffer);
		} 
		else 
		{
			instance->WriteTCP(writeBuffer);
		}
	}
}

// -------------------------------------------------------------------
// OnDataWrite
// -------------------------------------------------------------------
void SFSIOHandler::OnDataWrite(boost::shared_ptr<IMessage> message)
{
	boost::shared_ptr<ByteArray> binData = message->Content()->ToBinary();
			
	bool compress = binData->Length() > bitSwarm->CompressionThreshold();
			
	if (binData->Length() > bitSwarm->MaxMessageSize()) 
	{
		/*
		* Houston we have problem!
		* The outgoing message is bigger than what the server allows
		* We should stop here and provide an error to the developer
		*/
				
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Message size is too big: %d, the server limit is: %d"));
		StringFormatter<long int, long int> (err, format, binData->Length(), bitSwarm->MaxMessageSize());
				
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	// 2. Handle Encryption
	// Not implemented yet TODO
			
	long int sizeBytes = SHORT_BYTE_SIZE;
	if (binData->Length() > 65535) 
	{
		sizeBytes = INT_BYTE_SIZE;
	}
	bool blueBoxed = this->bitSwarm->UseBlueBox();
			
	boost::shared_ptr<PacketHeader> packetHeader (new PacketHeader(message->IsEncrypted(), compress, blueBoxed, sizeBytes == INT_BYTE_SIZE));
				
	if (bitSwarm->Debug()) 
	{
		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		boost::shared_ptr<string> logMessage (new string());

		boost::shared_ptr<string> format (new string("Data written: %s"));
		StringFormatter<const char*> (logMessage, format, message->Content()->GetHexDump()->c_str());
		
		logMessages->push_back(*logMessage);
		log->Info(logMessages);
	}
	
	boost::shared_ptr<WriteBinaryDataDelegate> callback (new WriteBinaryDataDelegate(&SFSIOHandler::WriteBinaryData, (unsigned long long)this));
	boost::shared_ptr<bool> isUDP (new bool());
	*isUDP = message->IsUDP();
	this->bitSwarm->ThreadManager()->EnqueueSend(callback, packetHeader, binData, isUDP);
}

// -------------------------------------------------------------------
// WriteTCP
// -------------------------------------------------------------------
void SFSIOHandler::WriteTCP(boost::shared_ptr<ByteArray> writeBuffer)
{
	bitSwarm->Socket()->Write(writeBuffer->Bytes());
}

// -------------------------------------------------------------------
// WriteUDP
// -------------------------------------------------------------------
void SFSIOHandler::WriteUDP(boost::shared_ptr<ByteArray> writeBuffer)
{
	bitSwarm->UdpManager()->Send(writeBuffer);
}

}	// namespace Core
}	// namespace Sfs2X
