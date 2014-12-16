// ===================================================================
//
// Description		
//		Contains the definition of MMORoomSettings
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MMORoomSettings__
#define __MMORoomSettings__

#include "../../Util/Common.h"
#include "../RoomSettings.h"
#include "../../Entities/Data/Vec3D.h"
#include "MapLimits.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Requests;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {
namespace MMO {

	/// <summary>
	/// The MMORoomSettings class is a container for the settings required to create an MMORoom using the CreateRoomRequest request.
	/// </summary>
	/// 
	/// <seealso cref="Sfs2X.Requests.CreateRoomRequest"/>
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	class DLLImportExport MMORoomSettings : public RoomSettings
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new MMORoomSettings instance.
		/// </summary>
		/// 
		/// <remarks>
		/// The instance must be passed to the <see cref="Sfs2X.Requests.CreateRoomRequest"/> class constructor.
		/// </remarks>
		/// 
		/// <param name="name">The name of the MMORoom to be created.</param>
		/// 
		/// <seealso cref="Sfs2X.Requests.CreateRoomRequest"/>
		MMORoomSettings (string name);

		virtual ~MMORoomSettings();

		/// <summary>
		/// Defines the Area of Interest (AoI) for the MMORoom.
		/// </summary>
		/// 
		/// <remarks>
		/// This value represents the area/range around the user that will be affected by server events and other users events.
		/// It is represented by a <em>Vec3D</em> object providing 2D or 3D coordinates.
		/// <para/>
		/// Setting this value is mandatory.
		/// </remarks>
		/// 
		/// <example>
		/// A <c>Vec3D(50,50)</c> describes a range of 50 units (e.g. pixels) in all four directions (top, bottom, left, right) with respect to the user position in a 2D coordinates system.
		/// 
		/// A <c>Vec3D(120,120,60)</c> describes a range of 120 units in all four directions (top, bottom, left, right) and 60 units along the two Z-axis directions (backward, forward) with respect to the user position in a 3D coordinates system.
		/// </example>
		boost::shared_ptr<Vec3D> DefaultAOI();

		/// <summary>
		/// Defines the Area of Interest (AoI) for the MMORoom.
		/// </summary>
		/// 
		/// <remarks>
		/// This value represents the area/range around the user that will be affected by server events and other users events.
		/// It is represented by a <em>Vec3D</em> object providing 2D or 3D coordinates.
		/// <para/>
		/// Setting this value is mandatory.
		/// </remarks>
		/// 
		/// <example>
		/// A <c>Vec3D(50,50)</c> describes a range of 50 units (e.g. pixels) in all four directions (top, bottom, left, right) with respect to the user position in a 2D coordinates system.
		/// 
		/// A <c>Vec3D(120,120,60)</c> describes a range of 120 units in all four directions (top, bottom, left, right) and 60 units along the two Z-axis directions (backward, forward) with respect to the user position in a 3D coordinates system.
		/// </example>
		void DefaultAOI(boost::shared_ptr<Vec3D> value);

		/// <summary>
		/// Defines the limits of the virtual environment represented by the MMORoom.
		/// </summary>
		/// 
		/// <remarks>
		/// When specified, this property must contain two non-null <em>Vec3D</em> objects representing the minimum and maximum limits of the 2D/3D coordinates systems.
		/// Any positional value that falls outside the provided limit will be refused by the server.
		/// <para/>
		/// This setting is optional but its usage is highly recommended.
		/// </remarks>
		boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits> MapLimits();
		
		/// <summary>
		/// Defines the limits of the virtual environment represented by the MMORoom.
		/// </summary>
		/// 
		/// <remarks>
		/// When specified, this property must contain two non-null <em>Vec3D</em> objects representing the minimum and maximum limits of the 2D/3D coordinates systems.
		/// Any positional value that falls outside the provided limit will be refused by the server.
		/// <para/>
		/// This setting is optional but its usage is highly recommended.
		/// </remarks>
		void MapLimits(boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits> value);

		/// <summary>
		/// Defines the time limit before a user without a physical position set inside the MMORoom is kicked from the Room.
		/// </summary>
		/// 
		/// <remarks>
		/// As soon as the MMORoom is joined, the user still doesn't have a physical position set in the coordinates system, therefore it is
		/// considered in a "limbo" state. At this point the user is expected to set his position (via the <see cref="SetUserPositionRequest"/> request) within the amount of seconds expressed by this value.
		/// <para/>
		/// The default value is <c>50</c> seconds.
		/// </remarks>
		long int UserMaxLimboSeconds();

		/// <summary>
		/// Defines the time limit before a user without a physical position set inside the MMORoom is kicked from the Room.
		/// </summary>
		/// 
		/// <remarks>
		/// As soon as the MMORoom is joined, the user still doesn't have a physical position set in the coordinates system, therefore it is
		/// considered in a "limbo" state. At this point the user is expected to set his position (via the <see cref="SetUserPositionRequest"/> request) within the amount of seconds expressed by this value.
		/// <para/>
		/// The default value is <c>50</c> seconds.
		/// </remarks>
		void UserMaxLimboSeconds(long int value);

		/// <summary>
		/// Configures the speed at which the PROXIMITY_LIST_UPDATE event is sent by the server.
		/// </summary>
		/// 
		/// <remarks>
		/// In an MMORoom, the regular users list is replaced by a proximity list, which keeps an updated view of the users currently within the Area of Interest
		/// of the current user. The speed at which these updates are fired by the server is regulated by this parameter, which sets the minimum time between two subsequent updates.
		/// <para/>
		/// The default value is <c>250</c> milliseconds.
		/// <para/>
		/// <b>NOTE:</b> values below the default might be unnecessary for most applications unless they are in realtime.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
		long int ProximityListUpdateMillis();

		/// <summary>
		/// Configures the speed at which the PROXIMITY_LIST_UPDATE event is sent by the server.
		/// </summary>
		/// 
		/// <remarks>
		/// In an MMORoom, the regular users list is replaced by a proximity list, which keeps an updated view of the users currently within the Area of Interest
		/// of the current user. The speed at which these updates are fired by the server is regulated by this parameter, which sets the minimum time between two subsequent updates.
		/// <para/>
		/// The default value is <c>250</c> milliseconds.
		/// <para/>
		/// <b>NOTE:</b> values below the default might be unnecessary for most applications unless they are in realtime.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
		void ProximityListUpdateMillis(long int value);

		/// <summary>
		/// Sets if the users entry points in the current user's Area of Interest should be transmitted in the PROXIMITY_LIST_UPDATE event.
		/// </summary>
		/// 
		/// <remarks>
		/// If this setting is set to <c>true</c>, when a user enters the AoI of another user, the server will also send the coordinates
		/// at which the former "appeared" within the AoI. This option should be turned off in case these coordinates are not needed, in order to save bandwidth.
		/// <para/>
		/// The default value is <c>true</c>.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Entities.User.AOIEntryPoint"/>
		/// <seealso cref="Sfs2X.Entities.MMOItem.AOIEntryPoint"/>
		/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
		bool SendAOIEntryPoint();

		/// <summary>
		/// Sets if the users entry points in the current user's Area of Interest should be transmitted in the PROXIMITY_LIST_UPDATE event.
		/// </summary>
		/// 
		/// <remarks>
		/// If this setting is set to <c>true</c>, when a user enters the AoI of another user, the server will also send the coordinates
		/// at which the former "appeared" within the AoI. This option should be turned off in case these coordinates are not needed, in order to save bandwidth.
		/// <para/>
		/// The default value is <c>true</c>.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Entities.User.AOIEntryPoint"/>
		/// <seealso cref="Sfs2X.Entities.MMOItem.AOIEntryPoint"/>
		/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
		void SendAOIEntryPoint(bool value);

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
		boost::shared_ptr<Vec3D> defaultAOI;
		boost::shared_ptr<Sfs2X::Requests::MMO::MapLimits> mapLimits;
		long int userMaxLimboSeconds;
		long int proximityListUpdateMillis;
		bool sendAOIEntryPoint;
	};

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X

#endif
