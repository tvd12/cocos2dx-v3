// ===================================================================
//
// Description		
//		Contains the definition of PacketReadState
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PacketReadState__
#define __PacketReadState__

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
    // Defines codes for PacketReadState
	// -------------------------------------------------------------------
    typedef enum PacketReadState
    {
		PACKETREADSTATE_WAIT_NEW_PACKET = 0,
		PACKETREADSTATE_WAIT_DATA_SIZE,
		PACKETREADSTATE_WAIT_DATA_SIZE_FRAGMENT,
		PACKETREADSTATE_WAIT_DATA,
		PACKETREADSTATE_INVALID_DATA
    };

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
