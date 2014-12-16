// ===================================================================
//
// Description		
//		Contains the implementation of MatchExpression
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "MatchExpression.h"

namespace Sfs2X {
namespace Entities {
namespace Match {

// -------------------------------------------------------------------
// ChainedMatchExpression
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> value, MatchExpressionValueType valueType, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent)
{
	boost::shared_ptr<MatchExpression> matchingExpression (new MatchExpression(varName, condition, value, valueType));
	matchingExpression->logicOp = logicOp;
	matchingExpression->parent = parent;

	return matchingExpression;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MatchExpression::MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	this->varName = varName;
	this->condition = condition;
	this->varValue = varValue;
	this->valueType = valueType;
	this->logicOp = boost::shared_ptr<LogicOperator>();
	this->parent = boost::shared_ptr<MatchExpression>();
	this->next = boost::shared_ptr<MatchExpression>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MatchExpression::MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	this->varName = boost::shared_ptr<string>(new string(varName));
	this->condition = condition;
	this->varValue = varValue;
	this->valueType = valueType;
	this->logicOp = boost::shared_ptr<LogicOperator>();
	this->parent = boost::shared_ptr<MatchExpression>();
	this->next = boost::shared_ptr<MatchExpression>();
}

// -------------------------------------------------------------------
// And
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	this->next = ChainedMatchExpression(varName, condition, varValue, valueType, LogicOperator::AND, shared_from_this());
	return this->next;
}

// -------------------------------------------------------------------
// And
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	boost::shared_ptr<string> refVarName (new string(varName));
	this->next = ChainedMatchExpression(refVarName, condition, varValue, valueType, LogicOperator::AND, shared_from_this());
	return this->next;
}

// -------------------------------------------------------------------
// Or
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	this->next = ChainedMatchExpression(varName, condition, varValue, valueType, LogicOperator::OR, shared_from_this());
	return this->next;
}

// -------------------------------------------------------------------
// Or
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<void> varValue, MatchExpressionValueType valueType)
{
	boost::shared_ptr<string> refVarName (new string(varName));
	this->next = ChainedMatchExpression(refVarName, condition, varValue, valueType, LogicOperator::OR, shared_from_this());
	return this->next;
}

// -------------------------------------------------------------------
// VarName
// -------------------------------------------------------------------
boost::shared_ptr<string> MatchExpression::VarName()
{
	return this->varName;
}

// -------------------------------------------------------------------
// Condition
// -------------------------------------------------------------------
boost::shared_ptr<IMatcher> MatchExpression::Condition()
{
	return this->condition;
}

// -------------------------------------------------------------------
// VarValue
// -------------------------------------------------------------------
boost::shared_ptr<void> MatchExpression::VarValue()
{
	return this->varValue;
}

// -------------------------------------------------------------------
// LogicOp
// -------------------------------------------------------------------
boost::shared_ptr<LogicOperator> MatchExpression::LogicOp()
{
	return this->logicOp;
}

// -------------------------------------------------------------------
// HasNext
// -------------------------------------------------------------------
bool MatchExpression::HasNext()
{
	return this->next != NULL;
}

// -------------------------------------------------------------------
// Next
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::Next()
{
	return this->next;
}

// -------------------------------------------------------------------
// Rewind
// -------------------------------------------------------------------
boost::shared_ptr<MatchExpression> MatchExpression::Rewind()
{
	boost::shared_ptr<MatchExpression> currNode = shared_from_this();

	while (true) {
		if (currNode->parent != NULL)
			currNode = currNode->parent;
		else
			break;
	}

	return currNode;
}

// -------------------------------------------------------------------
// AsString
// -------------------------------------------------------------------
boost::shared_ptr<string> MatchExpression::AsString()
{
	boost::shared_ptr<string> returned (new string());

	if (logicOp != NULL)
		returned->append(" " + *(logicOp->Id()) + " ");

	returned->append("(");

	if (valueType == MatchExpression_ValueString)
	{
		returned->append(*varName + " " + *(condition->Symbol()) + " " + "'" + *((string*)varValue.get()) + "'");
	}
	else
	{
		char bufferVarValue[512];
		sprintf (bufferVarValue, "%d", *(boost::static_pointer_cast<double>(varValue)));
		string stringVarValue = bufferVarValue;

		returned->append(*varName + " " + *(condition->Symbol()) + " " + stringVarValue);
	}

	returned->append(")");

	return returned;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> MatchExpression::ToString()
{
	boost::shared_ptr<MatchExpression> expr = Rewind();

	boost::shared_ptr<string> sb = expr->AsString();
			
	while (expr->HasNext()) {
		expr = expr->next;

		boost::shared_ptr<string> exprString = expr->AsString();
		sb->append(*exprString.get());
	}
			
	return sb;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MatchExpression::ToSFSArray()
{
	boost::shared_ptr<MatchExpression> expr = Rewind();
			
	// Start with the main expression
	boost::shared_ptr<ISFSArray> sfsa (new SFSArray());
	sfsa->AddSFSArray(expr->ExpressionAsSFSArray());
			
	// continue with other linked expressions, if any
	while (expr->HasNext()) {
		expr = expr->Next();
		sfsa->AddSFSArray(expr->ExpressionAsSFSArray());
	}
			
	return sfsa;
}

// -------------------------------------------------------------------
// ExpressionAsSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MatchExpression::ExpressionAsSFSArray()
{
	boost::shared_ptr<ISFSArray> expr (new SFSArray());

	// 0 -> Logic operator
	if (logicOp.get() != NULL)
		expr->AddUtfString(logicOp->Id());
	else
		expr->AddNull();

	// 1 -> Var name
	expr->AddUtfString(varName);

	// 2 -> Matcher type
	boost::shared_ptr<unsigned char> ptrType (new unsigned char());
	*ptrType = (unsigned char)condition->Type();
	expr->AddByte(ptrType);

	// 3 -> Condition symbol
	expr->AddUtfString(condition->Symbol());

	// 4 -> Value to match against
	if (condition->Type() == 0)
		expr->AddBool((boost::static_pointer_cast<bool>)(varValue));

	else if (condition->Type() == 1)
		expr->AddDouble((boost::static_pointer_cast<double>)(varValue));

	else
		expr->AddUtfString((boost::static_pointer_cast<string>)(varValue));

	return expr;
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


