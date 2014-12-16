// ===================================================================
//
// Description		
//		Contains the definition of SFSRoomVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSRoomVariable__
#define __SFSRoomVariable__

#include "../../Util/Common.h"
#include "SFSUserVariable.h"
#include "RoomVariable.h"
#include "../Data/ISFSArray.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Variables {

    /// <summary>
    /// The RoomVariable class is used to represent variables maintained on the Server side and automatically updated to the clients. 
    /// </summary>
    /// <remarks>
    /// They are particularly useful to "attach" any custom data to each Room such as the current game status and other Room-specific properties etc...
    /// <para/>
    /// RoomVariables support basic data types and nested complex objects:
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
    /// <para/>
    /// RoomVariables also support different flags:
    /// <ul>
    /// 		<li><b>Private</b>: a private variable can only be modified by its creator</li>
    /// 		<li><b>Persistent</b>: a persistent variable will continue to exist even if its creator has left the room. </li>
    /// 		<li><b>Global</b>: a global variable will fire updates not only to all Users in the Room but also to all Users in the Room Group</li>
    /// </ul>
    /// </remarks>
    /// <seealso cref="SFSRoom"/>
    /// <seealso cref="Requests.SetRoomVariablesRequest"/>	
	class DLLImportExport SFSRoomVariable : public SFSUserVariable, public RoomVariable
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<RoomVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <overrides>
		/// <summary>
		/// 
		/// </summary>
		/// </overrides>
		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		SFSRoomVariable(string name, boost::shared_ptr<void> val);

		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		/// <param name="type">
		/// it's usually not necessary to pass this parameter as the variable value is auto-detected
		/// </param>
		SFSRoomVariable(string name, boost::shared_ptr<void> val, long int type);

		virtual ~SFSRoomVariable();

		bool IsPrivate();
		void IsPrivate(bool value);

		bool IsPersistent();
		void IsPersistent(bool value);

		boost::shared_ptr<string> ToString();
		boost::shared_ptr<ISFSArray> ToSFSArray();

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

		bool isPersistent;
		bool isPrivate;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
