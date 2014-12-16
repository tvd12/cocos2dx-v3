// ===================================================================
//
// Description		
//		Contains the definition of SFSArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSArray__
#define __SFSArray__

#include "ISFSArray.h"
#include "../../Util/ByteArray.h"
#include "../../Protocol/Serialization/ISFSDataSerializer.h"
#include "../../Entities/Data/SFSDataWrapper.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <map>							// STL library: map object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSArray
	/// </summary>
	/// <remarks>
	/// <b>SFSArray</b> is used from server and client side to exchange data. It can be thought of a specialized Array/List object that can contain any type of data. The advantage of using SFSArray is that you can fine tune the way your data will be transmitted over the network.
	/// For instance, a number like 100 can be transmitted as a normal <b>integer</b> (which takes 32 bits) but also a <b>short</b> (16 bit) or even a <b>byte</b> (8 bit)
	/// <para/>
	/// <b>SFSArray</b> supports many primitive data types and related arrays of primitives. It also allows to serialize class instances and rebuild them on the Java side. This is explained in greater detail in a separate document.
	/// </remarks>
	/// <seealso cref="SFSObject"/>
	class DLLImportExport SFSArray : public ISFSArray, public boost::enable_shared_from_this<SFSArray>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Alternative static constructor that builds an SFSArray populated with the data found in the passed Array
		/// </summary>
		/// <param name="o">
		/// A vector of <see cref="SFSDataWrapper"/> pointers
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="SFSArray"/> instance
		/// </returns>
		static boost::shared_ptr<SFSArray> NewFromArray(vector<boost::shared_ptr<SFSDataWrapper> > o);

		/// <summary>
		/// Alternative static constructor that builds an SFSArray from a valid SFSArray binary representation
		/// </summary>
		/// <param name="ba">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSArray"/> instance
		/// </returns>
		static boost::shared_ptr<SFSArray> NewFromBinaryData(boost::shared_ptr<ByteArray> ba);

		/// <summary>
		/// Alternative static constructor
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="SFSArray"/> instance
		/// </returns>
		static boost::shared_ptr<SFSArray> NewInstance();

		SFSArray();
		virtual ~SFSArray();

		bool Contains(boost::shared_ptr<void> obj);
		boost::shared_ptr<SFSDataWrapper> GetWrappedElementAt(long int index);
		boost::shared_ptr<void> GetElementAt(long int index);
		boost::shared_ptr<void> RemoveElementAt(unsigned long int index);
		long int Size();
		boost::shared_ptr<ByteArray> ToBinary();
		boost::shared_ptr<string> GetDump();
		boost::shared_ptr<string> GetDump(bool format);
		boost::shared_ptr<string> GetHexDump();

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		 void AddNull();
		 void AddBool(boost::shared_ptr<bool> val);
		 void AddBool(bool val);
		 void AddByte(boost::shared_ptr<unsigned char> val);
		 void AddByte(unsigned char val);
		 void AddShort(boost::shared_ptr<short int> val);
		 void AddShort(short int val);
		 void AddInt(boost::shared_ptr<long int> val);
		 void AddInt(long int val);
		 void AddLong(boost::shared_ptr<long long> val);
		 void AddLong(long long val);
		 void AddFloat(boost::shared_ptr<float> val);
		 void AddFloat(float val);
		 void AddDouble(boost::shared_ptr<double> val);
		 void AddDouble(double val);
		 void AddUtfString(boost::shared_ptr<string> val);
		 void AddUtfString(string val);
		 void AddBoolArray(boost::shared_ptr<vector<boost::shared_ptr<bool> > > val);
		 void AddByteArray(boost::shared_ptr<ByteArray> val);
		 void AddShortArray(boost::shared_ptr<vector<boost::shared_ptr<short int> > > val);
		 void AddIntArray(boost::shared_ptr<vector<boost::shared_ptr<long int> > > val);
		 void AddLongArray(boost::shared_ptr<vector<boost::shared_ptr<long long> > > val);
 		 void AddFloatArray(boost::shared_ptr<vector<boost::shared_ptr<float> > > val);
 		 void AddDoubleArray(boost::shared_ptr<vector<boost::shared_ptr<double> > > val);
		 void AddUtfStringArray(boost::shared_ptr<vector<boost::shared_ptr<string> > > val);
		 void AddSFSArray(boost::shared_ptr<ISFSArray> val);
		 void AddSFSObject(boost::shared_ptr<ISFSObject> val);
		 void AddClass(boost::shared_ptr<void> val);
		 void Add(boost::shared_ptr<SFSDataWrapper> wrappedObject);
		 void AddObject(boost::shared_ptr<void> val, SFSDataType tp);

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		 bool IsNull(unsigned long int index);
		 // T GetValue<T>(int index)
		 bool GetBool(unsigned long int index);
		 unsigned char GetByte(unsigned long int index);
		 short int GetShort(unsigned long int index);
		 long int GetInt(unsigned long int index);
		 long long GetLong(unsigned long int index);
		 float GetFloat(unsigned long int index);
		 double GetDouble(unsigned long int index);
		 boost::shared_ptr<string> GetUtfString(unsigned long int index);
		 boost::shared_ptr<vector<boost::shared_ptr<void> > > GetArray(unsigned long int index);
		 boost::shared_ptr<vector<bool> > GetBoolArray(unsigned long int index);
		 boost::shared_ptr<ByteArray> GetByteArray(unsigned long int index);
		 boost::shared_ptr<vector<short int> > GetShortArray(unsigned long int index);
		 boost::shared_ptr<vector<long int> > GetIntArray(unsigned long int index);
		 boost::shared_ptr<vector<long long> > GetLongArray(unsigned long int index);
		 boost::shared_ptr<vector<float> > GetFloatArray(unsigned long int index);
		 boost::shared_ptr<vector<double> > GetDoubleArray(unsigned long int index);
		 boost::shared_ptr<vector<string> > GetUtfStringArray(unsigned long int index);
		 boost::shared_ptr<ISFSArray> GetSFSArray(unsigned long int index);
		 boost::shared_ptr<void> GetClass(unsigned long int index);
		 boost::shared_ptr<ISFSObject> GetSFSObject(unsigned long int index);

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

		boost::shared_ptr<ISFSDataSerializer> serializer;
		boost::shared_ptr<vector<boost::shared_ptr<SFSDataWrapper> > > dataHolder; 
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
