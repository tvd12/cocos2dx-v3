// ===================================================================
//
// Description		
//		Contains the implementation of ConfigData
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#include "ConfigData.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ConfigData::ConfigData()
{
	host = boost::shared_ptr<string>(new string("127.0.0.1"));
	port = 9933;
	udpHost = boost::shared_ptr<string>(new string("127.0.0.1"));
	udpPort = 9933;
	zone = boost::shared_ptr<string>();
	debug = false;
		
	httpPort = 8080;
	useBlueBox = true;
	blueBoxPollingRate = 750;
}

// -------------------------------------------------------------------
// Host
// -------------------------------------------------------------------
string ConfigData::Host()
{
	return *host;
}

// -------------------------------------------------------------------
// Host
// -------------------------------------------------------------------
void ConfigData::Host(string value)
{
	host = boost::shared_ptr<string>(new string(value));
}

// -------------------------------------------------------------------
// Port
// -------------------------------------------------------------------
unsigned short int ConfigData::Port()
{
	return port;
}

// -------------------------------------------------------------------
// Port
// -------------------------------------------------------------------
void ConfigData::Port(unsigned short int value)
{
	port = value;
}

// -------------------------------------------------------------------
// UdpHost
// -------------------------------------------------------------------
string ConfigData::UdpHost()
{
	return *udpHost;
}

// -------------------------------------------------------------------
// UdpHost
// -------------------------------------------------------------------
void ConfigData::UdpHost(string value)
{
	udpHost = boost::shared_ptr<string>(new string(value));
}

// -------------------------------------------------------------------
// UdpPort
// -------------------------------------------------------------------
unsigned short int ConfigData::UdpPort()
{
	return udpPort;
}

// -------------------------------------------------------------------
// UdpPort
// -------------------------------------------------------------------
void ConfigData::UdpPort(unsigned short int value)
{
	udpPort = value;
}

// -------------------------------------------------------------------
// Zone
// -------------------------------------------------------------------
string ConfigData::Zone()
{
	return *zone;
}

// -------------------------------------------------------------------
// Zone
// -------------------------------------------------------------------
void ConfigData::Zone(string value)
{
	zone = boost::shared_ptr<string>(new string(value));
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
bool ConfigData::Debug()
{
	return debug;
}

// -------------------------------------------------------------------
// Debug
// -------------------------------------------------------------------
void ConfigData::Debug(bool value)
{
	debug = value;
}

// -------------------------------------------------------------------
// HttpPort
// -------------------------------------------------------------------
unsigned short int ConfigData::HttpPort()
{
	return httpPort;
}

// -------------------------------------------------------------------
// HttpPort
// -------------------------------------------------------------------
void ConfigData::HttpPort(unsigned short int value)
{
	httpPort = value;
}

// -------------------------------------------------------------------
// UseBlueBox
// -------------------------------------------------------------------
bool ConfigData::UseBlueBox()
{
	return useBlueBox;
}

// -------------------------------------------------------------------
// UseBlueBox
// -------------------------------------------------------------------
void ConfigData::UseBlueBox(bool value)
{
	useBlueBox = value;
}

// -------------------------------------------------------------------
// BlueBoxPollingRate
// -------------------------------------------------------------------
long int ConfigData::BlueBoxPollingRate()
{
	return blueBoxPollingRate;
}

// -------------------------------------------------------------------
// BlueBoxPollingRate
// -------------------------------------------------------------------
void ConfigData::BlueBoxPollingRate(long int value)
{
	blueBoxPollingRate = value;
}

}	// namespace Util
}	// namespace Sfs2X
