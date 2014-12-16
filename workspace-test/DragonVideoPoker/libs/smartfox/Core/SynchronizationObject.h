// ===================================================================
//
// Description		
//		Contains the definition of SynchronizationObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SynchronizationObject__
#define __SynchronizationObject__

#include <boost/interprocess/sync/interprocess_mutex.hpp>	// Boost mutex

using namespace boost::interprocess;

namespace Sfs2X {
namespace Core {

	// -------------------------------------------------------------------
	// Class SynchronizationObject
	// -------------------------------------------------------------------
	class SynchronizationObject
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// lock
		// Take the ownership of the synchronization object
		void lock()
		{
			mutex.lock();
		}

		// unlock
		// Release the ownership of the synchronization object
		void unlock()
		{
			mutex.unlock();
		}

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

		boost::interprocess::interprocess_mutex mutex;	// Mutex to grant thread safe access
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
