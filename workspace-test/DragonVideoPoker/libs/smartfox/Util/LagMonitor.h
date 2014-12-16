// ===================================================================
//
// Description		
//		Contains the definition of LagMonitor
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __LagMonitor__
#define __LagMonitor__

// Forward class declaration
namespace Sfs2X {
namespace Util {
	class LagMonitor;
}	// namespace Util
}	// namespace Sfs2X

#include "../SmartFox.h"

#include <boost/bind.hpp>								// Boost Asio header
#include <boost/asio.hpp>								// Boost Asio header
#include <boost/asio/deadline_timer.hpp>				// Boost Asio header
#include <boost/shared_ptr.hpp>							// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <list>							// STL library: list object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Requests;
using boost::asio::ip::tcp;					// Boost Asio namespace

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class LagMonitor
	// -------------------------------------------------------------------
	class DLLImportExport LagMonitor
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs);
		LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval);
		LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval, unsigned long int queueSize);
		virtual ~LagMonitor();

		void Start();
		void Stop();
		void Destroy();
		bool IsRunning();
		long int OnPingPong();
		long int LastPingTime();
		long int AveragePingTime();

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
		void Init(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval, unsigned long int queueSize);
		void OnPollEvent(const boost::system::error_code& code);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<boost::posix_time::ptime> lastReqTime;
		boost::shared_ptr<list<long int> > valueQueue;
		long int interval;
		unsigned long int queueSize;
		boost::shared_ptr<SmartFox> sfs;

		boost::asio::io_service& boostIoService;			// Boost Asio IO service		
		boost::shared_ptr<boost::asio::deadline_timer> pollTimer;		
		bool isPollTimerRunning;
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
