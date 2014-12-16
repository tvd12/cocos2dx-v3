// ===================================================================
//
// Description		
//		Contains the implementation of SFSRoomVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSRoomVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<RoomVariable> SFSRoomVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<RoomVariable> roomVariable (new SFSRoomVariable (
		*(sfsa->GetUtfString(0)), 	// name
		sfsa->GetElementAt(2),		// typed value
		sfsa->GetByte(1)			// type id
	));
	
	roomVariable->IsPrivate(sfsa->GetBool(3)); // Private
	roomVariable->IsPersistent(sfsa->GetBool(4)); // Persistent					
			
	return roomVariable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<void> val)
	: SFSUserVariable(name, val, -1)
{
	isPersistent = false;
	isPrivate = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<void> val, long int type)
	: SFSUserVariable(name, val, type)
{
	isPersistent = false;
	isPrivate = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSRoomVariable::~SFSRoomVariable()
{
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
bool SFSRoomVariable::IsPrivate()
{
	return isPrivate;
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
void SFSRoomVariable::IsPrivate(bool value)
{
	isPrivate = value;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
bool SFSRoomVariable::IsPersistent()
{
	return isPersistent;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
void SFSRoomVariable::IsPersistent(bool value)
{
	isPersistent = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::ToString()
{
	char buffer[512];

	switch (type)
	{
	case VARIABLETYPE_UNKNOWN:
		sprintf (buffer, "[RVar: %s, type: %d, value: Unknown, isPriv: %d]", name->c_str(), type, isPrivate);
		break;

	case VARIABLETYPE_NULL:
		sprintf (buffer, "[RVar: %s, type: %d, value: NULL, isPriv: %d]", name->c_str(), type, isPrivate);
		break;

	case VARIABLETYPE_BOOL:
		sprintf (buffer, "[RVar: %s, type: %d, value: %d, isPriv: %d]", name->c_str(), type, *(boost::static_pointer_cast<bool>(val)), isPrivate);
		break;

	case VARIABLETYPE_INT:
		sprintf (buffer, "[RVar: %s, type: %d, value: %d, isPriv: %d]", name->c_str(), type, *(boost::static_pointer_cast<long int>(val)), isPrivate);
		break;

	case VARIABLETYPE_DOUBLE:
		sprintf (buffer, "[RVar: %s, type: %d, value: %d, isPriv: %d]", name->c_str(), type, *(boost::static_pointer_cast<double>(val)), isPrivate);
		break;

	case VARIABLETYPE_STRING:
		sprintf (buffer, "[RVar: %s, type: %d, value: %s, isPriv: %d]", name->c_str(), type, (boost::static_pointer_cast<string>(val))->c_str(), isPrivate);
		break;

	case VARIABLETYPE_OBJECT:
		sprintf (buffer, "[RVar: %s, type: %d, value: object, isPriv: %d]", name->c_str(), type, isPrivate);
		break;

	case VARIABLETYPE_ARRAY:
		sprintf (buffer, "[RVar: %s, type: %d, value: array, isPriv: %d]", name->c_str(), type, isPrivate);
		break;
	}

	boost::shared_ptr<string> returned (new string(buffer));

	return returned;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSRoomVariable::ToSFSArray()
{
	boost::shared_ptr<ISFSArray> arr = SFSUserVariable::ToSFSArray();
			
	// isPrivate (3)
	boost::shared_ptr<bool> valueIsPrivate (new bool());
	*valueIsPrivate = isPrivate;
	arr->AddBool(valueIsPrivate);
			
	// isPersistent (4)
	boost::shared_ptr<bool> valueIsPersistent (new bool());
	*valueIsPersistent = isPersistent;
	arr->AddBool(valueIsPersistent);
			
	return arr;
}

// -----
// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::Name()
{
	return name;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSRoomVariable::Type()
{
	return type;
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSRoomVariable::Value()
{
	return val;
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSRoomVariable::GetBoolValue()
{
	return (boost::static_pointer_cast<bool>)(val);
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSRoomVariable::GetIntValue()
{
	return (boost::static_pointer_cast<long int>)(val);
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSRoomVariable::GetDoubleValue()
{
	return (boost::static_pointer_cast<double>)(val);
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::GetStringValue()
{
	return (boost::static_pointer_cast<string>)(val);
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSRoomVariable::GetSFSObjectValue()
{
	return (boost::static_pointer_cast<ISFSObject>)(val);
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSRoomVariable::GetSFSArrayValue()
{
	return (boost::static_pointer_cast<ISFSArray>)(val);
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSRoomVariable::IsNull()
{
	return type == VARIABLETYPE_NULL;
}

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

