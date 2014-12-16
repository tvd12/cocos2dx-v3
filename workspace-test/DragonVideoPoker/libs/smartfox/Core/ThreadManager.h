// ===================================================================
//
// Description		
//		Contains the definition of thread manager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ThreadManager__
#define __ThreadManager__

#include "../Util/DelegateOneArgument.h"		// Delegate with one parameter
#include "../Util/DelegateThreeArguments.h"		// Delegate with three parameter
#include "../Core/Sockets/ISocketLayer.h"		// ISocketLayer interface

#include "../Core/PacketHeader.h"
#include "../Util/ByteArray.h"

#include <boost/thread.hpp>				// Boost thread
#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <map>							// STL library: map object
#include <vector>						// STL library: vector object
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Core::Sockets;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Core {

	// -------------------------------------------------------------------
	// Definition of delegates specific for the thread manager
	// -------------------------------------------------------------------
	typedef DelegateOneArgument<boost::shared_ptr<void> > ParameterizedThreadStart;
	typedef DelegateThreeArguments<boost::shared_ptr<PacketHeader>, boost::shared_ptr<ByteArray>, bool> WriteBinaryDataDelegate;

	// -------------------------------------------------------------------
	// Class ThreadManager
	// -------------------------------------------------------------------
	class ThreadManager
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		ThreadManager();
		~ThreadManager();

		void EnqueueCustom(boost::shared_ptr<ParameterizedThreadStart> callback, boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data);
		void EnqueueDataCall(boost::shared_ptr<OnDataDelegate> callback, boost::shared_ptr<vector<unsigned char> > data);
		void EnqueueSend(boost::shared_ptr<WriteBinaryDataDelegate> callback, boost::shared_ptr<PacketHeader> header, boost::shared_ptr<ByteArray> data, boost::shared_ptr<bool> udp);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		void Start();

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

		void InThread();
		void OutThread();
		void ProcessOutItem(boost::shared_ptr<map<string, boost::shared_ptr<void> > > item);
		void ProcessItem(boost::shared_ptr<map<string, boost::shared_ptr<void> > > item);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		bool running;
		
		boost::shared_ptr<boost::thread> inThread;
		bool inHasQueuedItems;
		boost::shared_ptr<list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > > > inThreadQueue;
		boost::mutex inQueueLocker;
		
		boost::shared_ptr<boost::thread> outThread;
		bool outHasQueuedItems;
		boost::shared_ptr<list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > > > outThreadQueue;
		boost::mutex outQueueLocker;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
