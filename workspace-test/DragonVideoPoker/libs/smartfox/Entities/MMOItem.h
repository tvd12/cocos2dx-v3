// ===================================================================
//
// Description		
//		Contains the definition of MMOItem
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MMOItem__
#define __MMOItem__

#include "../Util/Common.h"
#include "IMMOItem.h"
#include "Variables/IMMOItemVariable.h"
#include "Data/Vec3D.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object 
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Variables;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {

	/// <summary>
	/// An MMOItem object represents an active non-player entity inside an MMORoom.
	/// </summary>
	/// 
	/// <remarks>
	/// MMOItems can be used to represent bonuses, triggers, bullets, etc, or any other non-player entity that will be handled using the MMORoom's rules of visibility.
	/// This means that whenever one or more MMOItems fall within the Area of Interest of a user, their presence will be notified to that user by means of the
	/// <see cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE">PROXIMITY_LIST_UPDATE</see> event.
	/// <para/>
	/// MMOItems are identified by a unique ID and can have one or more MMOItem Variables associated to store custom data.
	/// <para/>
	/// <b>NOTE:</b> MMOItems can be created in a server side Extension only; client side creation is not allowed.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	/// <seealso cref="Sfs2X.Entities.Variables.MMOItemVariable"/>
	class DLLImportExport MMOItem : public IMMOItem
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <exclude/>
		MMOItem (long int id);

		virtual ~MMOItem();

		/// <exclude/>
		static boost::shared_ptr<IMMOItem> FromSFSArray(boost::shared_ptr<ISFSArray> encodedItem);

		/// <inheritdoc />
		virtual long int Id();

		/// <inheritdoc />
		virtual boost::shared_ptr<vector<boost::shared_ptr<IMMOItemVariable> > > GetVariables();
		
		/// <inheritdoc />
		virtual boost::shared_ptr<IMMOItemVariable> GetVariable(string name);
		
		/// <exclude/>
		virtual void SetVariable(boost::shared_ptr<IMMOItemVariable> variable);
		
		/// <exclude/>
		virtual void SetVariables(boost::shared_ptr<vector<boost::shared_ptr<IMMOItemVariable> > > variables);
		
		/// <inheritdoc />
		virtual bool ContainsVariable(string name);

		/// <inheritdoc />
		virtual boost::shared_ptr<Vec3D> AOIEntryPoint();
		virtual void AOIEntryPoint(boost::shared_ptr<Vec3D> value);

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
		long int id;
		boost::shared_ptr<Vec3D> aoiEntryPoint;
		boost::shared_ptr<map<string, boost::shared_ptr<IMMOItemVariable> > > variables;
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
