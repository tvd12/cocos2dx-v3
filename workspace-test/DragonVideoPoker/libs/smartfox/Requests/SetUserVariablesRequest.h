// ===================================================================
//
// Description		
//		Contains the definition of SetUserVariablesRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __SetUserVariablesRequest__
#define __SetUserVariablesRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "../Entities/Data/ISFSArray.h"
#include "../Entities/Data/SFSArray.h"
#include "../Entities/Variables/UserVariable.h"

#include <boost/shared_ptr.hpp>			// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <vector>						// STL library: vector object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {

	/// <summary>
	/// Set custom User Variables for the current User
	/// </summary>
	/// <seealso cref="SFSUserVariable"/>
	class DLLImportExport SetUserVariablesRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="userVariables">
		/// an Array of UserVariables
		/// </param>
		/// <example>
		/// <b>Example #1</b> Shows how set a number of User variables
		///		\code{.cpp}
		///			boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable (new vector<boost::shared_ptr<UserVariable>>());
		///
		///			boost::shared_ptr<UserVariable> variable (new UserVariable ("avatarType", "SwedishCook", VARIABLETYPE_STRING));
		///			collectionUserVariable->push_back(variable);
		///
		///			boost::shared_ptr<UserVariable> variable1 (new UserVariable ("country", "Sweden", VARIABLETYPE_STRING));
		///			collectionUserVariable->push_back(variable1);
		///
		///			boost::shared_ptr<UserVariable> variable2 (new UserVariable ("x", 10, VARIABLETYPE_INT));
		///			collectionUserVariable->push_back(variable2);
		///
		///			boost::shared_ptr<UserVariable> variable3 (new UserVariable ("y", 10, VARIABLETYPE_INT));
		///			collectionUserVariable->push_back(variable3);
		/// 
		///			boost::shared_ptr<IRequest> request (new SetUserVariablesRequest(collectionUserVariable)); 
		///			ptrSmartFox->Send(request);
		/// 	\endcode
		/// 
		/// <b>Example #2</b> Shows how to listen and react to some other User's updates
		///		\code{.cpp}
		///				ptrSmartFox->AddEventListener(SFSEvent::USER_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate> (EventListenerDelegate(CMyClass::OnUserVarsUpdate, (unsigned long long)this));
		///
		///				static void OnUserVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///
		///				void CMyClass::OnUserVarsUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
		///				{
		///					CMyClass* ptrMyClass = (CMyClass*)ptrContext;
		///
		///					boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
		///					boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
		///					boost::shared_ptr<vector<boost::shared_ptr<string>>> changedVars = ((boost::static_pointer_cast<vector<boost::shared_ptr<string>>>)(ptrEventParamValueVars));
		///
		///					boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
		///					boost::shared_ptr<User> user = ((boost::static_pointer_cast<User>)(ptrEventParamValueUser));
		///					boost::shared_ptr<UserVariable> variable = user->GetVariable("x");
		///					boost::shared_ptr<UserVariable> variable1 = user->GetVariable("y");
		///					if ((variable != NULL) && (variable1 != NULL))
		///					{
		///						// Move the character to a new position...
		///					}
		///				}
		/// 	\endcode
		/// </example>
		/// <seealso cref="SFSUserVariable"/>
		SetUserVariablesRequest(boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > userVariables);

		virtual ~SetUserVariablesRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<string> KEY_USER;

		static boost::shared_ptr<string> KEY_VAR_LIST;

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
		boost::shared_ptr<vector<boost::shared_ptr<UserVariable> > > userVariables;
	};

}	// namespace Requests
}	// namespace Sfs2X

#endif
