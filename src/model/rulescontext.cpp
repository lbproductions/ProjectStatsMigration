#include "rulescontext.h"

#include "rule.h"

const QString RulesContext::Name("Rules");
RulesContext::RulesContext(const ::LBDatabase::ContextMetaData &metaData, LBDatabase::Storage *parent) :
	LBDatabase::Context(metaData, parent)
{
	registerEntityClass<Rule>();
}

Rule *RulesContext::rule(int id) const
{
	return static_cast<Rule *>(entity(id));
}

QList<Rule*> RulesContext::rules() const
{
	QList<Rule *> rules;
	foreach(LBDatabase::Entity *entity, entities())
		rules.append(static_cast<Rule *>(entity));
	return rules;
}


	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
