#include "enumattribute.h"

#include "attribute_p.h"
#include "entitytype.h"
#include "storage.h"

#include <QStringList>
#include <QDebug>

namespace LBDatabase {

const QString EnumAttribute::EnumsTable("lbmeta_enums");
const QString EnumAttribute::AttributeColumn("attribute");
const QString EnumAttribute::IdentifierColumn("name");
const QString EnumAttribute::ValueColumn("value");


class EnumAttributePrivate : public AttributePrivate {
    void init();

    QMap<int, QString> enumValues;

    Q_DECLARE_PUBLIC(EnumAttribute)
};

void EnumAttributePrivate::init()
{
    AttributePrivate::init();
}

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
