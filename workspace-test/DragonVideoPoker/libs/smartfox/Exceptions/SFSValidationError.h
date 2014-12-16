// ===================================================================
//
// Description		
//		Contains the definition of SFSValidationError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SFSValidationError__
#define __SFSValidationError__

#include <boost/exception/exception.hpp>	// Boost exception
#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Exceptions {

	// ------------------------------------------------------------------- 
	// Class SFSValidationError
	// -------------------------------------------------------------------
	class SFSValidationError : public boost::exception
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSValidationError(boost::shared_ptr<string> message, boost::shared_ptr<list<string> > errors);
		~SFSValidationError () throw () {};
		const char* what() { return message.get()->c_str();}
		boost::shared_ptr<string> Message() {return message;};
		boost::shared_ptr<list<string> > Errors();

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

		boost::shared_ptr<string> message;
		boost::shared_ptr<list<string> > errors;
	};

}	// namespace Exceptions
}	// namespace Sfs2X

#endif
