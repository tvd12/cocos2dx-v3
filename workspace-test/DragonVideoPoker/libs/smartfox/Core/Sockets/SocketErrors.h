// ===================================================================
//
// Description		
//		Contains the definition of all socket errors
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SocketErrors__
#define __SocketErrors__

namespace Sfs2X {
namespace Core {
namespace Sockets {

	// -------------------------------------------------------------------
    // Defines error codes for socket
	// -------------------------------------------------------------------
    typedef enum SocketErrors
    {
        // An unspecified socket error has occurred.
        SocketErrors_SocketError = -1,

        // The socket operation succeeded.
        SocketErrors_Success = 0,

		// The overlapped operation was aborted due to the closure of the socket.
        SocketErrors_OperationAborted = 995,
        
        // The application has initiated an overlapped operation that cannot be completed immediately.
        SocketErrors_IOPending = 997,

		// A blocking socket call was canceled.
        SocketErrors_Interrupted = 10004,

		// An attempt was made to access a socket in a way that is forbidden by its access permissions.
        SocketErrors_AccessDenied = 10013,

		// An invalid pointer address was detected by the underlying socket provider.
        SocketErrors_Fault = 10014,

		// An invalid argument was supplied to a socket member.
        SocketErrors_InvalidArgument = 10022,

		// There are too many open sockets in the underlying socket provider.
        SocketErrors_TooManyOpenSockets = 10024,

		// An operation on a nonblocking socket cannot be completed immediately.
        SocketErrors_WouldBlock = 10035,

		// A blocking operation is in progress.
        SocketErrors_InProgress = 10036,

		// The nonblocking socket already has an operation in progress.
        SocketErrors_AlreadyInProgress = 10037,

		// A socket operation was attempted on a non-socket.
        SocketErrors_NotSocket = 10038,

		// A required address was omitted from an operation on a socket.
        SocketErrors_DestinationAddressRequired = 10039,

		// The datagram is too long.
        SocketErrors_MessageSize = 10040,

		// The protocol type is incorrect for this socket.
        SocketErrors_ProtocolType = 10041,

		// An unknown, invalid, or unsupported option or level was used with a socket.
        SocketErrors_ProtocolOption = 10042,

		// The protocol is not implemented or has not been configured.
        SocketErrors_ProtocolNotSupported = 10043,

		// The support for the specified socket type does not exist in this address family.
        SocketErrors_SocketNotSupported = 10044,
        
		// The address family is not supported by the protocol family.
        SocketErrors_OperationNotSupported = 10045,
        
		// The protocol family is not implemented or has not been configured.
        SocketErrors_ProtocolFamilyNotSupported = 10046,

		// The address family specified is not supported. This error is returned if
        // the IPv6 address family was specified and the IPv6 stack is not installed
        // on the local machine. This error is returned if the IPv4 address family was
        // specified and the IPv4 stack is not installed on the local machine.
        SocketErrors_AddressFamilyNotSupported = 10047,

        // Only one use of an address is normally permitted.
        SocketErrors_AddressAlreadyInUse = 10048,

		// The selected IP address is not valid in this context.
        SocketErrors_AddressNotAvailable = 10049,

		// The network is not available.
        SocketErrors_NetworkDown = 10050,

		// No route to the remote host exists.
        SocketErrors_NetworkUnreachable = 10051,
  
		// The application tried to set socketOptionName.KeepAlive
        // on a connection that has already timed out.
        SocketErrors_NetworkReset = 10052,

		// The connection was aborted by the underlying socket provider.
        SocketErrors_ConnectionAborted = 10053,

		// The connection was reset by the remote peer.
        SocketErrors_ConnectionReset = 10054,

		// No free buffer space is available for a socket operation.
        SocketErrors_NoBufferSpaceAvailable = 10055,

		// The socket is already connected.
        SocketErrors_IsConnected = 10056,

		// The application tried to send or receive data, and the socket is not connected.
        SocketErrors_NotConnected = 10057,

		// A request to send or receive data was disallowed because the socket has already been closed.
        SocketErrors_Shutdown = 10058,

		// The connection attempt timed out, or the connected host has failed to respond.
        SocketErrors_TimedOut = 10060,

		// The remote host is actively refusing a connection.
        SocketErrors_ConnectionRefused = 10061,

		// The operation failed because the remote host is down.
        SocketErrors_HostDown = 10064,

		// There is no network route to the specified host.
        SocketErrors_HostUnreachable = 10065,

		// Too many processes are using the underlying socket provider.
        SocketErrors_ProcessLimit = 10067,

		// The network subsystem is unavailable.
        SocketErrors_SystemNotReady = 10091,

		// The version of the underlying socket provider is out of range.
        SocketErrors_VersionNotSupported = 10092,

		// The underlying socket provider has not been initialized.
        SocketErrors_NotInitialized = 10093,

		// A graceful shutdown is in progress.
        SocketErrors_Disconnecting = 10101,

		// The specified class was not found.
        SocketErrors_TypeNotFound = 10109,

		// No such host is known. The name is not an official host name or alias.
        SocketErrors_HostNotFound = 11001,

		// The name of the host could not be resolved. Try again later.
        SocketErrors_TryAgain = 11002,

		// The error is unrecoverable or the requested database cannot be located.
        SocketErrors_NoRecovery = 11003,

		// The requested name or IP address was not found on the name server.
        SocketErrors_NoData = 11004,
    };

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X

#endif
