// ===================================================================
//
// Description		
//		Contains the definition of UserVariable interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __UserVariable__
#define __UserVariable__

#include "../../Util/Common.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Entities {
namespace Variables {

	class DLLImportExport UserVariable
	{
	public:
		/// <summary>
		/// The Variable name
		/// </summary>
		virtual boost::shared_ptr<string> Name() = 0;
		
		/// <summary>
		/// The Variable Type
		/// </summary>
		/// <seealso cref="VariableType"/>
		virtual VariableType Type() = 0;

		/// <summary>
		/// The Variable value
		/// </summary>
		virtual boost::shared_ptr<void> Value() = 0;

		/// <summary>
		/// The Variable value as Boolean
		/// </summary>
		/// <returns>
		/// A pointer to a boolean
		/// </returns>
		virtual boost::shared_ptr<bool> GetBoolValue() = 0;
		
		/// <summary>
		/// The Variable value as int
		/// </summary>
		/// <returns>
		/// A pointer to a long integer
		/// </returns>
		virtual boost::shared_ptr<long int> GetIntValue() = 0;
		
		/// <summary>
		/// The Variable value as Double
		/// </summary>
		/// <returns>
		/// A pointer to a double
		/// </returns>
		virtual boost::shared_ptr<double> GetDoubleValue() = 0;
		
		/// <summary>
		/// The Variable value as String
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual boost::shared_ptr<string> GetStringValue() = 0;
		
		/// <summary>
		/// The Variable value as SFSObject
		/// </summary>
		/// <returns>
		/// Pointer to an <see cref="ISFSObject"/> instance
		/// </returns>
		/// <seealso cref="SFSObject"/>
		virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue() = 0;
		
		/// <summary>
		/// The Variable value as SFSArray
		/// </summary>
		/// <returns>
		/// Pointer to an <see cref="ISFSArray"/> instance
		/// </returns>
		virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue() = 0;
		
		/// <summary>
		/// Checks if the variable value is null
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool IsNull() = 0;
		
		virtual boost::shared_ptr<ISFSArray> ToSFSArray() = 0;
	};

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

#endif
