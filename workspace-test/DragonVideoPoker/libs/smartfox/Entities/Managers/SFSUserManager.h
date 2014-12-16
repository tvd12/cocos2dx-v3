// ===================================================================
//
// Description		
//		Contains the definition of SFSUserManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSUserManager__
#define __SFSUserManager__

#include "IUserManager.h"
#include "../User.h"
#include "../../SmartFox.h"
#include "../Room.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Logging;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	/// <summary>
	/// Manages the local Users.
	/// </summary>
	/// <remarks>
	/// The client side API only see the Users that are joined in the same Rooms of the current User.
	/// </remarks>
	class DLLImportExport SFSUserManager : public IUserManager
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		SFSUserManager(boost::shared_ptr<SmartFox> sfs);
		SFSUserManager(boost::shared_ptr<Room> room);
		virtual ~SFSUserManager();
		bool ContainsUserName(string userName);
		bool ContainsUserId(long int userId);
		bool ContainsUser(boost::shared_ptr<User> user);
		boost::shared_ptr<User> GetUserByName(string userName);
		boost::shared_ptr<User> GetUserById(long int userId);
		virtual void AddUser(boost::shared_ptr<User> user);
		virtual void RemoveUser(boost::shared_ptr<User> user);
		void RemoveUserById(long int id);
		long int UserCount();
		boost::shared_ptr<SmartFox> SmartFoxClient();
		boost::shared_ptr<vector<boost::shared_ptr<User> > > GetUserList();
		void ClearAll();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		void LogWarn(boost::shared_ptr<string> msg);
		void AddUserInternal(boost::shared_ptr<User> user);

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------
		
		boost::shared_ptr<Room> room;
		boost::shared_ptr<SmartFox> sfs;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<map<string, boost::shared_ptr<User> > > usersByName;
		boost::shared_ptr<map<long int, boost::shared_ptr<User> > > usersById;
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
