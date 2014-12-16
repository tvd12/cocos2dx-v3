// ===================================================================
//
// Description		
//		Contains the definition of SFSBuddyManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSBuddyManager__
#define __SFSBuddyManager__

#include "IBuddyManager.h"
#include "../../SmartFox.h"
#include "../SFSBuddy.h"

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
using namespace Sfs2X::Entities::Variables;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	/// <summary>
	/// The class manages the current User's Buddy List
	/// </summary>
	class DLLImportExport SFSBuddyManager : public IBuddyManager
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		SFSBuddyManager(boost::shared_ptr<SmartFox> sfs);
		virtual ~SFSBuddyManager();

		bool Inited();
		void Inited(bool value);
		void AddBuddy(boost::shared_ptr<Buddy> buddy);
		void ClearAll();
		boost::shared_ptr<Buddy> RemoveBuddyById(long int id);
		boost::shared_ptr<Buddy> RemoveBuddyByName(string name);
		boost::shared_ptr<Buddy> GetBuddyById(long int id);
		bool ContainsBuddy(string name);
		boost::shared_ptr<Buddy> GetBuddyByName(string name);
		boost::shared_ptr<Buddy> GetBuddyByNickName(string nickName);
		boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > OfflineBuddies();
		boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > OnlineBuddies();
		boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > BuddyList();
		boost::shared_ptr<BuddyVariable> GetMyVariable(string varName);
		boost::shared_ptr<BuddyVariable> GetMyVariable(boost::shared_ptr<string> varName);
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > MyVariables();
		void MyVariables(boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > value);
		bool MyOnlineState();
		void MyOnlineState(bool value);
		boost::shared_ptr<string> MyNickName();
		void MyNickName(string value);
		boost::shared_ptr<string> MyState();
		void MyState(string value);
		boost::shared_ptr<vector<string> > BuddyStates();
		void BuddyStates(boost::shared_ptr<vector<string> > value);
		void SetMyVariable(boost::shared_ptr<BuddyVariable> bVar);

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
		boost::shared_ptr<map<string, boost::shared_ptr<Buddy> > > buddiesByName;
		boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > > myVariables;
		bool myOnlineState;
		bool inited;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<vector<string> > buddyStates;
		boost::shared_ptr<SmartFox> sfs;		
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
