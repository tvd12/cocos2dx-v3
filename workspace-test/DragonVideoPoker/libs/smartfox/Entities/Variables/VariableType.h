// ===================================================================
//
// Description		
//		Contains the definition of VariableType
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __VariableType__
#define __VariableType__

namespace Sfs2X {
namespace Entities {
namespace Variables {

    typedef enum VariableType 
    {
		VARIABLETYPE_UNKNOWN = -1,
		VARIABLETYPE_NULL = 0,
		VARIABLETYPE_BOOL = 1,
		VARIABLETYPE_INT = 2,
		VARIABLETYPE_DOUBLE = 3,
		VARIABLETYPE_STRING = 4,
		VARIABLETYPE_OBJECT = 5,
		VARIABLETYPE_ARRAY = 6
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
