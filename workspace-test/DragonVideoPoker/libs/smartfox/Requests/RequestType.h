// ===================================================================
//
// Description		
//		Contains the definition of RequestType
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __RequestType__
#define __RequestType__

namespace Sfs2X {
namespace Requests {

	typedef enum RequestType
    {
		//--- System API Requests -----------------------------------------------------
		RequestType_Handshake = 0,
		RequestType_Login = 1,
		RequestType_Logout = 2,
		RequestType_GetRoomList = 3,
		RequestType_JoinRoom = 4,
		RequestType_AutoJoin = 5,
		RequestType_CreateRoom = 6,
		RequestType_GenericMessage = 7,
		RequestType_ChangeRoomName = 8,
		RequestType_ChangeRoomPassword = 9,
		RequestType_ObjectMessage = 10,
		RequestType_SetRoomVariables = 11,
		RequestType_SetUserVariables = 12,
		RequestType_CallExtension = 13,
		RequestType_LeaveRoom = 14,
		RequestType_SubscribeRoomGroup = 15,
		RequestType_UnsubscribeRoomGroup = 16,
		RequestType_SpectatorToPlayer = 17,
		RequestType_PlayerToSpectator = 18,
		RequestType_ChangeRoomCapacity = 19,
		RequestType_PublicMessage = 20,
		RequestType_PrivateMessage = 21,
		RequestType_ModeratorMessage = 22,
		RequestType_AdminMessage = 23,
		RequestType_KickUser = 24,
		RequestType_BanUser = 25,
		RequestType_ManualDisconnection = 26,
		RequestType_FindRooms = 27,
		RequestType_FindUsers = 28,
		RequestType_PingPong = 29,
		RequestType_SetUserPosition = 30,

		//--- Buddy List API Requests -------------------------------------------------
		RequestType_InitBuddyList = 200,
		RequestType_AddBuddy = 201,
		RequestType_BlockBuddy = 202,
		RequestType_RemoveBuddy = 203,
		RequestType_SetBuddyVariables = 204,
		RequestType_GoOnline = 205,
		
		//--- Game API Requests --------------------------------------------------------
		RequestType_InviteUser = 300,
		RequestType_InvitationReply = 301,
		RequestType_CreateSFSGame = 302,
		RequestType_QuickJoinGame = 303
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
