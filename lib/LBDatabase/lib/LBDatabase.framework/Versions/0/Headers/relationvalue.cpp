#ifndef LBDATABASE_RELATIONVALUE_CPP
#define LBDATABASE_RELATIONVALUE_CPP

#include "relationvalue.h"

#include <QMetaMethod>

namespace LBDatabase {

template<class EntityClass, class SortType>
class FunctionSorter;

template<class EntityClass>
RelationValue<EntityClass>::RelationValue(Relation *relation, Entity *parent) :
    RelationValueBase(relation, parent)
{
    if(relation->isCalculated()) {
        int i = metaObject()->indexOfMethod("changed()");
        if(i < 0)
            return;
        QMetaMethod changedSignal = metaObject()->method(i);
<<<<<<< HEAD
        i = parent->metaObject()->indexOfMethod(QString(relation->identifier() + "Changed()").toAscii());
=======
        i = parent->metaObject()->indexOfMethod(relation->signalSignature().toAscii());
>>>>>>> refs/heads/uncommited
        if(i < 0)
            return;
        QMetaMethod trueSignal = parent->metaObject()->method(i);
        QObject::connect(this, changedSignal, parent, trueSignal);
    }
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
    QList<EntityClass *> e = entities();

    if(role == Qt::DisplayRole) {
        if(e.isEmpty())
            return QVariant();

        if(e.size() == 1)
            return static_cast<Entity *>(e.at(0))->displayName();

        return QVariant(QString::number(e.size())+QLatin1String(" ")+e.at(0)->entityType()->displayNamePlural());
    }
    else if(role == PropertyValue::PlainDataRole) {
        return QVariant::fromValue<QList<EntityClass *> >(e);
    }

    return QVariant();
}

template<class EntityClass>
QVariant RelationValue<EntityClass>::value() const
{
    return dataForModel(PropertyValue::PlainDataRole);
}

template<class EntityClass>
QList<EntityClass *> RelationValue<EntityClass>::entities() const
{
    return otherEntities.value(0);
}

template<class EntityClass>
EntityClass *RelationValue<EntityClass>::firstEntity() const
{
    QList<EntityClass *> e = entities();
    if(e.isEmpty())
        return 0;

    return e.first();
}

template<class EntityClass>
void RelationValue<EntityClass>::addEntity(EntityClass *entity)
{
    if((relation()->transposeRelation()->isEditableTranspose() || relation()->isEditable()) && !relation()->isTranspose()) {
        RelationValueData data;
        data.rowId = rowIds.value(entity,0);
        data.leftId = this->entity()->id();
        data.rightId = entity->id();

        int id = relation()->storage()->driver()->addRelatedEntity(this, data);

        addOtherEntityWhileStartup(entity, id);

        RelationValueBase *rightValue = static_cast<RelationValueBase *>(entity->propertyValue(relation()->transposeRelation()));
        if(rightValue)
            addOtherEntityTo(rightValue, this->entity(), data.rowId);

        emit entityAdded(entity);
        emit changed();
    }
    else if(relation()->isEditableTranspose() && relation()->isTranspose()) {
        RelationValue<Entity> *transpose = static_cast<RelationValue<Entity> *>(entity->propertyValue(relation()->transposeRelation()));
        transpose->addEntity(this->entity());
        emit entityAdded(entity);
        emit changed();
    }
}
template<class EntityClass>
int RelationValue<EntityClass>::rowId(EntityClass *entity) const
{
    return rowIds.value(entity, 0);
}

template<class EntityClass>
void RelationValue<EntityClass>::addOtherEntityWhileStartup(Entity *entity, int rowId)
{
    QList<EntityClass *> entities = otherEntities.value(0);
    EntityClass *entityCasted = static_cast<EntityClass *>(entity);
    if(!entities.contains(entityCasted)) {
        entities.append(entityCasted);
        otherEntities.insert(0, entities);
        rowIds.insert(entityCasted, rowId);
        otherEntitiesSortedByAttribute.clear();
    }
}

template<class EntityClass>
void RelationValue<EntityClass>::addOtherEntity(Entity *entity)
{
    addOtherEntityWhileStartup(entity, 0);
}

template<class EntityClass>
void RelationValue<EntityClass>::removeOtherEntity(Entity *e)
{
    if(!relation()->isTranspose())
        return; // this is used by non-transpose relations when recalculating
                // therefore it should only be called upon transpose relations

    EntityClass *entity = static_cast<EntityClass *>(e);
    QList<EntityClass *> entities = otherEntities.value(0);
    if(!entities.contains(entity))
        return;

    otherEntities.clear();
    entities.removeAll(entity);
    otherEntities.insert(0, entities);
    otherEntitiesSortedByAttribute.clear();
    emit changed();
}

template<class EntityClass>
void RelationValue<EntityClass>::recalculateAfterDependencyChange()
{
    if(!relation()->isCalculated() || relation()->isTranspose())
        return; // non-calculated and transpose relations must not be recalculated!

    QList<Entity *> rightEntities = calculate();

    Entity *e = entity();
    Relation *transpose = relation()->transposeRelation();

    foreach(EntityClass *rightEntity, entities()) {
        RelationValueBase *rightValue =
                static_cast<RelationValueBase *>(rightEntity->propertyValue(transpose));
        if(!rightEntities.contains(e))
            removeOtherEntityFrom(rightValue, e);
    }

    otherEntities.clear();

    foreach(Entity *rightEntity, rightEntities) {
        addOtherEntityWhileStartup(rightEntity, 0);
        RelationValueBase *rightValue =
                static_cast<RelationValueBase *>(rightEntity->propertyValue(transpose));
        if(rightValue)
            addOtherEntityTo(rightValue, e, 0);
    }

    emit changed();
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
