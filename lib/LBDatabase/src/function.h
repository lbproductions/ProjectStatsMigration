#ifndef LBDATABASE_FUNCTION_H
#define LBDATABASE_FUNCTION_H

#include "property.h"

#include "attribute.h"

namespace LBDatabase {

class EntityType;
class FunctionMetaData;
class Storage;

class FunctionPrivate;
class Function : public Property
{
    Q_OBJECT
public:
    ~Function();

    // Property implementation
    int id() const;
    QString displayName() const;
    QString identifier() const;
    Property::Type propertyType() const;
    bool isEditable() const;
    bool isCalculated() const;
    EntityType *entityType() const;
    QList<PropertyValue *> propertyValues() const;

    // General
    bool isCached() const;
    Attribute::Type type() const;

    void setDisplayName(const QString &displayName);
    void setIdentifier(const QString &identifier);
    void setType(Attribute::Type type);
    void setEditable(bool editable);

    EntityType *keyEntityType() const;
    void setKeyEntityType(EntityType *keyEntityType);

    // Used by drivers
    QString tableName() const;
    QString entityColumnName() const;
    QString keyEntityColumnName() const;
    QString valueColumnName() const;

    // Used for export
    QString qtTypeName() const;
    QList<EntityType *> reimplementingEntityTypes() const;

    EntityType *returnEntityType() const;

    QString signalSignature() const;

Q_SIGNALS:
    void identifierChanged(QString);
    void typeChanged(Attribute::Type);
    void editableChanged(bool);
    void keyEntityTypeChanged(EntityType *);

private:
    friend class StoragePrivate;
    friend class FunctionValue;
    friend class EntityType;

    explicit Function(const FunctionMetaData &metaData, Storage *parent);

    void addReimplementingEntityType(EntityType *type);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    QScopedPointer<FunctionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Function)
    Q_DISABLE_COPY(Function)
};

class FunctionMetaData
{
public:
    int id;
    int entityTypeId;
    int keyEntityTypeId;
    Attribute::Type type;
    int returnEntityTypeId;
    bool calculated;
    bool cached;
    bool editable;
    QString identifier;
    QString displayName;
    QString tableName;
    QString entityColumnName;
    QString keyEntityColumnName;
    QString valueColumnName;
};

class FunctionReimplementationMetaData
{
public:
    int reimplementedFunctionId;
    int reimplementingEntityTypeId;
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTION_H
