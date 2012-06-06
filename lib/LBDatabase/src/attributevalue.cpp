#include "attributevalue.h"

#include "attribute.h"
#include "calculator.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "enumattribute.h"
#include "storage.h"
#include "storagedriver.h"

#include <QVariant>

namespace LBDatabase {

/******************************************************************************
** AttributeValuePrivate
*/
class AttributeValuePrivate {
    AttributeValuePrivate() : cached(false) {}

    QVariant calculate();

    Entity *entity;
    Attribute *attribute;

    mutable QVariant cachedData;
    mutable bool cached;

    AttributeValue * q_ptr;
    Q_DECLARE_PUBLIC(AttributeValue)
};

QVariant AttributeValuePrivate::calculate()
{
    Q_Q(AttributeValue);
    Calculator *calculator = entity->entityType()->calculator();
    if(!calculator)
        return QVariant();

    return calculator->calculate(entity,q);
}

/******************************************************************************
** AttributeValue
*/
/*!
  \class AttributeValue
  \brief The AttributeValue class represents a value of an Attribute of a
  concrete Entity instance.

  \ingroup highlevel-database-classes

  \todo Document when done.
  */

/*!
  \var AttributeValue::d_ptr
  \internal
  */

/*!
  Creates an AttributeValue instance, which represents a conrete property with
  the Attribute description \a attribute of the Entity \a parent.
  */
AttributeValue::AttributeValue(Attribute *attribute, Entity *parent) :
    PropertyValue(parent),
    d_ptr(new AttributeValuePrivate)
{
    Q_D(AttributeValue);
    d->q_ptr = this;
    d->attribute = attribute;
    d->entity = parent;
    connect(this, SIGNAL(changed()), entity()->context(), SLOT(onPropertyValueChanged()));
}

/*!
  Destroys the attribute value.
  */
AttributeValue::~AttributeValue()
{
}

/*!
  Returns the Entity to which this attribute value belongs.
  */
Entity *AttributeValue::entity() const
{
    Q_D(const AttributeValue);
    return d->entity;
}

/*!
  Returns the value of the attribute.

  The \a role parameter is currently being ignored.
  */
QVariant AttributeValue::dataForModel(int role) const
{
    Q_D(const AttributeValue);
    Q_UNUSED(role);

    if(d->attribute->propertyType() == Property::EnumAttribute)
        return static_cast<EnumAttribute *>(d->attribute)->stringValue(value().toInt());

    return value();
}

/*!
  Sets the value of the attribute to \a data.

  Does nothing if the attribute is not editable.
  */
bool AttributeValue::setData(const QVariant &data)
{
    Q_D(AttributeValue);
    if(!d->attribute->isEditable())
        return false;

    if(data == d->cachedData)
        return true;

    d->entity->storage()->driver()->setAttributeValue(this, data);

    if(d->attribute->cacheData()) {
        d->cachedData = data;
        d->cached = true;
    }
    emit changed();
    emit dataChanged(data);
    return true;
}

/*!
  Returns the Property instance, which describes this attribute value.
  */
Property *AttributeValue::property() const
{
    Q_D(const AttributeValue);
    return d->attribute;
}

Attribute *AttributeValue::attribute() const
{
    Q_D(const AttributeValue);
    return d->attribute;
}

QVariant AttributeValue::value() const
{
    Q_D(const AttributeValue);

    if(d->cached)
        return d->cachedData;

    QVariant value;
    if(d->attribute->isCalculated())
        value = const_cast<AttributeValue *>(this)->calculate();
    else
        value = d->entity->storage()->driver()->attributeValue(this);

    if(d->attribute->cacheData()) {
        d->cachedData = value;
        d->cached = true;
    }
    return value;
}

QVariant AttributeValue::calculate()
{
    Q_D(AttributeValue);
    return d->calculate();
}

} // namespace LBDatabase
