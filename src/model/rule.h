#ifndef RULE_H
#define RULE_H

#include <LBDatabase/LBDatabase.h>


namespace RuleProperties {
const QString AttributeNameAttribute("attributeName");
const QString ConstraintIdAttribute("constraintId");
const QString ParameterAttribute("parameter");
const QString ParentRuleIdAttribute("parentRuleId");
const QString TypeAttribute("type");
} // namespace RuleProperties


class Rule : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Rule(const ::LBDatabase::EntityMetaData &metaData, ::LBDatabase::Context *context);
	static const QString Name;
	static const int EntityTypeId;

	QString displayName() const;

	QString attributeName() const;
	int constraintId() const;
	QString parameter() const;
	int parentRuleId() const;
	int type() const;





	// Write anything you want to remain unchanged between these comments: 
	//START
	// END

signals:
};

Q_DECLARE_METATYPE(QList<Rule *>)

#endif // RULE_H
