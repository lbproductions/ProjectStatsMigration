#ifndef LBDATABASE_ENUMATTRIBUTE_H
#define LBDATABASE_ENUMATTRIBUTE_H

#include "attribute.h"

#include <QMap>

namespace LBDatabase {

class EnumAttributePrivate;
class EnumAttribute : public LBDatabase::Attribute
{
    Q_OBJECT
public:

    QString stringValue(int value) const;

    QString typeName() const;
    QString qtType() const;

    QMap<int, QString> enumValues() const;

    Property::Type propertyType() const;

private:
    friend class StoragePrivate;
    EnumAttribute(const AttributeMetaData &metaData, Storage *parent);

    void addEnumValue(const QString &identifier, int value);

    Q_DECLARE_PRIVATE(EnumAttribute)
};

class EnumAttributeMetaData
{
public:
    int attributeId;
    QString identifier;
    int value;
};

} // namespace LBDatabase

#endif // LBDATABASE_ENUMATTRIBUTE_H
