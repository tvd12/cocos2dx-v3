// ===================================================================
//
// Description		
//		Contains the implementation of ByteArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// =================================================================== 
#if defined(_MSC_VER)
#pragma warning(disable:4996)			// disable warning 4996
#endif

#include "ByteArray.h"
#include <bitset>  

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray()
{
	buffer = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	position = 0;
	compressed = false;
	zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray(boost::shared_ptr<vector<unsigned char> > buf)
{
	buffer = buf;
	position = 0;
	compressed = false;
	zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ByteArray::~ByteArray()
{
}

// -------------------------------------------------------------------
// IsLittleEndian
// -------------------------------------------------------------------
bool ByteArray::IsLittleEndian()
{
    short int number = 0x1;
    char *numPtr = (char*)&number;
    return (numPtr[0] == 1);
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
boost::shared_ptr<vector<unsigned char> > ByteArray::Bytes()
{
	return buffer;
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
void ByteArray::Bytes(boost::shared_ptr<vector<unsigned char> > value)
{
	buffer = value;
	compressed = false;
}

// -------------------------------------------------------------------
// Length
// -------------------------------------------------------------------
long int ByteArray::Length()
{
	return buffer->size();
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
long int ByteArray::Position()
{
	return position;
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
void ByteArray::Position(long int value)
{
	position = value;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
long int ByteArray::BytesAvailable()
{
	long int val = buffer->size() - position;
	if (((unsigned long int)val) > buffer->size() || val < 0) val = 0;
	return val;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
bool ByteArray::Compressed()
{
	return compressed;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
void ByteArray::Compressed(bool value)
{
	compressed = value;
}

// -------------------------------------------------------------------
// Compress
// -------------------------------------------------------------------
void ByteArray::Compress()
{
	if (compressed) {
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Buffer is already compressed"))); 
	}

	// Destination buffer must be at least 0.1% larger than sourceLen plus 12 bytes
	// We set destination buffer length to 1% of source + 12 bytes
	unsigned long sizeCompressed = buffer->size() + (buffer->size() / 100) + 12;
	boost::shared_ptr<unsigned char> dataCompressed (new unsigned char[sizeCompressed]);
	memset (dataCompressed.get(), 0x00, sizeCompressed);

	boost::shared_ptr<unsigned char> dataToCompress (new unsigned char[buffer->size()]);
	memset (dataToCompress.get(), 0x00, buffer->size());

	std::copy(buffer->begin(), buffer->end(), dataToCompress.get());

	compress(dataCompressed.get(), &sizeCompressed, dataToCompress.get(), buffer->size());

	buffer->clear();
	buffer->insert(buffer->end(), &dataCompressed.get()[0], &dataCompressed.get()[sizeCompressed]);

	this->position = 0;
	this->compressed = true;
}

// -------------------------------------------------------------------
// Uncompress
// -------------------------------------------------------------------
void ByteArray::Uncompress()
{
	// We set destination buffer length as double of source
	unsigned long sizeAreaUncompressed = buffer->size() * 2;
	unsigned long sizeUncompressed = 0;
	boost::shared_ptr<unsigned char> dataUncompressed;

	boost::shared_ptr<unsigned char> dataToUncompress = boost::shared_ptr<unsigned char>(new unsigned char[buffer->size()]);
	memset (dataToUncompress.get(), 0x00, buffer->size());

	std::copy(buffer->begin(), buffer->end(), dataToUncompress.get());

	// Loop up to destination buffer is large enough to hold the entire uncompressed data
	do 
	{
		dataUncompressed = boost::shared_ptr<unsigned char>(new unsigned char[sizeAreaUncompressed]);
		memset (dataUncompressed.get(), 0x00, sizeAreaUncompressed);

		sizeUncompressed = sizeAreaUncompressed;
		long int result = uncompress(dataUncompressed.get(), &sizeUncompressed, dataToUncompress.get(), buffer->size());

		if (result == Z_BUF_ERROR) 
		{
			sizeAreaUncompressed += buffer->size();
			continue;
		}

		break;

	} while (true);

	buffer->clear();
	buffer->insert(buffer->end(), &dataUncompressed.get()[0], &dataUncompressed.get()[sizeUncompressed]);

	this->position = 0;
	this->compressed = false;
}

// -------------------------------------------------------------------
// CheckCompressedWrite
// -------------------------------------------------------------------
void ByteArray::CheckCompressedWrite()
{
	if (compressed) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Only raw bytes can be written a compressed array. Call Uncompress first."))); 
	}
}

// -------------------------------------------------------------------
// CheckCompressedRead
// -------------------------------------------------------------------
void ByteArray::CheckCompressedRead()
{
	if (compressed) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("Only raw bytes can be read from a compressed array."))); 
	}
}

// -------------------------------------------------------------------
// ReverseOrder
// -------------------------------------------------------------------
void ByteArray::ReverseOrder(vector<unsigned char>& dt)
{
	// if BitCOnverter becomes BigEndian in future MONO/.NET implementations, use this to work correctly
	if (!IsLittleEndian()) return;

	std::reverse(dt.begin(), dt.end());
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(boost::shared_ptr<SFSDataType> tp)
{
	WriteByte((unsigned char)((int)(*tp)));
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(unsigned char b)
{
	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(b);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(boost::shared_ptr<vector<unsigned char> > data)
{
	WriteBytes(data, 0, data->size());
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(boost::shared_ptr<vector<unsigned char> > data, long int ofs, long int count)
{
	buffer->insert(buffer->end(), data->begin() + ofs, data->begin() + ofs + count);
}

// -------------------------------------------------------------------
// WriteBool
// -------------------------------------------------------------------
void ByteArray::WriteBool(bool b)
{
	CheckCompressedWrite();

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(b ? (unsigned char)1 : (unsigned char)0);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteInt
// -------------------------------------------------------------------
void ByteArray::WriteInt(long int i)
{
	CheckCompressedWrite();

	unsigned char bytes[4];

	bytes[0] = (i >> 24) & 0xFF;
	bytes[1] = (i >> 16) & 0xFF;
	bytes[2] = (i >> 8) & 0xFF;
	bytes[3] = i & 0xFF;

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUShort
// -------------------------------------------------------------------
void ByteArray::WriteUShort(unsigned short int us)
{
	CheckCompressedWrite();

	unsigned char bytes[2];

	bytes[0] = (us >> 8) & 0xFF;
	bytes[1] = us & 0xFF;

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteShort
// -------------------------------------------------------------------
void ByteArray::WriteShort(short int s)
{
	CheckCompressedWrite();

	unsigned char bytes[2];

	bytes[0] = (s >> 8) & 0xFF;
	bytes[1] = s & 0xFF;

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteLong
// -------------------------------------------------------------------
void ByteArray::WriteLong(long long l)
{
	CheckCompressedWrite();

	unsigned char bytes[8];

	bytes[0] = (l >> 56) & 0xFF;
	bytes[1] = (l >> 48) & 0xFF;
	bytes[2] = (l >> 40) & 0xFF;
	bytes[3] = (l >> 32) & 0xFF;
	bytes[4] = (l >> 24) & 0xFF;
	bytes[5] = (l >> 16) & 0xFF;
	bytes[6] = (l >> 8) & 0xFF;
	bytes[7] = l & 0xFF;

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	buf->push_back(bytes[4]);
	buf->push_back(bytes[5]);
	buf->push_back(bytes[6]);
	buf->push_back(bytes[7]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteFloat
// -------------------------------------------------------------------
void ByteArray::WriteFloat(float f)
{
	CheckCompressedWrite();

	unsigned char bytes[4];

	union  
    {  
         float input;   
         long int output;  
    }    data;  
  
    data.input = f;  
  
    std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);  

	bytes[0] = ((long int)data.output >> 24) & 0xFF;
	bytes[1] = ((long int)data.output >> 16) & 0xFF;
	bytes[2] = ((long int)data.output >> 8) & 0xFF;
	bytes[3] = (long int)data.output & 0xFF;
  
	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteDouble
// -------------------------------------------------------------------
void ByteArray::WriteDouble(double d)
{
	CheckCompressedWrite();

	unsigned char bytes[8];

	union  
    {  
         double input;   
         unsigned long long output;  
    }    data;  
  
    data.input = d;  
  
    std::bitset<sizeof(double) * CHAR_BIT> bits(data.output);  

	bytes[0] = ((unsigned long long)data.output >> 56) & 0xFF;
	bytes[1] = ((unsigned long long)data.output >> 48) & 0xFF;
	bytes[2] = ((unsigned long long)data.output >> 40) & 0xFF;
	bytes[3] = ((unsigned long long)data.output >> 32) & 0xFF;
	bytes[4] = ((unsigned long long)data.output >> 24) & 0xFF;
	bytes[5] = ((unsigned long long)data.output >> 16) & 0xFF;
	bytes[6] = ((unsigned long long)data.output >> 8) & 0xFF;
	bytes[7] = (unsigned long long)data.output & 0xFF;

	boost::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	buf->push_back(bytes[4]);
	buf->push_back(bytes[5]);
	buf->push_back(bytes[6]);
	buf->push_back(bytes[7]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUTF
// -------------------------------------------------------------------
void ByteArray::WriteUTF(string str)
{
	boost::shared_ptr<string> value (new string(str));
	WriteUTF(value);
}

void ByteArray::WriteUTF(boost::shared_ptr<string> str)
{
	CheckCompressedWrite();
	
	// Incoming string must be encoded as UTF8 by API user
	// No additional conversion to UTF8 is required 
	/*
	unsigned long int utfLen = 0;
	for (unsigned long int i = 0; i < str->size(); i++) 
	{
		unsigned long int c = (*str)[i];
        if ((c >= (unsigned long int)0x0001) && (c <= (unsigned long int)0x007F)) 
		{
			utfLen++;
        }
        else if (c > (unsigned long int)0x07FF) 
		{
			utfLen += 3;
        }
        else 
		{
			utfLen += 2;
        }
	}
			
	if (utfLen > 32768) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("String length cannot be greater then 32768 !"))); 
	}
	
	WriteUShort((unsigned short int)(utfLen));

	boost::shared_ptr<wstring> src (new wstring());
	src->assign(str->begin(), str->end());

	boost::shared_ptr<string> dest (new string());
	WStrToUtf8(src, dest);

	vector<unsigned char>utfBuffer;

	const char* utfStringArray = dest->c_str();
	for (unsigned long int enumerator = 0; enumerator < dest->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(utfBuffer));
	WriteBytes(data);
	*/

	if (str->size() > 32768) 
	{
		boost::throw_exception(boost::enable_error_info (std::runtime_error("String length cannot be greater then 32768 !"))); 
	}
	
	WriteUShort((unsigned short int)(str->size()));

	vector<unsigned char>utfBuffer;

	const char* utfStringArray = str->c_str();
	for (unsigned long int enumerator = 0; enumerator < str->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	boost::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(utfBuffer));
	WriteBytes(data);

}

// -------------------------------------------------------------------
// ReadByte
// -------------------------------------------------------------------
void ByteArray::ReadByte(unsigned char& returnedValue)
{
	CheckCompressedRead();
			
	returnedValue = buffer->at(position++);

	return;
}

// -------------------------------------------------------------------
// ReadBytes
// -------------------------------------------------------------------
void ByteArray::ReadBytes(long int count, vector<unsigned char>& returnedValue)
{
	for (long int enumerator = 0; enumerator < count; enumerator++)
	{
		returnedValue.push_back(buffer->at(position + enumerator));
	}

	position += count;
	
	return;
}

// -------------------------------------------------------------------
// ReadBool
// -------------------------------------------------------------------
void ByteArray::ReadBool(bool& returnedValue)
{
	CheckCompressedRead();
	returnedValue = buffer->at(position++) == 1;
	return;
}

// -------------------------------------------------------------------
// ReadInt
// -------------------------------------------------------------------
void ByteArray::ReadInt(long int& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(4, data);

	returnedValue = (((long int)data.at(0)) << 24) |
				    (((long int)data.at(1) << 16)) |
				    (((long int)data.at(2) << 8)) |
				    (((long int)data.at(3)));
			
	return;
}

// -------------------------------------------------------------------
// ReadUShort
// -------------------------------------------------------------------
void ByteArray::ReadUShort(unsigned short int& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(2, data);

	returnedValue = (((unsigned short int)data.at(0) << 8)) |
				    (((unsigned short int)data.at(1)));
			
	return;
}

// -------------------------------------------------------------------
// ReadShort
// -------------------------------------------------------------------
void ByteArray::ReadShort(short int& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(2, data);

	returnedValue = (((short int)data.at(0) << 8)) |
				    (((short int)data.at(1)));
			
	return;
}

// -------------------------------------------------------------------
// ReadLong
// -------------------------------------------------------------------
void ByteArray::ReadLong(long long& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(8, data);

	returnedValue = (((unsigned long long)data.at(0)) << 56) |
				    (((unsigned long long)data.at(1)) << 48) |
				    (((unsigned long long)data.at(2)) << 40) |
				    (((unsigned long long)data.at(3)) << 32) |
				    (((unsigned long long)data.at(4)) << 24) |
				    (((unsigned long long)data.at(5)) << 16) |
				    (((unsigned long long)data.at(6)) << 8) |
				    (((unsigned long long)data.at(7)));
			
	return;
}

// -------------------------------------------------------------------
// ReadFloat
// -------------------------------------------------------------------
void ByteArray::ReadFloat(float& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(4, data);

	long int readNumber = ((((long int)data.at(0)) << 24) |
					       (((long int)data.at(1)) << 16) |
					       (((long int)data.at(2)) << 8) |
					       (((long int)data.at(3))));
		
//    std::bitset<32> set(readNumber);        
//    long int hexNumber = set.to_ulong();  
  
//    bool negative = !!(hexNumber & 0x80000000);  
//    long int exponent = (hexNumber & 0x7f800000) >> 23;      
    bool negative = !!(readNumber & 0x80000000);  
    long int exponent = (readNumber & 0x7f800000) >> 23;      
    long int sign = negative ? -1 : 1;  
  
    // Subtract 127 from the exponent  
    exponent -= 127;  
  
    // Convert the mantissa into decimal using the last 23 bits  
    long int power = -1;  
    float total = 0.0;  
    for (int i = 0; i < 23; i++)  
    {  
        long int c = (readNumber & (0x80000000 >> (9 + i))) != 0 ? 1 : 0;  
        total += (float)c * (float)pow(2.0f, (float)power);
        power--;  
    }  
    total += 1.0;  
  
    returnedValue = sign * (float)pow(2.0f, (float)exponent) * total;

	return;
}

// -------------------------------------------------------------------
// ReadDouble
// -------------------------------------------------------------------
void ByteArray::ReadDouble(double& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(8, data);

	unsigned long long readNumber = ((((unsigned long long)data.at(0)) << 56) |
									(((unsigned long long)data.at(1)) << 48) |
									(((unsigned long long)data.at(2)) << 40) |
									(((unsigned long long)data.at(3)) << 32) |
									(((unsigned long long)data.at(4)) << 24) |
									(((unsigned long long)data.at(5)) << 16) |
									(((unsigned long long)data.at(6)) << 8) |
									(((unsigned long long)data.at(7))));
		
//    std::bitset<64> set(readNumber);        
//    unsigned long long hexNumber = set.to_ullong();  
  
//    bool negative = !!(hexNumber & 0x8000000000000000);  
//    long int exponent = (hexNumber & 0x7ff0000000000000) >> 52;      
    bool negative = !!(readNumber & 0x8000000000000000);  
    long int exponent = (readNumber & 0x7ff0000000000000) >> 52;      
    long int sign = negative ? -1 : 1;  
  
    // Subtract 1023 from the exponent  
    exponent -= 1023;  
  
    // Convert the mantissa into decimal using the last 52 bits  
    long int power = -1;  
    double total = 0.0;  
    for (int i = 0; i < 52; i++)  
    {  
        long int c = (readNumber & (0x8000000000000000 >> (12 + i))) != 0 ? 1 : 0;  
        total += (double)c * (double)pow(2.0f, (float)power);
        power--;  
    }  
    total += 1.0;  
  
    returnedValue = sign * (double)pow(2.0f, (float)exponent) * total;

	return;
}

// -------------------------------------------------------------------
// ReadUTF
// -------------------------------------------------------------------
void ByteArray::ReadUTF(string& returnedValue)
{
	CheckCompressedRead();

	// Incoming string must be encoded as UTF8 by API user
	// No additional conversion to UTF8 is required 
	/*
	unsigned short int size;
	ReadUShort(size);

	boost::shared_ptr<string> src (new string());

	for (long int enumerator = 0; enumerator < size; enumerator++)
	{
		src->push_back(buffer->at(position + enumerator));
	}

	boost::shared_ptr<wstring> dest (new wstring());
	Utf8toWStr(src, dest);

	returnedValue.assign(dest->begin(), dest->end()); 
	position += size;
	*/
	unsigned short int size;
	ReadUShort(size);

	boost::shared_ptr<string> src (new string());

	for (long int enumerator = 0; enumerator < size; enumerator++)
	{
		src->push_back(buffer->at(position + enumerator));
	}

	returnedValue.assign(src->begin(), src->end()); 
	position += size;

	return;
}

}	// namespace Util
}	// namespace Sfs2X
