// ===================================================================
//
// Description		
//		Contains the definition of SFSBuddyVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSBuddyVariable__
#define __SFSBuddyVariable__

#include "../../Util/Common.h"
#include "SFSBuddyVariable.h"
#include "BuddyVariable.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// BuddyVariables are custom values attached to any Buddy in a BuddyList.
	/// </summary>
	/// <remarks>
	/// They work with the same principle of the User/Room Variables.<br/>
	/// The only difference is the logic by which they get propagated to other Users. While RoomVariables are broadcast to all clients in the same Room, BuddyVariables are updated to all Users who have the BuddyVariable owner in their BuddyLists.
	///  <para/>
	/// BuddyVariables support basic data types and nested complex objects:
	/// 
	/// <ul>
	/// 		<li>Null</li>
	/// 		<li>Bool</li>
	/// 		<li>Int</li>
	/// 		<li>Double</li>
	/// 		<li>String</li>
	/// 		<li>SFSObject</li>
	/// 		<li>SFSArray</li>
	/// </ul>
	/// 
	/// Also there is a special convention that allows certain Variables to be "offline" Buddy Variables. <br/>
	/// All variable names starting with a dollar sign ($) will set the BuddyVariable as persistent and make them available at any time whether the owner is online or not.
	/// </remarks>
	/// <seealso cref="SFSBuddy"/>
	/// <seealso cref="Requests.SetBuddyVariablesRequest"/>
	/// <seealso cref="Core.SFSBuddyEvent.BUDDY_VARIABLES_UPDATE"/>
	class DLLImportExport SFSBuddyVariable : public BuddyVariable
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<BuddyVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		/// <param name="type">
		/// it's usually not necessary to pass this parameter as the variable value is auto-detected
		/// </param>
		SFSBuddyVariable(string name, boost::shared_ptr<void> val, long int type);

		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		/// <param name="type">
		/// it's usually not necessary to pass this parameter as the variable value is auto-detected
		/// </param>
		SFSBuddyVariable(boost::shared_ptr<string> name, boost::shared_ptr<void> val, long int type);

		virtual ~SFSBuddyVariable();

		bool IsOffline();
		boost::shared_ptr<string> Name();
		VariableType Type();
		boost::shared_ptr<void> Value();
		boost::shared_ptr<bool> GetBoolValue();
		boost::shared_ptr<long int> GetIntValue();
		boost::shared_ptr<double> GetDoubleValue();
		boost::shared_ptr<string> GetStringValue();
		boost::shared_ptr<ISFSObject> GetSFSObjectValue();
		boost::shared_ptr<ISFSArray> GetSFSArrayValue();
		bool IsNull();
		virtual boost::shared_ptr<ISFSArray> ToSFSArray();
		boost::shared_ptr<string> ToString();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> OFFLINE_PREFIX;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------
		boost::shared_ptr<string> name;
		VariableType type;
		boost::shared_ptr<void> val;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------
		void PopulateArrayWithValue(boost::shared_ptr<ISFSArray> arr);
		void SetValue(boost::shared_ptr<void> val, VariableType type);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
