// ===================================================================
//
// Description		
//		Contains the definition of BaseEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BaseEvent__
#define __BaseEvent__

#include "../Util/Common.h"
#include <stdio.h>

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>				// STL library: string object
#include <map>					// STL library: map object
using namespace std;			// Declare the STL namespace

namespace Sfs2X {
namespace Core {

	/// <summary>
	/// This is the Base class of all Events in the API
	/// </summary>
	/// <seealso cref="SFSEvent"/>
	/// <seealso cref="SFSBuddyEvent"/>
	class DLLImportExport BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		BaseEvent();
		BaseEvent(boost::shared_ptr<string> type);
		BaseEvent(boost::shared_ptr<string> type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > args);
		~BaseEvent();

		boost::shared_ptr<string> Type();
		void Type(boost::shared_ptr<string> value);

		/// <summary>
        /// A Hashtable containing the event's parameters.
		/// </summary>
		boost::shared_ptr<map<string, boost::shared_ptr<void> > > Params();
		void Params(boost::shared_ptr<map<string, boost::shared_ptr<void> > > value);

		boost::shared_ptr<void> Target();
		void Target(boost::shared_ptr<void> value);

		boost::shared_ptr<string> ToString();
		boost::shared_ptr<BaseEvent> Clone();	

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

		boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments;
		boost::shared_ptr<string> type;
		boost::shared_ptr<void> target;

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
