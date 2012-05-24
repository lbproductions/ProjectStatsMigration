#include "enumattribute.h"

#include "attribute_p.h"
#include "entitytype.h"
#include "storage.h"

#include <QStringList>
#include <QDebug>

namespace LBDatabase {


class EnumAttributePrivate : public AttributePrivate {
    QMap<int, QString> enumValues;

    Q_DECLARE_PUBLIC(EnumAttribute)
};

EnumAttribute::EnumAttribute(const AttributeMetaData &metaData, Storage *parent) :
    Attribute(*new EnumAttributePrivate, metaData, parent)
{
}

Property::Type EnumAttribute::propertyType() const
{
    return Property::EnumAttribute;
}

QString EnumAttribute::stringValue(int value) const
{
    Q_D(const EnumAttribute);
    return d->enumValues.value(value);
}

QString EnumAttribute::typeName() const
{
    Q_D(const EnumAttribute);
    return d->metaData.identifier;
}

QString EnumAttribute::qtType() const
{
    return typeName().left(1).toUpper() + typeName().mid(1);
}

QMap<int, QString> EnumAttribute::enumValues() const
{
    Q_D(const EnumAttribute);
    return d->enumValues;
}

void EnumAttribute::addEnumValue(const QString &name, int value)
{
    Q_D(EnumAttribute);
    d->enumValues.insert(value, name);
}

} // namespace LBDatabase
