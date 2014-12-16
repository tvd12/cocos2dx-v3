// ===================================================================
//
// Description		
//		Contains the definition of BBClient
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BBClient__
#define __BBClient__

// Forward class declaration
namespace Sfs2X {
namespace Bitswarm {
namespace BBox {
	class BBClient;
}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X

#include "../../Http/SFSWebClient.h"
#include "../../Core/IDispatchable.h"
#include "../../Util/ByteArray.h"
#include "../../Logging/Logger.h"
#include "../BitSwarmClient.h"

#include <boost/asio/deadline_timer.hpp>		// Boost Asio header
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

using namespace Sfs2X::Core;
using namespace Sfs2X::Util;
using namespace Sfs2X::Logging;
using namespace Sfs2X::Http;

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

	// -------------------------------------------------------------------
	// Class BBClient
	// -------------------------------------------------------------------
	class BBClient : public boost::enable_shared_from_this<BBClient>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		void Initialize();

		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Getters / Setters
		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		BBClient(boost::shared_ptr<BitSwarmClient> bs);
		bool IsConnected();
		bool IsDebug();
		void IsDebug(bool value);
		boost::shared_ptr<string> Host();
		unsigned short int Port();
		boost::shared_ptr<string> SessionId();
		long int PollSpeed();
		void PollSpeed(long int value);

		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Public methods
		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		void Connect (boost::shared_ptr<string> host, unsigned short int port);
		void Send (boost::shared_ptr<ByteArray> binData);
		void Close();
		void AddEventListener (boost::shared_ptr<string> eventType, boost::shared_ptr<EventListenerDelegate> listener);
		boost::shared_ptr<EventDispatcher> Dispatcher();
		void DispatchEvent(boost::shared_ptr<BaseEvent> evt);

		// ------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		static boost::shared_ptr<string> BB_SERVLET;

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
		static void OnHttpResponse (unsigned long long context, bool error, boost::shared_ptr<string> response); 
		void Poll (const boost::system::error_code& code);
		void SendRequest (boost::shared_ptr<string> cmd);
		void SendRequest (boost::shared_ptr<string> cmd, boost::shared_ptr<void> data);
		boost::shared_ptr<SFSWebClient> GetWebClient();
		void HandleConnectionLost (bool fireEvent);

		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Message Codec
		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		boost::shared_ptr<string> EncodeRequest (boost::shared_ptr<string> cmd);
		boost::shared_ptr<string> EncodeRequest (boost::shared_ptr<string> cmd, boost::shared_ptr<void> data);
		boost::shared_ptr<ByteArray> DecodeResponse (boost::shared_ptr<string> rawData);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> BB_DEFAULT_HOST;
		const static unsigned short int BB_DEFAULT_PORT = 8080;
		static boost::shared_ptr<string> BB_NULL;

		static boost::shared_ptr<string> CMD_CONNECT;
		static boost::shared_ptr<string> CMD_POLL;
		static boost::shared_ptr<string> CMD_DATA;
		static boost::shared_ptr<string> CMD_DISCONNECT;
		static boost::shared_ptr<string> ERR_INVALID_SESSION; 

		static boost::shared_ptr<string> SFS_HTTP;

		const static long int MIN_POLL_SPEED = 50;
		// ms
		const static long int MAX_POLL_SPEED = 5000;
		// ms
		const static long int DEFAULT_POLL_SPEED = 300;
		// ms

		bool isConnected;
		boost::shared_ptr<string> host;
		unsigned short int port;
		boost::shared_ptr<string> bbUrl;
		bool debug;
		boost::shared_ptr<string> sessId;
		long int pollSpeed;
		
		boost::shared_ptr<EventDispatcher> dispatcher;

		boost::shared_ptr<Logger> log;

		boost::shared_ptr<boost::asio::deadline_timer> pollTimer;			// Boost Asio deadline timer
		boost::shared_ptr<boost::asio::io_service> boostService;
	};

}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
