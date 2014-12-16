// ===================================================================
//
// Description		
//		Contains the implementation of CreateRoomRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "CreateRoomRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<string> CreateRoomRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> CreateRoomRequest::KEY_NAME (new string("n"));
boost::shared_ptr<string> CreateRoomRequest::KEY_PASSWORD (new string("p"));
boost::shared_ptr<string> CreateRoomRequest::KEY_GROUP_ID (new string("g"));
boost::shared_ptr<string> CreateRoomRequest::KEY_ISGAME (new string("ig"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MAXUSERS (new string("mu"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MAXSPECTATORS (new string("ms"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MAXVARS (new string("mv"));
boost::shared_ptr<string> CreateRoomRequest::KEY_ROOMVARS (new string("rv"));
boost::shared_ptr<string> CreateRoomRequest::KEY_PERMISSIONS (new string("pm"));
boost::shared_ptr<string> CreateRoomRequest::KEY_EVENTS (new string("ev"));
boost::shared_ptr<string> CreateRoomRequest::KEY_EXTID (new string("xn"));
boost::shared_ptr<string> CreateRoomRequest::KEY_EXTCLASS (new string("xc"));
boost::shared_ptr<string> CreateRoomRequest::KEY_EXTPROP (new string("xp"));
boost::shared_ptr<string> CreateRoomRequest::KEY_AUTOJOIN (new string("aj"));
boost::shared_ptr<string> CreateRoomRequest::KEY_ROOM_TO_LEAVE (new string("rl"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_DEFAULT_AOI (new string("maoi"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_MAP_LOW_LIMIT (new string("mllm"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_MAP_HIGH_LIMIT (new string("mlhm"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_USER_MAX_LIMBO_SECONDS (new string("muls"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_PROXIMITY_UPDATE_MILLIS (new string("mpum"));
boost::shared_ptr<string> CreateRoomRequest::KEY_MMO_SEND_ENTRY_POINT (new string("msep"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
CreateRoomRequest::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin, boost::shared_ptr<Room> roomToLeave)
	: BaseRequest (RequestType_CreateRoom)
{
	Init(settings, autoJoin, roomToLeave);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
CreateRoomRequest::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin)
	: BaseRequest (RequestType_CreateRoom)
{
	Init(settings, autoJoin, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
CreateRoomRequest::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings)
	: BaseRequest (RequestType_CreateRoom)
{
	Init(settings, false, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
CreateRoomRequest::~CreateRoomRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void CreateRoomRequest::Init(boost::shared_ptr<RoomSettings> settings, bool autoJoin, boost::shared_ptr<Room> roomToLeave)
{
	this->settings = settings;
	this->autoJoin = autoJoin;
	this->roomToLeave = roomToLeave;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void CreateRoomRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());

	if (settings->Name()->empty()  || settings->Name()->size() == 0)
		errors->push_back("Missing room name");
				
	if (settings->MaxUsers() <= 0)
		errors->push_back("maxUsers must be > 0");
			
	if (settings->Extension() != NULL)	{
		if (settings->Extension()->ClassName() == NULL || settings->Extension()->ClassName()->empty() || settings->Extension()->ClassName()->size() == 0)
			errors->push_back("Missing Extension class name");
					
		if (settings->Extension()->Id() == NULL || settings->Extension()->Id()->empty() || settings->Extension()->Id()->size() == 0)
			errors->push_back("Missing Extension id");
	}

	if (dynamic_cast<MMORoomSettings*>(settings.get()) != NULL)
	{
		boost::shared_ptr<MMORoomSettings> mmoSettings = (boost::static_pointer_cast<MMORoomSettings>(settings));

		if (mmoSettings->DefaultAOI() == NULL)
			errors->push_back("Missing default AOI (area of interest)");

		if (mmoSettings->MapLimits() != NULL && (mmoSettings->MapLimits()->LowerLimit() == NULL || mmoSettings->MapLimits()->HigherLimit() == NULL))
			errors->push_back("Map limits must be both defined");
	}	

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("CreateRoom request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void CreateRoomRequest::Execute (boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutUtfString(KEY_NAME, settings->Name());
	sfso->PutUtfString(KEY_GROUP_ID, settings->GroupId());
	sfso->PutUtfString(KEY_PASSWORD, settings->Password());

	boost::shared_ptr<bool> valueIsGame (new bool());
	*valueIsGame = settings->IsGame();
	sfso->PutBool(KEY_ISGAME, valueIsGame);
	
	boost::shared_ptr<short int> valueMaxUsers (new short int());
	*valueMaxUsers = settings->MaxUsers();
	sfso->PutShort(KEY_MAXUSERS, valueMaxUsers); 

	boost::shared_ptr<short int> valueMaxSpectators (new short int());
	*valueMaxSpectators = settings->MaxSpectators();
	sfso->PutShort(KEY_MAXSPECTATORS, valueMaxSpectators); 

	boost::shared_ptr<short int> valueMaxVariables (new short int());
	*valueMaxVariables = settings->MaxVariables();
	sfso->PutShort(KEY_MAXVARS, valueMaxVariables);
			
	// Handle Room Variables
	if (settings->Variables() != NULL && settings->Variables()->size() > 0)
	{
		boost::shared_ptr<ISFSArray> roomVars = SFSArray::NewInstance();
	
		vector<boost::shared_ptr<RoomVariable> >::iterator iterator;
		for (iterator = settings->Variables()->begin(); iterator != settings->Variables()->end(); iterator++)
		{
			boost::shared_ptr<RoomVariable> item = (*iterator);
			roomVars->AddSFSArray(item->ToSFSArray());
		}
				
		sfso->PutSFSArray(KEY_ROOMVARS, roomVars);
	}
			
	// Handle Permissions	
	if (settings->Permissions() != NULL)
	{
		boost::shared_ptr<vector<boost::shared_ptr<bool> > > sfsPermissions (new vector<boost::shared_ptr<bool> >());

		boost::shared_ptr<bool> valueAllowNameChange (new bool());
		*valueAllowNameChange = settings->Permissions()->AllowNameChange();
		sfsPermissions->push_back(valueAllowNameChange);

		boost::shared_ptr<bool> valueAllowPasswordStateChange (new bool());
		*valueAllowPasswordStateChange = settings->Permissions()->AllowPasswordStateChange();
		sfsPermissions->push_back(valueAllowPasswordStateChange);

		boost::shared_ptr<bool> valueAllowPublicMessages (new bool());
		*valueAllowPublicMessages = settings->Permissions()->AllowPublicMessages();
		sfsPermissions->push_back(valueAllowPublicMessages);

		boost::shared_ptr<bool> valueAllowResizing (new bool());
		*valueAllowResizing = settings->Permissions()->AllowResizing();
		sfsPermissions->push_back(valueAllowResizing);
				
		sfso->PutBoolArray(KEY_PERMISSIONS, sfsPermissions);
	}
				
	// Handle Events
	if (settings->Events() != NULL)
	{
		boost::shared_ptr<vector<boost::shared_ptr<bool> > > sfsEvents (new vector<boost::shared_ptr<bool> >());

		boost::shared_ptr<bool> valueAllowUserEnter (new bool());
		*valueAllowUserEnter = settings->Events()->AllowUserEnter();
		sfsEvents->push_back(valueAllowUserEnter);

		boost::shared_ptr<bool> valueAllowUserExit (new bool());
		*valueAllowUserExit = settings->Events()->AllowUserExit();
		sfsEvents->push_back(valueAllowUserExit);

		boost::shared_ptr<bool> valueAllowUserCountChange (new bool());
		*valueAllowUserCountChange = settings->Events()->AllowUserCountChange();
		sfsEvents->push_back(valueAllowUserCountChange);

		boost::shared_ptr<bool> valueAllowUserVariablesUpdate (new bool());
		*valueAllowUserVariablesUpdate = settings->Events()->AllowUserVariablesUpdate();
		sfsEvents->push_back(valueAllowUserVariablesUpdate);
				
		sfso->PutBoolArray(KEY_EVENTS, sfsEvents);
	}
			
	// Handle Extension data
	if (settings->Extension() != NULL)
	{
		boost::shared_ptr<string> id (new string(*(settings->Extension()->Id())));
		sfso->PutUtfString(KEY_EXTID, id);

		boost::shared_ptr<string> name (new string(*(settings->Extension()->ClassName())));
		sfso->PutUtfString(KEY_EXTCLASS, name);
				
		// Send the properties file only if was specified
		if (settings->Extension()->PropertiesFile() != NULL && !settings->Extension()->PropertiesFile()->empty() && settings->Extension()->PropertiesFile()->size() > 0)
		{
			boost::shared_ptr<string> properties (new string(*(settings->Extension()->PropertiesFile())));
			sfso->PutUtfString(KEY_EXTPROP, properties);
		}
	}
			
	//--- MMO Rooms ------------------------------------------------------------------------
	if (dynamic_cast<MMORoomSettings*>(settings.get()) != NULL)
	{
		boost::shared_ptr<MMORoomSettings> mmoSettings = (boost::static_pointer_cast<MMORoomSettings>(settings));
		bool useFloats = mmoSettings->DefaultAOI()->IsFloat();
				
		if (useFloats)
		{
			boost::shared_ptr<vector<float> > defaultAOI = mmoSettings->DefaultAOI()->ToFloatArray();
			boost::shared_ptr<vector<boost::shared_ptr<float> > > defaultAOIReallocated (new vector<boost::shared_ptr<float> >());

			vector<float>::iterator itDefaultAOI;
			for (itDefaultAOI = defaultAOI->begin(); itDefaultAOI != defaultAOI->end(); itDefaultAOI++)
			{
				boost::shared_ptr<float> valueDefaultAOI (new float());
				*valueDefaultAOI = (*itDefaultAOI);
				defaultAOIReallocated->push_back(valueDefaultAOI);
			}

			sfso->PutFloatArray(KEY_MMO_DEFAULT_AOI, defaultAOIReallocated);

			if (mmoSettings->MapLimits() != NULL)
			{
				boost::shared_ptr<vector<float> > lowerLimit = mmoSettings->MapLimits()->LowerLimit()->ToFloatArray();
				boost::shared_ptr<vector<boost::shared_ptr<float> > > lowerLimitReallocated (new vector<boost::shared_ptr<float> >());

				vector<float>::iterator itLowerLimit;
				for (itLowerLimit = lowerLimit->begin(); itLowerLimit != lowerLimit->end(); itLowerLimit++)
				{
					boost::shared_ptr<float> valueLowerLimit (new float());
					*valueLowerLimit = (*itLowerLimit);
					lowerLimitReallocated->push_back(valueLowerLimit);
				}

				sfso->PutFloatArray(KEY_MMO_MAP_LOW_LIMIT, lowerLimitReallocated);

				/* ------------------------ */

				boost::shared_ptr<vector<float> > higherLimit = mmoSettings->MapLimits()->HigherLimit()->ToFloatArray();
				boost::shared_ptr<vector<boost::shared_ptr<float> > > higherLimitReallocated (new vector<boost::shared_ptr<float> >());

				vector<float>::iterator itHigherLimit;
				for (itHigherLimit = higherLimit->begin(); itHigherLimit != higherLimit->end(); itHigherLimit++)
				{
					boost::shared_ptr<float> valueHigherLimit (new float());
					*valueHigherLimit = (*itHigherLimit);
					higherLimitReallocated->push_back(valueHigherLimit);
				}

				sfso->PutFloatArray(KEY_MMO_MAP_HIGH_LIMIT, higherLimitReallocated);
			}
		}
		else
		{
			boost::shared_ptr<vector<long int> > defaultAOI = mmoSettings->DefaultAOI()->ToIntArray();
			boost::shared_ptr<vector<boost::shared_ptr<long int> > > defaultAOIReallocated (new vector<boost::shared_ptr<long int> >());

			vector<long int>::iterator itDefaultAOI;
			for (itDefaultAOI = defaultAOI->begin(); itDefaultAOI != defaultAOI->end(); itDefaultAOI++)
			{
				boost::shared_ptr<long int> valueDefaultAOI (new long int());
				*valueDefaultAOI = (*itDefaultAOI);
				defaultAOIReallocated->push_back(valueDefaultAOI);
			}

			sfso->PutIntArray(KEY_MMO_DEFAULT_AOI, defaultAOIReallocated);

			if (mmoSettings->MapLimits() != NULL)
			{
				boost::shared_ptr<vector<long int> > lowerLimit = mmoSettings->MapLimits()->LowerLimit()->ToIntArray();
				boost::shared_ptr<vector<boost::shared_ptr<long int> > > lowerLimitReallocated (new vector<boost::shared_ptr<long int> >());

				vector<long int>::iterator itLowerLimit;
				for (itLowerLimit = lowerLimit->begin(); itLowerLimit != lowerLimit->end(); itLowerLimit++)
				{
					boost::shared_ptr<long int> valueLowerLimit (new long int());
					*valueLowerLimit = (*itLowerLimit);
					lowerLimitReallocated->push_back(valueLowerLimit);
				}

				sfso->PutIntArray(KEY_MMO_MAP_LOW_LIMIT, lowerLimitReallocated);

				/* ------------------------ */

				boost::shared_ptr<vector<long int> > higherLimit = mmoSettings->MapLimits()->HigherLimit()->ToIntArray();
				boost::shared_ptr<vector<boost::shared_ptr<long int> > > higherLimitReallocated (new vector<boost::shared_ptr<long int> >());

				vector<long int>::iterator itHigherLimit;
				for (itHigherLimit = higherLimit->begin(); itHigherLimit != higherLimit->end(); itHigherLimit++)
				{
					boost::shared_ptr<long int> valueHigherLimit (new long int());
					*valueHigherLimit = (*itHigherLimit);
					higherLimitReallocated->push_back(valueHigherLimit);
				}

				sfso->PutIntArray(KEY_MMO_MAP_HIGH_LIMIT, higherLimitReallocated);
			}
		}

		boost::shared_ptr<short> valueUserMaxLimboSeconds (new short());
		*valueUserMaxLimboSeconds = (short)mmoSettings->UserMaxLimboSeconds();
		sfso->PutShort(KEY_MMO_USER_MAX_LIMBO_SECONDS, valueUserMaxLimboSeconds);

		boost::shared_ptr<short> valueProximityListUpdateMillis (new short());
		*valueProximityListUpdateMillis = (short)mmoSettings->ProximityListUpdateMillis();
		sfso->PutShort(KEY_MMO_PROXIMITY_UPDATE_MILLIS, valueProximityListUpdateMillis);

		boost::shared_ptr<bool> valueSendAOIEntryPoint (new bool());
		*valueSendAOIEntryPoint = mmoSettings->SendAOIEntryPoint();
		sfso->PutBool(KEY_MMO_SEND_ENTRY_POINT, valueSendAOIEntryPoint);
	}

	// AutoJoin
	boost::shared_ptr<bool> valueAutoJoin (new bool());
	*valueAutoJoin = autoJoin;
	sfso->PutBool(KEY_AUTOJOIN, valueAutoJoin);
			
	// Room to leave
	if (roomToLeave != NULL)
	{
		boost::shared_ptr<long> valueId (new long());
		*valueId = roomToLeave->Id();
		sfso->PutInt(KEY_ROOM_TO_LEAVE, valueId);
	}
}

}	// namespace Requests
}	// namespace Sfs2X

