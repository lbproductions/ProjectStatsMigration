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

    void init();
    void fetchValue();
    QVariant calculate();

    Entity *entity;
    Attribute *attribute;

    mutable QVariant cachedData;
    mutable bool cached;

    AttributeValue * q_ptr;
    Q_DECLARE_PUBLIC(AttributeValue)
};

void AttributeValuePrivate::init()
{
}

void AttributeValuePrivate::fetchValue()
{
}

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
    d->init();
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
QVariant AttributeValue::data(int role) const
{
    Q_UNUSED(role);
    Q_D(const AttributeValue);

    if(d->attribute->type() == Attribute::Enum)
        return d->entity->storage()->driver()->attributeValue(this);

    if(d->cached)
        return d->cachedData;

    QVariant value = d->entity->storage()->driver()->attributeValue(this);

    if(d->attribute->cacheData()) {
        d->cachedData = value;
        d->cached = true;
    }
    return value;
}

/*!
  Sets the value of the attribute to \a data.

  Does nothing if the attribute is not editable.
  */
bool AttributeValue::setData(const QVariant &data)
{
    Q_D(AttributeValue);
    if(!isEditable())
        return false;

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
  Returns true.
  */
bool AttributeValue::isEditable() const
{
    Q_D(const AttributeValue);
    return !d->attribute->isCalculated() && d->attribute->isEditable();
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

/*!
  Reads the value of the attribute from the database.
  */
void AttributeValue::fetchValue()
{
    Q_D(AttributeValue);
    d->fetchValue();
}

QVariant AttributeValue::calculate()
{
    Q_D(AttributeValue);
    return d->calculate();
}

} // namespace LBDatabase
