// ===================================================================
//
// Description		
//		Contains the definition of RoomSettings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomSettings__
#define __RoomSettings__

#include "../Util/Common.h"
#include "RoomPermissions.h"
#include "RoomEvents.h"
#include "RoomExtension.h"
#include "../Entities/Variables/RoomVariable.h"
#include "../Entities/SFSConstants.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X;
using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Variables;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This class provides the Room settings that you can pass to a <see cref="CreateRoomRequest"/>
	/// </summary>
	/// <remarks>
	/// Some of these fields are mandatory and some other are populated by default if you don't specify them.
	/// <ul>
	/// 		<li><b>name:</b> mandatory, each Room must have a unique name</li>
	/// 		<li><b>password:</b> optional, by default a Room is created without a password</li>
	/// 		<li><b>groupId:</b> optional, by default Rooms are created in the 'default' group if none is specified</li>
	/// 		<li><b>isGame:</b> optional, by default isGame flage is set to false</li>
	/// 		<li><b>maxUsers:</b> optional, if no value is provided the default value of 10 is used</li>
	/// 		<li><b>maxSpectators:</b> optional, if no value is provided the default value of 0 is used</li>
	/// 		<li><b>maxVariables:</b> optional, if no value is provided the default value of 5 is used</li>
	/// 		<li><b>variables:</b> optional, an array of RoomVariables to be set at creation time</li>
	/// 		<li><b>permissions:</b> optional, if no value is provided the default RoomPermissions configuration is used</li>
	/// 		<li><b>events:</b> optional, if no value is provided the default RoomEvents configuration is used</li>
	/// 		<li><b>extension:</b> optional. No default values</li>
	/// </ul>
	/// </remarks>
	/// <seealso cref="RoomEvents"/>
	/// <seealso cref="RoomPermissions"/>
	/// <seealso cref="RoomExtension"/>
	/// <seealso cref="CreateRoomRequest"/>
	class DLLImportExport RoomSettings
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="name">
		/// the room name
		/// </param>
		/// <seealso cref="Core.SFSEvent.PUBLIC_MESSAGE"/>
		/// <seealso cref="PrivateMessageRequest"/>
		RoomSettings(string name);

		virtual ~RoomSettings();

		/// <summary>
		/// The name of the new Room
		/// </summary>
		boost::shared_ptr<string> Name();

		/// <summary>
		/// The name of the new Room
		/// </summary>
		void Name(string value);

		/// <summary>
		/// The password of the Room. If empty the Room will not be password protected
		/// </summary>
		boost::shared_ptr<string> Password();

		/// <summary>
		/// The password of the Room. If empty the Room will not be password protected
		/// </summary>
		void Password(string value);

		/// <summary>
		/// Indicates if this is a Game Room
		/// </summary>
		bool IsGame();

		/// <summary>
		/// Indicates if this is a Game Room
		/// </summary>
		void IsGame(bool value);

		/// <summary>
		/// The maximum number of users/players allowed in the Room
		/// </summary>
		short int MaxUsers();

		/// <summary>
		/// The maximum number of users/players allowed in the Room
		/// </summary>
		void MaxUsers(short int value);

		/// <summary>
		/// The maximum number of Room Variables allowed for this Room
		/// </summary>
		short int MaxVariables();

		/// <summary>
		/// The maximum number of Room Variables allowed for this Room
		/// </summary>
		void MaxVariables(short int value);

		/// <summary>
		/// The maximum number of spectators allowed for this Room (only for Game Rooms)
		/// </summary>
		short int MaxSpectators();

		/// <summary>
		/// The maximum number of spectators allowed for this Room (only for Game Rooms)
		/// </summary>
		void MaxSpectators(short int value);

		/// <summary>
		/// A list of Room Variables that should be attached to the newly created Room
		/// </summary>
		/// <seealso cref="SFSRoomVariable"/>
		boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > Variables();

		/// <summary>
		/// A list of Room Variables that should be attached to the newly created Room
		/// </summary>
		/// <seealso cref="SFSRoomVariable"/>
		void Variables(boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > value);

		/// <summary>
		/// The Room Permission settings of the new Room
		/// </summary>
		/// <seealso cref="RoomPermissions"/>
		boost::shared_ptr<RoomPermissions> Permissions();

		/// <summary>
		/// The Room Permission settings of the new Room
		/// </summary>
		/// <seealso cref="RoomPermissions"/>
		void Permissions(boost::shared_ptr<RoomPermissions> value);

		/// <summary>
		/// The Room Event settings of the new Room
		/// </summary>
		/// <seealso cref="RoomEvents"/>
		boost::shared_ptr<RoomEvents> Events();

		/// <summary>
		/// The Room Event settings of the new Room
		/// </summary>
		/// <seealso cref="RoomEvents"/>
		void Events(boost::shared_ptr<RoomEvents> value);

		/// <summary>
		/// The Extension settings for the new Room
		/// </summary>
		/// <seealso cref="RoomExtension"/>
		boost::shared_ptr<RoomExtension> Extension();

		/// <summary>
		/// The Extension settings for the new Room
		/// </summary>
		/// <seealso cref="RoomExtension"/>
		void Extension(boost::shared_ptr<RoomExtension> value);

		/// <summary>
		/// The id of the Room Group in which the new Room should be created
		/// </summary>
		boost::shared_ptr<string> GroupId();

		/// <summary>
		/// The id of the Room Group in which the new Room should be created
		/// </summary>
		void GroupId(string value);

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
		boost::shared_ptr<string> name;
		boost::shared_ptr<string> password;
		boost::shared_ptr<string> groupId;
		bool isGame;
		short int maxUsers;
		short int maxSpectators;
		short int maxVariables;
		boost::shared_ptr<vector<boost::shared_ptr<RoomVariable> > > variables;
		boost::shared_ptr<RoomPermissions> permissions;
		boost::shared_ptr<RoomEvents> events;
		boost::shared_ptr<RoomExtension> extension;	
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
