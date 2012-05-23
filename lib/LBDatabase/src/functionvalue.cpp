#include "functionvalue.h"

#include "calculator.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "function.h"
#include "storage.h"
#include "storagedriver.h"

#include <QDebug>

#define COMMA ,
Q_DECLARE_METATYPE(QHash<const LBDatabase::Entity * COMMA QVariant>)

namespace LBDatabase {
/******************************************************************************
** FunctionValuePrivate
*/
class FunctionValuePrivate {
    FunctionValuePrivate() : cached(false) {}

    void init();
    void fetchValue();
    QHash<const Entity *, QVariant> calculate();
    QVariant calculate(const Entity *key);

    Entity *entity;
    Function *function;

    mutable bool cached;

    mutable QHash<const Entity *, int> rowIds;
    mutable QHash<const Entity *, QVariant> values;

    FunctionValue * q_ptr;
    Q_DECLARE_PUBLIC(FunctionValue)
};

void FunctionValuePrivate::init()
{
    Q_Q(FunctionValue);
    QObject::connect(q, SIGNAL(dataChanged(QVariant)), entity->context(), SLOT(onPropertyValueDataChanged(QVariant)));
}

void FunctionValuePrivate::fetchValue()
{
}

QVariant FunctionValuePrivate::calculate(const Entity *key)
{
    Q_Q(FunctionValue);
    Calculator *calculator = entity->entityType()->calculator();

    if(calculator)
        return calculator->calculate(entity,q,key);

    return QVariant();
}

QHash<const Entity *, QVariant> FunctionValuePrivate::calculate()
{
    Q_Q(FunctionValue);
    Calculator *calculator = entity->entityType()->calculator();

    if(calculator)
        return calculator->calculate(entity,q);

    return QHash<const Entity *, QVariant>();
}

/******************************************************************************
** FunctionValue
*/
FunctionValue::FunctionValue(Function *function, Entity *parent) :
    PropertyValue(parent),
    d_ptr(new FunctionValuePrivate)
{
    Q_D(FunctionValue);
    d->q_ptr = this;
    d->function = function;
    d->entity = parent;
    d->init();
}

void FunctionValue::fetchValue()
{
    Q_D(FunctionValue);
    d->fetchValue();
}

QVariant FunctionValue::calculate()
{
    return QVariant();
}

void FunctionValue::addValue(Entity *key, const FunctionValueData& data)
{
    Q_D(FunctionValue);
    d->rowIds.insert(key, data.rowId);
    d->values.insert(key, data.value);
}

FunctionValue::~FunctionValue()
{
}

Entity *FunctionValue::entity() const
{
    Q_D(const FunctionValue);
    return d->entity;
}

Property *FunctionValue::property() const
{
    Q_D(const FunctionValue);
    return d->function;
}

Function *FunctionValue::function() const
{
    Q_D(const FunctionValue);
    return d->function;
}

QVariant FunctionValue::value(const Entity *entity) const
{
    Q_D(const FunctionValue);

    if(d->function->isCalculated()) {
        if(!d->function->cacheData()) {
            return const_cast<FunctionValuePrivate*>(d)->calculate(entity);
        }
        if(!d->cached) {
            d->values = const_cast<FunctionValuePrivate*>(d)->calculate();
            d->cached = true;
        }
    }

    return d->values.value(entity);
}

QVariant FunctionValue::data(int role) const
{
    Q_D(const FunctionValue);
    Q_UNUSED(role);

    if(d->function->isCalculated()) {
        if(!d->function->cacheData()) {
            return QVariant::fromValue<QHash<const Entity *, QVariant> >(const_cast<FunctionValuePrivate*>(d)->calculate());
        }
        if(!d->cached) {
            d->values = const_cast<FunctionValuePrivate*>(d)->calculate();
            d->cached = true;
        }
    }

    if(role == Qt::DisplayRole) {
        if(d->values.isEmpty())
            return QVariant();

        if(d->values.size() == 1) {
            const Entity *key = d->values.keys().at(0);
            QVariant value = d->values.value(key);
            return QVariant(key->displayName() + QLatin1String("=") + value.toString());
        }

        return QVariant(QString::number(d->values.size()) +QLatin1String(" values"));
    }
    else if(role == PropertyValue::PlainDataRole) {
        return QVariant::fromValue<QHash<const Entity *, QVariant> >(d->values);
    }

    return QVariant();
}

bool FunctionValue::setData(const QVariant &data)
{
    return false;
}

QHash<const Entity *, QVariant> FunctionValue::values() const
{
    Q_D(const FunctionValue);

    return d->values;
}

void FunctionValue::setValue(const Entity *key, const QVariant &value)
{
    Q_D(const FunctionValue);
    if(d->function->isCalculated())
        return;

    if(d->values.value(key) == value)
        return;

    FunctionValueData data;
    data.entityId = d->entity->id();
    data.keyEntityId = key->id();
    data.value = value;
    data.rowId = 0;

    d->entity->storage()->driver()->setFunctionValue(this, data);
    d->values.insert(key, value);
    emit valueChanged(key, value);
}

bool FunctionValue::isEditable() const
{
    return false;
}

} // namespace LBDatabase
