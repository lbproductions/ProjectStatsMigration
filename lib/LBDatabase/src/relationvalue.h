#ifndef LBDATABASE_RELATIONVALUE_H
#define LBDATABASE_RELATIONVALUE_H

#include "relationvaluebase.h"

#include "storage.h"
#include "context.h"
#include "functionvalue.h"
#include "entity.h"
#include "storagedriver.h"

#include <QVariant>
#include <QDebug>

namespace LBDatabase {

class Relation;
class Entity;
class Attribute;

enum SortingDirection {
    SortAscending,
    SortDescending
};

class RelationValueData
{
public:
    int rowId;
    int leftId;
    int rightId;
};

template<class EntityClass>
class RelationValue : public RelationValueBase
{
public:
    RelationValue(Relation *relation, Entity *parent);

    QVariant dataForModel(int role) const;
    QVariant value() const;

    EntityClass *firstEntity() const;
    QList<EntityClass *> entities() const;
    void addEntity(EntityClass *entity);

    template<typename SortType>
    QList<EntityClass *> sort(FunctionValue *sortFunction, SortingDirection dir = SortAscending);
    template<typename SortType>
    QList<EntityClass *> sort(const QString &sortAttributeName, SortingDirection dir = SortAscending);

private:
    friend class ContextPrivate;

    void addOtherEntityWhileStartup(Entity *entity, int rowId);
    void addOtherEntity(Entity *entity);
    void removeOtherEntity(Entity *entity);
    void recalculateAfterDependencyChange();

    QHash<EntityClass *, int> rowIds;
    QHash<FunctionValue *, QList<EntityClass *> > otherEntities;
    QHash<QString, QList<EntityClass *> > otherEntitiesSortedByAttribute;
};

} // namespace LBDatabase

#include "relationvalue.cpp"

#endif // LBDATABASE_RELATIONVALUE_H
