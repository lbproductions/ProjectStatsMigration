#ifndef RULESCONTEXT_H
#define RULESCONTEXT_H

#include <LBDatabase/LBDatabase.h>

class Rule;

class RulesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE RulesContext(const ::LBDatabase::ContextMetaData &metaData, ::LBDatabase::Storage *parent);
	static const QString Name;

	Rule *rule(int id) const;
	QList<Rule *> rules() const;

	// Write anything you want to remain unchanged between these comments: 
	//START
	// END
};

#endif // RULESCONTEXT_H
