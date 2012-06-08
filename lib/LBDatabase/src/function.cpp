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
    entity->addFunctionValue(new FunctionValue(q, entity));
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

bool Function::cacheData() const
{
    Q_D(const Function);
    return d->metaData.cacheData;
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
