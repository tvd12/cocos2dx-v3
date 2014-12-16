// ===================================================================
//
// Description		
//		Contains the definition of MMORoom
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MMORoom__
#define __MMORoom__

#include "../Util/Common.h"
#include "IMMOItem.h"
#include "SFSRoom.h"
#include "Data/Vec3D.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object 
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {

	/// <summary>
	/// The MMORoom object represents a specialized type of Room entity on the client.
	/// </summary>
	///
	/// <remarks>
	/// The MMORoom is ideal for huge virtual worlds and MMO games because it works with proximity lists instead of "regular" users lists.
	/// This allows thousands of users to interact with each other based on their Area of Interest (AoI). The AoI represents a range around the user
	/// that is affected by server and user events, outside which no other events are received.
	/// <para/>
	/// The size of the AoI is set at Room creation time and it is the same for all users who joined it.
	/// Supposing that the MMORoom hosts a 3D virtual world, setting an AoI of (x=100, y=100, z=40) for the Room tells the server to transmit updates and broadcast
	/// events to and from those users that fall within the AoI range around the current user; this means the area within +/- 100 units on the X axis, +/- 100 units on the Y axis and +/- 40 units on the Z axis.
	/// <para/>
	/// As the user moves around in the virtual environment, he can update his position in the corresponding MMORoom and thus continuously receive events
	/// about other users (and items - see below) entering and leaving his AoI.
	/// The player will be able to update his position via the <em>SetUserPositionRequest</em> request and receive updates on his current proximity list by means of the
	/// <see cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE">PROXIMITY_LIST_UPDATE</see> event.
	/// <para/>
	/// Finally, MMORooms can also host any number of "MMOItems" which represent dynamic non-player objects that users can interact with.
	/// They are handled by the MMORoom using the same rules of visibility described before.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Requests.CreateRoomRequest"/>
	/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings"/>
	/// <seealso cref="Sfs2X.Requests.MMO.SetUserPositionRequest"/>
	/// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
	/// <seealso cref="Sfs2X.Entities.MMOItem"/>
	class DLLImportExport MMORoom : public SFSRoom//, public boost::enable_shared_from_this<MMORoom>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <exclude/>
		MMORoom (long int id, string name, string groupId);
		
		/// <exclude/>
		MMORoom (long int id, string name);
		
		/// <exclude/>
		virtual ~MMORoom();

		/// <summary>
		/// Returns the default Area of Interest (AoI) of this MMORoom.
		/// </summary>
		/// 
		/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings.DefaultAOI"/>
		boost::shared_ptr<Vec3D> DefaultAOI(); 
		void DefaultAOI(boost::shared_ptr<Vec3D> value); 
		
		/// <summary>
		/// Returns the lower coordinates limit of the virtual environment represented by the MMORoom along the X,Y,Z axes.
		/// </summary>
		/// 
		/// <remarks>
		/// If <c>null</c> is returned, then no limits were set at Room creation time.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings.MapLimits"/>
		boost::shared_ptr<Vec3D> LowerMapLimit(); 
		void LowerMapLimit(boost::shared_ptr<Vec3D> value); 
		
		/// <summary>
		/// Returns the higher coordinates limit of the virtual environment represented by the MMORoom along the X,Y,Z axes.
		/// </summary>
		/// 
		/// <remarks>
		/// If <c>null</c> is returned, then no limits were set at Room creation time.
		/// </remarks>
		/// 
		/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings.MapLimits"/>
		boost::shared_ptr<Vec3D> HigherMapLimit(); 
		void HigherMapLimit(boost::shared_ptr<Vec3D> value); 
		
		/// <summary>
		/// Retrieves an <em>MMOItem</em> object from its <em>id</em> property.
		/// </summary>
		/// 
		/// <remarks>
		/// The item is available to the current user if it falls within his Area of Interest only.
		/// </remarks>
		/// 
		/// <param name="id">The id of the item to be retrieved.</param>
		/// 
		/// <returns>An <em>MMOItem</em> object, or <c>null</c> if the item with the passed id is not in proximity of the current user.</returns>
		boost::shared_ptr<IMMOItem> GetMMOItem(long int id);

		/// <summary>
		/// Retrieves all <em>MMOItem</em> object in the MMORoom that fall within the current user's Area of Interest.
		/// </summary>
		/// 
		/// <returns>A list of <em>MMOItem</em> objects, or an empty list if no item is in proximity of the current user.</returns>
		boost::shared_ptr<vector<boost::shared_ptr<IMMOItem> > > GetMMOItems();

		/// <exclude/>
		void AddMMOItem(boost::shared_ptr<IMMOItem> item);

		/// <exclude/>
		void RemoveItem(long int id);

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
		boost::shared_ptr<Vec3D> lowerMapLimit;
		boost::shared_ptr<Vec3D> higherMapLimit;
		boost::shared_ptr<map<long int, boost::shared_ptr<IMMOItem> > > itemsById;
	};

}	// namespace Entities
}	// namespace Sfs2X

#endif
