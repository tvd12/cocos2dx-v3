// ===================================================================
//
// Description		
//		Contains the utility to format strings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __StringFormatter__
#define __StringFormatter__

#include <stdio.h>
#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1>
	static void StringFormatter (boost::shared_ptr<string> stringToFormat, boost::shared_ptr<string> stringFormat, Type1 p1)
	{
		long int previousStringSize = stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)(stringToFormat->c_str()), (const char*)(stringFormat->c_str()), p1);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2>
	static void StringFormatter (boost::shared_ptr<string> stringToFormat, boost::shared_ptr<string> stringFormat, Type1 p1, Type2 p2)
	{
		long int previousStringSize = stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)(stringToFormat->c_str()), (const char*)(stringFormat->c_str()), p1, p2);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2, class Type3>
	static void StringFormatter (boost::shared_ptr<string> stringToFormat, boost::shared_ptr<string> stringFormat, Type1 p1, Type2 p2, Type3 p3)
	{
		long int previousStringSize = stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)stringToFormat->c_str(), (char*)stringFormat->c_str(), p1, p2, p3);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2, class Type3, class Type4>
	static void StringFormatter (boost::shared_ptr<string> stringToFormat, boost::shared_ptr<string> stringFormat, Type1 p1, Type2 p2, Type3 p3, Type4 p4)
	{
		long int previousStringSize = stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)stringToFormat->c_str(), (char*)stringFormat->c_str(), p1, p2, p3, p4);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// Utf8toWStr
	// -------------------------------------------------------------------
	static void Utf8toWStr(boost::shared_ptr<string> src, boost::shared_ptr<wstring> dest)
	{
		dest->clear();
		wchar_t w = 0;
		int bytes = 0;
		wchar_t err = L'?';
		for (size_t i = 0; i < src->size(); i++)
		{
			unsigned char c = (unsigned char)(*src)[i];
			if (c <= 0x7f)
			{
				//first byte
				if (bytes)
				{
					dest->push_back(err);
					bytes = 0;
				}
				dest->push_back((wchar_t)c);
			}
			else if (c <= 0xbf)
			{
				//second/third/etc byte
				if (bytes){
					w = ((w << 6)|(c & 0x3f));
					bytes--;
					if (bytes == 0)
						dest->push_back(w);
				}
				else
					dest->push_back(err);
			}
			else if (c <= 0xdf)
			{
				//2byte sequence start
				bytes = 1;
				w = c & 0x1f;
			}
			else if (c <= 0xef)
			{
				//3byte sequence start
				bytes = 2;
				w = c & 0x0f;
			}
			else if (c <= 0xf7)
			{
				//3byte sequence start
				bytes = 3;
				w = c & 0x07;
			}
			else
			{
				dest->push_back(err);
				bytes = 0;
			}
		}
		if (bytes)
			dest->push_back(err);
	}

	// -------------------------------------------------------------------
	// WStrToUtf8
	// -------------------------------------------------------------------
	static void WStrToUtf8(boost::shared_ptr<wstring> src, boost::shared_ptr<string> dest)
	{
		dest->clear();
		for (size_t i = 0; i < src->size(); i++)
		{
			wchar_t w = (*src)[i];
			if (w <= 0x7f)
				dest->push_back((char)w);
			else if (w <= 0x7ff)
			{
				dest->push_back(0xc0 | ((w >> 6)& 0x1f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else if (w <= 0xffff)
			{
				dest->push_back(0xe0 | ((w >> 12)& 0x0f));
				dest->push_back(0x80| ((w >> 6) & 0x3f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else if (w <= 0x10ffff)
			{
				dest->push_back(0xf0 | (((unsigned long int)w >> 18) & 0x07));
				dest->push_back(0x80| ((w >> 12) & 0x3f));
				dest->push_back(0x80| ((w >> 6) & 0x3f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else
				dest->push_back('?');
		}
	}

}	// namespace Util
}	// namespace Sfs2X

#endif

