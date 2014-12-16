// ===================================================================
//
// Description		
//		Contains the definition of ISFSObject interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ISFSObject__
#define __ISFSObject__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
	class ISFSObject;
}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#include "../../Util/ByteArray.h"
#include "SFSDataWrapper.h"
#include "ISFSArray.h"

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
	/// SFSObject interface
	/// </summary>
	class DLLImportExport ISFSObject
	{
	public:
		/// <summary>
		/// Checks if a specific element in the SFSObject is null
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool IsNull(string key) = 0;

		/// <summary>
		/// Checks if a specific element in the SFSObject is null
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool IsNull(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns true if an element exists with the provided key
		/// </summary>
		/// <param name="key">
		/// A string
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool ContainsKey(string key) = 0;

		/// <summary>
		/// Returns true if an element exists with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool ContainsKey(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Removes an element
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
        virtual void RemoveElement(string key) = 0;

		/// <summary>
		/// Removes an element
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
        virtual void RemoveElement(boost::shared_ptr<string> key) = 0;

        /// <summary>
        /// Return an array with all the keys in the SFSObject
        /// </summary>
        /// <returns>
        /// A string[]
        /// </returns>
		virtual boost::shared_ptr<vector<string> > GetKeys() = 0;
		
		/// <summary>
		/// Return the number of elements in the SFSObject
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
		virtual boost::shared_ptr<string> GetDump() = 0;  // default to true

		/// <summary>
		/// Returns a detailed hex-dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetHexDump() = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual boost::shared_ptr<SFSDataWrapper> GetData(string key) = 0;
		virtual boost::shared_ptr<SFSDataWrapper> GetData(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a Boolean
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual boost::shared_ptr<bool> GetBool(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a Boolean
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual boost::shared_ptr<bool> GetBool(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a signed byte (8 bit) (int in AS3)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A pointer to an unsigned char
		/// </returns>
		virtual boost::shared_ptr<unsigned char> GetByte(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a signed byte (8 bit) (int in AS3)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A pointer to an unsigned char
		/// </returns>
		virtual boost::shared_ptr<unsigned char> GetByte(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a short int (16 bit) (int in AS3)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to a short integer
		/// </returns>
		virtual boost::shared_ptr<short int> GetShort(string key) = 0;

				/// <summary>
		/// Get the element for the provided key as a short int (16 bit) (int in AS3)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to a short integer
		/// </returns>
		virtual boost::shared_ptr<short int> GetShort(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an int (32 bit)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to long integer
		/// </returns>
		virtual boost::shared_ptr<long int> GetInt(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an int (32 bit)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to long integer
		/// </returns>
		virtual boost::shared_ptr<long int> GetInt(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a long int (64 bit) (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to a long
		/// </returns>
		virtual boost::shared_ptr<long long> GetLong(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a long int (64 bit) (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to a long
		/// </returns>
		virtual boost::shared_ptr<long long> GetLong(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a float (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to a float
		/// </returns>
		virtual boost::shared_ptr<float> GetFloat(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a float (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to a float
		/// </returns>
		virtual boost::shared_ptr<float> GetFloat(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a double (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to a double
		/// </returns>
		virtual boost::shared_ptr<double> GetDouble(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a double (Number in AS3)
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to a double
		/// </returns>
		virtual boost::shared_ptr<double> GetDouble(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a UTF-8 String
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetUtfString(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a UTF-8 String
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetUtfString(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of Booleans
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A bool[]
		/// </returns>
		virtual boost::shared_ptr<vector<bool> > GetBoolArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of Booleans
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A bool[]
		/// </returns>
		virtual boost::shared_ptr<vector<bool> > GetBoolArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a an array of byte
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ByteArray> GetByteArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a an array of byte
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ByteArray> GetByteArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of short int
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A short[]
		/// </returns>
		virtual boost::shared_ptr<vector<short int> > GetShortArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of short int
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A short[]
		/// </returns>
		virtual boost::shared_ptr<vector<short int> > GetShortArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of int
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A int[]
		/// </returns>
		virtual boost::shared_ptr<vector<long int> > GetIntArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of int
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A int[]
		/// </returns>
		virtual boost::shared_ptr<vector<long int> > GetIntArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of long int 
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A long[]
		/// </returns>
		virtual boost::shared_ptr<vector<long long> > GetLongArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of long int 
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A long[]
		/// </returns>
		virtual boost::shared_ptr<vector<long long> > GetLongArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of floats
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A float[]
		/// </returns>
		virtual boost::shared_ptr<vector<float> > GetFloatArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of floats
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A float[]
		/// </returns>
		virtual boost::shared_ptr<vector<float> > GetFloatArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of doubles 
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A double[]
		/// </returns>
		virtual boost::shared_ptr<vector<double> > GetDoubleArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of doubles 
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A double[]
		/// </returns>
		virtual boost::shared_ptr<vector<double> > GetDoubleArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of UTF-8 Strings
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// A string[]
		/// </returns>
		virtual boost::shared_ptr<vector<string> > GetUtfStringArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an array of UTF-8 Strings
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A string[]
		/// </returns>
		virtual boost::shared_ptr<vector<string> > GetUtfStringArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as a pointer to an SFSArray instance 
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="ISFSArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSArray> GetSFSArray(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as a pointer to an SFSArray instance 
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="ISFSArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSArray> GetSFSArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an SFSObject
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="ISFSObject"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSObject> GetSFSObject(string key) = 0;

		/// <summary>
		/// Get the element for the provided key as an SFSObject
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="ISFSObject"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSObject> GetSFSObject(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Get the element for the provided key as an instance of a custom Class.
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
		///			boost::shared_ptr<string> name (new string("spaceShip"));
		///			boost::shared_ptr<SpaceShip> mySpaceShip = (boost::static_pointer_cast<SpaceShip>)sfsObject->getClass(name) 
		/// 	\endcode
		/// </example>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual boost::shared_ptr<void> GetClass(string key) = 0;
		virtual boost::shared_ptr<void> GetClass(boost::shared_ptr<string> key) = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual void PutNull(string key) = 0;
		virtual void PutNull(boost::shared_ptr<string> key) = 0;
		
		/// <summary>
		/// puts a Boolean value with the provided key 
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A boolean pointer
		/// </param>
		virtual void PutBool(string key, boost::shared_ptr<bool> val) = 0;

		/// <summary>
		/// puts a Boolean value with the provided key 
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A boolean pointer
		/// </param>
		virtual void PutBool(boost::shared_ptr<string> key, boost::shared_ptr<bool> val) = 0;

		/// <summary>
		/// puts a Boolean value with the provided key 
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A boolean 
		/// </param>
		virtual void PutBool(string key, bool val) = 0;

		/// <summary>
		/// puts a Boolean value with the provided key 
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A boolean 
		/// </param>
		virtual void PutBool(boost::shared_ptr<string> key, bool val) = 0;

		/// <summary>
		/// puts a byte value (8 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to an unsigned char
		/// </param>
		virtual void PutByte(string key, boost::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// puts a byte value (8 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to an unsigned char
		/// </param>
		virtual void PutByte(boost::shared_ptr<string> key, boost::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// puts a byte value (8 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void PutByte(string key, unsigned char val) = 0;

		/// <summary>
		/// puts a byte value (8 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string poiinter
		/// </param>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void PutByte(boost::shared_ptr<string> key, unsigned char val) = 0;

		/// <summary>
		/// puts a short int (16 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a short integer
		/// </param>
		virtual void PutShort(string key, boost::shared_ptr<short int> val) = 0;

		/// <summary>
		/// puts a short int (16 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a short integer
		/// </param>
		virtual void PutShort(boost::shared_ptr<string> key, boost::shared_ptr<short int> val) = 0;

		/// <summary>
		/// puts a short int (16 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void PutShort(string key, short int val) = 0;

		/// <summary>
		/// puts a short int (16 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void PutShort(boost::shared_ptr<string> key, short int val) = 0;

		/// <summary>
		/// puts an int (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a long integer
		/// </param>
		virtual void PutInt(string key, boost::shared_ptr<long int> val) = 0;

		/// <summary>
		/// puts an int (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a long integer
		/// </param>
		virtual void PutInt(boost::shared_ptr<string> key, boost::shared_ptr<long int> val) = 0;

		/// <summary>
		/// puts an int (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void PutInt(string key, long int val) = 0;

		/// <summary>
		/// puts an int (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void PutInt(boost::shared_ptr<string> key, long int val) = 0;

		/// <summary>
		/// puts a long int (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a long
		/// </param>
		virtual void PutLong(string key, boost::shared_ptr<long long> val) = 0;

		/// <summary>
		/// puts a long int (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a long
		/// </param>
		virtual void PutLong(boost::shared_ptr<string> key, boost::shared_ptr<long long> val) = 0;

		/// <summary>
		/// puts a long int (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void PutLong(string key, long long val) = 0;

		/// <summary>
		/// puts a long int (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void PutLong(boost::shared_ptr<string> key, long long val) = 0;

		/// <summary>
		/// puts a float (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a float
		/// </param>
		virtual void PutFloat(string key, boost::shared_ptr<float> val) = 0;

		/// <summary>
		/// puts a float (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a float
		/// </param>
		virtual void PutFloat(boost::shared_ptr<string> key, boost::shared_ptr<float> val) = 0;

		/// <summary>
		/// puts a float (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void PutFloat(string key, float val) = 0;

		/// <summary>
		/// puts a float (32 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void PutFloat(boost::shared_ptr<string> key, float val) = 0;

		/// <summary>
		/// puts a double (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a double
		/// </param>
		virtual void PutDouble(string key, boost::shared_ptr<double> val) = 0;

		/// <summary>
		/// puts a double (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a double
		/// </param>
		virtual void PutDouble(boost::shared_ptr<string> key, boost::shared_ptr<double> val) = 0;

		/// <summary>
		/// puts a double (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void PutDouble(string key, double val) = 0;

		/// <summary>
		/// puts a double (64 bit) with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void PutDouble(boost::shared_ptr<string> key, double val) = 0;

		/// <summary>
		/// puts a UTF-8 String with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void PutUtfString(string key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// puts a UTF-8 String with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void PutUtfString(boost::shared_ptr<string> key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// puts a UTF-8 String with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A string 
		/// </param>
		virtual void PutUtfString(string key, string val) = 0;

		/// <summary>
		/// puts a UTF-8 String with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A string 
		/// </param>
		virtual void PutUtfString(boost::shared_ptr<string> key, string val) = 0;

		/// <summary>
		/// puts an array of Booleans with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of bool
		/// </param>
		virtual void PutBoolArray(string key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val) = 0;

		/// <summary>
		/// puts an array of Booleans with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of bool
		/// </param>
		virtual void PutBoolArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val) = 0;

		/// <summary>
		/// puts an array of bytes with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		virtual void PutByteArray(string key, boost::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// puts an array of bytes with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		virtual void PutByteArray(boost::shared_ptr<string> key, boost::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// puts an array of short ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of short
		/// </param>
		virtual void PutShortArray(string key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val) = 0;

		/// <summary>
		/// puts an array of short ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of short
		/// </param>
		virtual void PutShortArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val) = 0;

		/// <summary>
		/// puts an array of ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of int
		/// </param>
		virtual void PutIntArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val) = 0;

		/// <summary>
		/// puts an array of ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of int
		/// </param>
		virtual void PutIntArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val) = 0;

		/// <summary>
		/// puts an array of long ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of long
		/// </param>
		virtual void PutLongArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val) = 0;

		/// <summary>
		/// puts an array of long ints with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of long
		/// </param>
		virtual void PutLongArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val) = 0;

		/// <summary>
		/// puts an array of floats with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of float
		/// </param>
		virtual void PutFloatArray(string key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val) = 0;

		/// <summary>
		/// puts an array of floats with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of float
		/// </param>
		virtual void PutFloatArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val) = 0;

		/// <summary>
		/// puts an array of doubles with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of double
		/// </param>
		virtual void PutDoubleArray(string key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val) = 0;

		/// <summary>
		/// puts an array of doubles with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of double
		/// </param>
		virtual void PutDoubleArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val) = 0;

		/// <summary>
		/// puts an array of Strings with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// A vector of string
		/// </param>
		virtual void PutUtfStringArray(string key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val) = 0;

		/// <summary>
		/// puts an array of Strings with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A vector of string
		/// </param>
		virtual void PutUtfStringArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val) = 0;

		/// <summary>
		/// puts an SFSArray with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to an <see cref="ISFSArray"/> instance
		/// </param>
		/// <seealso cref="SFSArray"/>
		virtual void PutSFSArray(string key, boost::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// puts an SFSArray with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to an <see cref="ISFSArray"/> instance
		/// </param>
		/// <seealso cref="SFSArray"/>
		virtual void PutSFSArray(boost::shared_ptr<string> key, boost::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// puts an SFSObject with the provided key
		/// </summary>
		/// <param name="key">
		/// A string 
		/// </param>
		/// <param name="val">
		/// Pointer to an <see cref="ISFSObject"/> instance
		/// </param>
		virtual void PutSFSObject(string key, boost::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// puts an SFSObject with the provided key
		/// </summary>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// Pointer to an <see cref="ISFSObject"/> instance
		/// </param>
		virtual void PutSFSObject(boost::shared_ptr<string> key, boost::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Puts an instance of a custom Class.
		/// </summary>
		/// <remarks>
		/// This is an advanced feature that allows to transmit object instances between .NET and Java provided that both classes are definined under the same package name.
		/// </remarks>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <param name="val">
		/// A void pointer
		/// </param>
		/// <seealso cref="GetClass"/>
		virtual void PutClass(string key, boost::shared_ptr<void> val) = 0;

		/// <summary>
		/// Puts an instance of a custom Class.
		/// </summary>
		/// <remarks>
		/// This is an advanced feature that allows to transmit object instances between .NET and Java provided that both classes are definined under the same package name.
		/// </remarks>
		/// <param name="key">
		/// A string pointer pointer
		/// </param>
		/// <param name="val">
		/// A void pointer
		/// </param>
		/// <seealso cref="GetClass"/>
		virtual void PutClass(boost::shared_ptr<string> key, boost::shared_ptr<void> val) = 0;

		virtual void Put(string key, boost::shared_ptr<SFSDataWrapper> val) = 0;
		virtual void Put(boost::shared_ptr<string> key, boost::shared_ptr<SFSDataWrapper> val) = 0;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
