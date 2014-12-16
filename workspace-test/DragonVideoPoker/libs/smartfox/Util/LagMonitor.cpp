// ===================================================================
//
// Description		
//		Contains the implementation of LagMonitor
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "LagMonitor.h"
#include "../Requests/PingPongRequest.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LagMonitor::LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs)
	: boostIoService(io_service)
{
	  this->Init(io_service, sfs, 4, 10);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LagMonitor::LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval)
	: boostIoService(io_service)
{
	  this->Init(io_service, sfs, interval, 10);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LagMonitor::LagMonitor(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval, unsigned long int queueSize)
	: boostIoService(io_service)
{
	  this->Init(io_service, sfs, interval, queueSize);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
LagMonitor::~LagMonitor()
{
	Destroy();
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void LagMonitor::Init(boost::asio::io_service& io_service, boost::shared_ptr<SmartFox> sfs, long int interval, unsigned long int queueSize)
{
	if (interval < 1) {
		interval = 1;
	}

	this->isPollTimerRunning = false;
	this->sfs = sfs;
	this->valueQueue = boost::shared_ptr<list<long int> >(new list<long int>());
	this->interval = interval;
	this->queueSize = queueSize;
	this->lastReqTime = boost::shared_ptr<boost::posix_time::ptime>(new boost::posix_time::ptime(boost::posix_time::microsec_clock::local_time())); 
	this->pollTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(io_service));
}

// -------------------------------------------------------------------
// Start
// -------------------------------------------------------------------
void LagMonitor::Start()
{
	if (IsRunning())
	{
		return;
	}

    pollTimer->expires_from_now(boost::posix_time::seconds(this->interval));
	pollTimer->async_wait(boost::bind(&LagMonitor::OnPollEvent, this, boost::asio::placeholders::error));
	isPollTimerRunning = true;
}

// -------------------------------------------------------------------
// Stop
// -------------------------------------------------------------------
void LagMonitor::Stop()
{
	if (IsRunning())
	{
		pollTimer->cancel();
		isPollTimerRunning = false;
	}
}

// -------------------------------------------------------------------
// Destroy
// -------------------------------------------------------------------
void LagMonitor::Destroy()
{
	Stop();
	valueQueue->clear();
}

// -------------------------------------------------------------------
// IsRunning
// -------------------------------------------------------------------
bool LagMonitor::IsRunning()
{
	return isPollTimerRunning;
}

// -------------------------------------------------------------------
// OnPingPong
// -------------------------------------------------------------------
long int LagMonitor::OnPingPong()
{
	// Calculate lag
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration duration = now - (*lastReqTime);
    long int lagValue = (long int)(duration.total_milliseconds());

	// Remove older value
	if (valueQueue->size() >= queueSize)
		valueQueue->pop_front();

	// Add new lag
	valueQueue->push_back(lagValue);

	return AveragePingTime();
}

// -------------------------------------------------------------------
// LastPingTime
// -------------------------------------------------------------------
long int LagMonitor::LastPingTime()
{
	if (valueQueue->size() > 0)
		return valueQueue->back();
	else
		return 0;
}

// -------------------------------------------------------------------
// AveragePingTime
// -------------------------------------------------------------------
long int LagMonitor::AveragePingTime()
{
	if (valueQueue->size() == 0)
		return 0;

	int lagAverage = 0;

	list<long int>::iterator iterator;
	for (iterator = valueQueue->begin(); iterator != valueQueue->end(); iterator++)
	{
		lagAverage += (*iterator);
	}

	return lagAverage / valueQueue->size();
}

// -------------------------------------------------------------------
// OnPollEvent
// -------------------------------------------------------------------
void LagMonitor::OnPollEvent(const boost::system::error_code& code)
{
	if (code == boost::asio::error::operation_aborted)
	{
		// Timer has been stopped
		// Nothing to do
		return;
	}

	*lastReqTime = boost::posix_time::microsec_clock::local_time();
	boost::shared_ptr<IRequest> request (new PingPongRequest());
	sfs->Send(request);

	if (IsRunning())
	{
		pollTimer->expires_from_now(boost::posix_time::seconds(this->interval));
		pollTimer->async_wait(boost::bind(&LagMonitor::OnPollEvent, this, boost::asio::placeholders::error));
	}
}

}	// namespace Util
}	// namespace Sfs2X

