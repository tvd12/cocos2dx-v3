// ===================================================================
//
// Description		
//		Contains the implementation of SFSObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSObject.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSObject::SFSObject()
{
	dataHolder = boost::shared_ptr<map<string, boost::shared_ptr<SFSDataWrapper> > >(new map<string, boost::shared_ptr<SFSDataWrapper> >());
	serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSObject::~SFSObject()
{
	dataHolder->clear();
}

// -------------------------------------------------------------------
// NewFromObject
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject> SFSObject::NewFromObject(boost::shared_ptr<void> o)
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("Not implemented"))); 
}


// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject> SFSObject::NewFromBinaryData(boost::shared_ptr<ByteArray> ba)
{
	return (boost::static_pointer_cast<SFSObject>)(DefaultSFSDataSerializer::Instance()->Binary2Object(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject> SFSObject::NewInstance()
{
	boost::shared_ptr<SFSObject> returned (new SFSObject());
	return returned;
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::Dump()
{
	boost::shared_ptr<string> strDump (new string());
	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);
	boost::shared_ptr<SFSDataWrapper> wrapper;

	long int type;

	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		wrapper = iterator->second;
		string key = iterator->first;
		type = wrapper->Type();

		strDump->append("(");
		
		switch (type)
		{
		case SFSDATATYPE_NULL: strDump->append("null"); break;
		case SFSDATATYPE_BOOL: strDump->append("bool"); break;
		case SFSDATATYPE_BYTE: strDump->append("byte"); break;
		case SFSDATATYPE_SHORT: strDump->append("short"); break;
		case SFSDATATYPE_INT: strDump->append("int"); break;
		case SFSDATATYPE_LONG: strDump->append("long"); break;
		case SFSDATATYPE_FLOAT: strDump->append("float"); break;
		case SFSDATATYPE_DOUBLE: strDump->append("double"); break;
		case SFSDATATYPE_UTF_STRING: strDump->append("utf_string"); break;
		case SFSDATATYPE_BOOL_ARRAY: strDump->append("bool_array"); break;
		case SFSDATATYPE_BYTE_ARRAY: strDump->append("byte_array"); break;
		case SFSDATATYPE_SHORT_ARRAY: strDump->append("short_array"); break;
		case SFSDATATYPE_INT_ARRAY: strDump->append("int_array"); break;
		case SFSDATATYPE_LONG_ARRAY: strDump->append("long_array"); break;
		case SFSDATATYPE_FLOAT_ARRAY: strDump->append("float_array"); break;
		case SFSDATATYPE_DOUBLE_ARRAY: strDump->append("double_array"); break;
		case SFSDATATYPE_UTF_STRING_ARRAY: strDump->append("utf_string_array"); break;
		case SFSDATATYPE_SFS_ARRAY: strDump->append("sfs_array"); break;
		case SFSDATATYPE_SFS_OBJECT: strDump->append("sfs_object"); break;
		case SFSDATATYPE_CLASS: strDump->append("class"); break;
		}

		strDump->append(")");

		strDump->append(" ");
		strDump->append(key);
		strDump->append(": ");

		switch (type)
		{
		case SFSDATATYPE_NULL: break;
		case SFSDATATYPE_BOOL: 
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<bool> (temporaryString, format, *((bool*)(wrapper->Data().get())));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_BYTE:
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<unsigned char> (temporaryString, format, *((unsigned char*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_SHORT: 
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<short int> (temporaryString, format, *((short int*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_INT: 
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long int> (temporaryString, format, *((long int*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_LONG: 
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long long> (temporaryString, format, *((long long*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_FLOAT: 
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<float> (temporaryString, format, *((float*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_DOUBLE:
			{
				boost::shared_ptr<string> temporaryString (new string());
		
				boost::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<double> (temporaryString, format, *((double*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_UTF_STRING: 
			{
				strDump->append("[");
				strDump->append(*((string*)wrapper->Data().get()));
				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BOOL_ARRAY: 
			{
				strDump->append("[");

				vector<boost::shared_ptr<bool> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<bool> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<bool> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<bool> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BYTE_ARRAY: 
			{
				strDump->append("[");

				vector<boost::shared_ptr<unsigned char> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<unsigned char> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<unsigned char> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<unsigned char> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SHORT_ARRAY:
			{
				strDump->append("[");

				vector<boost::shared_ptr<short int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<short int> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<short int> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<short int> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_INT_ARRAY:
			{
				strDump->append("[");

				vector<boost::shared_ptr<long int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<long int> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<long int> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long int> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_LONG_ARRAY: 
			{
				strDump->append("[");

				vector<boost::shared_ptr<long long> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<long long> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<long long> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long long> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_FLOAT_ARRAY: 
			{
				strDump->append("[");

				vector<boost::shared_ptr<float> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<float> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<float> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<float> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_DOUBLE_ARRAY:
			{
				strDump->append("[");

				vector<boost::shared_ptr<double> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<double> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<double> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<double> (temporaryString, format, *((*iteratorWrapperData).get()));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_UTF_STRING_ARRAY: 
			{
				strDump->append("[");

				vector<boost::shared_ptr<string> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<boost::shared_ptr<string> >*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<boost::shared_ptr<string> >*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
		
					boost::shared_ptr<string> format (new string("[%s]"));
					StringFormatter<const char*> (temporaryString, format, ((*iteratorWrapperData).get())->c_str());

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SFS_ARRAY: strDump->append(*(((SFSArray*)wrapper->Data().get())->GetDump(false))); break;
		case SFSDATATYPE_SFS_OBJECT: strDump->append(*(((SFSObject*)wrapper->Data().get())->GetDump(false))); break;
		case SFSDATATYPE_CLASS:  break;
		}

		strDump->append(1, DefaultObjectDumpFormatter::TOKEN_DIVIDER);
	}

	// We do this only if the object is not empty
	if (Size() > 0) 
	{
		strDump = boost::shared_ptr<string>(new string(strDump->substr(0, strDump->size() - 1)));
	}

	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE);

	return strDump;
}

// Type getters
// Raw

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper> SFSObject::GetData(string key) 
{
	return dataHolder->at(key);
}

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper> SFSObject::GetData(boost::shared_ptr<string> key) 
{
	return GetData(*key);
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSObject::GetBool(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<bool>();
	}

	return (boost::static_pointer_cast<bool>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSObject::GetBool(boost::shared_ptr<string> key) 
{
	return GetBool(*key);
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
boost::shared_ptr<unsigned char> SFSObject::GetByte(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<unsigned char>();
	}

	return (boost::static_pointer_cast<unsigned char>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
boost::shared_ptr<unsigned char> SFSObject::GetByte(boost::shared_ptr<string> key) 
{
	return GetByte(*key);
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
boost::shared_ptr<short int> SFSObject::GetShort(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<short int>();
	}

	return (boost::static_pointer_cast<short int>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
boost::shared_ptr<short int> SFSObject::GetShort(boost::shared_ptr<string> key) 
{
	return GetShort(*key);
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSObject::GetInt(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<long int>();
	}

	return (boost::static_pointer_cast<long int>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSObject::GetInt(boost::shared_ptr<string> key) 
{
	return GetInt(*key);
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
boost::shared_ptr<long long> SFSObject::GetLong(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<long long>();
	}

	return (boost::static_pointer_cast<long long>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
boost::shared_ptr<long long> SFSObject::GetLong(boost::shared_ptr<string> key) 
{
	return GetLong(*key);
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
boost::shared_ptr<float> SFSObject::GetFloat(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<float>();
	}

	return (boost::static_pointer_cast<float>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
boost::shared_ptr<float> SFSObject::GetFloat(boost::shared_ptr<string> key) 
{
	return GetFloat(*key);
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSObject::GetDouble(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<double>();
	}

	return (boost::static_pointer_cast<double>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSObject::GetDouble(boost::shared_ptr<string> key) 
{
	return GetDouble(*key);
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::GetUtfString(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<string>();
	}

	return (boost::static_pointer_cast<string>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::GetUtfString(boost::shared_ptr<string> key) 
{
	return GetUtfString(*key);
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<unsigned char> > SFSObject::GetArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<unsigned char> >();
	}

	return (boost::static_pointer_cast<vector<unsigned char> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<unsigned char> > SFSObject::GetArray(boost::shared_ptr<string> key) 
{
	return GetArray(*key);
}

// Arrays

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<bool> > SFSObject::GetBoolArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<bool> >();
	}

	return (boost::static_pointer_cast<vector<bool> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<bool> > SFSObject::GetBoolArray(boost::shared_ptr<string> key) 
{
	return GetBoolArray(*key);
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSObject::GetByteArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<ByteArray>();
	}

	return (boost::static_pointer_cast<ByteArray>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSObject::GetByteArray(boost::shared_ptr<string> key) 
{
	return GetByteArray(*key);
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<short int> > SFSObject::GetShortArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<short int> >();
	}

	return (boost::static_pointer_cast<vector<short int> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<short int> > SFSObject::GetShortArray(boost::shared_ptr<string> key) 
{
	return GetShortArray(*key);
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<long int> > SFSObject::GetIntArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<long int> >();
	}
	
	return (boost::static_pointer_cast<vector<long int> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<long int> > SFSObject::GetIntArray(boost::shared_ptr<string> key) 
{
	return GetIntArray(*key);
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<long long> > SFSObject::GetLongArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<long long> >();
	}

	return (boost::static_pointer_cast<vector<long long> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<long long> > SFSObject::GetLongArray(boost::shared_ptr<string> key) 
{
	return GetLongArray(*key);
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<float> > SFSObject::GetFloatArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<float> >();
	}

	return (boost::static_pointer_cast<vector<float> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<float> > SFSObject::GetFloatArray(boost::shared_ptr<string> key) 
{
	return GetFloatArray(*key);
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<double> > SFSObject::GetDoubleArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<double> >();
	}

	return (boost::static_pointer_cast<vector<double> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<double> > SFSObject::GetDoubleArray(boost::shared_ptr<string> key) 
{
	return GetDoubleArray(*key);
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<string> > SFSObject::GetUtfStringArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<vector<string> >();
	}

	return (boost::static_pointer_cast<vector<string> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
boost::shared_ptr<vector<string> > SFSObject::GetUtfStringArray(boost::shared_ptr<string> key) 
{
	return GetUtfStringArray(*key);
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSObject::GetSFSArray(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<ISFSArray>();
	}

	return (boost::static_pointer_cast<ISFSArray>)((*iterator).second->Data());
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSObject::GetSFSArray(boost::shared_ptr<string> key) 
{
	return GetSFSArray(*key);
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSObject::GetSFSObject(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<ISFSObject>();
	}

	return (boost::static_pointer_cast<ISFSObject>)((*iterator).second->Data());
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSObject::GetSFSObject(boost::shared_ptr<string> key) 
{
	return GetSFSObject(*key);
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(string key)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_NULL, boost::shared_ptr<void>()));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(boost::shared_ptr<string> key)
{
	PutNull(*key);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(string key, boost::shared_ptr<bool> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BOOL, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(boost::shared_ptr<string> key, boost::shared_ptr<bool> val)
{
	PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(string key, bool val)
{
	boost::shared_ptr<bool> value (new bool());
	*value = val;
	PutBool(key, value);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(boost::shared_ptr<string> key, bool val)
{
	PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(string key, boost::shared_ptr<unsigned char> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BYTE, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(boost::shared_ptr<string> key, boost::shared_ptr<unsigned char> val)
{
	PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(string key, unsigned char val)
{
	boost::shared_ptr<unsigned char> value (new unsigned char());
	*value = val;
	PutByte(key, value);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(boost::shared_ptr<string> key, unsigned char val)
{
	PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(string key, boost::shared_ptr<short int> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SHORT, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(boost::shared_ptr<string> key, boost::shared_ptr<short int> val)
{
	PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(string key, short int val)
{
	boost::shared_ptr<short int> value (new short int());
	*value = val;
	PutShort(key, value);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(boost::shared_ptr<string> key, short int val)
{
	PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(string key, boost::shared_ptr<long int> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_INT, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(boost::shared_ptr<string> key, boost::shared_ptr<long int> val)
{
	PutInt(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(string key, long int val)
{
	boost::shared_ptr<long int> value (new long int());
	*value = val;
	PutInt(key, value);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(boost::shared_ptr<string> key, long int val)
{
	PutInt (*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(string key, boost::shared_ptr<long long> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_LONG, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(boost::shared_ptr<string> key, boost::shared_ptr<long long> val)
{
	PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(string key, long long val)
{
	boost::shared_ptr<long long> value (new long long());
	*value = val;
	PutLong(key, value);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(boost::shared_ptr<string> key, long long val)
{
	PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(string key, boost::shared_ptr<float> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_FLOAT, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(boost::shared_ptr<string> key, boost::shared_ptr<float> val)
{
	PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(string key, float val)
{
	boost::shared_ptr<float> value (new float());
	*value = val;
	PutFloat(key, value);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(boost::shared_ptr<string> key, float val)
{
	PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(string key, boost::shared_ptr<double> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_DOUBLE, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(boost::shared_ptr<string> key, boost::shared_ptr<double> val)
{
	PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(string key, double val)
{
	boost::shared_ptr<double> value (new double());
	*value = val;
	PutDouble(key, value);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(boost::shared_ptr<string> key, double val)
{
	PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(string key, boost::shared_ptr<string> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_UTF_STRING, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(boost::shared_ptr<string> key, boost::shared_ptr<string> val)
{
	PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(string key, string val)
{
	boost::shared_ptr<string> value (new string(val));
	PutUtfString(key, value);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(boost::shared_ptr<string> key, string val)
{
	PutUtfString(*key, val);
}

// Arrays

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(string key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BOOL_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<bool> > > val)
{
	PutBoolArray(*key, val);
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(string key, boost::shared_ptr<ByteArray> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BYTE_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(boost::shared_ptr<string> key, boost::shared_ptr<ByteArray> val)
{
	PutByteArray(*key, val);
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(string key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SHORT_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<short int> > > val)
{
	PutShortArray(*key, val);
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_INT_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long int> > > val)
{
	PutIntArray(*key, val);
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(string key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_LONG_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<long long> > > val)
{
	PutLongArray(*key, val);
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(string key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_FLOAT_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<float> > > val)
{
	PutFloatArray(*key, val);
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(string key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_DOUBLE_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<double> > > val)
{
	PutDoubleArray(*key, val);
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(string key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_UTF_STRING_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<boost::shared_ptr<string> > > val)
{
	PutUtfStringArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(string key, boost::shared_ptr<ISFSArray> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SFS_ARRAY, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(boost::shared_ptr<string> key, boost::shared_ptr<ISFSArray> val)
{
	PutSFSArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(string key, boost::shared_ptr<ISFSObject> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SFS_OBJECT, (boost::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(boost::shared_ptr<string> key, boost::shared_ptr<ISFSObject> val)
{
	PutSFSObject(*key, val);
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(string key, boost::shared_ptr<SFSDataWrapper> val)
{
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, val));
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(boost::shared_ptr<string> key, boost::shared_ptr<SFSDataWrapper> val)
{
	Put(*key, val);
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return false;
	}

	return true;
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(boost::shared_ptr<string> key)
{
	return ContainsKey(*key);
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSObject::GetClass(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return boost::shared_ptr<void>();
	}

	return ((*iterator).second)->Data();
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSObject::GetClass(boost::shared_ptr<string> key) 
{
	return GetClass(*key);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::GetDump(bool format)
{
	if (format == false)
	{
		return Dump();
	}

	return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::GetDump()
{
	return GetDump(true);
}

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSObject::GetHexDump()
{
	return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

// -------------------------------------------------------------------
// GetKeys
// -------------------------------------------------------------------
boost::shared_ptr<vector<string> > SFSObject::GetKeys()
{
	boost::shared_ptr<vector<string> > keyList (new vector<string>());

	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		keyList->push_back(iterator->first);
	}

	return keyList;
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return true;
	}

	if (iterator->second == NULL)
	{
		return true;
	}

	return false;
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(boost::shared_ptr<string> key)
{
	return IsNull(*key);
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(string key, boost::shared_ptr<void> val)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_CLASS, val));
	dataHolder->insert(pair<string, boost::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(boost::shared_ptr<string> key, boost::shared_ptr<void> val)
{
	PutClass(*key, val);
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(string key)
{
	map<string, boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator != dataHolder->end())
	{
		dataHolder->erase(iterator);
	}
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(boost::shared_ptr<string> key)
{
	RemoveElement(*key);
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
long int SFSObject::Size()
{
	return dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSObject::ToBinary()
{
	return serializer->Object2Binary(shared_from_this());
}

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

