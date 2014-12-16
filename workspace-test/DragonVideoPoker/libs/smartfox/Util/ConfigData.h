// ===================================================================
//
// Description		
//		Contains the definition of ConfigData
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ConfigData__
#define __ConfigData__

#include "./Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	/// <summary>
	/// Stores the client configuration data loaded from an external XML file
	/// </summary>
	class DLLImportExport ConfigData
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		ConfigData();

		string Host();
		void Host(string value);

		unsigned short int Port();
		void Port(unsigned short int value);

		string UdpHost();
		void UdpHost(string value);

		unsigned short int UdpPort();
		void UdpPort(unsigned short int value);

		string Zone();
		void Zone(string value);

		bool Debug();
		void Debug(bool value);

		unsigned short int HttpPort();
		void HttpPort(unsigned short int value);

		bool UseBlueBox();
		void UseBlueBox(bool value);

		long int BlueBoxPollingRate();
		void BlueBoxPollingRate(long int value);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

		
	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<string> host;
		unsigned short int port;
		boost::shared_ptr<string> udpHost;
		unsigned short int udpPort;
		boost::shared_ptr<string> zone;
		bool debug;
		
		unsigned short int httpPort;
		bool useBlueBox;
		long int blueBoxPollingRate;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
