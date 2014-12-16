// ===================================================================
//
// Description		
//		Contains the implementation of MMOItemVariable
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItemVariable> MMOItemVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<IMMOItemVariable> variable (new MMOItemVariable (
		*(sfsa->GetUtfString(0)), 	// name
		sfsa->GetElementAt(2),		// typed value
		sfsa->GetByte(1)			// type id
	));
	
	return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<void> val, long int type)
	: SFSUserVariable(name, val, type)
{
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<void> val)
	: SFSUserVariable(name, val, -1)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMOItemVariable::~MMOItemVariable()
{
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> MMOItemVariable::Name()
{
	return SFSUserVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType MMOItemVariable::Type()
{
	return SFSUserVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> MMOItemVariable::Value()
{
	return SFSUserVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> MMOItemVariable::GetBoolValue()
{
	return SFSUserVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> MMOItemVariable::GetIntValue()
{
	return SFSUserVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> MMOItemVariable::GetDoubleValue()
{
	return SFSUserVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> MMOItemVariable::GetStringValue()
{
	return SFSUserVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> MMOItemVariable::GetSFSObjectValue()
{
	return SFSUserVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::GetSFSArrayValue()
{
	return SFSUserVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool MMOItemVariable::IsNull()
{
	return SFSUserVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::ToSFSArray()
{
	return SFSUserVariable::ToSFSArray();
}

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X
		
		
