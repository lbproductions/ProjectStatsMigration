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

    QHash<const Entity *, QVariant> calculate() const;

    Entity *entity;
    Function *function;

    mutable bool cached;

    mutable QHash<const Entity *, int> rowIds;
    mutable QHash<const Entity *, QVariant> values;

    FunctionValue * q_ptr;
    Q_DECLARE_PUBLIC(FunctionValue)
};

QHash<const Entity *, QVariant> FunctionValuePrivate::calculate() const
{
    Q_Q(const FunctionValue);
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
    if(!function->isCalculated())
        d->cached = true; // this is not correct yet, but it will be after the storage has been initialized,
                          // so there is no harm, when we set cached=true right now.

    connect(this, SIGNAL(changed()), entity()->context(), SLOT(onPropertyValueChanged()));
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
    return values().value(entity);
}

QVariant FunctionValue::dataForModel(int role) const
{
    Q_D(const FunctionValue);
    Q_UNUSED(role);

    QHash<const Entity *, QVariant> v = values();

    if(role == Qt::DisplayRole) {
        if(v.isEmpty())
            return QLatin1String("No values");

        if(d->values.size() == 1) {
            const Entity *key = v.keys().at(0);
            QVariant variant = v.value(key);
            if(function()->type() == Attribute::Entity)
                return QVariant(key->displayName() + QLatin1String(" = ") + function()->returnEntityType()->displayName());
            else if(function()->type() == Attribute::EntityList) {
                return QVariant(key->displayName() + QLatin1String(" = ") +
                                function()->returnEntityType()->displayNamePlural());
            }
            else {
                return QVariant(key->displayName() + QLatin1String(" = ") + variant.toString());
            }
        }

        return QVariant(QString::number(v.size()) +QLatin1String(" values"));
    }
    else if(role == PropertyValue::PlainDataRole) {
        return QVariant::fromValue<QHash<const Entity *, QVariant> >(v);
    }

    return QVariant();
}

QVariant FunctionValue::value() const
{
    return dataForModel(PropertyValue::PlainDataRole);
}

QHash<const Entity *, QVariant> FunctionValue::values() const
{
    Q_D(const FunctionValue);

    if(d->cached)
        return d->values; // for non calculated functions this should always happen...

    //...so that everything here only applies to calculated functions
    d->values = const_cast<FunctionValuePrivate*>(d)->calculate();
    d->cached = true;

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
    data.rowId = d->rowIds.value(key);

    d->entity->storage()->driver()->setFunctionValue(this, data);
    d->values.insert(key, value);
    emit valueChanged(key, value);
    emit changed();
}

void FunctionValue::recalculateAfterDependencyChange()
{
    Q_D(FunctionValue);
    if(!d->function->isCalculated())
        return; // non-calculated functions must not be recalculated!

    QHash<const Entity *, QVariant> newValues = d->calculate();

    qDebug() << d->function->identifier() << "of" << d->entity->displayName() << "recalculating.";

    if(!function()->returnEntityType()) // cannot compare custom types
        if(d->cached && newValues == d->values)
            return; // no change

    if(d->function->isCached()) {
        d->values = newValues;
        d->cached = true;
    }

    emit changed();
}

} // namespace LBDatabase
