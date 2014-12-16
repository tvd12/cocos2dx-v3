// ===================================================================
//
// Description		
//		Contains the definition of BaseRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BaseRequest__
#define __BaseRequest__

// Forward class declaration
namespace Sfs2X {
namespace Requests {
	class BaseRequest;
}	// namespace Requests
}	// namespace Sfs2X

#include "IRequest.h"
#include "RequestType.h"
#include "../Util/Common.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Entities/Data/SFSObject.h"
#include "../Bitswarm/Message.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Bitswarm;
using namespace Sfs2X;

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Logging;

namespace Sfs2X {
namespace Requests {

	// -------------------------------------------------------------------
	// Class BaseRequest
	// -------------------------------------------------------------------
	class DLLImportExport BaseRequest : public IRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		BaseRequest();
		BaseRequest(RequestType tp);
		BaseRequest(long int id);
		virtual ~BaseRequest();

		long int Id();
		void Id(long int value);

		RequestType Type();
		void Type(RequestType value);

		// IRequest implementation

		virtual void Validate(boost::shared_ptr<SmartFox> sfs);
		virtual void Execute(boost::shared_ptr<SmartFox> sfs);
		
		virtual long int TargetController();
		virtual void TargetController(long int value);
		
		virtual bool IsEncrypted();
		virtual void IsEncrypted(bool value);
		
		virtual boost::shared_ptr<IMessage> Message();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static boost::shared_ptr<string> KEY_ERROR_CODE;
		static boost::shared_ptr<string> KEY_ERROR_PARAMS;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

		boost::shared_ptr<ISFSObject> sfso;
		long int targetController;
		
	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		long int id;
		bool isEncrypted;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
