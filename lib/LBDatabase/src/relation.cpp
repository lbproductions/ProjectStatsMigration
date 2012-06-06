#include "relation.h"

#include "attribute.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "relationvalue.h"
#include "relationvaluebase_p.h"
#include "storage.h"
#include "storagedriver.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** RelationPrivate
*/
class RelationPrivate {
public:
    virtual ~RelationPrivate() {}

protected:
    RelationPrivate() :transposeRelation(0)
    {}

    friend class TransposeRelation;

    virtual void init();
    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    Storage *storage;
    bool transpose;

    RelationMetaData metaData;

    EntityType *entityType;
    EntityType *entityTypeOther;

    TransposeRelation *transposeRelation;

    Relation * q_ptr;
    Q_DECLARE_PUBLIC(Relation)
};

class TransposeRelationPrivate : public RelationPrivate
{
    TransposeRelationPrivate() {}
    void init();

    Q_DECLARE_PUBLIC(TransposeRelation)
};

void RelationPrivate::init()
{
    Q_Q(Relation);

    entityType = storage->entityType(metaData.entityTypeId);
    entityTypeOther = storage->entityType(metaData.entityTypeOtherId);
    transpose = false;

    if(metaData.direction == Relation::Both)
        transposeRelation = new TransposeRelation(q);

    entityType->addRelation(q);
    entityType->context()->addRelation(q);
}

void RelationPrivate::addPropertyValueToEntities()
{
    Q_Q(Relation);
    foreach(Entity *entity, entityType->entities()) {
        entity->addRelationValue(new RelationValue<Entity>(q, entity));
    }

    if(transposeRelation)
        transposeRelation->addPropertyValueToEntities();
}

void RelationPrivate::fetchValues()
{
    Q_Q(Relation);
    foreach(RelationValueData entities, storage->driver()->relatedEntities(q)) {
        Entity *leftEntity = entityType->context()->entity(entities.leftId);
        Entity *rightEntity = entityTypeOther->context()->entity(entities.rightId);

        if(!leftEntity || !rightEntity)
            continue;

        RelationValueBase *leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
        if(leftValue)
            leftValue->addOtherEntity(rightEntity, entities.rowId);

        RelationValueBase *rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(transposeRelation));
        if(rightValue)
            rightValue->addOtherEntity(leftEntity, entities.rowId);
    }
}

void RelationPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Relation);
    entity->addRelationValue(new RelationValue<Entity>(q, entity));
}

/******************************************************************************
** Relation
*/
/*!
  \class Relation
  \brief The Relation class represents a description of a relation between two
  EntityTypes.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var Relation::d_ptr
  \internal
  */

/*!
  \enum Relation::Cardinality

  This enumeration describes the cardinality of a relation.

  */

/*!
  Creates a relation in the given \a storage, which is described by \a row.
  */
Relation::Relation(const RelationMetaData &metaData, Storage *parent) :
    Property(parent),
    d_ptr(new RelationPrivate)
{
    Q_D(Relation);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

Relation::Relation(RelationPrivate &dd, const RelationMetaData &metaData, Storage *parent) :
    Property(parent),
    d_ptr(&dd)
{
    Q_D(Relation);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the relation.
  */
Relation::~Relation()
{
}

/*!
  Returns the storage-global ID of the relation.
  */
int Relation::id() const
{
    Q_D(const Relation);
    return d->metaData.id;
}

/*!
  Returns the name of the relation. If the relation has a 1:N cardinality this
  is the name of the column in the left context, if the cardinatlity is N:M, it
  is the name of the table, which stores the pairs of the relation.
  */
QString Relation::identifier() const
{
    Q_D(const Relation);
    return d->metaData.identifier;
}

/*!
  Returns the display name in the given \a context, if its the left or right
  context or name(), if the context has nothing to do with the relation.
  */
QString Relation::displayName() const
{
    Q_D(const Relation);
    return d->metaData.displayName;
}

QString Relation::tableName() const
{
    Q_D(const Relation);
    return d->metaData.tableName;
}

QString Relation::leftEntityIdColumnName() const
{
    Q_D(const Relation);
    return d->metaData.leftEntityIdColumnName;
}

QString Relation::rightEntityIdColumnName() const
{
    Q_D(const Relation);
    return d->metaData.rightEntityIdColumnName;
}

Property::Type Relation::propertyType() const
{
    return Property::Relation;
}

/*!
  Returns the entity type from which the relation maps.
  */
EntityType *Relation::entityType() const
{
    Q_D(const Relation);
    return d->entityType;
}

EntityType *Relation::entityTypeOther() const
{
    Q_D(const Relation);
    return d->entityTypeOther;
}

/*!
  Returns the cardinality of the relation.
  */
Relation::Cardinality Relation::cardinality() const
{
    Q_D(const Relation);
    return d->metaData.cardinality;
}

Relation::Direction Relation::direction() const
{
    Q_D(const Relation);
    return d->metaData.direction;
}

bool Relation::isEditable() const
{
    Q_D(const Relation);
    return d->metaData.editable;
}

bool Relation::isCalculated() const
{
    Q_D(const Relation);
    return d->metaData.calculated;
}

bool Relation::isTranspose() const
{
    Q_D(const Relation);
    return d->transpose;
}

/*!
  \internal

  Adds a RelationValueLeft to each Entity of the left EntityType and a
  RelationValueRight to each Entity of the right one.
  */
void Relation::addPropertyValueToEntities()
{
    Q_D(Relation);
    return d->addPropertyValueToEntities();
}

/*!
  \internal

  Adds a RelationValueLeft or Right to \a entity, if its of the leftEntityType()
  respectively rightEntityType().

  Does nothing if \a entity is of unkown type.
  */
void Relation::addPropertyValue(Entity *entity)
{
    Q_D(Relation);
    return d->addPropertyValue(entity);
}

void Relation::fetchValues()
{
    Q_D(Relation);
    return d->fetchValues();
}

Storage* Relation::storage() const
{
    Q_D(const Relation);
    return d->storage;
}

TransposeRelation::TransposeRelation(Relation *relation) :
    Relation(*new TransposeRelationPrivate, relation->d_ptr->metaData, relation->storage())
{
}

TransposeRelation::~TransposeRelation()
{
}

void TransposeRelationPrivate::init()
{
    Q_Q(Relation);

    qSwap(metaData.entityTypeId, metaData.entityTypeOtherId);
    qSwap(metaData.displayName, metaData.displayNameRight);
    qSwap(metaData.leftEntityIdColumnName, metaData.rightEntityIdColumnName);
    qSwap(metaData.identifier, metaData.identifierRight);

    entityType = storage->entityType(metaData.entityTypeId);
    entityTypeOther = storage->entityType(metaData.entityTypeOtherId);
    transpose = true;

    entityType->addRelation(q);
    entityType->context()->addRelation(q);
}

} // namespace LBDatabase
