// ===================================================================
//
// Description		
//		Contains the definition of SFSBuddy
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSBuddy__
#define __SFSBuddy__

#include "Data/ISFSArray.h"
#include "Buddy.h"
#include "Variables/BuddyVariable.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object 
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {

	/// <summary>
	/// The <b>SFSBuddy</b> class represent a Buddy in the User's <b>Buddy List</b>
	/// </summary>
	/// <remarks>
	/// <h2>Overview</h2>
	/// The <b>SFSBuddy</b> class represent a Buddy in the User's <b>Buddy List</b>.
	/// Each Buddy has several properties:
	///
	/// <ul>
	/// 	<li><b>name</b>: the name of the Buddy, corresponds to the User name</li>
	/// 	<li><b>nickname</b>: an optional nickname (default = null)</li>
	/// 	<li><b>isOnline</b>: whether the Buddy is online in the Buddy system or not</li>
	/// 	<li><b>state</b>: a string representing a "state message", such as: <i>Available</i>, <i>Busy</i>...</li>
	/// 	<li><b>isBlocked</b>: whether the Buddy is blocked in the User Buddy List</li>
	/// 	<li><b>isTemp</b>: a temporary Buddy is not stored in the Buddy List, it will be removed at the end of the session (see below)</li>
	/// 	<li><b>variables</b>: the Buddy variables which can be transient or persistent (see below)</li>
	/// </ul>
	///
	/// <h3>Online State</h3>
	/// Any user can decide if they want to be online/off-line as Buddy in the Buddy system. By default a User is online 
	/// every time he joins the Zone, but the User can also turn off this flag at runtime and disappear from other User's buddy lists.
	/// The <b>Online State</b> is persistent and based on a reserved Buddy Variable.
	/// 
	/// <h3>Blocked Buddies</h3>
	/// Buddies that are blocked won't be able to send any messages to the User, also they won't be able to see if the Buddy is online/off-line.
	/// 
	/// <h3>Buddy State message</h3>
	/// The state message represents a typical IM Buddy state such as Available, Busy etc...
	/// By default the system already provides 3 default states: <b>Available</b>, <b>Away</b>, <b>Occupied</b> which can be changed or enriched at any time 
	/// The state message is based on a reserved Buddy Variable.
	/// 
	/// <h3>Temp Buddy</h3>
	/// A temporary Buddy is added to the User List when another User adds me to his Buddy List. 
	/// This way we can see each others and exchange messages. 
	/// If I don't add the User as Buddy in my list the User will remain temporary and it won't be persisted. 
	/// 
	/// <h3>Variables</h3>
	/// Buddy Variables enable each Buddy to show/send updates for specific informations to each User that has the Buddy in the list. 
	/// For example one could send real-time updates on his last activity (ala Twitter) or post the title of the song he's listening right now, scores, 
	/// rankings and whatnot.
	/// </remarks>
	class DLLImportExport SFSBuddy : public Buddy
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		static boost::shared_ptr<Buddy> FromSFSArray(boost::shared_ptr<ISFSArray> arr);

		SFSBuddy(long int id, string name);
		SFSBuddy(long int id, string name, bool isBlocked);
		SFSBuddy(long int id, string name, bool isBlocked, bool isTemp);
		virtual ~SFSBuddy();

		long int Id();
		void Id(long int value);
		bool IsBlocked();
		void IsBlocked(bool value);
		bool IsTemp();
		boost::shared_ptr<string> Name();
		bool IsOnline();
		boost::shared_ptr<string> State();
		boost::shared_ptr<string> NickName();
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > Variables();
		boost::shared_ptr<BuddyVariable> GetVariable(string varName);
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > GetOfflineVariables();
		boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > GetOnlineVariables();
		bool ContainsVariable(string varName);
		void SetVariable(boost::shared_ptr<BuddyVariable> bVar);
		void SetVariables(boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > variables);
		void RemoveVariable(string varName);
		void ClearVolatileVariables();
		boost::shared_ptr<string> ToString();

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
		boost::shared_ptr<string> name;
		long int id;
		bool isBlocked;
		boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable> > > variables;
		bool isTemp;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
