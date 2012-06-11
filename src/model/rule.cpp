#include "rule.h"



const QString Rule::Name("rule");
const int Rule::EntityTypeId(19);

Rule::Rule(const ::LBDatabase::EntityMetaData &metaData, LBDatabase::Context *context) :
	Entity(metaData, context)
{
}

QString Rule::attributeName() const
{
	return value(RuleProperties::AttributeNameAttribute).value<QString>();
}

int Rule::constraintId() const
{
	return value(RuleProperties::ConstraintIdAttribute).value<int>();
}

QString Rule::parameter() const
{
	return value(RuleProperties::ParameterAttribute).value<QString>();
}

int Rule::parentRuleId() const
{
	return value(RuleProperties::ParentRuleIdAttribute).value<int>();
}

int Rule::type() const
{
	return value(RuleProperties::TypeAttribute).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Rule::displayName() const
{
	return Entity::displayName();
}

	// END

