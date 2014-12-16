// ===================================================================
//
// Description		
//		Contains the definition of Vec3D
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#ifndef __Vec3D__
#define __Vec3D__

#include "../../Util/Common.h"
#include "SFSDataType.h"
#include <stdio.h>

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// The Vec3D object represents a position in a 2D or 3D space.
	/// </summary>
	/// 
	/// <remarks>
	/// This class is used to express a position inside a virtual environment with no specific unit of measure (could be pixels, feet, meters, etc).
	///	<para/>
	///	Positions along the X,Y,Z axes can be expressed as Integers or Floats, based on the game's coordinate system requirements.
	/// </remarks>
	class DLLImportExport Vec3D
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		~Vec3D();

		/// <exclude/>
		static boost::shared_ptr<Vec3D> fromArray(long int tp, boost::shared_ptr<void> array);

		/// <summary>
		/// Creates a new Vec3D instance for a 3D coordinates system with integer values.
		/// </summary>
		/// 
		/// <param name="px">The position along the X axis.</param>
		/// <param name="py">The position along the Y axis.</param>
		/// <param name="pz">The position along the Z axis.</param>
		Vec3D (long int px, long int py, long int pz);

		/// <summary>
		/// Creates a new Vec3D instance for a 2D coordinates system with integer values.
		/// </summary>
		/// 
		/// <param name="px">The position along the X axis.</param>
		/// <param name="py">The position along the Y axis.</param>
		Vec3D (long int px, long int py);

		/// <summary>
		/// Creates a new Vec3D instance for a 3D coordinates system with float values.
		/// </summary>
		/// 
		/// <param name="px">The position along the X axis.</param>
		/// <param name="py">The position along the Y axis.</param>
		/// <param name="pz">The position along the Z axis.</param>
		Vec3D (float px, float py, float pz);

		/// <summary>
		/// Creates a new Vec3D instance for a 2D coordinates system with float values.
		/// </summary>
		/// 
		/// <param name="px">The position along the X axis.</param>
		/// <param name="py">The position along the Y axis.</param>
		Vec3D (float px, float py);

		/// <summary>
		/// Indicates whether the position is expressed using floating point values or not.
		/// </summary>
		/// 
		/// <returns><c>true</c> if the position is expressed using floating point values.</returns>
		bool IsFloat();

		/// <summary>
		/// Returns the position along the X axis as a float value.
		/// </summary>
		float FloatX();

		/// <summary>
		/// Returns the position along the Y axis as a float value.
		/// </summary>
		float FloatY();

		/// <summary>
		/// Returns the position along the Z axis as a float value.
		/// </summary>
		float FloatZ();

		/// <summary>
		/// Returns the position along the X axis as an integer value.
		/// </summary>
		long int IntX();

		/// <summary>
		/// Returns the position along the Y axis as an integer value.
		/// </summary>
		long int IntY();

		/// <summary>
		/// Returns the position along the Z axis as an integer value.
		/// </summary>
		long int IntZ();

		/// <exclude/>
		boost::shared_ptr<vector<long int> > ToIntArray();

		/// <exclude/>
		boost::shared_ptr<vector<float> > ToFloatArray();

		/// <exclude/>
		boost::shared_ptr<string> ToString();

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
		
		static boost::shared_ptr<Vec3D> fromIntArray(boost::shared_ptr<vector<long int> > array);
		static boost::shared_ptr<Vec3D> fromFloatArray(boost::shared_ptr<vector<float> > array);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		float fx, fy, fz;
		long int ix, iy, iz;
		bool useFloat;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
