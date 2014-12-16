// ===================================================================
//
// Description		
//		Contains the definition of ISocketLayer interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ISocketLayer__
#define __ISocketLayer__

#include "IPAddress.h"							// An ip address entity
#include "SocketErrors.h"						// Socket error codes
#include "../../Util/DelegateZeroArgument.h"	// Delegate without parameters
#include "../../Util/DelegateOneArgument.h"		// Delegate with one parameter
#include "../../Util/DelegateTwoArguments.h"	// Delegate with two parameters

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Core;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {
namespace Sockets {

	// -------------------------------------------------------------------
	// Definition of delegates specific for the socket layer 
	// -------------------------------------------------------------------
	typedef DelegateZeroArgument ConnectionDelegate;
	typedef DelegateOneArgument<boost::shared_ptr<vector<unsigned char> > > OnDataDelegate;
	typedef DelegateTwoArguments<boost::shared_ptr<string>, Sfs2X::Core::Sockets::SocketErrors> OnErrorDelegate;

	// -------------------------------------------------------------------
	// Interface ISocketLayer
	// -------------------------------------------------------------------
	class ISocketLayer
	{
	public:
		virtual void Connect(boost::shared_ptr<IPAddress> address, unsigned short int port) = 0;
		virtual bool IsConnected() = 0;
		virtual bool RequiresConnection() = 0;
		virtual void Disconnect() = 0;

		virtual boost::shared_ptr<ConnectionDelegate> OnConnect() = 0;						// Get delegate
		virtual void OnConnect(boost::shared_ptr<ConnectionDelegate> onConnect) = 0;		// Set delegate

		virtual boost::shared_ptr<ConnectionDelegate> OnDisconnect() = 0;					// Get delegate
		virtual void OnDisconnect(boost::shared_ptr<ConnectionDelegate> onDisconnect) = 0;	// Set delegate

		virtual void Write(boost::shared_ptr<vector<unsigned char> >) = 0;

		virtual boost::shared_ptr<OnDataDelegate> OnData() = 0;								// Get delegate
		virtual void OnData(boost::shared_ptr<OnDataDelegate> onData) = 0;					// Set delegate

		virtual boost::shared_ptr<OnErrorDelegate> OnError() = 0;							// Get delegate
		virtual void OnError(boost::shared_ptr<OnErrorDelegate> onError) = 0;				// Set delegate

		virtual void Kill() = 0;
	};

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X

#endif
