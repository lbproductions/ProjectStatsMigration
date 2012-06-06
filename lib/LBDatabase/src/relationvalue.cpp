#ifndef LBDATABASE_RELATIONVALUE_CPP
#define LBDATABASE_RELATIONVALUE_CPP

#include "relationvalue.h"

namespace LBDatabase {

template<class EntityClass, class SortType>
class FunctionSorter;

template<class EntityClass>
RelationValue<EntityClass>::RelationValue(Relation *relation, Entity *parent) :
    RelationValueBase(relation, parent)
{
}

template<class EntityClass>
template<typename SortType>
QList<EntityClass *> RelationValue<EntityClass>::sort(FunctionValue *sortFunction, SortingDirection dir)
{
    if(otherEntities.contains(sortFunction))
        return otherEntities.value(sortFunction);


    QList<EntityClass *> list = otherEntities.value(0);

    qSort(list.begin(), list.end(), FunctionSorter<EntityClass, SortType>(sortFunction, dir));

    otherEntities.insert(sortFunction, list);
    return list;
}

template<class EntityClass>
template<typename SortType>
QList<EntityClass *> RelationValue<EntityClass>::sort(const QString &sortAttributeName, SortingDirection dir)
{
    if(otherEntitiesSortedByAttribute.contains(sortAttributeName))
        return otherEntitiesSortedByAttribute.value(sortAttributeName);

    QList<EntityClass *> list = otherEntities.value(0);

    qSort(list.begin(), list.end(), FunctionSorter<EntityClass, SortType>(sortAttributeName, dir));

    otherEntitiesSortedByAttribute.insert(sortAttributeName, list);
    return list;
}

template<class EntityClass>
QVariant RelationValue<EntityClass>::dataForModel(int role) const
{
    if(role == Qt::DisplayRole) {
        if(otherEntities.value(0).isEmpty())
            return QVariant();

        if(otherEntities.value(0).size() == 1)
            return static_cast<Entity *>(otherEntities.value(0).at(0))->displayName();

        return QVariant(QString::number(entities().size())+QLatin1String(" ")+otherEntities.value(0).at(0)->entityType()->displayNamePlural());
    }
    else if(role == PropertyValue::PlainDataRole) {
        return QVariant::fromValue<QList<EntityClass *> >(otherEntities.value(0));
    }

    return QVariant();
}

template<class EntityClass>
QList<EntityClass *> RelationValue<EntityClass>::entities() const
{
    return otherEntities.value(0);
}

template<class EntityClass>
EntityClass *RelationValue<EntityClass>::firstEntity() const
{
    if(otherEntities.value(0).isEmpty())
        return 0;

    return otherEntities.value(0).first();
}

template<class EntityClass>
void RelationValue<EntityClass>::addEntity(EntityClass *entity)
{
    if(!relation()->isEditable() || relation()->isTranspose())
        return;

    RelationValueData data;
    data.rowId = rowIds.value(entity,0);
    data.leftId = this->entity()->id();
    data.rightId = entity->id();

    int id = relation()->storage()->driver()->addRelatedEntity(this, data);

    addOtherEntity(entity, id);
    emit changed();
}

template<class EntityClass>
void RelationValue<EntityClass>::addOtherEntity(Entity *entity, int rowId)
{
    QList<EntityClass *> entities = otherEntities.value(0);
    EntityClass *entityCasted = static_cast<EntityClass *>(entity);
    if(!entities.contains(entityCasted)) {
        entities.append(entityCasted);
        otherEntities.insert(0, entities);
        rowIds.insert(entityCasted, rowId);
    }
}

template<class EntityClass, class SortType>
class FunctionSorter
{
public:

    FunctionSorter(FunctionValue *value, SortingDirection dir) : m_sortFunction(value),m_sortAttributeName(QString()), m_dir(dir) {}
    FunctionSorter(const QString &attributeName, SortingDirection dir) : m_sortFunction(0), m_sortAttributeName(attributeName), m_dir(dir) {}

    bool operator()(const EntityClass *left, const EntityClass *right) const
    {
        QVariant leftVariant;
        QVariant rightVariant;
        if(m_sortFunction) {
            leftVariant = m_sortFunction->value(left);
            rightVariant = m_sortFunction->value(right);
        }
        else if(!m_sortAttributeName.isEmpty()) {
            leftVariant = left->value(m_sortAttributeName);
            rightVariant = right->value(m_sortAttributeName);
        }

        SortType leftValue = leftVariant.value<SortType>();
        SortType rightValue = rightVariant.value<SortType>();
        if(m_dir == SortAscending) {
            return rightValue > leftValue;
        }
        else {
            return rightValue < leftValue;
        }
    }

    FunctionValue *m_sortFunction;
    QString m_sortAttributeName;
    SortingDirection m_dir;
};

}

#endif // LBDATABASE_RELATIONVALUE_CPP
