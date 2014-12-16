// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddyVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddyVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

boost::shared_ptr<string> SFSBuddyVariable::OFFLINE_PREFIX (new string("$")); 

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable> SFSBuddyVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<SFSBuddyVariable> variable (new SFSBuddyVariable(sfsa->GetUtfString(0), 	// name
													  sfsa->GetElementAt(2),	// typed value
													  sfsa->GetByte(1)			// type id
													  ));

	return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<void> val, long int type)
{
	this->name = boost::shared_ptr<string>(new string(name));
	this->val = val;
	this->type = (VariableType)type;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyVariable::SFSBuddyVariable(boost::shared_ptr<string> name, boost::shared_ptr<void> val, long int type)
{
	this->name = name;
	this->val = val;
	this->type = (VariableType)type;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSBuddyVariable::~SFSBuddyVariable()
{
}

// -------------------------------------------------------------------
// IsOffline
// -------------------------------------------------------------------
bool SFSBuddyVariable::IsOffline()
{
	return (name->find("$") == 0);
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::Name()
{
	return name;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSBuddyVariable::Type()
{
	return type;
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSBuddyVariable::Value()
{
	return val;
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSBuddyVariable::GetBoolValue()
{
	return (boost::static_pointer_cast<bool>)(val);
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSBuddyVariable::GetIntValue()
{
	return (boost::static_pointer_cast<long int>)(val);
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSBuddyVariable::GetDoubleValue()
{
	return (boost::static_pointer_cast<double>)(val);
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::GetStringValue()
{
	return (boost::static_pointer_cast<string>)(val);
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSBuddyVariable::GetSFSObjectValue()
{
	return (boost::static_pointer_cast<ISFSObject>)(val);
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSBuddyVariable::GetSFSArrayValue()
{
	return (boost::static_pointer_cast<ISFSArray>)(val);
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSBuddyVariable::IsNull()
{
	return type == VARIABLETYPE_NULL;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSBuddyVariable::ToSFSArray()
{
	boost::shared_ptr<ISFSArray> sfsa = SFSArray::NewInstance();
			
	// var name (0)
	sfsa->AddUtfString(name);

	// var type (1)
	boost::shared_ptr<unsigned char> ptrType (new unsigned char());
	*ptrType = type;
	sfsa->AddByte(ptrType);

	// var value (2)
	PopulateArrayWithValue(sfsa);

	return sfsa;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::ToString()
{
	char buffer[512];

	switch (type)
	{
	case VARIABLETYPE_UNKNOWN:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: Unknown]", name->c_str(), type);
		break;

	case VARIABLETYPE_NULL:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: NULL]", name->c_str(), type);
		break;

	case VARIABLETYPE_BOOL:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: %d]", name->c_str(), type, *(boost::static_pointer_cast<bool>(val)));
		break;

	case VARIABLETYPE_INT:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: %d]", name->c_str(), type, *(boost::static_pointer_cast<long int>(val)));
		break;

	case VARIABLETYPE_DOUBLE:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: %d]", name->c_str(), type, *(boost::static_pointer_cast<double>(val)));
		break;

	case VARIABLETYPE_STRING:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: %s]", name->c_str(), type, (boost::static_pointer_cast<string>(val))->c_str());
		break;

	case VARIABLETYPE_OBJECT:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: object]", name->c_str(), type);
		break;

	case VARIABLETYPE_ARRAY:
		sprintf (buffer, "[BuddyVar: %s, type: %d, value: array]", name->c_str(), type);
		break;
	}

	boost::shared_ptr<string> returned (new string(buffer));

	return returned;
}

// -------------------------------------------------------------------
// PopulateArrayWithValue
// -------------------------------------------------------------------
void SFSBuddyVariable::PopulateArrayWithValue(boost::shared_ptr<ISFSArray> arr)
{
	switch(type)
	{
	case VARIABLETYPE_NULL:
		arr->AddNull();
		break;

	case VARIABLETYPE_BOOL:
		arr->AddBool(GetBoolValue());
		break;

	case VARIABLETYPE_INT:
		arr->AddInt(GetIntValue());
		break;

	case VARIABLETYPE_DOUBLE:
		arr->AddDouble(GetDoubleValue());
		break;

	case VARIABLETYPE_STRING:
		arr->AddUtfString(GetStringValue());
		break;

	case VARIABLETYPE_OBJECT:
		arr->AddSFSObject(GetSFSObjectValue());
		break;

	case VARIABLETYPE_ARRAY:
		arr->AddSFSArray(GetSFSArrayValue());
		break;
	}

}

// -------------------------------------------------------------------
// SetValue
// -------------------------------------------------------------------
void SFSBuddyVariable::SetValue(boost::shared_ptr<void> val, VariableType type)
{
	this->val = val;

	if (val == NULL) {
		type = VARIABLETYPE_NULL;
	} else {
		this->type = type;
	}
}

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

