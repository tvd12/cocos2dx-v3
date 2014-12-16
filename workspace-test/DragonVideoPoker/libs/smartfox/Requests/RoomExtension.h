// ===================================================================
//
// Description		
//		Contains the definition of RoomExtension
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RoomExtension__
#define __RoomExtension__

#include "../Util/Common.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// This object is part of the RoomSettings parameters used for creating a new Room. 
	/// </summary>
	/// <remarks>
	/// It describes the properties of an Extension attached to the Room
	/// </remarks>
	/// <seealso cref="RoomSettings"/>
	/// <seealso cref="CreateRoomRequest"/>
	class DLLImportExport RoomExtension
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="id">
		/// the name of the extension
		/// </param>
		/// <param name="className">
		/// the fully qualified name of the main class in the extension
		/// </param>
		/// <seealso cref="RoomSettings"/>
		/// <seealso cref="CreateRoomRequest"/>
		RoomExtension(string id, string className);

		/// <summary>
		/// The name of the extension
		/// </summary>
		boost::shared_ptr<string> Id(); 

		/// <summary>
		/// The fully qualified name of the main class in the extension
		/// </summary>
		boost::shared_ptr<string> ClassName();

		/// <summary>
		/// An optional properties file that will be loaded on the server side when the extension is initialized
		/// </summary>
		boost::shared_ptr<string> PropertiesFile();

		/// <summary>
		/// An optional properties file that will be loaded on the server side when the extension is initialized
		/// </summary>
		void PropertiesFile(string value);

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

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<string> id;					// <-- mandatory
		boost::shared_ptr<string> className;			// <-- mandatory
		boost::shared_ptr<string> propertiesFile;		// <-- optional
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
