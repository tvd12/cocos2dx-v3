// ===================================================================
//
// Description		
//		Contains the definition of Invitation
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Invitation__
#define __Invitation__

#include "../User.h"
#include "../Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Invitation {

	/// <summary>
	/// Represents an Invitation object
	/// </summary>
	/// <remarks>
	/// For more details see the SFSInvitation implementation
	/// </remarks>
	/// <seealso cref="SFSInvitation"/>
	class DLLImportExport Invitation
	{
	public:

		/// <summary>
		/// The id of the invitation 
		/// </summary>
		virtual long int Id() = 0;

		/// <summary>
		/// The id of the invitation 
		/// </summary>
		virtual void Id(long int value) = 0;

		/// <summary>
		/// The inviter User 
		/// </summary>
		virtual boost::shared_ptr<User> Inviter() = 0;

		/// <summary>
		/// The invited User 
		/// </summary>
		virtual boost::shared_ptr<User> Invitee() = 0;

		/// <summary>
		/// The amount of time (seconds) allowed to reply to the invitation 
		/// </summary>
		virtual long int SecondsForAnswer() = 0;
		
		/// <summary>
		/// A custom set of parameters. 
		/// </summary>
		/// <remarks>
		/// Can be used to provide a message for the invitation and any other relevant data 
		/// </remarks>
		virtual boost::shared_ptr<ISFSObject> Params() = 0;
	};

}	// namespace Invitation
}	// namespace Entities
}	// namespace Sfs2X

#endif
