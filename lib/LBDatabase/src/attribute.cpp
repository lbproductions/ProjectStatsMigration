#include "attribute.h"
#include "attribute_p.h"

#include "attributevalue.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "storage.h"
#include "storagedriver.h"

#include <QStringList>
#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** AttributePrivate
*/
void AttributePrivate::init()
{
    Q_Q(Attribute);

    entityType = storage->entityType(metaData.entityTypeId);
    if(!entityType) {
        qWarning() << "No such entity type:" << metaData.entityTypeId;
        return;
    }

    entityType->addAttribute(q);
    entityType->context()->addAttribute(q);
}

void AttributePrivate::addPropertyValueToEntities()
{
    foreach(Entity *entity, entityType->entities()) {
        addPropertyValue(entity);
    }
}

void AttributePrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Attribute);
    entity->addAttributeValue(new AttributeValue(q, entity));
}

void AttributePrivate::fetchValues()
{
}

/******************************************************************************
** Attribute
*/
/*!
  \class Attribute
  \brief The Attribute class represents a simple single-value property of an
  EntityType.

  \ingroup highlevel-database-classes

  \todo Document when class is done.

  */

/*!
  \var Attribute::d_ptr
  \internal
  */

/*!
  \enum Attribute::Type

  This enumeration describes the type stored in the attribute.

  */

/*!
  \enum Attribute::PrefetchStrategy
  \brief Describes if and when the value of an attribute will be prefetched.
  */

/*!
  Creates an attribute, which contains the meta data from \a row in the given \a
  storage.
  */
Attribute::Attribute(const AttributeMetaData &metaData, Storage *parent) :
    Property(parent),
    d_ptr(new AttributePrivate)
{
    Q_D(Attribute);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

Attribute::Attribute(AttributePrivate &dd, const AttributeMetaData &metaData, Storage *parent) :
    Property(parent),
    d_ptr(&dd)
{
    Q_D(Attribute);
    d->q_ptr = this;
    d->metaData = metaData;
    d->storage = parent;
    d->init();
}

/*!
  Adds an AttributeValue instance to every existing Entity of the corrent
  EntityType.
  */
void Attribute::addPropertyValueToEntities()
{
    Q_D(Attribute);
    d->addPropertyValueToEntities();
}

/*!
  Adds an AttributeValue instance to the given \a entity.
  */
void Attribute::addPropertyValue(Entity *entity)
{
    Q_D(Attribute);
    d->addPropertyValue(entity);
}

void Attribute::fetchValues()
{
    Q_D(Attribute);
    d->fetchValues();
}

/*!
  Destroys the attribute.
  */
Attribute::~Attribute()
{
}

/*!
  Returns the storage-global ID of the attribute.
  */
int Attribute::id() const
{
    Q_D(const Attribute);
    return d->metaData.id;
}

/*!
  Returns the name of the attribute. if the attribute is stored in the database
  this name is the name of the column where it is stored.
  */
QString Attribute::identifier() const
{
    Q_D(const Attribute);
    return d->metaData.identifier;
}

bool Attribute::isCalculated() const
{
    Q_D(const Attribute);
    return d->metaData.calculated;
}

void Attribute::setDisplayName(const QString &displayName)
{
    Q_D(Attribute);
    if(displayName == d->metaData.displayName)
        return;

    d->metaData.displayName = displayName;
    d->storage->driver()->setAttributeDisplayName(d->metaData.id, displayName);
    emit displayNameChanged(displayName);
}

void Attribute::setIdentifier(const QString &identifier)
{
    Q_D(Attribute);
    if(identifier == d->metaData.identifier)
        return;

    d->metaData.identifier = identifier;
    d->storage->driver()->setAttributeIdentifier(d->metaData.id, identifier);
    emit identifierChanged(identifier);
}

bool Attribute::isCached() const
{
    Q_D(const Attribute);
    return d->metaData.cached;
}

void Attribute::setCached(bool cached)
{
    Q_D(Attribute);
    if(cached == d->metaData.cached)
        return;

    d->metaData.cached = cached;
    d->storage->driver()->setAttributeCached(d->metaData.id, cached);
    emit cachedChanged(cached);
}

EntityType *Attribute::entityType() const
{
    Q_D(const Attribute);
    return d->entityType;
}

bool Attribute::isEditable() const
{
    Q_D(const Attribute);
    return d->metaData.editable;
}

Property::Type Attribute::propertyType() const
{
    return Property::Attribute;
}

/*!
  Returns the display name of the attribute. Since each Attribute can only be
  part of one Context, the \a context parameter will be ignored.
  */
QString Attribute::displayName() const
{
    Q_D(const Attribute);
    return d->metaData.displayName;
}

Attribute::Type Attribute::type() const
{
    Q_D(const Attribute);
    return d->metaData.type;
}

void Attribute::setType(Attribute::Type type)
{
    Q_D(Attribute);
    if(type == d->metaData.type)
        return;

    d->metaData.type = type;
    d->storage->driver()->setAttributeType(d->metaData.id, type);
    emit typeChanged(type);
}

void Attribute::setEditable(bool editable)
{
    Q_D(Attribute);
    if(editable == d->metaData.editable)
        return;

    d->metaData.editable = editable;
    d->storage->driver()->setAttributeEditable(d->metaData.id, editable);
    emit editableChanged(editable);
}

void Attribute::setCalculated(bool calculated)
{
    Q_D(Attribute);
    if(calculated == d->metaData.calculated)
        return;

    d->metaData.calculated = calculated;
    d->storage->driver()->setAttributeCalculated(d->metaData.id, calculated);
    emit calculatedChanged(calculated);
}

QString Attribute::typeName() const
{
    Q_D(const Attribute);
    return Attribute::typeToName(d->metaData.type);
}

QString Attribute::typeToName(Type type)
{
    return Attribute::typeNames().at(static_cast<int>(type));
}

QStringList Attribute::typeNames()
{
    QStringList names;
    names << "Unkown" <<
    "Text" <<
    "Integer" <<
    "Real" <<
    "Icon" <<
    "Pixmap" <<
    "DateTime" <<
    "Time" <<
    "Bool" <<
    "Color" <<
    "Enum";
    return names;
}

Attribute::Type Attribute::typeNameToType(const QString &typeName)
{
    return static_cast<Type>(typeNames().indexOf(typeName));
}

QString Attribute::qtType() const
{
    Q_D(const Attribute);
    return Attribute::typeToQtType(d->metaData.type);
}

QString Attribute::typeToQtType(Type type)
{
    return Attribute::qtTypeNames().at(static_cast<int>(type));
}

QStringList Attribute::qtTypeNames()
{
    QStringList names;
    names << "QVariant" << //Unknown
    "QString" << //Text
    "int" << //Integer
    "double" << //Real
    "QIcon" << //Icon
    "QPixmap" << //Pixmap
    "QDateTime" << //DateTime
    "QTime" << //Time
    "bool" << //Bool
    "QColor" << //Color
    "Enum"; //Enum
    return names;
}

} // namespace LBDatabase
