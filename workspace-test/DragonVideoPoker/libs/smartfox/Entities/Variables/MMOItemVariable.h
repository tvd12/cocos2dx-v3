// ===================================================================
//
// Description		
//		Contains the definition of MMOItemVariable
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MMOItemVariable__
#define __MMOItemVariable__

#include "../../Util/Common.h"
#include "SFSUserVariable.h"
#include "IMMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

	/// <summary>
	/// The MMOItemVariable object represents a SmartFoxServer MMOItem Variable entity on the client.
	/// </summary>
	/// 
	/// <remarks>
	/// An MMOItem Variable is a custom value attached to an MMOItem object that gets automatically synchronized between client and server on every change, provided that the MMOItem is inside the Area of Interest of the current user in a MMORoom.
	/// <para />
	/// <b>NOTE:</b> MMOItem Variables behave exactly like User Variables and support the same data types, but they can be created, updated and deleted on the server side only.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Entities.MMOItem"/>
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	class DLLImportExport MMOItemVariable : public SFSUserVariable, public IMMOItemVariable
	{
	public:
		
		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <exclude/>
		static boost::shared_ptr<IMMOItemVariable> FromSFSArray(boost::shared_ptr<ISFSArray> sfsa);

		/// <exclude/>
		MMOItemVariable(string name, boost::shared_ptr<void> val, long int type);

		/// <exclude/>
		MMOItemVariable(string name, boost::shared_ptr<void> val);

		virtual ~MMOItemVariable();

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

	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
