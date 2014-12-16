// ===================================================================
//
// Description		
//		Contains the definition of Message
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Message__
#define __Message__

#include "../Entities/Data/ISFSObject.h"
#include "IMessage.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Bitswarm {
	
	// -------------------------------------------------------------------
	// Class Message
	// -------------------------------------------------------------------
	class Message : public IMessage
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		Message();
		virtual ~Message();

		long int Id();
		void Id(long int value);
		
		boost::shared_ptr<ISFSObject> Content();
		void Content(boost::shared_ptr<ISFSObject> value);

		long int TargetController();
		void TargetController(long int value);

		bool IsEncrypted();
		void IsEncrypted(bool value);

		bool IsUDP();
		void IsUDP(bool value);

		long long PacketId();
		void PacketId(long long value);

		boost::shared_ptr<string> ToString();
		
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

		long int id;
		boost::shared_ptr<ISFSObject> content;
		long int targetController;
		bool isEncrypted;
		bool isUDP;
		long long packetId;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
