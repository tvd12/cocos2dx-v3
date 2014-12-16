// ===================================================================
//
// Description		
//		Contains the definition of DefaultSFSDataSerializer
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __DefaultSFSDataSerializer__
#define __DefaultSFSDataSerializer__

#include "ISFSDataSerializer.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Data/ISFSArray.h"
#include "../../Entities/Data/SFSObject.h"
#include "../../Entities/Data/SFSArray.h"
#include "../../Entities/Data/SFSDataType.h"
#include "../../Util/ByteArray.h"
#include "../../Exceptions/SFSCodecError.h"
#include "../../Util/StringFormatter.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
#include <map>							// STL library: map object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	// -------------------------------------------------------------------
	// Class DefaultSFSDataSerializer
	// -------------------------------------------------------------------
	class DefaultSFSDataSerializer : public ISFSDataSerializer
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static boost::shared_ptr<DefaultSFSDataSerializer> Instance();

		DefaultSFSDataSerializer();
		virtual ~DefaultSFSDataSerializer();

		// SFSObject ==> Binary

		boost::shared_ptr<ByteArray> Object2Binary(boost::shared_ptr<ISFSObject> obj);

		// SFSArray ==> Binary

		boost::shared_ptr<ByteArray> Array2Binary(boost::shared_ptr<ISFSArray> arrayobj);

		// Binary ==> SFSObject

		boost::shared_ptr<ISFSObject> Binary2Object(boost::shared_ptr<ByteArray> data);

		// Binary ==> SFSArray

		boost::shared_ptr<ISFSArray> Binary2Array(boost::shared_ptr<ByteArray> data);


		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> CLASS_MARKER_KEY;
		static boost::shared_ptr<string> CLASS_FIELDS_KEY;
		static boost::shared_ptr<string> FIELD_NAME_KEY;
		static boost::shared_ptr<string> FIELD_VALUE_KEY;

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

		boost::shared_ptr<ByteArray> Obj2bin(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<ByteArray> Arr2bin(boost::shared_ptr<ISFSArray> arrayobj, boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<ISFSObject> DecodeSFSObject(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<ISFSArray> DecodeSFSArray(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<ByteArray> EncodeObject(boost::shared_ptr<ByteArray> buffer, int typeId, boost::shared_ptr<void> data);

		/*
	 	* The buffer pointer (position) must located on the 1st byte of the object to decode
	 	* Throws SFSCodecException
	 	*/
		boost::shared_ptr<SFSDataWrapper> DecodeObject(boost::shared_ptr<ByteArray> buffer);

		// Binary Entities Decoding Methods

		boost::shared_ptr<SFSDataWrapper> BinDecode_NULL(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_BOOL(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_BYTE(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_SHORT(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_INT(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_LONG(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_FLOAT(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_DOUBLE(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_UTF_STRING(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_BOOL_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_BYTE_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_SHORT_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_INT_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_LONG_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_FLOAT_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_DOUBLE_ARRAY(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<SFSDataWrapper> BinDecode_UTF_STRING_ARRAY(boost::shared_ptr<ByteArray> buffer);
		long int GetTypedArraySize(boost::shared_ptr<ByteArray> buffer);

		// Binary Entities Encoding Methods

		boost::shared_ptr<ByteArray> BinEncode_NULL(boost::shared_ptr<ByteArray> buffer);
		boost::shared_ptr<ByteArray> BinEncode_BOOL(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<bool> val);
		boost::shared_ptr<ByteArray> BinEncode_BYTE(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<unsigned char> val);
		boost::shared_ptr<ByteArray> BinEncode_SHORT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<short int> val);
		boost::shared_ptr<ByteArray> BinEncode_INT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<long int> val);
		boost::shared_ptr<ByteArray> BinEncode_LONG(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<long long> val);
		boost::shared_ptr<ByteArray> BinEncode_FLOAT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<float> val);
		boost::shared_ptr<ByteArray> BinEncode_DOUBLE(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<double> val);
		boost::shared_ptr<ByteArray> BinEncode_INT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<double> val);
		boost::shared_ptr<ByteArray> BinEncode_UTF_STRING(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<string> val);
		boost::shared_ptr<ByteArray> BinEncode_BOOL_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val);
		boost::shared_ptr<ByteArray> BinEncode_BYTE_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<ByteArray> val);
		boost::shared_ptr<ByteArray> BinEncode_SHORT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val);
		boost::shared_ptr<ByteArray> BinEncode_INT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val);
		boost::shared_ptr<ByteArray> BinEncode_LONG_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val);
		boost::shared_ptr<ByteArray> BinEncode_FLOAT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<float> > > val);
		boost::shared_ptr<ByteArray> BinEncode_DOUBLE_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<double> > > val);
		boost::shared_ptr<ByteArray> BinEncode_UTF_STRING_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<string> > > val);
		boost::shared_ptr<ByteArray> EncodeSFSObjectKey(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<string> val);

		/*
		* Returns the same buffer
		* (could be used also to create copies)
		*/
		boost::shared_ptr<ByteArray> AddData(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<ByteArray> newData);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		static boost::shared_ptr<DefaultSFSDataSerializer> instance;
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X

#endif
