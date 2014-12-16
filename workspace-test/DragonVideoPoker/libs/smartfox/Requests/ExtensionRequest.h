// ===================================================================
//
// Description		
//		Contains the definition of ExtensionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ExtensionRequest__
#define __ExtensionRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Room.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities;
using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Sends a request to a Zone or Room Extension.
	/// </summary>
	/// <remarks>
	/// Each request to an extension is characterized by two parameters:
	///	<ul>
	/// 		<li><b>command name:</b> any string that identifies an action that should be executed on the server side. We recommend to use the same command name for both the client request and the server response.</li>
	/// 		<li><b>request data:</b> you can send any simple or complex data structures to your extension(s) via the SFSObject class</li>
	/// </ul>
	/// </remarks>
	class DLLImportExport ExtensionRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="extCmd">
		/// the command name
		/// </param>
		/// <param name="parameters">
		/// the custom extension request data
		/// </param>
		/// <param name="room">
		/// when specified it will send the request to the Room Extension. The user must be joined in that Room. 
		/// </param>
		/// <param name="useUDP">
		/// (optional) uses UDP to send the request
		/// </param>
		/// <example>
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::EXTENSION_RESPONSE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnExtensionResponse, (unsigned long long)this));
		///
		/// 			// Send two integers to the Zone extension and get their sum in return
		/// 			boost::shared_ptr<ISFSObject> parameters (new SFSObject());
		/// 			parameers->PutInt("n1", 26);
		/// 			parameters->PutInt("n2", 16);
		///
		/// 			// Send request
		///				boost::shared_ptr<IRequest> request (new ExtensionRequest("add", parameters)); 
		///				ptrSmartFox->Send(request);
		///
		///				static void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEventParams)["cmd"];
		///					boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
		///
		///					if (*ptrNotifiedCmd == "add")
		///					{
		/// 					// Similarly the server sends us an object with custom data.
		///						boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEventParams)["params"];
		///						boost::shared_ptr<ISFSObject> ptrNotifiedISFSObject = ((boost::static_pointer_cast<ISFSObject>)(ptrEventParamValueParams));
		///
		/// 					// We expect an int called sum
		///						ptrNotifiedISFSObject->GetInt("sum");
		///					}
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="Core.SFSEvent.EXTENSION_RESPONSE"/>
		ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room, bool useUDP); 

		/// <summary>
		/// <see cref="ExtensionRequest(string, boost::shared_ptr<ISFSObject>, boost::shared_ptr<Room>, bool)"/>
		/// </summary>
		ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room);

		/// <summary>
		/// <see cref="ExtensionRequest(string, boost::shared_ptr<ISFSObject>, boost::shared_ptr<Room>, bool)"/>
		/// </summary>
		ExtensionRequest(string extCmd, boost::shared_ptr<ISFSObject> parameters);

		virtual ~ExtensionRequest();

		bool UseUDP();
		void Validate(boost::shared_ptr<SmartFox> sfs);
		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_CMD;
		static boost::shared_ptr<string> KEY_PARAMS;
		static boost::shared_ptr<string> KEY_ROOM;

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
		void Init(string extCmd, boost::shared_ptr<ISFSObject> parameters, boost::shared_ptr<Room> room, bool useUDP);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		boost::shared_ptr<string> extCmd;
		boost::shared_ptr<ISFSObject> parameters;
		boost::shared_ptr<Room> room;		
		bool useUDP;

	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
