// ===================================================================
//
// Description		
//		Contains the implementation of thread manager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ThreadManager.h"

namespace Sfs2X {
namespace Core {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ThreadManager::ThreadManager()
{
	running = false;
	inHasQueuedItems = false;
	inThreadQueue = boost::shared_ptr<list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > > >(new list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > >());
	inThread = boost::shared_ptr<boost::thread>();
		
	outHasQueuedItems = false;
	outThreadQueue = boost::shared_ptr<list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > > >(new list<boost::shared_ptr<map<string, boost::shared_ptr<void> > > >());
	outThread = boost::shared_ptr<boost::thread>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ThreadManager::~ThreadManager()
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > item;

	while (inThreadQueue->size() > 0) 
	{
		item = inThreadQueue->front();
		inThreadQueue->pop_front();

		item->clear();
	}

	while (outThreadQueue->size() > 0) 
	{
		item = outThreadQueue->front();
		outThreadQueue->pop_front();

		item->clear();
	}
}

// -------------------------------------------------------------------
// InThread
// -------------------------------------------------------------------
void ThreadManager::InThread()
{
	boost::posix_time::milliseconds workTime(5);

	while (running) 
	{
		boost::this_thread::sleep(workTime);  
				
		if (!inHasQueuedItems) continue;
				
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > item;
				
		inQueueLocker.lock();

		while (inThreadQueue->size() > 0) 
		{
			item = inThreadQueue->front();
			inThreadQueue->pop_front();
			ProcessItem(item);

			item->clear();
		}
					
		inHasQueuedItems = false;

		inQueueLocker.unlock();
	}
}

// -------------------------------------------------------------------
// OutThread
// -------------------------------------------------------------------
void ThreadManager::OutThread()
{
	boost::posix_time::milliseconds workTime(5);

	while (running) 
	{
		boost::this_thread::sleep(workTime);  
				
		if (!outHasQueuedItems) continue;
				
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > item;
				
		outQueueLocker.lock();

		while (outThreadQueue->size() > 0) 
		{
			item = outThreadQueue->front();
			outThreadQueue->pop_front();
			ProcessOutItem(item);

			item->clear();
		}
					
		outHasQueuedItems = false;

		outQueueLocker.unlock();
	}
}

// -------------------------------------------------------------------
// ProcessOutItem
// -------------------------------------------------------------------
void ThreadManager::ProcessOutItem(boost::shared_ptr<map<string, boost::shared_ptr<void> > > item)
{
	map<string, boost::shared_ptr<void> >::iterator iterator; 
	
	iterator = item->find("callback");
	boost::shared_ptr<void> callback = iterator == item->end() ? boost::shared_ptr<void>() : iterator->second;
			
	boost::shared_ptr<WriteBinaryDataDelegate> onData = (boost::static_pointer_cast<WriteBinaryDataDelegate>)(callback);

	if (onData != NULL) 
	{
		iterator = item->find("data");
		boost::shared_ptr<ByteArray> data = iterator == item->end() ? boost::shared_ptr<ByteArray>() : (boost::static_pointer_cast<ByteArray>)(iterator->second);
		
		iterator = item->find("header");
		boost::shared_ptr<PacketHeader> header = iterator == item->end() ? boost::shared_ptr<PacketHeader>() : (boost::static_pointer_cast<PacketHeader>)(iterator->second);

		iterator = item->find("udp");
		boost::shared_ptr<bool> udp = iterator == item->end() ? boost::shared_ptr<bool>() : (boost::static_pointer_cast<bool>)(iterator->second);
			
		onData->Invoke(header, data, *udp);
		return;
	}
}

// -------------------------------------------------------------------
// ProcessItem
// -------------------------------------------------------------------
void ThreadManager::ProcessItem(boost::shared_ptr<map<string, boost::shared_ptr<void> > > item)
{
	map<string, boost::shared_ptr<void> >::iterator iterator; 
	
	iterator = item->find("callback");
	boost::shared_ptr<void> callback = iterator == item->end() ? boost::shared_ptr<void>() : iterator->second;

	if (callback != NULL) 
	{
		iterator = item->find("data");
		if (iterator != item->end())
		{
			boost::shared_ptr<OnDataDelegate> onData = (boost::static_pointer_cast<OnDataDelegate>)(callback);

			boost::shared_ptr<vector<unsigned char> > data = (boost::static_pointer_cast<vector<unsigned char> >)(iterator->second);
			onData->Invoke(data);

			return; 
		}
	}

	boost::shared_ptr<ParameterizedThreadStart> custom = (boost::static_pointer_cast<ParameterizedThreadStart>)(callback);
	if (custom != NULL) 
	{
		custom->Invoke(item);
		return;
	}
}

// -------------------------------------------------------------------
// Start
// -------------------------------------------------------------------
void ThreadManager::Start()
{
	if (running) return;
			
	running = true;
		
	if (this->inThread == NULL) 
	{
		this->inThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&ThreadManager::InThread, this)));
	}
			
	if (this->outThread == NULL) 
	{
		this->outThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&ThreadManager::OutThread, this)));
	}
}

// -------------------------------------------------------------------
// EnqueueDataCall
// -------------------------------------------------------------------
void ThreadManager::EnqueueDataCall(boost::shared_ptr<OnDataDelegate> callback, boost::shared_ptr<vector<unsigned char> > data)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());
	args->insert (pair<string, boost::shared_ptr<void> >("callback", callback));
	args->insert (pair<string, boost::shared_ptr<void> >("data", data));

	inQueueLocker.lock();

	inThreadQueue->push_back(args);
	inHasQueuedItems = true;
	
	inQueueLocker.unlock();
}

// -------------------------------------------------------------------
// EnqueueCustom
// -------------------------------------------------------------------
void ThreadManager::EnqueueCustom(boost::shared_ptr<ParameterizedThreadStart> callback, boost::shared_ptr<std::map<string, boost::shared_ptr<void> > > data)
{
	data->insert (pair<string, boost::shared_ptr<void> >("callback", callback));

	inQueueLocker.lock();
	
	inThreadQueue->push_back(data);
	inHasQueuedItems = true;

	inQueueLocker.unlock();
}

// -------------------------------------------------------------------
// EnqueueSend
// -------------------------------------------------------------------
void ThreadManager::EnqueueSend(boost::shared_ptr<WriteBinaryDataDelegate> callback, boost::shared_ptr<PacketHeader> header, boost::shared_ptr<ByteArray> data, boost::shared_ptr<bool> udp)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > args (new map<string, boost::shared_ptr<void> >());
	args->insert (pair<string, boost::shared_ptr<void> >("callback", callback));
	args->insert (pair<string, boost::shared_ptr<void> >("header", header));
	args->insert (pair<string, boost::shared_ptr<void> >("data", data));
	args->insert (pair<string, boost::shared_ptr<void> >("udp", udp));

	outQueueLocker.lock();

	outThreadQueue->push_back(args);
	outHasQueuedItems = true;
		
	outQueueLocker.unlock();
}

}	// namespace Core
}	// namespace Sfs2X
