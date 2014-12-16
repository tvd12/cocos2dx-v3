// ===================================================================
//
// Description		
//		Contains the definition of MapLimits
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __MapLimits__
#define __MapLimits__

#include "../../Util/Common.h"
#include "../../Entities/Data/Vec3D.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {
namespace MMO {

	/// <summary>
	/// The MapLimits class is used to set the limits of the virtual environment represented by an MMORoom when creating it.
	/// </summary>
	/// 
	/// <remarks>
	/// The limits represent the minimum and maximum coordinate values (2D or 3D) that the MMORoom should expect.
	/// </remarks>
	/// 
	/// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings"/>
	/// <seealso cref="Sfs2X.Entities.MMORoom"/>
	/// <seealso cref="Sfs2X.Entities.Data.Vec3D"/>
	class DLLImportExport MapLimits
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new MapLimits instance.
		/// </summary>
		/// 
		/// <remarks>
		/// The <see cref="MMORoomSettings.MapLimits"/> property must be set to this instance during the MMORoom creation.
		/// </remarks>
		/// 
		/// <param name="lowerLimit">The lower coordinates limit of the virtual environment along the X,Y,Z axes.</param>
		/// <param name="higherLimit">The higher coordinates limit of the virtual environment along the X,Y,Z axes.</param>
		MapLimits (boost::shared_ptr<Vec3D> lowerLimit, boost::shared_ptr<Vec3D> higherLimit);

		virtual ~MapLimits();

		/// <summary>
		/// Returns the lower coordinates limit of the virtual environment along the X,Y,Z axes.
		/// </summary>
		boost::shared_ptr<Vec3D> LowerLimit();

		/// <summary>
		/// Returns the higher coordinates limit of the virtual environment along the X,Y,Z axes.
		/// </summary>
		boost::shared_ptr<Vec3D> HigherLimit();

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
		boost::shared_ptr<Vec3D> lowerLimit;
		boost::shared_ptr<Vec3D> higherLimit;
	};

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X

#endif
