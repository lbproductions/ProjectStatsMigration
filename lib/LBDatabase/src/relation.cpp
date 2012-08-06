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
    void calculateValues();

    Storage *storage;
    bool transpose;
    Relation *transposeRelation;

    RelationMetaData metaData;

    EntityType *entityType;
    EntityType *entityTypeOther;

    QList<EntityType *> reimplementingEntityTypes;
    QList<PropertyValue *> propertyValues;

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
    foreach(Entity *entity, entityType->entities()) {
        addPropertyValue(entity);
    }

    if(!transpose && transposeRelation)
        transposeRelation->addPropertyValueToEntities();
}

void RelationPrivate::fetchValues()
{
    Q_Q(Relation);
    if(!metaData.calculated) {
        foreach(RelationValueData entities, storage->driver()->relatedEntities(q)) {
            Entity *leftEntity = entityType->context()->entity(entities.leftId);
            Entity *rightEntity = entityTypeOther->context()->entity(entities.rightId);

            if(!leftEntity || !rightEntity)
                continue;

            RelationValueBase *leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
            if(leftValue)
                leftValue->addOtherEntityWhileStartup(rightEntity, entities.rowId);

            RelationValueBase *rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(transposeRelation));
            if(rightValue)
                rightValue->addOtherEntityWhileStartup(leftEntity, entities.rowId);
        }
    }

}

void RelationPrivate::calculateValues()
{
    Q_Q(Relation);
    if(metaData.calculated) {
        foreach(Entity *leftEntity, entityType->entities()) {
            RelationValueBase *leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
            if(!leftValue)
                continue;

            QList<Entity *> rightEntities = leftValue->calculate();
            foreach(Entity *rightEntity, rightEntities) {
                leftValue->addOtherEntityWhileStartup(rightEntity, 0);
                RelationValueBase *rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(transposeRelation));
                if(rightValue)
                    rightValue->addOtherEntityWhileStartup(leftEntity, 0);
            }
        }
    }
}

void RelationPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Relation);
    RelationValue<Entity> *value = new RelationValue<Entity>(q, entity);
    entity->addRelationValue(value);
    propertyValues.append(value);
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

void Relation::addReimplementingEntityType(EntityType *type)
{
    Q_D(Relation);
    d->reimplementingEntityTypes.append(type);
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

QString Relation::identifierRight() const
{
    Q_D(const Relation);
    return d->metaData.identifierRight;
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

QString Relation::displayNameRight() const
{
    Q_D(const Relation);
    return d->metaData.displayNameRight;
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

QList<PropertyValue *> Relation::propertyValues() const
{
    Q_D(const Relation);
    return d->propertyValues;
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

bool Relation::isEditableTranspose() const
{
    Q_D(const Relation);
    return d->metaData.editableTranspose;
}

Relation *Relation::transposeRelation() const
{
    Q_D(const Relation);
    return d->transposeRelation;
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

void Relation::calculateValues()
{
    Q_D(Relation);
    return d->calculateValues();
}

Storage* Relation::storage() const
{
    Q_D(const Relation);
    return d->storage;
}

void Relation::setIdentifier(const QString &identifier)
{
    Q_D(Relation);
    if(identifier == d->metaData.identifier)
        return;

    d->metaData.identifier = identifier;
    d->storage->driver()->setRelationIdentifier(d->metaData.id, identifier);
    emit identifierChanged(identifier);
}

void Relation::setIdentifierRight(const QString &identifierRight)
{
    Q_D(Relation);
    if(identifierRight == d->metaData.identifierRight)
        return;

    if(transposeRelation()) {
        transposeRelation()->d_func()->metaData.identifier = identifierRight;
    }
    d->metaData.identifierRight = identifierRight;
    d->storage->driver()->setRelationIdentifierRight(d->metaData.id, identifierRight);
    emit identifierRightChanged(identifierRight);
}

void Relation::setDisplayName(const QString &displayName)
{
    Q_D(Relation);
    if(displayName == d->metaData.displayName)
        return;

    d->metaData.displayName = displayName;
    d->storage->driver()->setRelationDisplayName(d->metaData.id, displayName);
    emit displayNameChanged(displayName);
}

void Relation::setDisplayNameRight(const QString &displayNameRight)
{
    Q_D(Relation);
    if(displayNameRight == d->metaData.displayNameRight)
        return;

    if(transposeRelation()) {
        transposeRelation()->d_func()->metaData.displayName = displayNameRight;
    }
    d->metaData.displayNameRight = displayNameRight;
    d->storage->driver()->setRelationDisplayNameRight(d->metaData.id, displayNameRight);
    emit displayNameRightChanged(displayNameRight);
}

void Relation::setCardinality(Relation::Cardinality cardinality)
{
    Q_D(Relation);
    if(cardinality == d->metaData.cardinality)
        return;

    d->metaData.cardinality = cardinality;
    d->storage->driver()->setRelationCardinality(d->metaData.id, cardinality);
    emit cardinalityChanged(cardinality);
}

void Relation::setDirection(Relation::Direction direction)
{
    Q_D(Relation);
    if(direction == d->metaData.direction)
        return;

    d->metaData.direction = direction;
    d->storage->driver()->setRelationDirection(d->metaData.id, direction);
    emit directionChanged(direction);
}

void Relation::setEntityTypeRight(EntityType *entityType)
{
    Q_D(Relation);
    if(entityType == d->entityTypeOther)
        return;

    d->metaData.entityTypeOtherId = entityType->id();
    d->entityTypeOther = entityType;
    d->storage->driver()->setRelationEntityTypeRight(d->metaData.id, entityType);
    emit entityTypeRightChanged(entityType);
}

void Relation::setEditable(bool editable)
{
    Q_D(Relation);
    if(editable == d->metaData.editable)
        return;

    d->metaData.editable = editable;
    d->storage->driver()->setRelationEditable(d->metaData.id, editable);
    emit editableChanged(editable);
}

void Relation::setCalculated(bool calculated)
{
    Q_D(Relation);
    if(calculated == d->metaData.calculated)
        return;

    d->metaData.calculated = calculated;
    d->storage->driver()->setRelationCalculated(d->metaData.id, calculated);
    emit calculatedChanged(calculated);
}

QList<EntityType *> Relation::reimplementingEntityTypes() const
{
    Q_D(const Relation);
    return d->reimplementingEntityTypes;
}

QString Relation::signalSignature() const
{
    return QString(identifier() + "Changed()");
}

TransposeRelation::TransposeRelation(Relation *relation) :
    Relation(*new TransposeRelationPrivate, relation->d_ptr->metaData, relation->storage())
{
    Q_D(Relation);
    d->transposeRelation = relation;
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
