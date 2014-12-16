// ===================================================================
//
// Description		
//		Contains the definition of SFSUserVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSUserVariable__
#define __SFSUserVariable__

#include "../../Util/Common.h"
#include "UserVariable.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"
#include "../../Exceptions/SFSError.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace


using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The UserVariable class is used to represent variables maintained on the Server side and automatically updated to the clients.
	/// </summary>
	/// <seealso cref="User"/>
	/// <seealso cref="Requests.SetUserVariablesRequest"/>
	class DLLImportExport SFSUserVariable : public UserVariable
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<UserVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <overrides>
		/// <summary>
		/// Contructor for SFSUserVariable
		/// </summary>
		/// </overrides>
		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		SFSUserVariable(string name, boost::shared_ptr<void> val);

		/// <param name="name">
		/// the name of the variable
		/// </param>
		/// <param name="val">
		/// the variable value ( can be Boolean, int, Number, String, SFSObject, SFSArray )
		/// </param>
		/// <param name="type">
		/// it's usually not necessary to pass this parameter as the variable value is auto-detected
		/// </param>
		SFSUserVariable(string name, boost::shared_ptr<void> val, long int type);

		virtual ~SFSUserVariable();

		virtual boost::shared_ptr<string> Name();
		virtual VariableType Type();
		virtual boost::shared_ptr<void> Value();
		virtual boost::shared_ptr<bool> GetBoolValue();
		virtual boost::shared_ptr<long int> GetIntValue();
		virtual boost::shared_ptr<double> GetDoubleValue();
		virtual boost::shared_ptr<string> GetStringValue();
		virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue();
		virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue();
		virtual bool IsNull();
		virtual boost::shared_ptr<ISFSArray> ToSFSArray();
		virtual boost::shared_ptr<string> ToString();

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

		boost::shared_ptr<string>  name;
		VariableType type;
		boost::shared_ptr<void> val;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		void PopulateArrayWithValue(boost::shared_ptr<ISFSArray> arr);
		void SetValue(boost::shared_ptr<void> val);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
