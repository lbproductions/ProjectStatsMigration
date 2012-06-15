#include "entity.h"

#include "attribute.h"
#include "attributevalue.h"
#include "context.h"
#include "entitytype.h"
#include "functionvalue.h"
#include "property.h"
#include "relation.h"
#include "relationvalue.h"
#include "storage.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** EntityPrivate
*/
class EntityPrivate {
    EntityPrivate() {}

    void init();
    void initializeRelations();
    void initializeRelationContent();

    EntityMetaData metaData;

    Storage *storage;
    Context *context;
    EntityType *entityType;
    QMultiHash<Property *, PropertyValue *> propertyValues;

    QList<AttributeValue *> attributeValues;
    QList<RelationValueBase *> relationValues;
    QList<FunctionValue *> functionValues;

    Entity * q_ptr;
    Q_DECLARE_PUBLIC(Entity)
};

void EntityPrivate::init()
{
    Q_Q(Entity);
    storage = context->storage();
    entityType = storage->entityType(metaData.entityTypeId);
    entityType->addEntity(q);
}

/******************************************************************************
** Entity
*/
/*!
  \class Entity
  \brief The Entity class models a concrete instance of an EntityType.

  \ingroup highlevel-database-classes

  While EntityType represents a description for a group of entities, th Entity
  class is responsible for concrete single instances of such a type.

  Each entity has a set of PropertyValues, one value for each Property of the
  corresponding EntityType. You may access these values one by one via
  propertyValue or as a list propertyValues().

  You can create new entity instances with Context::insertEntity().
  */

/*!
  \var Entity::d_ptr
  \internal
  */

/*!
  Creates a new entity, which represents the data in \a row in the Context \a
  parent.
  */
Entity::Entity(const EntityMetaData &metaData, Context *parent) :
    QObject(parent),
    d_ptr(new EntityPrivate)
{
    Q_D(Entity);
    d->q_ptr = this;
    d->context = parent;
    d->metaData = metaData;
    d->init();
}

/*!
  Destroys the entity.
  */
Entity::~Entity()
{
}

/*!
  Returns a display name for the entity.
  */
QString Entity::displayName() const
{
    Q_D(const Entity);
    return d->entityType->identifier()+QLatin1String(" ID: ")+QString::number(id());
}

int Entity::id() const
{
    Q_D(const Entity);
    return d->metaData.id;
}

/*!
  Returns the EntityType of the entity.
  */
EntityType *Entity::entityType() const
{
    Q_D(const Entity);
    return d->entityType;
}

/*!
  Returns the Storage in which the Entity is stored.
  */
Storage *Entity::storage() const
{
    Q_D(const Entity);
    return d->storage;
}

/*!
  Returns the Context to which the entity belongs.
  */
Context *Entity::context() const
{
    Q_D(const Entity);
    return d->context;
}

/*!
  Returns a list of property values of the entity,
  */
QList<PropertyValue *> Entity::propertyValues() const
{
    Q_D(const Entity);
    return d->propertyValues.values();
}

/*!
  Returns the property value for the Property \a property or \a 0 if the
  EntityType has no such property.
  */
PropertyValue *Entity::propertyValue(Property *property) const
{
    Q_D(const Entity);
    return d->propertyValues.value(property, 0);
}

AttributeValue *Entity::attribute(const QString &name) const
{
    return static_cast<LBDatabase::AttributeValue *>(propertyValue(entityType()->property(name)));
}

FunctionValue *Entity::function(const QString &name) const
{
    return static_cast<LBDatabase::FunctionValue *>(propertyValue(entityType()->property(name)));
}

QVariant Entity::value(const QString &name) const
{
    Q_D(const Entity);
    PropertyValue *value = d->propertyValues.value(d->entityType->property(name), 0);
    if(!value)
        return QVariant();

    return value->value();
}

void Entity::setValue(const QString &propertyIdentifier, const QVariant &data)
{
    Q_D(const Entity);
    Property *p = d->entityType->property(propertyIdentifier);
    if(!p || !p->isEditable())
        return;

    PropertyValue *value = d->propertyValues.value(p, 0);
    if(!value ||
            !(value->property()->propertyType() == Property::Attribute ||
              value->property()->propertyType() == Property::EnumAttribute)
            )
        return;

    static_cast<LBDatabase::AttributeValue *>(value)->setData(data);
}

/*!
  \internal
  Adds the AttributeValue \a value to this entity. This is done when loading the storage.
  */
void Entity::addAttributeValue(AttributeValue *value)
{
    Q_D(Entity);
    d->propertyValues.insert(value->property(), value);
    d->attributeValues.append(value);
}

void Entity::removeAttributeValue(Attribute *attribute)
{
    Q_D(Entity);
    AttributeValue *value = static_cast<AttributeValue *>(d->propertyValues.take(attribute));
    d->attributeValues.removeAll(value);
}

/*!
  \internal
  Adds the RelationValue \a value to this entity. This is done when loading the storage.
  */
void Entity::addRelationValue(RelationValueBase *value)
{
    Q_D(Entity);
    d->propertyValues.insert(value->property(), value);
    d->relationValues.append(value);
}

void Entity::addFunctionValue(FunctionValue *value)
{
    Q_D(Entity);
    d->propertyValues.insert(value->property(), value);
    d->functionValues.append(value);
}

} // namespace LBDatabase
