// ===================================================================
//
// Description		
//		Contains the implementation of DefaultObjectDumpFormatter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "DefaultObjectDumpFormatter.h"

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

/*
const char DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN = '{'; //(char) 0x01;
const char DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
const char DefaultObjectDumpFormatter::TOKEN_DIVIDER = ';'; //(char) 0x03;
const char DefaultObjectDumpFormatter::NEW_LINE = '\n';
const char DefaultObjectDumpFormatter::TAB = '\t';
const char DefaultObjectDumpFormatter::DOT = '.';
*/

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
DefaultObjectDumpFormatter::~DefaultObjectDumpFormatter()
{
}

// -------------------------------------------------------------------
// PrettyPrintDump
// -------------------------------------------------------------------
boost::shared_ptr<string> DefaultObjectDumpFormatter::PrettyPrintDump(boost::shared_ptr<string> rawDump)
{
	boost::shared_ptr<string> strBuf (new string());

	long int indentPos = 0;
	for (unsigned int i = 0; i < rawDump->size(); i++) 
	{
		char ch = rawDump->at(i);
				
		if (ch == TOKEN_INDENT_OPEN) 
		{
			indentPos++;
			strBuf->append(NEW_LINE + (*GetFormatTabs(indentPos)));
		}
		else if (ch == TOKEN_INDENT_CLOSE) 
		{
			indentPos--;
			if (indentPos < 0) 
			{
				boost::shared_ptr<string> message(new string("DumpFormatter: the indentPos is negative. TOKENS ARE NOT BALANCED!"));
				boost::shared_ptr<SFSError> exception(new SFSError(message));
				throw exception;
			}	
			
			strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
		}
		else if (ch == TOKEN_DIVIDER) 
		{
			strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
		}
		else 
		{
			boost::shared_ptr<string> temporaryString (new string());

			boost::shared_ptr<string> format (new string("%c"));
			StringFormatter<char> (temporaryString, format, ch);

			strBuf->append(*temporaryString.get());
		}
	}
			
	if (indentPos != 0) 
	{
		boost::shared_ptr<string> message (new string("DumpFormatter: the indentPos is not == 0. TOKENS ARE NOT BALANCED!"));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
					
	return strBuf;
}

// -------------------------------------------------------------------
// GetFormatTabs
// -------------------------------------------------------------------
boost::shared_ptr<string> DefaultObjectDumpFormatter::GetFormatTabs(long int howMany)
{
	return StrFill(TAB, howMany);
}

// -------------------------------------------------------------------
// StrFill
// -------------------------------------------------------------------
boost::shared_ptr<string> DefaultObjectDumpFormatter::StrFill(char ch, long int howMany)
{
	boost::shared_ptr<string> strBuf (new string());

	for (int i = 0; i < howMany; i++) 
	{
		boost::shared_ptr<string> temporaryString (new string());
		boost::shared_ptr<string> format (new string("%c"));
		StringFormatter<char> (temporaryString, format, ch);

		strBuf->append(*temporaryString.get());
	}
			
	return strBuf;
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
boost::shared_ptr<string> DefaultObjectDumpFormatter::HexDump(boost::shared_ptr<ByteArray> ba)
{
	return HexDump(ba, HEX_BYTES_PER_LINE);
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
boost::shared_ptr<string> DefaultObjectDumpFormatter::HexDump(boost::shared_ptr<ByteArray> ba, long int bytesPerLine)
{
	boost::shared_ptr<string> sb (new string());
	boost::shared_ptr<string> temporaryString (new string());
	
	boost::shared_ptr<string> format (new string("Binary Size: %d%c"));
	StringFormatter<long int, char> (temporaryString, format, ba->Length(), NEW_LINE);
	
	sb->append(*temporaryString.get());
	temporaryString->clear();

	if (ba->Length() > MAX_DUMP_LENGTH) 
	{
		boost::shared_ptr<string> format (new string("** Data larger than max dump size of %d. Data not displayed"));
		StringFormatter<long int> (temporaryString, format, MAX_DUMP_LENGTH);
		
		sb->append(*temporaryString.get());
		return sb;
	}

	string hexLine;
	string chrLine;

	long int index = 0;
	long int count = 0;
	char currChar;
	unsigned char currByte;
						
	do 
	{
		boost::shared_ptr<vector<unsigned char> > vectorBaBytes = ba->Bytes();
		currByte = vectorBaBytes->at(index);

		boost::shared_ptr<string> format (new string("%02x"));
		StringFormatter<unsigned char> (temporaryString, format, currByte);
		
		string hexByte(*temporaryString.get());
		temporaryString->clear();
								
		if (hexByte.size() == 1) 
		{
			hexByte = "0" + hexByte;
		}
				
		hexLine.append(hexByte);
		hexLine.append(" ");
				
		if (currByte >= 33 && currByte <= 126) 
		{
			currChar = (unsigned char)(currByte);
		}
		else 
		{
			currChar = DOT;
		}

		format = boost::shared_ptr<string>(new string("%c"));
		StringFormatter<char> (temporaryString, format, currChar);
		
		chrLine.append(*temporaryString.get());
		temporaryString->clear();
				
		if (++count == bytesPerLine) 
		{
			count = 0;
			sb->append(hexLine);

			boost::shared_ptr<string> format (new string("%c"));
			StringFormatter<char> (temporaryString, format, TAB);
		
			sb->append(*temporaryString.get());
			sb->append(chrLine);
			temporaryString->clear();

			format = boost::shared_ptr<string>(new string("%c"));
			StringFormatter<char> (temporaryString, format, NEW_LINE);
		
			sb->append(*temporaryString.get());
			temporaryString->clear();
					
			hexLine.clear();
			chrLine.clear();
		}
				
	} 
	while(++index < ba->Length());
			
	// Add last incomplete line
	if (count != 0) 	
	{
		for (int j = bytesPerLine - count; j > 0; j--)
		{
			hexLine.append("   ");
			chrLine.append(" ");
		}
				
		sb->append(hexLine);

		boost::shared_ptr<string> format (new string("%c"));
		StringFormatter<char> (temporaryString, format, TAB);

		sb->append(*temporaryString.get());
		sb->append(chrLine);
		temporaryString->clear();

		format = boost::shared_ptr<string>(new string("%c"));
		StringFormatter<char> (temporaryString, format, NEW_LINE);

		sb->append(*temporaryString.get());
	}

	return sb;
}


}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X
