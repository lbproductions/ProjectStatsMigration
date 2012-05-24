#ifndef LBDATABASE_ATTRIBUTE_H
#define LBDATABASE_ATTRIBUTE_H

#include "property.h"

namespace LBDatabase {

class AttributeMetaData;
class EntityType;
class Storage;

class AttributePrivate;
class Attribute : public Property
{
    Q_OBJECT
public:
    enum Type {
        Unkown,     // 0
        Text,       // 1
        Integer,    // 2
        Real,       // 3
        Icon,       // 4
        Pixmap,     // 5
        DateTime,   // 6
        Time,       // 7
        Bool,       // 8
        Color,      // 9
        Enum        //10
    };

    ~Attribute();


    // Property implementation
    int id() const;
    QString displayName() const;
    QString identifier() const;
    Property::Type propertyType() const;

    // General
    bool isCalculated() const;
    bool cacheData() const;
    bool isEditable() const;

    // Used for export
    Type type() const;
    virtual QString typeName() const;
    static QString typeToName(Type type);
    static QStringList typeNames();

    virtual QString qtType() const;
    static QStringList qtTypeNames();
    static QString typeToQtType(Type type);

    // Used by drivers
    int columnIndex() const;

protected:
    friend class StoragePrivate;
    friend class EntityTypePrivate;

    explicit Attribute(const AttributeMetaData &metaData, Storage *parent);
    explicit Attribute(AttributePrivate &dd, const AttributeMetaData &metaData, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);

    void fetchValues();

    QScopedPointer<AttributePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Attribute)
    Q_DISABLE_COPY(Attribute)
};

class AttributeMetaData
{
public:
    int id;
    int entityTypeId;

    QString identifier;
    QString displayName;
    bool calculated;
    bool cacheData;
    bool editable;
    Attribute::Type type;
};

} // namespace LBDatabase

#endif // LBDATABASE_ATTRIBUTE_H
