// ===================================================================
//
// Description		
//		Contains the implementation of UDPManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "UDPManager.h"
#include "../Core/Sockets/UDPSocketLayer.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
UDPManager::UDPManager(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs)
	: boostIoService(io_service),
	  initThread(io_service)
{
	this->sfs = sfs;
	this->packetId = 0;
	if (sfs != NULL) {
		this->log = sfs->Log();
	}
	else {
		this->log = boost::shared_ptr<Logger>(new Logger(boost::shared_ptr<SmartFox>())); // Dummy log for tests
	}
	this->currentAttempt = 1;

	this->udpSocket = boost::shared_ptr<ISocketLayer>();
	this->inited = false;
	this->locked = false;  
	this->initSuccess = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
UDPManager::~UDPManager()
{
}

// -------------------------------------------------------------------
// Initialize
// -------------------------------------------------------------------
void UDPManager::Initialize(string udpAddr, unsigned short int udpPort)
{
	if (this->initSuccess)
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back("UDP Channel already initialized!");

		log->Warn(messages);
		return;
	}

	if (!this->locked)
	{
		// Lock the object
		this->locked = true;
		udpSocket = boost::shared_ptr<ISocketLayer>(new UDPSocketLayer(this->sfs));

		boost::shared_ptr<OnDataDelegate> delegateOnData(new OnDataDelegate(&UDPManager::OnUDPData, (unsigned long long)this));
		udpSocket->OnData(delegateOnData);

		boost::shared_ptr<OnErrorDelegate> delegateOnError(new OnErrorDelegate(&UDPManager::OnUDPError, (unsigned long long)this));
		udpSocket->OnError(delegateOnError);

		boost::shared_ptr<IPAddress> address (new IPAddress(IPAddress::IPADDRESSTYPE_IPV4, udpAddr));
		udpSocket->Connect(address, udpPort);	

		SendInitializationRequest();
	}
	else {
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back("UPD initialization is already in progress!");

		log->Warn(messages);
	}		
}

// -------------------------------------------------------------------
// NextUdpPacketId
// -------------------------------------------------------------------
long long UDPManager::NextUdpPacketId()
{
	return packetId++;
}

// -------------------------------------------------------------------
// Send
// -------------------------------------------------------------------
void UDPManager::Send(boost::shared_ptr<ByteArray> binaryData)
{
	if (initSuccess) {
		try {
			udpSocket->Write(binaryData->Bytes());

			if (sfs->Debug()) {

				boost::shared_ptr<vector<string> > logMessages (new vector<string>());
				logMessages->push_back("UDP Data written: ");
				logMessages->push_back(*(DefaultObjectDumpFormatter::HexDump(binaryData)));
				log->Info(logMessages);
			}
		}
		catch(exception ex) {

			boost::shared_ptr<string> message (new string(ex.what()));

			char buffer[512];
			sprintf (buffer, "WriteUDP operation failed due to Error: %s", message->c_str());
			string logMessage = buffer;

			boost::shared_ptr<vector<string> > logMessages (new vector<string>());
			logMessages->push_back(logMessage);
			log->Error(logMessages);
		}
	}
	else {
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back("UDP protocol is not initialized yet. Pleas use the initUDP() method.");
		log->Warn(messages);
	}
}

// -------------------------------------------------------------------
// Inited
// -------------------------------------------------------------------
bool UDPManager::Inited()
{
	return initSuccess;
}

// -------------------------------------------------------------------
// isConnected
// -------------------------------------------------------------------
bool UDPManager::isConnected()
{
	return udpSocket->IsConnected();
}

// -------------------------------------------------------------------
// Reset
// -------------------------------------------------------------------
void UDPManager::Reset()
{
	StopTimer();
	currentAttempt = 1;
	inited = false;
	initSuccess = false;
	locked = false;
	packetId  = 0;
}

// -------------------------------------------------------------------
// OnUDPData
// -------------------------------------------------------------------
void UDPManager::OnUDPData(unsigned long long context, boost::shared_ptr<vector<unsigned char> > bt)
{
	// Map context
	UDPManager* instance = (UDPManager*)context;

	boost::shared_ptr<ByteArray> bytes (new ByteArray(bt));

	// Not enough data!
	if (bytes->BytesAvailable() < 4) {
		char buffer[512];
		sprintf (buffer, "Too small UDP packet. Len: %ld", bytes->Length());
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		instance->log->Warn(logMessages);

		return;
	}

	if (instance->sfs->Debug()) {

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back("UDP Data Read: ");
		logMessages->push_back(*(DefaultObjectDumpFormatter::HexDump(bytes)));
		instance->log->Info(logMessages);
	}

	// Skip the header byte
	unsigned char header;
	bytes->ReadByte(header);

	// Get the compression flag
	bool compressed = (header & 0x20) > 0; 

	// Read the size of message (UDP can only use the short version)
	short dataSize;
	bytes->ReadShort(dataSize);

	if (dataSize != bytes->BytesAvailable()) {
		char buffer[512];
		sprintf (buffer, "Insufficient UDP data. Expected: %ld, got: %ld", dataSize, bytes->BytesAvailable());
		string logMessage = buffer;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());
		logMessages->push_back(logMessage);
		instance->log->Warn(logMessages);

		return;
	}

	// Grab the message body and deserialize it
	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>());
	bytes->ReadBytes(bytes->BytesAvailable(), *(data.get()));
	boost::shared_ptr<ByteArray> objBytes (new ByteArray(data));
	if (compressed) {
		objBytes->Uncompress();
	}

	boost::shared_ptr<ISFSObject> reqObj = SFSObject::NewFromBinaryData(objBytes);

	// Check if this is an UDP Handshake response. If so, fire event and stop here.
	if (reqObj->ContainsKey("h")) {
		if (!instance->initSuccess) {
			// Unlock
			instance->StopTimer();
			instance->locked = false;
			instance->initSuccess = true;

			boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
			boost::shared_ptr<bool> value (new bool());
			*value = true;
			evtParams->insert(pair<string, boost::shared_ptr<void> >("success", value));
			boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::UDP_INIT, evtParams));
			instance->sfs->DispatchEvent(evt);
		}
		return;
	}
			
	// Hand it to the ProtocolCodec
	instance->sfs->GetSocketEngine()->IoHandler()->Codec()->OnPacketRead(reqObj);
}

// -------------------------------------------------------------------
// OnUDPError
// -------------------------------------------------------------------
void UDPManager::OnUDPError(unsigned long long context, boost::shared_ptr<string> msg, SocketErrors se)
{
	// Map context
	UDPManager* instance = (UDPManager*)context;

	char buffer[512];
	sprintf (buffer, "Unexpected UDP I/O Error. %s [%ld]", msg->c_str(), se);
	string logMessage = buffer;

	boost::shared_ptr<vector<string> > logMessages (new vector<string>());
	logMessages->push_back(logMessage);
	instance->log->Warn(logMessages);
}

// -------------------------------------------------------------------
// SendInitializationRequest
// -------------------------------------------------------------------
void UDPManager::SendInitializationRequest()
{
	// Prepare full packet
	boost::shared_ptr<ISFSObject> message (new SFSObject());
	
	boost::shared_ptr<unsigned char> valueUChar;
	boost::shared_ptr<long long> valueLong;
	boost::shared_ptr<long int> valueInt;

	valueUChar = boost::shared_ptr<unsigned char>(new unsigned char());
	*valueUChar = 1;
	message->PutByte("c", valueUChar);	
	
	valueUChar = boost::shared_ptr<unsigned char>(new unsigned char());
	*valueUChar = 1;
	message->PutByte("h", valueUChar); // <<---- Handshake!

	valueLong = boost::shared_ptr<long long>(new long long());
	*valueLong = NextUdpPacketId();
	message->PutLong("i", valueLong);

	valueInt = boost::shared_ptr<long int>(new long int());
	*valueInt = sfs->MySelf()->Id();
	message->PutInt("u", valueInt);
			
	boost::shared_ptr<ByteArray> binData = message->ToBinary();
			
	// TODO - looks like not needed
	//bool compress = false;
			
	// Assemble SFS2X packet
	boost::shared_ptr<ByteArray> writeBuffer (new ByteArray());
			
	// Regular Header
	writeBuffer->WriteByte(0x80);
			
	// Message len
	writeBuffer->WriteShort((short int)binData->Length());
			
	// Packet data
	writeBuffer->WriteBytes(binData->Bytes());
			
	udpSocket->Write(writeBuffer->Bytes());
			
	// Start the timeout thread
	StartTimer();
}

// -------------------------------------------------------------------
// OnTimeout
// -------------------------------------------------------------------
void UDPManager::OnTimeout(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Timer has been stopped
		// Nothing to do
		return;
	}

	// Timer is expired

	if (initSuccess) return;
			
	if (currentAttempt < MAX_RETRY) {
		// Try again
		currentAttempt++;

		boost::shared_ptr<vector<string> > logMessages (new vector<string>());

		boost::shared_ptr<string> logMessage (new string());
		boost::shared_ptr<string> format (new string("UDP Init Attempt: %d"));
		StringFormatter<long int> (logMessage, format, currentAttempt);
		
		logMessages->push_back(*logMessage);
		log->Debug(logMessages);

					
		SendInitializationRequest();
		StartTimer();
	}
	else {
		// If we get here all trials failed
		currentAttempt = 0;
		locked = false;

		boost::shared_ptr<map<string, boost::shared_ptr<void> > > evtParams (new map<string, boost::shared_ptr<void> >());
		boost::shared_ptr<bool> value (new bool());
		*value = false;
		evtParams->insert(pair<string, boost::shared_ptr<void> >("success", value));
		boost::shared_ptr<SFSEvent> evt (new SFSEvent(SFSEvent::UDP_INIT, evtParams));
		sfs->DispatchEvent(evt);
	}
}

// -------------------------------------------------------------------
// StartTimer
// -------------------------------------------------------------------
void UDPManager::StartTimer()
{
    initThread.expires_from_now(boost::posix_time::seconds(RESPONSE_TIMEOUT));
	initThread.async_wait(boost::bind(&UDPManager::OnTimeout, this, boost::asio::placeholders::error));
}

// -------------------------------------------------------------------
// StopTimer
// -------------------------------------------------------------------
void UDPManager::StopTimer()
{
	initThread.cancel();
}

// -------------------------------------------------------------------
// Disconnect
// -------------------------------------------------------------------
void UDPManager::Disconnect()
{
	this->udpSocket->Disconnect();
	Reset ();
}

}	// namespace Bitswarm
}	// namespace Sfs2X
