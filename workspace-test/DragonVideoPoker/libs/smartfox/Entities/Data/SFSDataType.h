// ===================================================================
//
// Description		
//		Contains the definition of SFSDataType
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSDataType__
#define __SFSDataType__

namespace Sfs2X {
namespace Entities {
namespace Data {

    typedef enum SFSDataType 
    {
		/// <summary>
		/// Null value
		/// </summary>
		SFSDATATYPE_NULL = 0,
		
		/// <summary>
		/// Boolean
		/// </summary>
		SFSDATATYPE_BOOL = 1,
		
		/// <summary>
		/// Byte, signed 8 bit
		/// </summary>
		SFSDATATYPE_BYTE = 2,
		
		/// <summary>
		/// Short integer, signed 16 bit
		/// </summary>
		SFSDATATYPE_SHORT = 3,
		
		/// <summary>
		/// Integer, signed 32 bit
		/// </summary>
		SFSDATATYPE_INT = 4,
		
		/// <summary>
		/// Long integer, signed 64 bit
		/// </summary>
		SFSDATATYPE_LONG = 5,

		/// <summary>
		/// Floating point decimal, signed 32 bit
		/// </summary>
		SFSDATATYPE_FLOAT = 6,
		
		/// <summary>
		/// Double precision decimal, signed 64 bit
		/// </summary>
		SFSDATATYPE_DOUBLE = 7,
		
		/// <summary>
		/// UTF-8 Encoded String
		/// </summary>
		SFSDATATYPE_UTF_STRING = 8,
		
		/// <summary>
		/// Array of Booleans
		/// </summary>
		SFSDATATYPE_BOOL_ARRAY = 9,
		
		/// <summary>
		/// Array of Bytes (treated as ByteArray)
		/// </summary>
		SFSDATATYPE_BYTE_ARRAY = 10,
		
		/// <summary>
		/// Array of Shorts
		/// </summary>
		SFSDATATYPE_SHORT_ARRAY = 11,
		
		/// <summary>
		/// Array of Integers
		/// </summary>
		SFSDATATYPE_INT_ARRAY = 12,
		
		/// <summary>
		/// Array of Long integers
		/// </summary>
		SFSDATATYPE_LONG_ARRAY = 13,
		
		/// <summary>
		/// Array of Floats
		/// </summary>
		SFSDATATYPE_FLOAT_ARRAY = 14,
		
		/// <summary>
		/// Array of Doubles
		/// </summary>
		SFSDATATYPE_DOUBLE_ARRAY = 15,
		
		/// <summary>
		/// Array of UTF-8 Strings
		/// </summary>
		SFSDATATYPE_UTF_STRING_ARRAY = 16,
		
		/// <summary>
		/// SFSArray
		/// </summary>
		/// <seealso cref="SFSArray"/>
		SFSDATATYPE_SFS_ARRAY = 17,
		
		/// <summary>
		/// SFSObject
		/// </summary>
		/// <seealso cref="SFSObject"/>
		SFSDATATYPE_SFS_OBJECT = 18,
		
		/// <summary>
		/// Uses SFSObject to serialize Class instances
		/// </summary>
		SFSDATATYPE_CLASS = 19		
    };

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
