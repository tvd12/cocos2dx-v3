// ===================================================================
//
// Description		
//		Contains the definition of SFSInvitation
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSInvitation__
#define __SFSInvitation__

#include "../../Util/Common.h"
#include "../Data/ISFSObject.h"
#include "../User.h"
#include "Invitation.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Invitation {

	/// <summary>
	/// Invitation object
	/// </summary>
	/// <remarks>
	/// An <b>Invitation</b> object provides the ability to send a generic invitation for a specific event going on
	/// in your application, be it a game, visiting a personal Room or another location of the virtual world etc...
	/// <para/>
	/// The SFS2X <b>Invitation Manager</b> is very simple to use. All you need to provide is:
	/// <ul>
	/// 	<li><b>inviter:</b> the User starting the invitation (null == Server)</li>
	/// 	<li><b>invitee:</b> the User to invite</li>
	/// 	<li><b>secondsForAnswer:</b> the amount of time (in seconds) that the invitee has to accept/refuse the invitation. (default is 15 sec)</li>
	/// 	<li><b>params:</b> any custom params to send with the invitation (e.g. a message, game name etc...)</li>
	/// </ul>
	/// </remarks>
	/// <seealso cref="Requests.Game.InviteUsersRequest"/>
	/// <seealso cref="Core.SFSEvent.INVITATION"/>
	class DLLImportExport SFSInvitation : public Invitation
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="inviter">
		/// the User that sends the Invitation
		/// </param>
		/// <param name="invitee">
		/// the User that receives the Invitation
		/// </param>
		SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="inviter">
		/// the User that sends the Invitation
		/// </param>
		/// <param name="invitee">
		/// the User that receives the Invitation
		/// </param>
		/// <param name="secondsForAnswer">
		/// the number of seconds allowed for the Invitee to reply (recommended range: 15-40 seconds)
		/// </param>
		SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="inviter">
		/// the User that sends the Invitation
		/// </param>
		/// <param name="invitee">
		/// the User that receives the Invitation
		/// </param>
		/// <param name="secondsForAnswer">
		/// the number of seconds allowed for the Invitee to reply (recommended range: 15-40 seconds)
		/// </param>
		/// <param name="parameters">
		/// custom params to send with the invitation
		/// </param>
		SFSInvitation(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer, boost::shared_ptr<ISFSObject> parameters);

		virtual ~SFSInvitation();

		long int Id();
		void Id(long int value);

		boost::shared_ptr<User> Inviter();
		boost::shared_ptr<User> Invitee();
		long int SecondsForAnswer();
		boost::shared_ptr<ISFSObject> Params();

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
		// The id is only used when the Invitation is built from a Server Side Invitation
		long int id;
		boost::shared_ptr<User> inviter;
		boost::shared_ptr<User> invitee;
		long int secondsForAnswer;
		boost::shared_ptr<ISFSObject> parameters;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------
		void Init(boost::shared_ptr<User> inviter, boost::shared_ptr<User> invitee, long int secondsForAnswer, boost::shared_ptr<ISFSObject> parameters);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Invitation
}	// namespace Entities
}	// namespace Sfs2X

#endif
