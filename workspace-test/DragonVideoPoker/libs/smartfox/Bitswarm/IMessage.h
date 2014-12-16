// ===================================================================
//
// Description		
//		Contains the definition of IMessage interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __IMessage__
#define __IMessage__

#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
	// Interface IMessage
	// -------------------------------------------------------------------
	class IMessage
	{
	public:
		virtual long int Id() = 0;
		virtual void Id(long int value) = 0;

		virtual boost::shared_ptr<ISFSObject> Content() = 0;
		virtual void Content(boost::shared_ptr<ISFSObject> object) = 0;

		virtual long int TargetController() = 0;
		virtual void TargetController(long int) = 0;

		virtual bool IsEncrypted() = 0;
		virtual void IsEncrypted(bool value) = 0;

		virtual bool IsUDP() = 0;
		virtual void IsUDP(bool value) = 0;

		virtual long long PacketId() = 0;
		virtual void PacketId(long long value) = 0;
	};

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
