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
#include "DefaultSFSDataSerializer.h"

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

boost::shared_ptr<string> DefaultSFSDataSerializer::CLASS_MARKER_KEY (new string("$C"));
boost::shared_ptr<string> DefaultSFSDataSerializer::CLASS_FIELDS_KEY (new string("$F"));
boost::shared_ptr<string> DefaultSFSDataSerializer::FIELD_NAME_KEY (new string("N"));
boost::shared_ptr<string> DefaultSFSDataSerializer::FIELD_VALUE_KEY (new string("V"));

boost::shared_ptr<DefaultSFSDataSerializer> DefaultSFSDataSerializer::instance = boost::shared_ptr<DefaultSFSDataSerializer>();

// -------------------------------------------------------------------
// Instance
// -------------------------------------------------------------------
boost::shared_ptr<DefaultSFSDataSerializer> DefaultSFSDataSerializer::Instance()
{
	if (instance == NULL)
	{
		instance = boost::shared_ptr<DefaultSFSDataSerializer>(new DefaultSFSDataSerializer());
	}

	return instance;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
DefaultSFSDataSerializer::DefaultSFSDataSerializer()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
DefaultSFSDataSerializer::~DefaultSFSDataSerializer()
{
}

// SFSObject ==> Binary

// -------------------------------------------------------------------
// Object2Binary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Object2Binary(boost::shared_ptr<ISFSObject> obj)
{
	boost::shared_ptr<ByteArray> buffer (new ByteArray());
	buffer->WriteByte((unsigned char)SFSDATATYPE_SFS_OBJECT);
	buffer->WriteShort((short int)obj->Size());
			
	return Obj2bin(obj, buffer);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Obj2bin(boost::shared_ptr<ISFSObject> obj, boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<vector<string> > keys = obj->GetKeys();
	boost::shared_ptr<SFSDataWrapper> wrapper;

	vector<string>::iterator iterator;
	for(iterator = keys->begin(); iterator != keys->end(); ++iterator)
	{
		boost::shared_ptr<string> key (new string(*iterator));

		wrapper = obj->GetData(*key);

		// Store the key
		buffer = EncodeSFSObjectKey(buffer, key);
																
		// Convert 2 binary
		buffer = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
	}

	keys->clear();

	return buffer;
}




// SFSArray ==> Binary

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Array2Binary(boost::shared_ptr<ISFSArray> arrayobj)
{
	boost::shared_ptr<ByteArray> buffer (new ByteArray());
	buffer->WriteByte((unsigned char) SFSDATATYPE_SFS_ARRAY);
	buffer->WriteShort((short)arrayobj->Size());
	return Arr2bin(arrayobj, buffer);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Arr2bin(boost::shared_ptr<ISFSArray> arrayobj, boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<SFSDataWrapper> wrapper;

	for (int i = 0; i < arrayobj->Size(); i++)	
	{
		wrapper = arrayobj->GetWrappedElementAt(i);
		buffer = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
	}
			
	return buffer;
}



// Binary ==> SFSObject

boost::shared_ptr<ISFSObject> DefaultSFSDataSerializer::Binary2Object(boost::shared_ptr<ByteArray> data)
{
	if (data->Length() < 3) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Can't decode an SFSObject. Byte data is insufficient. Size: %d byte(s)"));
		StringFormatter<long int> (err, format, data->Length());
		
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	data->Position(0);
	return DecodeSFSObject(data);
}

boost::shared_ptr<ISFSObject> DefaultSFSDataSerializer::DecodeSFSObject(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<SFSObject> sfsObject (SFSObject::NewInstance());
						
	// Get tpyeId
	unsigned char headerByte;
	buffer->ReadByte(headerByte);
						
	// Validate typeId
	if (headerByte != (unsigned char)SFSDATATYPE_SFS_OBJECT) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Invalid SFSDataType. Expected: %d, found: %d"));
		StringFormatter<long int, unsigned char> (err, format, SFSDATATYPE_SFS_OBJECT, headerByte);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
	
	short int size;
	buffer->ReadShort(size);
			
	// Validate size
	if (size < 0) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Can't decode SFSObject. Size is negative: %d"));
		StringFormatter<long int> (err, format, size);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}		
			
	/*
     * NOTE: we catch codec exceptions OUTSIDE of the loop
     * meaning that any exception of that type will stop the process of looping through the
     * object data and immediately discard the whole packet of data. 
     */

	try 
	{
		for (int i = 0; i < size; i++) 
		{
			// Decode object key
	     	string key;
			buffer->ReadUTF(key);
		     		
			//Console.WriteLine("Decoding object "+key);
					
	     	// Decode the next object
	     	boost::shared_ptr<SFSDataWrapper> decodedObject = DecodeObject(buffer);
		     		
	     	// Store decoded object and keep going
	     	if (decodedObject != NULL) 
			{
				boost::shared_ptr<string> keyRef (new string(key));
	     		sfsObject->Put(keyRef, decodedObject);
			}		
	     	else 
			{
				boost::shared_ptr<string> err (new string());

				boost::shared_ptr<string> format (new string("Could not decode value for SFSObject with key: %s"));
				StringFormatter<const char*> (err, format, key.c_str());

				boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
				throw exception;
			}
	    }	
	}
	catch (SFSCodecError err) 
	{
		throw err;
	}
		
	return sfsObject;
}



// Binary ==> SFSArray

boost::shared_ptr<ISFSArray> DefaultSFSDataSerializer::Binary2Array(boost::shared_ptr<ByteArray> data)
{
	if (data->Length() < 3) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Can't decode an SFSArray. Byte data is insufficient. Size:: %d byte(s)"));
		StringFormatter<long int> (err, format, data->Length());
		
		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	data->Position(0);
	return DecodeSFSArray(data);
}

boost::shared_ptr<ISFSArray> DefaultSFSDataSerializer::DecodeSFSArray(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<ISFSArray> sfsArray (SFSArray::NewInstance());

	// Get tpyeId
	unsigned char type;
	buffer->ReadByte(type);
	SFSDataType headerType = (SFSDataType)(long int)(type);
			
	// Validate typeId
	if (headerType != SFSDATATYPE_SFS_ARRAY) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Invalid SFSDataType. Expected: %d, found: %d"));
		StringFormatter<long int, long int> (err, format, SFSDATATYPE_SFS_ARRAY, headerType);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	short int size;
	buffer->ReadShort(size);
			
	// Validate size
	if (size < 0) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Can't decode SFSArray. Size is negative: %d"));
		StringFormatter<long int> (err, format, size);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	/*
	 * NOTE: we catch codec exceptions OUTSIDE of the loop
	 * meaning that any exception of that type will stop the process of looping through the
	 * object data and immediately discard the whole packet of data. 
	 */

	try
	{
		for (long int i = 0; i < size; i++) 
		{
			// Decode the next object
		    boost::shared_ptr<SFSDataWrapper> decodedObject = DecodeObject(buffer);

		     // Store decoded object and keep going
		     if (decodedObject != NULL) 
			 {
				sfsArray->Add(decodedObject);
			}
		    else 
			{
				boost::shared_ptr<string> err (new string());

				boost::shared_ptr<string> format (new string("Could not decode SFSArray item at index: %d"));
				StringFormatter<long int> (err, format, i);

				boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
				throw exception;
			}
		}	
	}
	catch (SFSCodecError err)
	{
		throw err;
	}
		     
	return sfsArray;
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::DecodeObject(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<SFSDataWrapper> decodedObject;
	unsigned char headerValue;
	buffer->ReadByte(headerValue);
	SFSDataType headerByte = (SFSDataType)(long int)(headerValue);
			
	// Console.WriteLine(headerByte);
	if (headerByte == SFSDATATYPE_NULL)
	 	decodedObject = BinDecode_NULL(buffer);
	else if (headerByte == SFSDATATYPE_BOOL)
		decodedObject = BinDecode_BOOL(buffer);
	else if (headerByte == SFSDATATYPE_BOOL_ARRAY)
		decodedObject = BinDecode_BOOL_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_BYTE)
		decodedObject = BinDecode_BYTE(buffer);
	else if (headerByte == SFSDATATYPE_BYTE_ARRAY)
		decodedObject = BinDecode_BYTE_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_SHORT)
		decodedObject = BinDecode_SHORT(buffer);
	else if (headerByte == SFSDATATYPE_SHORT_ARRAY)
		decodedObject = BinDecode_SHORT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_INT)
		decodedObject = BinDecode_INT(buffer);
	else if (headerByte == SFSDATATYPE_INT_ARRAY)
		decodedObject = BinDecode_INT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_LONG)
		decodedObject = BinDecode_LONG(buffer);
	else if (headerByte == SFSDATATYPE_LONG_ARRAY)
		decodedObject = BinDecode_LONG_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_FLOAT)
		decodedObject = BinDecode_FLOAT(buffer);
	else if (headerByte == SFSDATATYPE_FLOAT_ARRAY)
		decodedObject = BinDecode_FLOAT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_DOUBLE)
		decodedObject = BinDecode_DOUBLE(buffer);
	else if (headerByte == SFSDATATYPE_DOUBLE_ARRAY)
		decodedObject = BinDecode_DOUBLE_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_UTF_STRING)
		decodedObject = BinDecode_UTF_STRING(buffer);
	else if (headerByte == SFSDATATYPE_UTF_STRING_ARRAY)
		decodedObject = BinDecode_UTF_STRING_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_SFS_ARRAY) {
		// pointer goes back 1 position
		buffer->Position(buffer->Position() - 1);
		decodedObject = boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper((long int)SFSDATATYPE_SFS_ARRAY, DecodeSFSArray(buffer)));
	}
	else if (headerByte == SFSDATATYPE_SFS_OBJECT)
	{
		// pointer goes back 1 position
		buffer->Position(buffer->Position() - 1);
				
		/*
		* See if this is a special type of SFSObject, the one that actually describes a Class
		*/
		boost::shared_ptr<ISFSObject> sfsObj = DecodeSFSObject(buffer);
		unsigned char type = (unsigned char)((long int)SFSDATATYPE_SFS_OBJECT);
		boost::shared_ptr<void> finalSfsObj = sfsObj;
				
		if (sfsObj->ContainsKey(CLASS_MARKER_KEY) && sfsObj->ContainsKey(CLASS_FIELDS_KEY)) 
		{   
			type = (unsigned char)((long int)SFSDATATYPE_CLASS);
		}
				
		decodedObject = boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(type, finalSfsObj));
	}
	// What is this typeID??
	else 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Unknow SFSDataType ID: %d"));
		StringFormatter<long int> (err, format, headerByte);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	return decodedObject;
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeObject(boost::shared_ptr<ByteArray> buffer, int typeId, boost::shared_ptr<void> data)
{
	switch((SFSDataType)typeId) 
	{
	case SFSDATATYPE_NULL:
		buffer = BinEncode_NULL(buffer);
		break;
	case SFSDATATYPE_BOOL:
		buffer = BinEncode_BOOL(buffer, (boost::static_pointer_cast<bool>)(data));
		break;
	case SFSDATATYPE_BYTE:
		buffer = BinEncode_BYTE(buffer, (boost::static_pointer_cast<unsigned char>)(data));
		break;
	case SFSDATATYPE_SHORT:
		buffer = BinEncode_SHORT(buffer, (boost::static_pointer_cast<short int>)(data));
		break;
	case SFSDATATYPE_INT:
		buffer = BinEncode_INT(buffer, (boost::static_pointer_cast<long int>)(data));
		break;
	case SFSDATATYPE_LONG:
		buffer = BinEncode_LONG(buffer, (boost::static_pointer_cast<long long>)(data));
		break;
	case SFSDATATYPE_FLOAT:
		buffer = BinEncode_FLOAT(buffer, (boost::static_pointer_cast<float>)(data));
		break;
	case SFSDATATYPE_DOUBLE:
		buffer = BinEncode_DOUBLE(buffer, (boost::static_pointer_cast<double>)(data));
		break;
	case SFSDATATYPE_UTF_STRING:
		buffer = BinEncode_UTF_STRING(buffer, (boost::static_pointer_cast<string>)(data));
		break;
	case SFSDATATYPE_BOOL_ARRAY:
		buffer = BinEncode_BOOL_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<bool> > >)(data));
		break;
	case SFSDATATYPE_BYTE_ARRAY:
		buffer = BinEncode_BYTE_ARRAY(buffer, (boost::static_pointer_cast<ByteArray>)(data)); 
		break;
	case SFSDATATYPE_SHORT_ARRAY:
		buffer = BinEncode_SHORT_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<short int> > >)(data));
		break;
	case SFSDATATYPE_INT_ARRAY:
		buffer = BinEncode_INT_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<long int> > >)(data));
		break;
	case SFSDATATYPE_LONG_ARRAY:
		buffer = BinEncode_LONG_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<long long> > >)(data));
		break;
	case SFSDATATYPE_FLOAT_ARRAY:
		buffer = BinEncode_FLOAT_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<float> > >)(data));
		break;
	case SFSDATATYPE_DOUBLE_ARRAY:
		buffer = BinEncode_DOUBLE_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<double> > >)(data));
		break;
	case SFSDATATYPE_UTF_STRING_ARRAY:
		buffer = BinEncode_UTF_STRING_ARRAY(buffer, (boost::static_pointer_cast<vector<boost::shared_ptr<string> > >)(data));
		break;
	case SFSDATATYPE_SFS_ARRAY:
		buffer = AddData(buffer, Array2Binary((boost::static_pointer_cast<ISFSArray>)(data)));
		break;
	case SFSDATATYPE_SFS_OBJECT:
		buffer = AddData(buffer, Object2Binary((boost::static_pointer_cast<SFSObject>)(data)));
		break;
	case SFSDATATYPE_CLASS:
		buffer = AddData(buffer, Object2Binary((boost::static_pointer_cast<SFSObject>)(data)));
		break;
	default:
		{
			boost::shared_ptr<string> err (new string());

			boost::shared_ptr<string> format (new string("Unrecognized type in SFSObject serialization: %d"));
			StringFormatter<long int> (err, format, typeId);

			boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
			throw exception;
		}
	}
			
	return buffer;
}



// Binary Entities Decoding Methods

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_NULL(boost::shared_ptr<ByteArray> buffer)
{
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_NULL, boost::shared_ptr<void>()));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BOOL(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<bool> value (new bool());
	buffer->ReadBool(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BOOL, (boost::static_pointer_cast<void>)(value)));
}
boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BYTE(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<unsigned char> value (new unsigned char());
	buffer->ReadByte(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BYTE, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_SHORT(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<short int> value (new short int());
	buffer->ReadShort(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_SHORT, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<long int> value (new long int());
	buffer->ReadInt(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_INT, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_LONG(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<long long> value (new long long());
	buffer->ReadLong(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_LONG, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_FLOAT(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<float> value (new float());
	buffer->ReadFloat(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_FLOAT, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_DOUBLE(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<double> value (new double());
	buffer->ReadDouble(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_DOUBLE, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_UTF_STRING(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<string> value (new string()); 
	buffer->ReadUTF(*value);
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_UTF_STRING, (boost::static_pointer_cast<void>)(value)));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BOOL_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
	boost::shared_ptr<vector<bool> > arrayobj (new vector<bool>());
			
	for (int j = 0; j < size; j++) 
	{
		boost::shared_ptr<bool> value (new bool);
		buffer->ReadBool(*value);
		arrayobj->push_back(*value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BOOL_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BYTE_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size;
	buffer->ReadInt(size);
			
	if (size < 0) 
	{
		boost::shared_ptr<string> err (new string());
		 
		boost::shared_ptr<string> format (new string("Array negative size: %d"));
		StringFormatter<long int> (err, format, size);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
	
	// copy bytes
	boost::shared_ptr<vector<unsigned char> > values (new vector<unsigned char>());
	buffer->ReadBytes(size, *values.get());
	boost::shared_ptr<ByteArray> arrayobj (new ByteArray());
	arrayobj->WriteBytes(values);
						
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BYTE_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_SHORT_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
	boost::shared_ptr<vector<short int> > arrayobj (new vector<short int>());
			
	for (int j = 0; j < size; j++) 
	{
		short int value;
		buffer->ReadShort(value);
		arrayobj->push_back(value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_SHORT_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
	boost::shared_ptr<vector<long int> > arrayobj (new vector<long int>());
			
	for (int j = 0; j < size; j++) 
	{
		long int value;
		buffer->ReadInt(value);
		arrayobj->push_back(value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_INT_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_LONG_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
	boost::shared_ptr<vector<long> > arrayobj (new vector<long>());
			
	for (int j = 0; j < size; j++) 
	{
		long long value;
		buffer->ReadLong(value);
		arrayobj->push_back((long)value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_LONG_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_FLOAT_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
			
	boost::shared_ptr<vector<float> > arrayobj (new vector<float>());
			
	for (int j = 0; j < size; j++) 
	{
		float value;
		buffer->ReadFloat(value);
		arrayobj->push_back(value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_FLOAT_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_DOUBLE_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
			
	boost::shared_ptr<vector<double> > arrayobj (new vector<double>());
			
	for (int j = 0; j < size; j++) 
	{
		double value;
		buffer->ReadDouble(value);
		arrayobj->push_back(value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_DOUBLE_ARRAY, arrayobj));
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_UTF_STRING_ARRAY(boost::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
			
	boost::shared_ptr<vector<string> > arrayobj (new vector<string>());
			
	for (int j = 0; j < size; j++) 
	{
		string value;
		buffer->ReadUTF(value);
		arrayobj->push_back(value);
	}
			
	return boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_UTF_STRING_ARRAY, arrayobj));
}

long int DefaultSFSDataSerializer::GetTypedArraySize(boost::shared_ptr<ByteArray> buffer)
{
	short int size;
	buffer->ReadShort(size);
			
	if (size < 0) 
	{
		boost::shared_ptr<string> err (new string());

		boost::shared_ptr<string> format (new string("Array negative size: %d"));
		StringFormatter<long int> (err, format, size);

		boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	return size;
}



// Binary Entities Encoding Methods

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_NULL(boost::shared_ptr<ByteArray> buffer)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte((unsigned char)0x00);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<bool> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BOOL);
	data->WriteBool(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<unsigned char> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BYTE);
	data->WriteByte(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<short int> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_SHORT);
	data->WriteShort(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<long int> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_INT);
	data->WriteInt(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<long long> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_LONG);
	data->WriteLong(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<float> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_FLOAT);
	data->WriteFloat(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<double> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE);
	data->WriteDouble(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<double> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE);
	data->WriteDouble(*val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_UTF_STRING(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<string> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_UTF_STRING);
	data->WriteUTF(val);
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BOOL_ARRAY);
	data->WriteShort((short int)(val->size()));
			
	vector<boost::shared_ptr<bool> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<bool> value = *iterator;
		data->WriteBool(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<ByteArray> val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BYTE_ARRAY);
	data->WriteInt(val->Length());
	data->WriteBytes(val->Bytes());
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_SHORT_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<boost::shared_ptr<short int> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<short int> value = *iterator;
		data->WriteShort(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_INT_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<boost::shared_ptr<long int> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<long int> value = *iterator;
		data->WriteInt(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_LONG_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<boost::shared_ptr<long long> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<long long> value = *iterator;
		data->WriteLong(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<float> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_FLOAT_ARRAY);
	data->WriteShort((short int)(val->size()));
			
	vector<boost::shared_ptr<float> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<float> value = *iterator;
		data->WriteFloat(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<double> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<boost::shared_ptr<double> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		boost::shared_ptr<double> value = *iterator;
		data->WriteDouble(*value);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_UTF_STRING_ARRAY(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<vector<boost::shared_ptr<string> > > val)
{
	boost::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_UTF_STRING_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<boost::shared_ptr<string> >::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteUTF(*iterator);
	}
			
	return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeSFSObjectKey(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<string> val)
{
	buffer->WriteUTF(val);	
	return buffer;
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::AddData(boost::shared_ptr<ByteArray> buffer, boost::shared_ptr<ByteArray> newData)
{
	buffer->WriteBytes(newData->Bytes());
	return buffer;
}




}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X

