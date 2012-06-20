#include "entitytype.h"

#include "attribute.h"
#include "context.h"
#include "entity.h"
#include "function.h"
#include "property.h"
#include "propertyvalue.h"
#include "relation.h"
#include "storage.h"
#include "storagedriver.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** EntityTypePrivate
*/
class EntityTypePrivate {
    EntityTypePrivate() : context(0), parentEntityType(0), calculator(0) {}

    void init();
    void inheritProperties(EntityType *parent);
    void inheritCalculator(EntityType *parent);
    Attribute *addAttribute(const QString &identifier, Attribute::Type type);
    Relation *addRelation(const QString &identifier, EntityType *otherType, Relation::Cardinality cardinality);

    EntityTypeMetaData metaData;

    Context *context;
    Storage *storage;
    EntityType *parentEntityType;

    QList<EntityType *> childEntityTypes;

    QHash<QString, Property *> propertiesByName;

    QList<Property *> properties;
    QList<Attribute *> attributes;
    QList<Relation *> relations;
    QList<Entity *> entities;
    QList<Function *> functions;

    Calculator *calculator;

    EntityType * q_ptr;
    Q_DECLARE_PUBLIC(EntityType)
};

void EntityTypePrivate::init()
{
    Q_Q(EntityType);
    context = storage->context(metaData.contextId);
    if(!context) {
        qWarning() << "No such context:" << metaData.contextId << "for entity type" << metaData.identifier;
        return;
    }
    context->addEntityType(q);
}

void EntityTypePrivate::inheritProperties(EntityType *parent)
{
    Q_Q(EntityType);

    QList<Relation *> newRelations = parent->relations();
    QList<Attribute *> newAttributes = parent->attributes();
    QList<Function *> newFunctions = parent->functions();

    properties.reserve(newAttributes.size() + newRelations.size() + newFunctions.size());
    attributes.reserve(newAttributes.size());
    relations.reserve(newRelations.size());
    functions.reserve(newFunctions.size());

    foreach(Attribute *attribute, newAttributes) {
        properties.append(attribute);
        propertiesByName.insert(attribute->identifier(), attribute);
    }
    foreach(Relation *relation, newRelations) {
        properties.append(relation);
        propertiesByName.insert(relation->identifier(), relation);
    }
    foreach(Function *function, newFunctions) {
        properties.append(function);
        propertiesByName.insert(function->identifier(), function);
    }

    relations.append(newRelations);
    attributes.append(newAttributes);
    functions.append(newFunctions);

    foreach(EntityType *type, childEntityTypes) {
        type->d_func()->inheritProperties(q);
    }
}

void EntityTypePrivate::inheritCalculator(EntityType *parent)
{
    Q_Q(EntityType);
    if(!calculator)
        calculator = parent->calculator();

    foreach(EntityType *type, childEntityTypes) {
        type->d_func()->inheritCalculator(q);
    }
}

/******************************************************************************
** EntityType
*/
/*!
  \class EntityType
  \brief The EntityType class represents a description of a type of entities.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var EntityType::d_ptr
  \internal
  */

/*!
  \fn EntityType::nameChanged(QString name)

  This signal is emitted, when the name of the entity type changes.
  */

/*!
  Creates a new entity type, which represents the type described in \a row in
  the Storage \a parent.
  */
EntityType::EntityType(EntityTypeMetaData metaData, Storage *parent) :
    QObject(parent),
    d_ptr(new EntityTypePrivate)
{
    Q_D(EntityType);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the type.
  */
EntityType::~EntityType()
{
}

/*!
  Returns the storage-global id of the type.
  */
int EntityType::id() const
{
    Q_D(const EntityType);
    return d->metaData.id;
}

/*!
  Returns the name of the type.
  */
QString EntityType::identifier() const
{
    Q_D(const EntityType);
    return d->metaData.identifier;
}

QString EntityType::displayName() const
{
    Q_D(const EntityType);
    return d->metaData.displayName;
}

QString EntityType::displayNamePlural() const
{
    Q_D(const EntityType);
    return d->metaData.displayNamePlural;
}

/*!
  Returns the context to which the type belongs.
  */
LBDatabase::Context *EntityType::context() const
{
    Q_D(const EntityType);
    return d->context;
}

/*!
  Returns the type, from which this type inherits its properties or \a 0 if this
  type is the base type of its Context.
  */
EntityType *EntityType::parentEntityType() const
{
    Q_D(const EntityType);
    return d->parentEntityType;
}

/*!
  \internal

  Sets the Context to \a context. This is done when loading the storage.
  */
void EntityType::setContext(LBDatabase::Context *context)
{
    Q_D(EntityType);
    if(d->context == context)
        return;
    d->context = context;
}

/*!
  \internal

  Adds a type, which inherits this type. This is done when loading the storage.
  */
void EntityType::addChildEntityType(EntityType *type)
{
    Q_D(EntityType);
    if(d->childEntityTypes.contains(type))
        return;

    d->childEntityTypes.append(type);
}

/*!
  \internal

  Sets the type from which this type inherits its properties. This is done when
  loading the storage.
  */
void EntityType::setParentEntityType(EntityType *type)
{
    Q_D(EntityType);
    if(d->parentEntityType == type)
        return;
    d->parentEntityType = type;
}

/*!
  \internal

  Returns the ID of the parent type. This is used when loading the storage.
  */
int EntityType::parentEntityTypeId() const
{
    Q_D(const EntityType);
    return d->metaData.parentEntityTypeId;
}

/*!
  Returns the list of types, which are derived from the type.
  */
QList<EntityType *> EntityType::childEntityTypes() const
{
    Q_D(const EntityType);
    return d->childEntityTypes;
}

Property *EntityType::property(const QString &name) const
{
    Q_D(const EntityType);
    return d->propertiesByName.value(name, 0);
}

/*!
  Returns the list of properties of the type.

  This includes all attributes and relations.
  */
QList<Property *> EntityType::properties() const
{
    Q_D(const EntityType);
    return d->properties;
}

/*!
  Returns the list of attributes of the type.
  */
QList<Attribute *> EntityType::attributes() const
{
    Q_D(const EntityType);
    return d->attributes;
}

/*!
  Returns the list of relations of the type.
  */
QList<Relation *> EntityType::relations() const
{
    Q_D(const EntityType);
    return d->relations;
}

QList<Function *> EntityType::functions() const
{
    Q_D(const EntityType);
    return d->functions;
}

Attribute *EntityType::addAttribute(AttributeMetaData &metaData)
{
    Q_D(EntityType);
    metaData.entityTypeId = id();
    d->storage->driver()->addAttribute(this, metaData);
    Attribute *attribute = new Attribute(metaData, d->storage);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritAttribute(attribute);
    }

    attribute->addPropertyValueToEntities();

    if(!attribute->defaultValue().toString().isEmpty()) {
        foreach(Entity *e, entities()) {
            e->setValue(attribute->identifier(), attribute->defaultValue());
        }
    }
    return attribute;
}

void EntityType::removeAttribute(Attribute *attribute)
{
    Q_D(EntityType);
    if(attribute->entityType() != this)
        return;

    d->storage->removeAttribute(attribute);
    d->context->removeAttribute(attribute);
    deinheritAttribute(attribute);
    foreach(Entity *e, entities()) {
        e->removeAttributeValue(attribute);
    }
    d->storage->driver()->removeAttribute(attribute->id());
    attribute->deleteLater();
}

Function *EntityType::addFunction(FunctionMetaData &metaData)
{
    Q_D(EntityType);
    metaData.entityTypeId = id();
    d->storage->driver()->addFunction(this, metaData);
    Function *function = new Function(metaData, d->storage);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritFunction(function);
    }

    function->addPropertyValueToEntities();

    return function;
}

Relation *EntityType::addRelation(RelationMetaData &metaData)
{
    Q_D(EntityType);
    metaData.entityTypeId = id();
    d->storage->driver()->addRelation(this, metaData);
    Relation *relation = new Relation(metaData, d->storage);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritRelation(relation);
    }

    relation->addPropertyValueToEntities();

    return relation;
}

QString EntityType::className()
{
    return identifier().left(1).toUpper()+identifier().mid(1);
}

QList<Property *> EntityType::nonInhertitedProperties() const
{
    QList<Property *> list = properties();
    if(parentEntityType()) {
        foreach(Property *property, parentEntityType()->properties()) {
            list.removeAll(property);
        }
    }
    return list;
}

QList<Attribute *> EntityType::nonInhertitedAttributes() const
{
    QList<Attribute *> list = attributes();
    if(parentEntityType()) {
        foreach(Attribute *attribute, parentEntityType()->attributes()) {
            list.removeAll(attribute);
        }
    }
    return list;
}

QList<Relation *> EntityType::nonInhertitedRelations() const
{
    QList<Relation *> list = relations();
    if(parentEntityType()) {
        foreach(Relation *relation, parentEntityType()->relations()) {
            if(!relation->reimplementingEntityTypes().contains(const_cast<EntityType*>(this)))
                list.removeAll(relation);
        }
    }
    return list;
}

QList<Function *> EntityType::nonInhertitedFunctions() const
{
    QList<Function *> list = functions();
    if(parentEntityType()) {
        foreach(Function *function, parentEntityType()->functions()) {
            if(!function->reimplementingEntityTypes().contains(const_cast<EntityType*>(this)))
                list.removeAll(function);
        }
    }
    return list;
}

/*!
  Returns a list of all entites of the type. This includes all entities of
  types, which inherit this type.
  */
QList<Entity *> EntityType::entities() const
{
    Q_D(const EntityType);
    return d->entities;
}

/*!
  Returns true, if the given \a entityType inherits or is equal to this type.
  This means, that the given type has at least the properties of this type.
  */
bool EntityType::inherits(EntityType *entityType) const
{
    Q_D(const EntityType);

    if(d->parentEntityType == entityType || this == entityType)
        return true;

    if(!d->parentEntityType || !entityType)
        return false;

    return d->parentEntityType->inherits(entityType);
}

Calculator *EntityType::calculator() const
{
    Q_D(const EntityType);
    return d->calculator;
}

/*!
  \internal

  Adds \a attribute to the attributes of this type. This is used when loading the storage.
  */
void EntityType::addAttribute(Attribute *attribute)
{
    Q_D(EntityType);
    d->properties.append(attribute);
    d->propertiesByName.insert(attribute->identifier(), attribute);
    d->attributes.append(attribute);
}

void EntityType::_removeAttribute(Attribute *attribute)
{
    Q_D(EntityType);
    qDebug() << "Removed" << d->properties.removeAll(attribute) << "properties";
    d->propertiesByName.remove(attribute->identifier());
    qDebug() << "Removed" << d->attributes.removeAll(attribute) << "attribtues";
}

/*!
  \internal

  Adds \a relation to the relations of this type. This is used when loading the storage.
  */
void EntityType::addRelation(Relation *relation)
{
    Q_D(EntityType);
    d->properties.append(relation);
    d->propertiesByName.insert(relation->identifier(), relation);
    d->relations.append(relation);
}

void EntityType::addFunction(Function *function)
{
    Q_D(EntityType);
    d->properties.append(function);
    d->propertiesByName.insert(function->identifier(), function);
    d->functions.append(function);
}

/*!
  \internal

  Adds the properties of \a parent to this entity.
  */
void EntityType::inheritProperties(EntityType *parent)
{
    Q_D(EntityType);
    d->inheritProperties(parent);
}

void EntityType::inheritCalculator(EntityType *parent)
{
    Q_D(EntityType);
    d->inheritCalculator(parent);
}

/*!
  \internal

  Adds \a entity to the list of all entities of this type and each type it is
  derived from.
  */
void EntityType::addEntity(Entity *entity)
{
    Q_D(EntityType);
    d->entities.append(entity);
    if(d->parentEntityType)
        d->parentEntityType->addEntity(entity);
}

void EntityType::inheritAttribute(Attribute *attribute)
{
    Q_D(EntityType);

    addAttribute(attribute);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritAttribute(attribute);
    }
}

void EntityType::deinheritAttribute(Attribute *attribute)
{
    Q_D(EntityType);
    _removeAttribute(attribute);

    foreach(EntityType *type, d->childEntityTypes) {
        type->deinheritAttribute(attribute);
    }
}

void EntityType::inheritFunction(Function *function)
{
    Q_D(EntityType);

    addFunction(function);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritFunction(function);
    }
}

void EntityType::inheritRelation(Relation *relation)
{
    Q_D(EntityType);

    addRelation(relation);

    foreach(EntityType *type, d->childEntityTypes) {
        type->inheritRelation(relation);
    }
}

void EntityType::setCalculator(Calculator *calculator)
{
    Q_D(EntityType);
    d->calculator = calculator;
}

} // namespace LBDatabase
