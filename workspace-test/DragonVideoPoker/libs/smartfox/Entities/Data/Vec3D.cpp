// ===================================================================
//
// Description		
//		Contains the implementation of Vec3D
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "Vec3D.h"

#include <boost/system/error_code.hpp> 

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Vec3D::Vec3D (long int px, long int py, long int pz)
{
	ix = px; iy = py; iz = pz;
	useFloat = false;
}

Vec3D::Vec3D (long int px, long int py) 
{ 
	ix = px; iy = py; iz = 0;
	useFloat = false;
}

Vec3D::Vec3D (float px, float py, float pz)
{
	fx = px; fy = py; fz = pz;
	useFloat = true;
}

Vec3D::Vec3D (float px, float py)
{
	fx = px; fy = py; fz = 0;
	useFloat = true;
}


// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Vec3D::~Vec3D()
{
}

// -------------------------------------------------------------------
// IsFloat
// -------------------------------------------------------------------
bool Vec3D::IsFloat()
{
	return useFloat;
}

// -------------------------------------------------------------------
// FloatX
// -------------------------------------------------------------------
float Vec3D::FloatX()
{
	return fx;
}
		
// -------------------------------------------------------------------
// FloatY
// -------------------------------------------------------------------
float Vec3D::FloatY()
{
	return fy;
}

// -------------------------------------------------------------------
// FloatZ
// -------------------------------------------------------------------
float Vec3D::FloatZ()
{
	return fz;
}

// -------------------------------------------------------------------
// IntX
// -------------------------------------------------------------------
long int Vec3D::IntX()
{
	return ix;
}
		
// -------------------------------------------------------------------
// IntY
// -------------------------------------------------------------------
long int Vec3D::IntY()
{
	return iy;
}

// -------------------------------------------------------------------
// IntZ
// -------------------------------------------------------------------
long int Vec3D::IntZ()
{
	return iz;
}

// -------------------------------------------------------------------
// fromIntArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> Vec3D::fromIntArray(boost::shared_ptr<vector<long int> > array)
{
	if (array->size() != 3)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Wrong array size. Vec3D requires an array with 3 parameters (x,y,z)"))); 

	return boost::shared_ptr<Vec3D>(new Vec3D(array->at(0), array->at(1), array->at(2)));
}

// -------------------------------------------------------------------
// fromFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> Vec3D::fromFloatArray(boost::shared_ptr<vector<float> > array)
{
	if (array->size() != 3)
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Wrong array size. Vec3D requires an array with 3 parameters (x,y,z)"))); 

	return boost::shared_ptr<Vec3D>(new Vec3D(array->at(0), array->at(1), array->at(2)));
}

// -------------------------------------------------------------------
// ToIntArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<long int> > Vec3D::ToIntArray()
{
	boost::shared_ptr<vector<long int> > returned (new vector<long int>());
	returned->push_back(ix);
	returned->push_back(iy);
	returned->push_back(iz);

	return returned;
}

// -------------------------------------------------------------------
// ToFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<float> > Vec3D::ToFloatArray()
{
	boost::shared_ptr<vector<float> > returned (new vector<float>());
	returned->push_back(fx);
	returned->push_back(fy);
	returned->push_back(fz);

	return returned;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> Vec3D::ToString()
{
	char buffer[512];

	if (IsFloat())
		sprintf (buffer, "(%f,%f,%f)\n", fx, fy, fz);
	else
		sprintf (buffer, "(%ld,%ld,%ld)\n", ix, iy, iz);

	boost::shared_ptr<string> str (new string(buffer));

	return str;
}

// -------------------------------------------------------------------
// fromArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> Vec3D::fromArray(long int tp, boost::shared_ptr<void> array)
{
	if (tp == SFSDATATYPE_INT_ARRAY)
	{
		return fromIntArray((boost::static_pointer_cast<vector<long int> >)(array));
	}
	else if (tp == SFSDATATYPE_FLOAT_ARRAY)
	{
		return fromFloatArray((boost::static_pointer_cast<vector<float> >)(array));
	}
	else
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Invalid Array Type, cannot convert to Vec3D!"))); 
}

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

