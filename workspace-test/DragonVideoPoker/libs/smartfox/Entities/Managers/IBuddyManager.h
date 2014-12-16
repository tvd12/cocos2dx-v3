// ===================================================================
//
// Description		
//		Contains the definition of IBuddyManager interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IBuddyManager__
#define __IBuddyManager__

#include "../Variables/BuddyVariable.h"
#include "../Buddy.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Variables;

namespace Sfs2X {
namespace Entities {
namespace Managers {

	/// <summary>
	/// The BuddyList Manager interface
	/// </summary>
	class DLLImportExport IBuddyManager
	{
	public:
		/// <summary>
		/// Checks if the current User's Buddy List is inited.
		/// </summary>
		/// <remarks>
		/// If not you should send an InitBuddyListRequest to the server in order to retrieve your persistent Buddy List data.
		/// </remarks>
		/// <seealso cref="Requests.InitBuddyListRequest"/>
		virtual bool Inited() = 0;

		/// <summary>
		/// Checks if the current User's Buddy List is inited.
		/// </summary>
		/// <remarks>
		/// If not you should send an InitBuddyListRequest to the server in order to retrieve your persistent Buddy List data.
		/// </remarks>
		/// <seealso cref="Requests.InitBuddyListRequest"/>
		virtual void Inited(bool value) = 0;
		
		virtual void AddBuddy(boost::shared_ptr<Buddy> buddy) = 0;
		
		virtual boost::shared_ptr<Buddy> RemoveBuddyById(long int id) = 0;
		
		virtual boost::shared_ptr<Buddy> RemoveBuddyByName(string name) = 0;
		
		/// <summary>
		/// Checks if a Buddy is present in the current User's Buddy List
		/// </summary>
		/// <param name="name">
		/// the Buddy name
		/// </param>
		/// <returns>
		/// true if the Buddy exists
		/// </returns>
		/// <seealso cref="SFSBuddy"/>
		virtual bool ContainsBuddy(string name) = 0;
		
		/// <summary>
		/// Find a Buddy from its User Id
		/// </summary>
		/// <param name="id">
		/// the user id
		/// </param>
		/// <returns>
		/// the Buddy, or null if not found
		/// </returns>
		/// <seealso cref="SFSBuddy"/>
		virtual boost::shared_ptr<Buddy> GetBuddyById(long int id) = 0;
		
		/// <summary>
		/// Find a Buddy from its name
		/// </summary>
		/// <param name="name">
		/// the Buddy name
		/// </param>
		/// <returns>
		/// the Buddy, or null if not found
		/// </returns>
		virtual boost::shared_ptr<Buddy> GetBuddyByName(string name) = 0;
		
		/// <summary>
		/// Find a Buddy from its optional nick name
		/// </summary>
		/// <param name="nickName">
		/// Athe nickname
		/// </param>
		/// <returns>
		/// the Buddy, or null if not found
		/// </returns>
		/// <seealso cref="SFSBuddy"/>
		virtual boost::shared_ptr<Buddy> GetBuddyByNickName(string nickName) = 0;
		
		/// <summary>
		/// Get a list of all online Buddies in the User's Buddy list
		/// </summary>
		virtual boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > OfflineBuddies() = 0;
		
		/// <summary>
		/// Get a list of all offline Buddies in the User's Buddy list
		/// </summary>
		virtual boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > OnlineBuddies() = 0;
		
		/// <summary>
		/// Get the User's buddy list. It could be null if the Buddy List was not initialized
		/// </summary>
        /// <seealso cref="Requests.InitBuddyListRequest"/>
		virtual boost::shared_ptr<vector<boost::shared_ptr<Buddy> > > BuddyList() = 0;
		
		/// <summary>
		/// Get a list of Strings representing the custom Buddy states that the application can use. The custom states are sent upon initialization of the Buddy List and are configured on the server side.
		/// </summary>
		virtual boost::shared_ptr<vector<string> > BuddyStates() = 0;

		/// <summary>
		/// Get a list of Strings representing the custom Buddy states that the application can use. The custom states are sent upon initialization of the Buddy List and are configured on the server side.
		/// </summary>
		virtual void BuddyStates(boost::shared_ptr<vector<string> > value) = 0;
		
		/// <summary>
		/// Get current Users' BuddyVariable by name
		/// </summary>
		/// <param name="varName">
		/// the variable name
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="BuddyVariable"/> instance
		/// </returns>
		virtual boost::shared_ptr<BuddyVariable> GetMyVariable(boost::shared_ptr<string> varName) = 0;

		/// <summary>
		/// Get current Users' BuddyVariable by name
		/// </summary>
		/// <param name="varName">
		/// the variable name
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="BuddyVariable"/> instance
		/// </returns>
		virtual boost::shared_ptr<BuddyVariable> GetMyVariable(string varName) = 0;

		/// <summary>
		/// Get all current User's Buddy Variables
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized
		/// </remarks>
		/// <seealso cref="SFSBuddyVariable"/>
		virtual boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > MyVariables() = 0;

		/// <summary>
		/// Get all current User's Buddy Variables
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized
		/// </remarks>
		/// <seealso cref="SFSBuddyVariable"/>
		virtual void MyVariables(boost::shared_ptr<vector<boost::shared_ptr<BuddyVariable> > > value) = 0;

		/// <summary>
		/// Get the current User's Online State
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// <para/>
		/// Returns true if the User is online, false otherwise
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual bool MyOnlineState() = 0;

		/// <summary>
		/// Get the current User's Online State
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// <para/>
		/// Returns true if the User is online, false otherwise
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual void MyOnlineState(bool value) = 0;

		/// <summary>
		/// Get the current User's optional nickname
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// <para/>
		/// Returns the Users' nickname or null if the nickname was never set
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual boost::shared_ptr<string> MyNickName() = 0;

		/// <summary>
		/// Get the current User's optional nickname
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// <para/>
		/// Returns the Users' nickname or null if the nickname was never set
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual void MyNickName(string value) = 0;

		/// <summary>
		/// Get the current User's optional custom state (e.g. "Available"; "Busy", "Be right back"...)
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual boost::shared_ptr<string> MyState() = 0;

		/// <summary>
		/// Get the current User's optional custom state (e.g. "Available"; "Busy", "Be right back"...)
		/// </summary>
		/// <remarks>
		/// This operation is valid only if the User's BuddyList has already been initialized<br/>
		/// The value is handled by a reserved Buddy Variable
		/// </remarks>
		/// <seealso cref="ReservedBuddyVariables"/>
		virtual void MyState(string value) = 0;

		virtual void SetMyVariable(boost::shared_ptr<BuddyVariable> bVar) = 0;
		
		virtual void ClearAll() = 0;		
	};

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X

#endif
