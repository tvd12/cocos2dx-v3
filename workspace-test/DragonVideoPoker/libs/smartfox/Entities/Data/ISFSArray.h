// ===================================================================
//
// Description		
//		Contains the definition of ISFSArray interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ISFSArray__
#define __ISFSArray__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
	class ISFSArray;
}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


#include "../../Util/ByteArray.h"
#include "SFSDataWrapper.h"
#include "ISFSObject.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSArray interface
	/// </summary>
	class DLLImportExport ISFSArray
	{
	public:
		/// <summary>
		/// Returns true if the passed object is contained in the Array
		/// </summary>
		/// <param name="obj">
		/// A void pointer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool Contains(boost::shared_ptr<void> obj) = 0;
		
		/// <summary>
		/// Returns the element at the specified index
		/// </summary>
		/// <param name="index">
		/// A long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual boost::shared_ptr<void> GetElementAt(long int index) = 0;
		
		virtual boost::shared_ptr<SFSDataWrapper> GetWrappedElementAt(long int index) = 0;
		
		/// <summary>
		/// Remove the element at the specified index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual boost::shared_ptr<void> RemoveElementAt(unsigned long int index) = 0;
		
		/// <summary>
		/// Return the number of elements in the Array
		/// </summary>
		/// <returns>
		/// A long integer
		/// </returns>
		virtual long int Size() = 0;
		
		/// <summary>
		/// Return the binary form of the object
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ByteArray> ToBinary() = 0;
		
		/// <summary>
		/// Return a formatted dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <param name="format">
		/// turns the "pretty print" on/off
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetDump(bool format) = 0;

		/// <summary>
		/// Return a formatted dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetDump() = 0; // Default to true
		
		/// <summary>
		/// Returns a detailed hex-dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetHexDump() = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		
		// Primitives
		/// <summary>
		/// Add a null element
		/// </summary>
		virtual void AddNull() = 0;
		
		/// <summary>
		/// Add a Boolean value
		/// </summary>
		/// <param name="val">
		/// A boolean
		/// </param>
		virtual void AddBool(boost::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Add a Boolean value
		/// </summary>
		/// <param name="val">
		/// A boolean
		/// </param>
		virtual void AddBool(bool val) = 0;

		/// <summary>
		/// Add a byte value (8 bit)
		/// </summary>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void AddByte(boost::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Add a byte value (8 bit)
		/// </summary>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void AddByte(unsigned char val) = 0;

		/// <summary>
		/// Add a short int value (16 bit)
		/// </summary>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void AddShort(boost::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Add a short int value (16 bit)
		/// </summary>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void AddShort(short int val) = 0;

		/// <summary>
		/// Add an int value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void AddInt(boost::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Add an int value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void AddInt(long int val) = 0;

		/// <summary>
		/// Add a long int value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void AddLong(boost::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Add a long int value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void AddLong(long long val) = 0;

		/// <summary>
		/// Add a float value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void AddFloat(boost::shared_ptr<float> val) = 0;

		/// <summary>
		/// Add a float value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void AddFloat(float val) = 0;

		/// <summary>
		/// Add a dobule value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void AddDouble(boost::shared_ptr<double> val) = 0;

		/// <summary>
		/// Add a dobule value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void AddDouble(double val) = 0;

		/// <summary>
		/// Add a UTF-8 String
		/// </summary>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void AddUtfString(boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// Add a UTF-8 String
		/// </summary>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void AddUtfString(string val) = 0;

		/// <summary>
		/// Add an array of Booleans
		/// </summary>
		/// <param name="val">
		/// A bool[]
		/// </param>
		virtual void AddBoolArray(boost::shared_ptr<vector<boost::shared_ptr<bool> > > val) = 0;
		
		/// <summary>
		/// Add an array of bytes
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		virtual void AddByteArray(boost::shared_ptr<ByteArray> val) = 0;
		
		/// <summary>
		/// Add an array of short ints 
		/// </summary>
		/// <param name="val">
		/// A short[]
		/// </param>
		virtual void AddShortArray(boost::shared_ptr<vector<boost::shared_ptr<short int> > > val) = 0;
		
		/// <summary>
		/// Add an array of ints
		/// </summary>
		/// <param name="val">
		/// A int[]
		/// </param>
		virtual void AddIntArray(boost::shared_ptr<vector<boost::shared_ptr<long int> > > val) = 0;
		
		/// <summary>
		/// Add an array of long ints
		/// </summary>
		/// <param name="val">
		/// A long[]
		/// </param>
		virtual void AddLongArray(boost::shared_ptr<vector<boost::shared_ptr<long long> > > val) = 0;
		
		/// <summary>
		/// Add an array of floats
		/// </summary>
		/// <param name="val">
		/// A float[]
		/// </param>
		virtual void AddFloatArray(boost::shared_ptr<vector<boost::shared_ptr<float> > > val) = 0;
		
		/// <summary>
		/// Add an array of doubles
		/// </summary>
		/// <param name="val">
		/// A double[]
		/// </param>
		virtual void AddDoubleArray(boost::shared_ptr<vector<boost::shared_ptr<double> > > val) = 0;
		
		/// <summary>
		/// Add an array of UTF-8 String
		/// </summary>
		/// <param name="val">
		/// A string[]
		/// </param>
		virtual void AddUtfStringArray(boost::shared_ptr<vector<boost::shared_ptr<string> > > val) = 0;

		/// <summary>
		/// Add an SFSArray
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ISFSArray"/> instance
		/// </param>
		virtual void AddSFSArray(boost::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Add an SFSObject
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ISFSObject"/> instance
		/// </param>
		/// <seealso cref="SFSObject"/>
		virtual void AddSFSObject(boost::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Add an instance of a custom Class.
		/// </summary>
		/// <remarks>
		/// This is an advanced feature that allows to transmit object instances between Actionscript and Java provided that both classes are definined under the same package name.
		/// </remarks>
		/// <example>
		/// This is an example of the same class on the server and client side:
		/// 
		/// <b>Server Java code:</b>
		///			\code{.cpp}
		/// 			package my.game.spacecombat
		/// 
		/// 			public class SpaceShip
		/// 			{
		/// 				private String type;
		/// 				private String name;
		/// 				private int firePower;
		/// 				private int maxSpeed;
        /// 				private List<String> weapons;
		/// 
		/// 				public SpaceShip(String name, String type)
		/// 				{
		/// 					this.name = name;
		/// 					this.type = type;
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		\endcode
		/// 
		/// <b>Client AS3 code:</b>
		///			\code{.cpp}
		/// 		package my.game.spacecombat
		/// 		{
		/// 			public class SpaceShip
		/// 			{
		/// 				private var _type:String
		/// 				private var _name:String
		/// 				private var _firePower:int;
		/// 				private var _maxSpeed:int;
		/// 				private var _weapons:Array;
		/// 
		/// 				public SpaceShip(name:String, type:Strig)
		/// 				{
		/// 					_name = name
		/// 					_type = type
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		}	
		/// 			
		/// 		\endcode
		/// 
		/// 	A SpaceShip instance from server side is sent to the client. This is how you get it: 
		///		\code{.cpp}
		/// 		boost::shared_ptr<SpaceShip> mySpaceShip = (boost::shared_ptr<SpaceShip>)sfsArray->getClass(0) 
		/// 	\endcode
		/// 
		/// </example>
		/// <param name="val">
		/// A void pointer
		/// </param>
		virtual void AddClass(boost::shared_ptr<void> val) = 0;

		virtual void Add(boost::shared_ptr<SFSDataWrapper> val) = 0;
	
		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <summary>
		/// Checks if a certain element in the Array is null
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool IsNull(unsigned long int index) = 0;

		/// <summary>
		/// Get a Boolean element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool GetBool(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a byte element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// An unsigned char
		/// </returns>
		virtual unsigned char GetByte(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a short int element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A short integer
		/// </returns>
		virtual short int GetShort(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an int element at the provided index 
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long integer
		/// </returns>
		virtual long int GetInt(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a long int element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long
		/// </returns>
		virtual long long GetLong(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a float element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A float
		/// </returns>
		virtual float GetFloat(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a double element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A double
		/// </returns>
		virtual double GetDouble(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a String element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetUtfString(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a Boolean Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A bool[]
		/// </returns>
		virtual boost::shared_ptr<vector<bool> > GetBoolArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a byte Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ByteArray> GetByteArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a short Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A short[]
		/// </returns>
		virtual boost::shared_ptr<vector<short int> > GetShortArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a int Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A int[]
		/// </returns>
		virtual boost::shared_ptr<vector<long int> > GetIntArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a lomg Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long[]
		/// </returns>
		virtual boost::shared_ptr<vector<long long> > GetLongArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a float Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A float[]
		/// </returns>
		virtual boost::shared_ptr<vector<float> > GetFloatArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a double Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A double[]
		/// </returns>
		virtual boost::shared_ptr<vector<double> > GetDoubleArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a String Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A string[]
		/// </returns>
		virtual boost::shared_ptr<vector<string> > GetUtfStringArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an SFSArray element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ISFSArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSArray> GetSFSArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an SFSObject element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ISFSObject"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSObject> GetSFSObject(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a class instance at the provided index.
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		/// <seealso cref="AddClass"/>
		virtual boost::shared_ptr<void> GetClass(unsigned long int index) = 0;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
