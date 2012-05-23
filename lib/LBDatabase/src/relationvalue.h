#ifndef LBDATABASE_RELATIONVALUE_H
#define LBDATABASE_RELATIONVALUE_H

#include "propertyvalue.h"

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

class RelationValueBasePrivate;
class RelationValueBase : public PropertyValue
{
    Q_OBJECT
public:
    ~RelationValueBase();

    virtual Entity *entity() const;
    Property *property() const;
    Relation *relation() const;

    Entity *firstEntity() const;

    bool isEditable() const;
    virtual bool setData(const QVariant &data);
    QVariant data(int role = Qt::DisplayRole) const = 0;


protected:
    friend class RelationPrivate;

    explicit RelationValueBase(Relation *relation, Entity *parent);

    void fetchValue();
    QVariant calculate();
    virtual void addOtherEntity(Entity *entity, int rowId) = 0;

    QScopedPointer<RelationValueBasePrivate> d_ptr;
    Q_DECLARE_PRIVATE(RelationValueBase)
    Q_DISABLE_COPY(RelationValueBase)
};

template<class EntityClass, class SortType>
class FunctionSorter;

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
    template<typename SortType>
    QList<EntityClass *> sort(FunctionValue *sortFunction, SortingDirection dir = SortAscending)
    {
        if(otherEntities.contains(sortFunction))
            return otherEntities.value(sortFunction);


        QList<EntityClass *> list = otherEntities.value(0);

        qSort(list.begin(), list.end(), FunctionSorter<EntityClass, SortType>(sortFunction, dir));

        otherEntities.insert(sortFunction, list);
        return list;
    }

    template<typename SortType>
    QList<EntityClass *> sort(const QString &sortAttributeName, SortingDirection dir = SortAscending)
    {
        if(otherEntitiesSortedByAttribute.contains(sortAttributeName))
            return otherEntitiesSortedByAttribute.value(sortAttributeName);

        QList<EntityClass *> list = otherEntities.value(0);

        qSort(list.begin(), list.end(), FunctionSorter<EntityClass, SortType>(sortAttributeName, dir));

        otherEntitiesSortedByAttribute.insert(sortAttributeName, list);
        return list;
    }

    /*!
      Returns a QVariant, which represents the content of the relation in the given role.

      Currently this method supports only the Qt::DisplayRole.
      */
    QVariant data(int role) const
    {
        if(role == Qt::DisplayRole) {
            if(otherEntities.value(0).isEmpty())
                return QVariant();

            if(otherEntities.value(0).size() == 1)
                return static_cast<Entity *>(otherEntities.value(0).at(0))->displayName();

            return QVariant(QString::number(entities().size())+QLatin1String(" ")+otherEntities.value(0).at(0)->entityType()->displayNamePlural());
        }
        else if(role == PropertyValue::PlainDataRole) {
            return QVariant::fromValue<QList<Entity *> >(otherEntities.value(0));
        }

        return QVariant();
    }

    RelationValue(Relation *relation, Entity *parent) :
        RelationValueBase(relation, parent)
    {
    }

    QList<EntityClass *> entities() const
    {
        return otherEntities.value(0);
    }

    EntityClass *firstEntity() const
    {
        if(otherEntities.value(0).isEmpty())
            return 0;

        return otherEntities.value(0).first();
    }

    void addEntity(EntityClass *entity)
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

private:
    void addOtherEntity(Entity *entity, int rowId)
    {
        QList<EntityClass *> entities = otherEntities.value(0);
        EntityClass *entityCasted = static_cast<EntityClass *>(entity);
        if(!entities.contains(entityCasted)) {
            entities.append(entityCasted);
            otherEntities.insert(0, entities);
            rowIds.insert(entityCasted, rowId);
        }
    }

    QHash<EntityClass *, int> rowIds;
    QHash<FunctionValue *, QList<EntityClass *> > otherEntities;
    QHash<QString, QList<EntityClass *> > otherEntitiesSortedByAttribute;
};

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


} // namespace LBDatabase

Q_DECLARE_METATYPE(QList<LBDatabase::Entity *>)

#endif // LBDATABASE_RELATIONVALUE_H
