// ===================================================================
//
// Description		
//		Contains the implementation of GenericMessageRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

#include "GenericMessageRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> GenericMessageRequest::KEY_ROOM_ID (new string("r"));
boost::shared_ptr<string> GenericMessageRequest::KEY_USER_ID (new string("u"));
boost::shared_ptr<string> GenericMessageRequest::KEY_MESSAGE (new string("m"));
boost::shared_ptr<string> GenericMessageRequest::KEY_MESSAGE_TYPE (new string("t"));
boost::shared_ptr<string> GenericMessageRequest::KEY_RECIPIENT (new string("rc"));	
boost::shared_ptr<string> GenericMessageRequest::KEY_RECIPIENT_MODE (new string("rm"));
boost::shared_ptr<string> GenericMessageRequest::KEY_XTRA_PARAMS (new string("p"));	
boost::shared_ptr<string> GenericMessageRequest::KEY_SENDER_DATA (new string("sd"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
GenericMessageRequest::GenericMessageRequest()
	: BaseRequest (RequestType_GenericMessage)
{
	this->type = -1;
	this->room = boost::shared_ptr<Room>();
	this->user = boost::shared_ptr<User>();
	this->message = boost::shared_ptr<string>();
	this->parameters = boost::shared_ptr<ISFSObject>();
	this->recipientUser = boost::shared_ptr<User>();
	this->recipientRoom = boost::shared_ptr<Room>();
	this->recipientString = boost::shared_ptr<string>();
	this->recipientInt = boost::shared_ptr<long int>();
	this->recipientUsersCollection = boost::shared_ptr<vector<boost::shared_ptr<User> > >();
	this->sendMode = 0;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
GenericMessageRequest::~GenericMessageRequest()
{
	if (recipientUsersCollection != NULL)
	{
		recipientUsersCollection->clear();
	}
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void GenericMessageRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	// Check for a valid type			
	if (type < 0) 
	{
		boost::shared_ptr<list<string> > log (new list<string>());
		log->push_back("Unsupported message type: " + type);

		boost::shared_ptr<string> message (new string("PublicMessage request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, log));
		throw exception;
	}		
				
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	switch ((GenericMessageType)type)
	{
		case GENERICMESSAGETYPE_PUBLIC_MSG:
			ValidatePublicMessage(sfs, errors);
			break;
		case GENERICMESSAGETYPE_PRIVATE_MSG:
			ValidatePrivateMessage(sfs, errors);
			break;
		case GENERICMESSAGETYPE_OBJECT_MSG:
			ValidateObjectMessage(sfs, errors);
			break;
		case GENERICMESSAGETYPE_BUDDY_MSG:
			ValidateBuddyMessage(sfs, errors);
			break;
		default:
			ValidateSuperUserMessage(sfs, errors);
			break;
	}
			
	if (errors->size() > 0) 
	{
		boost::shared_ptr<string> message (new string("Request error - "));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}		
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void GenericMessageRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	// Set the message type
	boost::shared_ptr<unsigned char> valueMessageType (new unsigned char());
	*valueMessageType = (unsigned char)type;
	this->sfso->PutByte(KEY_MESSAGE_TYPE, valueMessageType);
			
	switch ((GenericMessageType)type) 
	{
		case GENERICMESSAGETYPE_PUBLIC_MSG :
			ExecutePublicMessage(sfs);
			break;
		case GENERICMESSAGETYPE_PRIVATE_MSG:
			ExecutePrivateMessage(sfs);
			break;
		case GENERICMESSAGETYPE_OBJECT_MSG:
			ExecuteObjectMessage(sfs);
			break;
		case GENERICMESSAGETYPE_BUDDY_MSG:
			ExecuteBuddyMessage(sfs);
			break;
		default:
			ExecuteSuperUserMessage(sfs);
			break;
	}
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Specialized validators
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// -------------------------------------------------------------------
// ValidatePublicMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ValidatePublicMessage(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<list<string> > errors)
{
	if (message == NULL || message->size() == 0) 
	{
		errors->push_back("Public message is empty!");
	}
				
	if (room != NULL && !sfs->MySelf()->IsJoinedInRoom(room)) 
	{
		errors->push_back("You are not joined in the target Room: " + (*room->Name()));
	}
}

// -------------------------------------------------------------------
// ValidatePrivateMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ValidatePrivateMessage(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<list<string> > errors)
{
	if (message == NULL || message->size() == 0) 
	{
		errors->push_back("Private message is empty!");
	}

	if ((recipientInt == NULL) || ((*recipientInt) < 0))
	{
		if (recipientInt != NULL)
		{
			errors->push_back("Invalid recipient id: " + (*recipientInt));
		}
		else
		{
			errors->push_back("Invalid recipient id");
		}
	}
}

// -------------------------------------------------------------------
// ValidateObjectMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ValidateObjectMessage(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<list<string> > errors)
{
	if (parameters == NULL) 
	{
		errors->push_back("Object message is null!");
	}
}

// -------------------------------------------------------------------
// ValidateBuddyMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ValidateBuddyMessage(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<list<string> > errors)
{
	if (!sfs->BuddyManager()->Inited())
		errors->push_back("BuddyList is not inited. Please send an InitBuddyRequest first.");
				
	if (sfs->BuddyManager()->MyOnlineState() == false)
		errors->push_back("Can't send messages while off-line");
				
	if (message == NULL || message->size() == 0) 
		errors->push_back("Buddy message is empty!");
				
	long int recipientId = *recipientInt.get();

	if (recipientId < 0)
		errors->push_back("Recipient is not online or not in your buddy list");
}

// -------------------------------------------------------------------
// ValidateSuperUserMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ValidateSuperUserMessage(boost::shared_ptr<SmartFox> sfs, boost::shared_ptr<list<string> > errors)
{
	if (message == NULL || message->size() == 0) 
	{
		errors->push_back("Moderator message is empty!");
	}

	switch ((MessageRecipientType)sendMode)
	{
	case MESSAGERECIPIENTTYPE_TO_USER:
		if (recipientUser == NULL) 
		{
			errors->push_back("TO_USER expects a User object as recipient");
		}
		break;
	case MESSAGERECIPIENTTYPE_TO_ROOM:
		if (recipientRoom == NULL) 
		{
			errors->push_back("TO_ROOM expects a Room object as recipient");
		}
		break;
	case MESSAGERECIPIENTTYPE_TO_GROUP:
		if (recipientString == NULL) 
		{
			errors->push_back("TO_GROUP expects a String object (the groupId) as recipient");
		}
		break;
	}

}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Specialized executors
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// -------------------------------------------------------------------
// ExecutePublicMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ExecutePublicMessage(boost::shared_ptr<SmartFox> sfs)
{
	// No room was passed, let's use the last joined one
	if (room == NULL)
		room = sfs->LastJoinedRoom();
			
	// If it doesn't exist we have a problem
	if (room == NULL) 
	{
		boost::shared_ptr<string> message (new string("User should be joined in a room in order to send a public message"));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
			
	boost::shared_ptr<long> valueId (new long());
	*valueId = room->Id();
	this->sfso->PutInt(KEY_ROOM_ID, valueId);

	boost::shared_ptr<long> valueMySelfId (new long());
	*valueMySelfId = sfs->MySelf()->Id();
	this->sfso->PutInt(KEY_USER_ID, valueMySelfId);

	this->sfso->PutUtfString(KEY_MESSAGE, message);
			
	if (parameters != NULL) 
	{
		sfso->PutSFSObject(KEY_XTRA_PARAMS, parameters);
	}
}

// -------------------------------------------------------------------
// ExecutePrivateMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ExecutePrivateMessage(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutInt(KEY_RECIPIENT, recipientInt);
	sfso->PutUtfString(KEY_MESSAGE, message);
			
	if (parameters != NULL) 
	{
		sfso->PutSFSObject(KEY_XTRA_PARAMS, parameters);
	}
}

// -------------------------------------------------------------------
// ExecuteBuddyMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ExecuteBuddyMessage(boost::shared_ptr<SmartFox> sfs)
{
	// Id of the recipient buddy
	sfso->PutInt(KEY_RECIPIENT, recipientInt);
			
	// Message
	sfso->PutUtfString(KEY_MESSAGE, message);
			
	// Params
	if (parameters != NULL) 
	{
		sfso->PutSFSObject(KEY_XTRA_PARAMS, parameters);
	}
}

// -------------------------------------------------------------------
// ExecuteSuperUserMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ExecuteSuperUserMessage(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_MESSAGE, message);
		
	if (parameters != NULL) 
	{
		sfso->PutSFSObject(KEY_XTRA_PARAMS, parameters);
	}
	
	boost::shared_ptr<long int> valueSendMode (new long int());
	*valueSendMode = sendMode;
	sfso->PutInt(KEY_RECIPIENT_MODE, valueSendMode);
			
	switch ((MessageRecipientType)sendMode)
	{
		// Put the User.id as Int
		case MESSAGERECIPIENTTYPE_TO_USER:
			{
				boost::shared_ptr<long> valueId (new long());
				*valueId = recipientUser->Id();

				sfso->PutInt(KEY_RECIPIENT, valueId);
				break;
			}
		// Put the Room.id as Int
		case MESSAGERECIPIENTTYPE_TO_ROOM:
			{
				boost::shared_ptr<long> valueId (new long());
				*valueId = recipientRoom->Id();

				sfso->PutInt(KEY_RECIPIENT, valueId);
				break;
			}
		// Put the Room Group as String
		case MESSAGERECIPIENTTYPE_TO_GROUP:
			sfso->PutUtfString(KEY_RECIPIENT, recipientString);
			break;
		// the TO_ZONE case does not need to pass any other params
	}
}

// -------------------------------------------------------------------
// ExecuteObjectMessage
// -------------------------------------------------------------------
void GenericMessageRequest::ExecuteObjectMessage(boost::shared_ptr<SmartFox> sfs)
{
	// No room was passed, let's use the last joined one
	if (room == NULL) 
		room = sfs->LastJoinedRoom();

	// Populate a recipient list, no duplicates allowed
	boost::shared_ptr<vector<boost::shared_ptr<long int> > > recipients (new vector<boost::shared_ptr<long int> >());

/*
			// Populate a recipient list, no duplicates allowed
			List<int> recipients = new List<int>();
			
			ICollection<User> potentialRecipients = recipient as ICollection<User>;
			if (potentialRecipients!=null) {
							
				// Check that recipient list is not bigger than the Room capacity 
				if (potentialRecipients.Count > room.Capacity) {
					throw new ArgumentException("The number of recipients is bigger than the target Room capacity: " + potentialRecipients.Count);
				}
					
				// Filter out potential wrong elements
				foreach (User uitem in potentialRecipients) {
					if (!recipients.Contains(uitem.Id)) { 
						recipients.Add(uitem.Id);
					}	
				}
				
			}
*/			

	boost::shared_ptr<long> valueId (new long());
	*valueId = room->Id();
	sfso->PutInt(KEY_ROOM_ID, valueId);
	sfso->PutSFSObject(KEY_XTRA_PARAMS, parameters);
			
	// Optional user list
	if (recipients->size() > 0) { 
		sfso->PutIntArray(KEY_RECIPIENT, recipients);
	}
	else
	{
		recipientUsersCollection->clear();
	}
}

}	// namespace Requests
}	// namespace Sfs2X


