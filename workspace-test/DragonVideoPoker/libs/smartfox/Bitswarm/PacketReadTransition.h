// ===================================================================
//
// Description		
//		Contains the definition of PacketReadTransition
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PacketReadTransition__
#define __PacketReadTransition__

namespace Sfs2X {
namespace Bitswarm {

	// -------------------------------------------------------------------
    // Defines codes for PacketReadTransition
	// -------------------------------------------------------------------
    typedef enum PacketReadTransition
    {
		PacketReadTransition_HeaderReceived = 0,
		PacketReadTransition_SizeReceived,
		PacketReadTransition_IncompleteSize,
		PacketReadTransition_WholeSizeReceived,
		PacketReadTransition_PacketFinished,
		PacketReadTransition_InvalidData,
		PacketReadTransition_InvalidDataFinished
    };

}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
