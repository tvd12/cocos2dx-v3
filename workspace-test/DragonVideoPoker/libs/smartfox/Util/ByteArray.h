// ===================================================================
//
// Description		
//		Contains the definition of ByteArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ByteArray__
#define __ByteArray__

#include "./Common.h"
#include "./StringFormatter.h"

#include "../Entities/Data/SFSDataType.h"
#include "../ZLib/zlib.h"
#include <boost/container/string.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

#define ZlibChunk 1024			// Chunk size (bytes) for Zlib buffers

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class ByteArray
	// -------------------------------------------------------------------
	class DLLImportExport ByteArray
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		ByteArray();
		ByteArray(boost::shared_ptr<vector<unsigned char> > buf);
		~ByteArray();

		boost::shared_ptr<vector<unsigned char> > Bytes();
		void Bytes(boost::shared_ptr<vector<unsigned char> > value);

		long int Length();
		long int Position();
		void Position(long int value);

		long int BytesAvailable();

		bool Compressed();
		void Compressed(bool value);

		void Compress();
		void Uncompress();
		void CheckCompressedWrite();
		void CheckCompressedRead();

		void ReverseOrder(vector<unsigned char>& dt);

		void WriteByte(boost::shared_ptr<SFSDataType> tp);
		void WriteByte(unsigned char b);
		void WriteBytes(boost::shared_ptr<vector<unsigned char> > data);
		void WriteBytes(boost::shared_ptr<vector<unsigned char> > data, long int ofs, long int count);
		void WriteBool(bool b);
		void WriteInt(long int i);
		void WriteUShort(unsigned short int us);
		void WriteShort(short int s);
		void WriteLong(long long l);
		void WriteFloat(float f);
		void WriteDouble(double d);
		void WriteUTF(boost::shared_ptr<string> str);
		void WriteUTF(string str);

		void ReadByte(unsigned char&);
		void ReadBytes(long int count, vector<unsigned char>&);
		void ReadBool(bool&);
		void ReadInt(long int&);
		void ReadUShort(unsigned short int&);
		void ReadShort(short int&);
		void ReadLong(long long&);
		void ReadFloat(float&);
		void ReadDouble(double&);
		void ReadUTF(string&);

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

		bool IsLittleEndian();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<vector<unsigned char> > buffer;
		long int position;
		bool compressed;

		bool zLibIsInitialized;
		z_stream zlibStrm;
	    unsigned char zlibIn[ZlibChunk];
	    unsigned char zlibOut[ZlibChunk];
	};

}	// namespace Util
}	// namespace Sfs2X

#endif
