// ===================================================================
//
// Description		
//		Contains the definition of SFSObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSObject__
#define __SFSObject__

#include "../../Protocol/Serialization/DefaultObjectDumpFormatter.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"
#include "ISFSObject.h"
#include "../../Util/StringFormatter.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSObject
	/// </summary>
	/// <remarks>
	/// <b>SFSObject</b> is used from server and client side to exchange data. It can be thought of a specialized Dictionary/Map object that can contain any type of data. <br/>
	/// The advantage of using SFSObject is that you can fine tune the way your data will be transmitted over the network.<br/>
	/// For instance, a number like 100 can be transmitted as a normal <b>integer</b> (which takes 32 bits) but also a <b>short</b> (16 bit) or even a <b>byte</b> (8 bit)
	/// <para/>
	/// <b>SFSObject</b> supports many primitive data types and related arrays of primitives. It also allows to serialize class instances and rebuild them on the Java side. <br/>
	/// This is explained in greater detail in a separate document.
	/// </remarks>
	/// <seealso cref="SFSArray"/>
	class DLLImportExport SFSObject : public ISFSObject, public boost::enable_shared_from_this<SFSObject>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		/// <summary>
		/// Alternative static constructor that builds an SFSObject populated with the data found in the passed Object
		/// </summary>
		/// <param name="o">
		/// A void pointer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static boost::shared_ptr<SFSObject> NewFromObject(boost::shared_ptr<void> o);

		/// <summary>
		/// Alternative static constructor that builds an SFSObject from a valid SFSObject binary representation
		/// </summary>
		/// <param name="ba">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static boost::shared_ptr<SFSObject> NewFromBinaryData(boost::shared_ptr<ByteArray> ba);

		/// <summary>
		/// Alternative static constructor
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static boost::shared_ptr<SFSObject> NewInstance();

		/// <summary>
        /// 
        /// </summary>
        /// <summary>
        /// 
        /// </summary>
		SFSObject();
		virtual ~SFSObject();

		boost::shared_ptr<SFSDataWrapper> GetData(string key);
		boost::shared_ptr<SFSDataWrapper> GetData(boost::shared_ptr<string> key);
		//T GetValue<T>(string key);
		boost::shared_ptr<bool> GetBool(string key);
		boost::shared_ptr<bool> GetBool(boost::shared_ptr<string> key);
		boost::shared_ptr<unsigned char> GetByte(string key);
		boost::shared_ptr<unsigned char> GetByte(boost::shared_ptr<string> key);
		boost::shared_ptr<short int> GetShort(string key);
		boost::shared_ptr<short int> GetShort(boost::shared_ptr<string> key);
		boost::shared_ptr<long int> GetInt(string key);
		boost::shared_ptr<long int> GetInt(boost::shared_ptr<string> key);
		boost::shared_ptr<long long> GetLong(string key);
		boost::shared_ptr<long long> GetLong(boost::shared_ptr<string> key);
		boost::shared_ptr<float> GetFloat(string key);
		boost::shared_ptr<float> GetFloat(boost::shared_ptr<string> key);
		boost::shared_ptr<double> GetDouble(string key);
		boost::shared_ptr<double> GetDouble(boost::shared_ptr<string> key);
		boost::shared_ptr<string> GetUtfString(string key);
		boost::shared_ptr<string> GetUtfString(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<unsigned char> > GetArray(string key);
		boost::shared_ptr<vector<unsigned char> > GetArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<bool> > GetBoolArray(string key);
		boost::shared_ptr<vector<bool> > GetBoolArray(boost::shared_ptr<string> key);
		boost::shared_ptr<ByteArray> GetByteArray(string key);
		boost::shared_ptr<ByteArray> GetByteArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<short int> > GetShortArray(string key);
		boost::shared_ptr<vector<short int> > GetShortArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<long int> > GetIntArray(string key);
		boost::shared_ptr<vector<long int> > GetIntArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<long long> > GetLongArray(string key);
		boost::shared_ptr<vector<long long> > GetLongArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<float> > GetFloatArray(string key);
		boost::shared_ptr<vector<float> > GetFloatArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<double> > GetDoubleArray(string key);
		boost::shared_ptr<vector<double> > GetDoubleArray(boost::shared_ptr<string> key);
		boost::shared_ptr<vector<string> > GetUtfStringArray(string key);
		boost::shared_ptr<vector<string> > GetUtfStringArray(boost::shared_ptr<string> key);
		boost::shared_ptr<ISFSArray> GetSFSArray(string key);
		boost::shared_ptr<ISFSArray> GetSFSArray(boost::shared_ptr<string> key);
		boost::shared_ptr<ISFSObject> GetSFSObject(string key);
		boost::shared_ptr<ISFSObject> GetSFSObject(boost::shared_ptr<string> key);

		void PutNull(string key);
		void PutNull(boost::shared_ptr<string> key);
		void PutBool(string key, boost::shared_ptr<bool> val);
		void PutBool(boost::shared_ptr<string> key, boost::shared_ptr<bool> val);
		void PutBool(string key, bool val);
		void PutBool(boost::shared_ptr<string> key, bool val);
		void PutByte(string key, boost::shared_ptr<unsigned char> val);
		void PutByte(boost::shared_ptr<string> key, boost::shared_ptr<unsigned char> val);
		void PutByte(string key, unsigned char val);
		void PutByte(boost::shared_ptr<string> key, unsigned char val);
		void PutShort(string key, boost::shared_ptr<short int> val);
		void PutShort(boost::shared_ptr<string> key, boost::shared_ptr<short int> val);
		void PutShort(string key, short int val);
		void PutShort(boost::shared_ptr<string> key, short int val);
		void PutInt(string key, boost::shared_ptr<long int> val);
		void PutInt(boost::shared_ptr<string> key, boost::shared_ptr<long int> val);
		void PutInt(string key, long int val);
		void PutInt(boost::shared_ptr<string> key, long int val);
		void PutLong(string key, boost::shared_ptr<long long> val);
		void PutLong(boost::shared_ptr<string> key, boost::shared_ptr<long long> val);
		void PutLong(string key, long long val);
		void PutLong(boost::shared_ptr<string> key, long long val);
		void PutFloat(string key, boost::shared_ptr<float> val);
		void PutFloat(boost::shared_ptr<string> key, boost::shared_ptr<float> val);
		void PutFloat(string key, float val);
		void PutFloat(boost::shared_ptr<string> key, float val);
		void PutDouble(string key, boost::shared_ptr<double> val);
		void PutDouble(boost::shared_ptr<string> key, boost::shared_ptr<double> val);
		void PutDouble(string key, double val);
		void PutDouble(boost::shared_ptr<string> key, double val);
		void PutUtfString(string key, boost::shared_ptr<string> val);
		void PutUtfString(boost::shared_ptr<string> key, boost::shared_ptr<string> val);
		void PutUtfString(string key, string val);
		void PutUtfString(boost::shared_ptr<string> key, string val);

		void PutBoolArray(string key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val);
		void PutBoolArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val);
		void PutByteArray(string key, boost::shared_ptr<ByteArray> val);
		void PutByteArray(boost::shared_ptr<string> key, boost::shared_ptr<ByteArray> val);
		void PutShortArray(string key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val);
		void PutShortArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val);
		void PutIntArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val);
		void PutIntArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val);
		void PutLongArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val);
		void PutLongArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val);
		void PutFloatArray(string key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val);
		void PutFloatArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val);
		void PutDoubleArray(string key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val);
		void PutDoubleArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val);
		void PutUtfStringArray(string key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val);
		void PutUtfStringArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val);
		void PutSFSArray(string key, boost::shared_ptr<ISFSArray> val);
		void PutSFSArray(boost::shared_ptr<string> key, boost::shared_ptr<ISFSArray> val);
		void PutSFSObject(string key, boost::shared_ptr<ISFSObject> val);
		void PutSFSObject(boost::shared_ptr<string> key, boost::shared_ptr<ISFSObject> val);

		void Put(string key, boost::shared_ptr<SFSDataWrapper> val);
		void Put(boost::shared_ptr<string> key, boost::shared_ptr<SFSDataWrapper> val);
		bool ContainsKey(string key);
		bool ContainsKey(boost::shared_ptr<string> key);
		boost::shared_ptr<void> GetClass(string key);
		boost::shared_ptr<void> GetClass(boost::shared_ptr<string> key);
		boost::shared_ptr<string> GetDump(bool format); 
		boost::shared_ptr<string> GetDump();
		boost::shared_ptr<string> GetHexDump();

		boost::shared_ptr<vector<string> > GetKeys();
		bool IsNull(boost::shared_ptr<string> key);
		bool IsNull(string key);
		void PutClass(string key, boost::shared_ptr<void> val);
		void PutClass(boost::shared_ptr<string> key, boost::shared_ptr<void> val);
        void RemoveElement(string key);
        void RemoveElement(boost::shared_ptr<string> key);
		long int Size();
		boost::shared_ptr<ByteArray> ToBinary();

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

		boost::shared_ptr<string> Dump();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<map<string, boost::shared_ptr<SFSDataWrapper> > > dataHolder;
		boost::shared_ptr<ISFSDataSerializer> serializer;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
