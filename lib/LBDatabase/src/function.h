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
public:
    ~Function();

    // Property implementation
    int id() const;
    QString displayName() const;
    QString identifier() const;
    Property::Type propertyType() const;

    // General
    bool isCalculated() const;
    bool cacheData() const;
    bool isEditable() const;

    EntityType *keyEntityType() const;

    // Used by drivers
    QString tableName() const;
    QString entityColumnName() const;
    QString keyEntityColumnName() const;
    QString valueColumnName() const;

    // Used for export
    QString qtTypeName() const;
    QList<EntityType *> reimplementingEntityTypes() const;

private:
    friend class StoragePrivate;
    friend class FunctionValue;

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
    bool calculated;
    bool cacheData;
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
