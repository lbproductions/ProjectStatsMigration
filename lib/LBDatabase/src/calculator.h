#ifndef LBDATABASE_CALCULATOR_H
#define LBDATABASE_CALCULATOR_H

#include <QObject>

#include <QHash>

namespace LBDatabase {

class AttributeValue;
class Entity;
class FunctionValue;
class RelationValueBase;


class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    
    QVariant calculate(const Entity *entity, AttributeValue *attributeValue); // AttributeValue
    QHash<const Entity *, QVariant> calculate(const Entity *entity, const FunctionValue *functionValue); // FunctionValue
    QList<Entity *> calculate(const Entity *entity, const RelationValueBase *relationValue); // FunctionValue
};

} // namespace LBDatabase

typedef QHash<const LBDatabase::Entity *, QVariant> EntityVariantHash;
typedef QList<LBDatabase::Entity *> RelatedEntities;

#endif // LBDATABASE_CALCULATOR_H
