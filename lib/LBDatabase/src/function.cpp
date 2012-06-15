#include "function.h"

#include "attribute.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "functionvalue.h"
#include "storage.h"
#include "storagedriver.h"

#include <QDebug>
#include <QThread>

namespace LBDatabase {

/******************************************************************************
** FunctionPrivate
*/
class FunctionPrivate {
    FunctionPrivate() :
        entityType(0),
        keyEntityType(0)
    {}

    void init();
    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    void setValue(Entity *key, const QVariant &value);

    FunctionMetaData metaData;

    Storage *storage;
    EntityType *entityType;
    EntityType *keyEntityType;

    QList<EntityType *> reimplementingEntityTypes;
    QList<PropertyValue *> propertyValues;

    Function * q_ptr;
    Q_DECLARE_PUBLIC(Function)
};

void FunctionPrivate::init()
{
    Q_Q(Function);
    entityType = storage->entityType(metaData.entityTypeId);
    keyEntityType = storage->entityType(metaData.keyEntityTypeId);

    entityType->addFunction(q);
    entityType->context()->addFunction(q);
}

void FunctionPrivate::addPropertyValueToEntities()
{
    Q_Q(Function);
    foreach(Entity *entity, entityType->entities()) {
        entity->addFunctionValue(new FunctionValue(q, entity));
    }
}

void FunctionPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Function);
    FunctionValue *value = new FunctionValue(q, entity);
    entity->addFunctionValue(value);
    propertyValues.append(value);
}

void FunctionPrivate::fetchValues()
{
    Q_Q(Function);

    if(!metaData.calculated) {
        foreach(FunctionValueData values, storage->driver()->functionValues(q)) {

            Entity *entity = entityType->context()->entity(values.entityId);
            Entity *keyEntity = keyEntityType->context()->entity(values.keyEntityId);

            if(!entity || !keyEntity)
                continue;

            FunctionValue *functionValue = static_cast<FunctionValue *>(entity->propertyValue(q));
            functionValue->addValue(keyEntity, values);
        }
    }
}

/******************************************************************************
** Function
*/
Function::Function(const FunctionMetaData &metaData, Storage *parent) :
    Property(parent),
    d_ptr(new FunctionPrivate)
{
    Q_D(Function);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

void Function::addReimplementingEntityType(EntityType *type)
{
    Q_D(Function);
    d->reimplementingEntityTypes.append(type);
}

Function::~Function()
{
}

int Function::id() const
{
    Q_D(const Function);
    return d->metaData.id;
}

Property::Type Function::propertyType() const
{
    return Property::Function;
}

QString Function::entityColumnName() const
{
    Q_D(const Function);
    return d->metaData.entityColumnName;
}

QString Function::keyEntityColumnName() const
{
    Q_D(const Function);
    return d->metaData.keyEntityColumnName;
}

QString Function::valueColumnName() const
{
    Q_D(const Function);
    return d->metaData.valueColumnName;
}

QString Function::displayName() const
{
    Q_D(const Function);
    return d->metaData.displayName;
}

QString Function::identifier() const
{
    Q_D(const Function);
    return d->metaData.identifier;
}

QString Function::tableName() const
{
    Q_D(const Function);
    return d->metaData.tableName;
}

EntityType *Function::keyEntityType() const
{
    Q_D(const Function);
    return d->keyEntityType;
}

QString Function::qtTypeName() const
{
    Q_D(const Function);
    return Attribute::typeToQtType(d->metaData.type);
}

bool Function::isCalculated() const
{
    Q_D(const Function);
    return d->metaData.calculated;
}

EntityType *Function::entityType() const
{
    Q_D(const Function);
    return d->entityType;
}

QList<PropertyValue *> Function::propertyValues() const
{
    Q_D(const Function);
    return d->propertyValues;
}

bool Function::isCached() const
{
    Q_D(const Function);
    return d->metaData.cached;
}

Attribute::Type Function::type() const
{
    Q_D(const Function);
    return d->metaData.type;
}

bool Function::isEditable() const
{
    Q_D(const Function);
    return d->metaData.editable;
}

void Function::setDisplayName(const QString &displayName)
{
    Q_D(Function);
    if(displayName == d->metaData.displayName)
        return;

    d->metaData.displayName = displayName;
    d->storage->driver()->setFunctionDisplayName(d->metaData.id, displayName);
    emit displayNameChanged(displayName);
}

void Function::setIdentifier(const QString &identifier)
{
    Q_D(Function);
    if(identifier == d->metaData.identifier)
        return;

    d->metaData.identifier = identifier;
    d->storage->driver()->setFunctionIdentifier(d->metaData.id, identifier);
    emit identifierChanged(identifier);
}


void Function::setType(Attribute::Type type)
{
    Q_D(Function);
    if(type == d->metaData.type)
        return;

    d->metaData.type = type;
    d->storage->driver()->setFunctionType(d->metaData.id, type);
    emit typeChanged(type);
}

void Function::setEditable(bool editable)
{
    Q_D(Function);
    if(editable == d->metaData.editable)
        return;

    d->metaData.editable = editable;
    d->storage->driver()->setFunctionEditable(d->metaData.id, editable);
    emit editableChanged(editable);
}

void Function::setKeyEntityType(EntityType *keyEntityType)
{
    Q_D(Function);
    if(keyEntityType == d->keyEntityType)
        return;

    d->metaData.keyEntityTypeId = keyEntityType->id();
    d->keyEntityType = keyEntityType;
    d->storage->driver()->setFunctionKeyEntityType(d->metaData.id, keyEntityType);
    emit keyEntityTypeChanged(keyEntityType);
}

QList<EntityType *> Function::reimplementingEntityTypes() const
{
    Q_D(const Function);
    return d->reimplementingEntityTypes;
}

void Function::addPropertyValueToEntities()
{
    Q_D(Function);
    d->addPropertyValueToEntities();
}

void Function::addPropertyValue(Entity *entity)
{
    Q_D(Function);
    d->addPropertyValue(entity);
}

void Function::fetchValues()
{
    Q_D(Function);
    d->fetchValues();
}

} // namespace LBDatabase
