// ===================================================================
//
// Description		
//		Contains the implementation of SFSArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSArray.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"
#include <typeinfo>

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSArray::SFSArray()
{
	dataHolder = boost::shared_ptr<vector<boost::shared_ptr<SFSDataWrapper> > >(new vector<boost::shared_ptr<SFSDataWrapper> >());
	serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSArray::~SFSArray()
{
	dataHolder->clear();
}

// -------------------------------------------------------------------
// NewFromArray
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray> SFSArray::NewFromArray(vector<boost::shared_ptr<SFSDataWrapper> > o)
{
	return boost::shared_ptr<SFSArray>();
}

// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray> SFSArray::NewFromBinaryData(boost::shared_ptr<ByteArray> ba)
{
	return (boost::static_pointer_cast<SFSArray>)(DefaultSFSDataSerializer::Instance()->Binary2Array(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray> SFSArray::NewInstance()
{
	boost::shared_ptr<SFSArray> returned (new SFSArray());
	return returned;
}

// -------------------------------------------------------------------
// Contains
// -------------------------------------------------------------------
bool SFSArray::Contains(boost::shared_ptr<void> obj)
{

	if ((typeid(obj) == typeid(boost::shared_ptr<ISFSArray>)) || (typeid(obj) == typeid(boost::shared_ptr<ISFSObject>))) 
	{
		boost::shared_ptr<string> message (new string("ISFSArray and ISFSObject are not supported by this method."));
		boost::shared_ptr<SFSError> exception (new SFSError(message));
		throw exception;
	}

	for (int j = 0; j < Size(); j++)	
	{
		boost::shared_ptr<void> wrappedObj = GetElementAt(j);
				
		if (wrappedObj == obj)
		{
			return true;
		}
	}	
			
	return false;
}

// -------------------------------------------------------------------
// GetWrappedElementAt
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper> SFSArray::GetWrappedElementAt(long int index)
{
	return dataHolder->at(index);
}


// -------------------------------------------------------------------
// GetElementAt
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSArray::GetElementAt(long int index)
{
	boost::shared_ptr<void> obj = boost::shared_ptr<void>();
	if (dataHolder->at(index) != NULL) 
	{
		obj = dataHolder->at(index)->Data();
	}
	
	return obj;
}

// -------------------------------------------------------------------
// RemoveElementAt
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSArray::RemoveElementAt(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<void>();
	boost::shared_ptr<SFSDataWrapper> elem = dataHolder->at(index);
	dataHolder->erase (dataHolder->begin() + index);
	return elem->Data();
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
long int SFSArray::Size()
{
	return dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSArray::ToBinary()
{
	return serializer->Array2Binary(shared_from_this());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSArray::GetDump()
{
	return GetDump(true);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSArray::GetDump(bool format)
{
	if (!format) 
	{
		return Dump();
	}		
	else 
	{
		return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
	}
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSArray::Dump()
{
	boost::shared_ptr<string> strDump (new string());
	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);
	boost::shared_ptr<SFSDataWrapper> wrapper;

	long int type;

	vector<boost::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		wrapper = *iterator;
		type = wrapper->Type();

		switch (type)
		{
		case SFSDATATYPE_NULL: 
			{
				strDump->append("(");
				strDump->append("null");
				strDump->append(") ");

				strDump->append("NULL"); 
				break;
			}
		case SFSDATATYPE_BOOL: 
			{
				strDump->append("(");
				strDump->append("bool");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<bool> (temporaryString, format, *((boost::static_pointer_cast<bool>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_BYTE:
			{
				strDump->append("(");
				strDump->append("byte");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<unsigned char> (temporaryString, format, *((boost::static_pointer_cast<unsigned char>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_SHORT: 
			{
				strDump->append("(");
				strDump->append("short");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<short int> (temporaryString, format, *((boost::static_pointer_cast<short int>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_INT: 
			{
				strDump->append("(");
				strDump->append("int");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long int> (temporaryString, format, *((boost::static_pointer_cast<long int>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_LONG: 
			{
				strDump->append("(");
				strDump->append("long");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long long> (temporaryString, format, *((boost::static_pointer_cast<long long>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_FLOAT: 
			{
				strDump->append("(");
				strDump->append("float");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<float> (temporaryString, format, *((boost::static_pointer_cast<float>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_DOUBLE:
			{
				strDump->append("(");
				strDump->append("double");
				strDump->append(") ");

				boost::shared_ptr<string> temporaryString (new string());
				boost::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<double> (temporaryString, format, *((boost::static_pointer_cast<double>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_UTF_STRING: 
			{
				strDump->append("(");
				strDump->append("utf_string");
				strDump->append(") ");

				strDump->append("[");
				strDump->append(*((boost::static_pointer_cast<string>)(wrapper->Data()).get()));
				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BOOL_ARRAY: 
			{
				strDump->append("(");
				strDump->append("bool_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<bool> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<bool> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<bool> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<bool> (temporaryString, format, *((boost::static_pointer_cast<bool>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BYTE_ARRAY: 
			{
				strDump->append("(");
				strDump->append("byte_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<unsigned char> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<unsigned char> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<unsigned char> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<unsigned char> (temporaryString, format, *((boost::static_pointer_cast<unsigned char>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SHORT_ARRAY:
			{
				strDump->append("(");
				strDump->append("short_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<short int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<short int> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<short int> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<short int> (temporaryString, format, *((boost::static_pointer_cast<short int>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_INT_ARRAY:
			{
				strDump->append("(");
				strDump->append("int_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<long int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<long int> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<long int> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long int> (temporaryString, format, *((boost::static_pointer_cast<long int>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_LONG_ARRAY: 
			{
				strDump->append("(");
				strDump->append("long_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<long long> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<long long> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<long long> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long long> (temporaryString, format, *((boost::static_pointer_cast<long long>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_FLOAT_ARRAY: 
			{
				strDump->append("(");
				strDump->append("float_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<float> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<float> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<float> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<float> (temporaryString, format, *((boost::static_pointer_cast<float>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_DOUBLE_ARRAY:
			{
				strDump->append("(");
				strDump->append("double_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<double> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<double> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<double> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<double> (temporaryString, format, *((boost::static_pointer_cast<double>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_UTF_STRING_ARRAY: 
			{
				strDump->append("(");
				strDump->append("utf_string_array");
				strDump->append(") ");

				strDump->append("[");

				vector<boost::shared_ptr<string> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((boost::static_pointer_cast<vector<boost::shared_ptr<string> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((boost::static_pointer_cast<vector<boost::shared_ptr<string> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					boost::shared_ptr<string> temporaryString (new string());
					boost::shared_ptr<string> format (new string("[%s]"));
					StringFormatter<const char*> (temporaryString, format, ((boost::static_pointer_cast<string>)(*iteratorWrapperData))->c_str());

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SFS_ARRAY: 
			{
				strDump->append("(");
				strDump->append("sfs_array");
				strDump->append(") ");

				strDump->append(*(((boost::static_pointer_cast<SFSArray>)(wrapper->Data()))->GetDump(false))); 
				break;
			}
		case SFSDATATYPE_SFS_OBJECT: 
			{
				strDump->append("(");
				strDump->append("sfs_object");
				strDump->append(") ");

				strDump->append(*(((boost::static_pointer_cast<SFSObject>)(wrapper->Data()))->GetDump(false))); 
				break;
			}
		case SFSDATATYPE_CLASS:  
			{
				strDump->append("(");
				strDump->append("class");
				strDump->append(") ");

				break;
			}
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

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSArray::GetHexDump()
{
	return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

/*
* :::::::::::::::::::::::::::::::::::::::::
* Type setters
* :::::::::::::::::::::::::::::::::::::::::	
*/

void SFSArray::AddNull()
{
	AddObject(boost::shared_ptr<void>(), SFSDATATYPE_NULL);
}

void SFSArray::AddBool(boost::shared_ptr<bool> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_BOOL);
}

void SFSArray::AddBool(bool val)
{
	boost::shared_ptr<bool> value (new bool());
	*value = val;
	AddBool(value);
}

void SFSArray::AddByte(boost::shared_ptr<unsigned char> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_BYTE);
}

void SFSArray::AddByte(unsigned char val)
{
	boost::shared_ptr<unsigned char> value (new unsigned char());
	*value = val;
	AddByte(value);
}

void SFSArray::AddShort(boost::shared_ptr<short int> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_SHORT);
}

void SFSArray::AddShort(short int val)
{
	boost::shared_ptr<short int> value (new short int());
	*value = val;
	AddShort(value);
}

void SFSArray::AddInt(boost::shared_ptr<long int> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_INT);
}

void SFSArray::AddInt(long int val)
{
	boost::shared_ptr<long int> value (new long int());
	*value = val;
	AddInt(value);
}

void SFSArray::AddLong(boost::shared_ptr<long long> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_LONG);
}

void SFSArray::AddLong(long long val)
{
	boost::shared_ptr<long long> value (new long long());
	*value = val;
	AddLong(value);
}

void SFSArray::AddFloat(boost::shared_ptr<float> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_FLOAT);
}

void SFSArray::AddFloat(float val)
{
	boost::shared_ptr<float> value (new float());
	*value = val;
	AddFloat(value);
}

void SFSArray::AddDouble(boost::shared_ptr<double> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_DOUBLE);
}

void SFSArray::AddDouble(double val)
{
	boost::shared_ptr<double> value (new double());
	*value = val;
	AddDouble(value);
}

void SFSArray::AddUtfString(boost::shared_ptr<string> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_UTF_STRING);
}

void SFSArray::AddUtfString(string val)
{
	boost::shared_ptr<string> value (new string(val));
	AddUtfString(value);
}

void SFSArray::AddBoolArray(boost::shared_ptr<vector<boost::shared_ptr<bool> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_BOOL_ARRAY);
}

void SFSArray::AddByteArray(boost::shared_ptr<ByteArray> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_BYTE_ARRAY);
}

void SFSArray::AddShortArray(boost::shared_ptr<vector<boost::shared_ptr<short int> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_SHORT_ARRAY);
}

void SFSArray::AddIntArray(boost::shared_ptr<vector<boost::shared_ptr<long int> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_INT_ARRAY);
}

void SFSArray::AddLongArray(boost::shared_ptr<vector<boost::shared_ptr<long long> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_LONG_ARRAY);
}
 
void SFSArray::AddFloatArray(boost::shared_ptr<vector<boost::shared_ptr<float> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_FLOAT_ARRAY);
}

void SFSArray::AddDoubleArray(boost::shared_ptr<vector<boost::shared_ptr<double> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_DOUBLE_ARRAY);
}

void SFSArray::AddUtfStringArray(boost::shared_ptr<vector<boost::shared_ptr<string> > > val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_UTF_STRING_ARRAY);
}

void SFSArray::AddSFSArray(boost::shared_ptr<ISFSArray> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_SFS_ARRAY);
}
		 
void SFSArray::AddSFSObject(boost::shared_ptr<ISFSObject> val)
{
	AddObject((boost::static_pointer_cast<void>)(val), SFSDATATYPE_SFS_OBJECT);
}

void SFSArray::AddClass(boost::shared_ptr<void> val)
{
	AddObject(val, SFSDATATYPE_CLASS);
}

void SFSArray::Add(boost::shared_ptr<SFSDataWrapper> wrappedObject)
{
	dataHolder->push_back(wrappedObject);
}

void SFSArray::AddObject(boost::shared_ptr<void> val, SFSDataType tp)
{
	boost::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper((long int)tp, val));
	dataHolder->push_back(wrapper);
}

/*
* :::::::::::::::::::::::::::::::::::::::::
* Type getters
* :::::::::::::::::::::::::::::::::::::::::	
*/
bool SFSArray::IsNull(unsigned long int index)
{
	if (index >= dataHolder->size()) return true;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (wrapper->Type() == (long int)SFSDATATYPE_NULL);
}

bool SFSArray::GetBool(unsigned long int index)
{
	if (index >= dataHolder->size()) return false;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (bool)(*((boost::static_pointer_cast<bool>)(wrapper->Data())));
}

unsigned char SFSArray::GetByte(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (unsigned char)(*((boost::static_pointer_cast<unsigned char>)(wrapper->Data())));
}

short int SFSArray::GetShort(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (short int)(*((boost::static_pointer_cast<short int>)(wrapper->Data())));
}

long int SFSArray::GetInt(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (long int)(*((boost::static_pointer_cast<long int>)(wrapper->Data())));
}

long long SFSArray::GetLong(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (long long)(*((boost::static_pointer_cast<long long>)(wrapper->Data())));
}

float SFSArray::GetFloat(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (float)(*((boost::static_pointer_cast<float>)(wrapper->Data())));
}

double SFSArray::GetDouble(unsigned long int index)
{
	if (index >= dataHolder->size()) return 0;
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (double)(*((boost::static_pointer_cast<double>)(wrapper->Data())));
}

boost::shared_ptr<string> SFSArray::GetUtfString(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<string>(new string());
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<string>)(wrapper->Data());
}

boost::shared_ptr<vector<boost::shared_ptr<void> > > SFSArray::GetArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<boost::shared_ptr<void> > >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<boost::shared_ptr<void> > >)(wrapper->Data());
}

boost::shared_ptr<vector<bool> > SFSArray::GetBoolArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<bool> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<bool> >)(wrapper->Data());
}

boost::shared_ptr<ByteArray> SFSArray::GetByteArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<ByteArray>();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<ByteArray>)(wrapper->Data());
}

boost::shared_ptr<vector<short int> > SFSArray::GetShortArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<short int> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<short int> >)(wrapper->Data());
}

boost::shared_ptr<vector<long int> > SFSArray::GetIntArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<long int> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<long int> >)(wrapper->Data());
}

boost::shared_ptr<vector<long long> > SFSArray::GetLongArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<long long> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<long long> >)(wrapper->Data());
}

boost::shared_ptr<vector<float> > SFSArray::GetFloatArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<float> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<float> >)(wrapper->Data());
}

boost::shared_ptr<vector<double> > SFSArray::GetDoubleArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<double> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<double> >)(wrapper->Data());
}

boost::shared_ptr<vector<string> > SFSArray::GetUtfStringArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<vector<string> >();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<vector<string> >)(wrapper->Data());
}

boost::shared_ptr<ISFSArray> SFSArray::GetSFSArray(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<ISFSArray>();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<ISFSArray>)(wrapper->Data());
}

boost::shared_ptr<void> SFSArray::GetClass(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<void>();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<void>)(wrapper->Data());
}

boost::shared_ptr<ISFSObject> SFSArray::GetSFSObject(unsigned long int index)
{
	if (index >= dataHolder->size()) return boost::shared_ptr<ISFSObject>();
	boost::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (boost::static_pointer_cast<ISFSObject>)(wrapper->Data());
}



}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

