// ===================================================================
//
// Description		
//		Contains the definition of SFSGlobalUserManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSGlobalUserManager__
#define __SFSGlobalUserManager__

#include "IUserManager.h"
#include "SFSUserManager.h"
#include "../Room.h"
#include "../User.h"
#include "../../SmartFox.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	// -------------------------------------------------------------------
	// Class SFSGlobalUserManager
	// -------------------------------------------------------------------
	class SFSGlobalUserManager : public SFSUserManager//, IUserManager
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSGlobalUserManager(boost::shared_ptr<SmartFox> sfs);
		SFSGlobalUserManager(boost::shared_ptr<Room> room);
		virtual ~SFSGlobalUserManager();

		/// <summary>
		/// Does not allow duplicates and keeps a reference count
		/// </summary>
		/// <param name="user">
		/// Pointer to an <see cref="User"/> instance
		/// </param>
		void AddUser(boost::shared_ptr<User> user);

		void RemoveUser(boost::shared_ptr<User> user);
		
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

		map<boost::shared_ptr<User>, long int> roomRefCount;
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
