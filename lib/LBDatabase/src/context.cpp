#include "context.h"

#include "attribute.h"
#include "attributevalue.h"
#include "calculator.h"
#include "entity.h"
#include "entitytype.h"
#include "function.h"
#include "relation.h"
#include "relationvalue.h"
#include "storage.h"
#include "storagedriver.h"

#include <QHash>
#include <QList>
#include <QDebug>
#include <QIcon>
#include <QPixmap>

namespace LBDatabase {

/******************************************************************************
** ContextPrivate
*/
class ContextPrivate {
    ContextPrivate() : baseEntityType(0) {}

    void init();
    void initializeEntityHierarchy();
    void loadEntities();
    void initializeRelations();
    void fillRelations();

    Entity *insertEntity(EntityType *type);

    Entity *createEntityInstance(const EntityMetaData &metaData);
    Calculator *createCalculatorInstance(const QString &entityTypeName);
    bool metaObjectForType(EntityType *type, QMetaObject &object);

    ContextMetaData metaData;

    Storage *storage;
    QList<EntityType *> entityTypes;
    EntityType *baseEntityType;
    QList<Entity *> entities;
    QHash<int, Entity *> entitiesById;
    QList<Property *> properties;

    QHash<QString, QMetaObject> entityMetaObjects;
    QHash<QString, QMetaObject> calculatorMetaObjects;

    Context * q_ptr;
    Q_DECLARE_PUBLIC(Context)
};

void ContextPrivate::init()
{
}

void ContextPrivate::initializeEntityHierarchy()
{
    EntityType *parentType;
    foreach(EntityType *type, entityTypes) {

        parentType = storage->entityType(type->parentEntityTypeId());
        if(parentType) {
            type->setParentEntityType(parentType);
            parentType->addChildEntityType(type);
        }
        else {
            baseEntityType = type;
        }
    }
    foreach(EntityType *type, entityTypes) {
        type->setCalculator(createCalculatorInstance(type->identifier()));
    }

    foreach(EntityType *child, baseEntityType->childEntityTypes()) {
        child->inheritProperties(baseEntityType);
        child->inheritCalculator(baseEntityType);
    }
}

void ContextPrivate::loadEntities()
{
    Q_Q(Context);
    QList<EntityMetaData> entityIds = storage->driver()->entities(q);

    entities.reserve(entityIds.size());
    entitiesById.reserve(entityIds.size());
    foreach(EntityMetaData metaData, entityIds) {
        Entity *entity = createEntityInstance(metaData);
        if(entity) {
            entities.append(entity);
            entitiesById.insert(metaData.id, entity);
        }
    }
}

Entity *ContextPrivate::createEntityInstance(const EntityMetaData &metaData)
{
    Q_Q(Context);
    EntityType *type = storage->entityType(metaData.entityTypeId);
    if(!type)
        return 0;

    QMetaObject metaObject;
    if(!metaObjectForType(type, metaObject))
        return new Entity(metaData, q);

    QObject *object = metaObject.newInstance(Q_ARG(const::LBDatabase::EntityMetaData&,metaData), Q_ARG(::LBDatabase::Context*, q));
    return static_cast<Entity *>(object);
}

Calculator *ContextPrivate::createCalculatorInstance(const QString &entityTypeName)
{
    Q_Q(Context);
    if(!calculatorMetaObjects.contains(entityTypeName))
        return 0;

    QObject *object = calculatorMetaObjects.value(entityTypeName).newInstance(Q_ARG(QObject*, q));
    return static_cast<Calculator *>(object);
}

bool ContextPrivate::metaObjectForType(EntityType *type, QMetaObject &object)
{
    QString entityTypeName = type->identifier();

    while(!entityMetaObjects.contains(entityTypeName)) {
        type = type->parentEntityType();
        if(!type)
            break;

        entityTypeName = type->identifier();
    }

    if(!entityMetaObjects.contains(entityTypeName))
        return false;

    object = entityMetaObjects.value(entityTypeName);
    return true;
}

Entity *ContextPrivate::insertEntity(EntityType *type)
{
    Q_Q(Context);
    EntityMetaData metaData = storage->driver()->createEntity(type);

    q->beginInsertRows(QModelIndex(), entities.size(), entities.size());
    Entity *entity =  createEntityInstance(metaData);
    entities.append(entity);
    entitiesById.insert(metaData.id, entity);

    foreach(Property *property, type->properties()) {
        property->addPropertyValue(entity);
    }

    foreach(Property *p, type->properties()) {
        PropertyValue *v = entity->propertyValue(p);
        v->recalculateAfterDependencyChange();
    }

    foreach(Property *property, properties) {
        property->initDependencies(entity);
    }

    q->endInsertRows();

    emit q->entityInserted(entity);
    return entity;
}

/******************************************************************************
** Context
*/
/*!
  \class Context
  \brief The Context class represents a context in a Storage.

  \ingroup highlevel-database-classes

  Each context is responsible for a hierarchy of EntityType and the concrete
  Entity instances of these types. It always has exactly one baseEntityType()
  from which other types in the context may be derived. The entityTypes() list
  contains every type in the context. You can add a new type with
  addEntityType().

  You may access the Entity instances of each context either by id (entity()),
  by index (entityAt()) or through the list of all entities(). You can insert
  new entities into the context by calling insertEntity().

  The Context class inherits QAbstractTableModel, so that you can add it as a
  model for any model-view based Qt class like QTreeView. This model is
  editable.

  */
/*!
  \fn Context::nameChanged(QString name)

  This signal is emitted when the name of this context changes.

  */

/*!
  \var Context::d_ptr
  \internal
  */

/*!
  Creates a new context in the Storage \a parent, which is described by /a row.
  */
Context::Context(const ContextMetaData &metaData, Storage *parent) :
    QAbstractTableModel(parent),
    d_ptr(new ContextPrivate)
{
    Q_D(Context);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the context.
  */
Context::~Context()
{
}

/*!
  Returns the storage-global ID of the context.
  */
int Context::id() const
{
    Q_D(const Context);
    return d->metaData.id;
}

/*!
  Returns the name of the context. This name is also the name of the Sqlite
  table, which contains the Entity instances of the context.
  */
QString Context::identifier() const
{
    Q_D(const Context);
    return d->metaData.identifier;
}

QString Context::displayName() const
{
    Q_D(const Context);
    return d->metaData.displayName;
}

QString Context::tableName() const
{
    Q_D(const Context);
    return d->metaData.tableName;
}

/*!
  Returns the storage, which contains the context.
  */
Storage *Context::storage() const
{
    Q_D(const Context);
    return d->storage;
}

/*!
  Returns the EntityType, from which all types in the context are somehow
  derived.
  */
EntityType *Context::baseEntityType() const
{
    Q_D(const Context);
    return d->baseEntityType;
}

/*!
  Returns a list of all types, for which the context is responsible.
  */
QList<EntityType *> Context::entityTypes() const
{
    Q_D(const Context);
    return d->entityTypes;
}

/*!
  Returns the Entity instance with the ID \a id.
  */
Entity *Context::entity(int id) const
{
    Q_D(const Context);
    return d->entitiesById.value(id);
}

/*!
  Returns a list of all Entity instances.
  */
QList<Entity *> Context::entities() const
{
    Q_D(const Context);
    return d->entities;
}

/*!
  Inserts a new Entity of the type \a type into the context and returns the
  instance.
  */
Entity *Context::insertEntity(EntityType *type)
{
    Q_D(Context);
    return d->insertEntity(type);
}

/*!
  \internal

  Adds the EntityType \a type to the context. This is when loading the storage.
  */
void Context::addEntityType(EntityType *type)
{
    Q_D(Context);
    if(d->entityTypes.contains(type))
        return;

    connect(type, SIGNAL(displayNameChanged(QString)), this, SLOT(onEntityTypeNameChanged(QString)));
    d->entityTypes.append(type);
}

/*!
  \internal

  Adds the Attribute \a attribute to the context. This is when loading the storage.
  */
void Context::addAttribute(Attribute *attribute)
{
    Q_D(Context);
    if(d->properties.contains(attribute))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(attribute);
    connect(attribute, SIGNAL(displayNameChanged(QString)), this, SLOT(onPropertyDisplayNameChanged(QString)));
    endInsertColumns();
}

void Context::removeAttribute(Attribute *attribute)
{
    Q_D(Context);
    if(!d->properties.contains(attribute))
        return;

    beginRemoveColumns(QModelIndex(), d->properties.indexOf(attribute), d->properties.indexOf(attribute));
    d->properties.removeAll(attribute);
    endInsertColumns();
}

void Context::addFunction(Function *function)
{
    Q_D(Context);
    if(d->properties.contains(function))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(function);
    connect(function, SIGNAL(displayNameChanged(QString)), this, SLOT(onPropertyDisplayNameChanged(QString)));
    endInsertColumns();
}

/*!
  \internal

  Adds the Relation \a relation to the context. This is when loading the storage.
  */
void Context::addRelation(Relation *relation)
{
    Q_D(Context);
    if(d->properties.contains(relation))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(relation);
    connect(relation, SIGNAL(displayNameChanged(QString)), this, SLOT(onPropertyDisplayNameChanged(QString)));
    endInsertColumns();
}

/*!
  \internal

  Initialized the hierarchy of the EntityTypes. This is when loading the storage.
  */
void Context::initializeEntityHierarchy()
{
    Q_D(Context);
    d->initializeEntityHierarchy();
}

/*!
  \internal

  Loads the Entity instances in this context. This is when loading the storage.
  */
void Context::loadEntities()
{
    Q_D(Context);
    d->loadEntities();
}

/*!
  Implements QAbstractTableModel::data()
  */
QVariant Context::data(const QModelIndex &index, int role) const
{
    Q_D(const Context);
    if(role == Qt::DecorationRole && index.column() > 1) {
        //        Entity *entity = d->entities.at(index.row());
        //        Property *property = d->properties.at(index.column() - 2);
        //        if(property->propertyType() == Property::Attribute) {
        //            Attribute *attribute = static_cast<Attribute *>(property);
        //            if(attribute->type() == Attribute::Icon) {
        //                QImage image(entity->data(attribute).toString());
        //                qDebug() << image.isNull();
        //                QPixmap pixmap(entity->data(attribute).toString());
        //                qDebug() << pixmap.isNull();
        //                return image;
        //            }
        //            else if(attribute->type() == Attribute::Pixmap) {
        //                return QImage(entity->data(attribute).toString());
        //            }
        //        }
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        Entity *entity = d->entities.at(index.row());
        switch(index.column()) {
        case 0:
            return entity->id();
        case 1:
            return entity->entityType()->displayName();
        default:
            Entity *entity = d->entities.at(index.row());
            Property *property = d->properties.at(index.column() - 2);
            PropertyValue *value = entity->propertyValue(property);
            if(value)
                return value->dataForModel(role);
        }
    }


    return QVariant();
}

/*!
  Implements QAbstractTableModel::headerData()
  */
QVariant Context::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal) {
        if(role == Qt::DisplayRole) {
            Q_D(const Context);
            switch(section) {
            case 0:
                return QLatin1String("ID");
            case 1:
                return QLatin1String("Type");
            default:
                return d->properties.at(section - 2)->displayName();
            }
        }
        else if(role == Qt::TextAlignmentRole) {
            return Qt::AlignLeft;
        }
    }
    return QVariant();
}

/*!
  Implements QAbstractTableModel::columnCount()
  */
int Context::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    Q_D(const Context);
    return d->properties.size() + 2;
}

/*!
  Implements QAbstractTableModel::rowCount()
  */
int Context::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    Q_D(const Context);
    return d->entities.size();
}

/*!
  \internal
  Listens to name changes of EntityTypes and updates the model accordingly.
  */
void Context::onEntityTypeNameChanged(QString name)
{
    Q_D(const Context);
    Q_UNUSED(name);
    EntityType *type = static_cast<EntityType *>(sender());
    QModelIndex i = index(d->entityTypes.indexOf(type), 1);
    emit dataChanged(i, i);
}

/*!
  \internal
  Listens to name changes of Properties and updates the model accordingly.
  */
void Context::onPropertyDisplayNameChanged(QString displayName)
{
    Q_D(const Context);
    Q_UNUSED(displayName);

    Property *p = static_cast<Property *>(sender());
    int i =d->properties.indexOf(p);
    emit headerDataChanged(Qt::Horizontal, i, i);
}

/*!
  \internal
  Listens to changes of PropertyValues and updates the model accordingly.
  */
void Context::onPropertyValueChanged()
{
    Q_D(const Context);

    PropertyValue *v = static_cast<PropertyValue *>(sender());
    QModelIndex i = index(d->entities.indexOf(v->entity()), d->properties.indexOf(v->property()) + 2);
    emit dataChanged(i, i);
}

/*!
  Implements QAbstractTableModel::setData()
  */
bool Context::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        Q_D(const Context);
        Entity *e = d->entities.at(index.row());
        PropertyValue *v = e->propertyValue(d->properties.value(index.column() - 2));
        if(v && (v->property()->propertyType() == Property::Attribute || v->property()->propertyType() == Property::EnumAttribute)) {
            return static_cast<AttributeValue *>(v)->setData(value);
        }
    }
    return false;
}

/*!
  Implements QAbstractTableModel::flags()
  */
Qt::ItemFlags Context::flags(const QModelIndex &index) const
{
    Q_D(const Context);
    if(index.column() > 1) {
        Property *p = d->properties.value(index.column() - 2);

        if(p && p->isEditable()) {
            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
        }
    }

    return QAbstractItemModel::flags(index);
}

void Context::registerEntityClass(const QString &entityName, QMetaObject metaObject)
{
    Q_D(Context);
    if(d->entityMetaObjects.contains(entityName))
        return;

    d->entityMetaObjects.insert(entityName, metaObject);
}

void Context::registerCalculatorClass(const QString &entityName, QMetaObject metaObject)
{
    Q_D(Context);
    if(d->calculatorMetaObjects.contains(entityName))
        return;

    d->calculatorMetaObjects.insert(entityName, metaObject);
}

} // namespace LBDatabase
