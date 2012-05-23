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
    static const QString IdentifierColumn;
    static const QString DisplayNameColumn;
    static const QString TableNameColumn;
    static const QString EntityColumnNameColumn;
    static const QString KeyEntityColumnNameColumn;
    static const QString ValueColumnNameColumn;
    static const QString EntityTypeColumn;
    static const QString KeyEntityTypeRightColumn;
    static const QString CalculatedColumn;
    static const QString CacheDataColumn;
    static const QString TypeColumn;
    static const QString EditableColumn;


    static const QString FunctionReimplementationsTable;
    static const QString ReimplementedFunctionColumn;
    static const QString ReimplementingEntityTypeColumn;

    ~Function();

    int id() const;
    QString displayName() const;
    QString identifier() const;

    QString tableName() const;
    QString entityColumnName() const;
    QString keyEntityColumnName() const;
    QString valueColumnName() const;

    EntityType *keyEntityType() const;
    QString qtTypeName() const;

    bool isCalculated() const;
    bool cacheData() const;
    bool isEditable() const;

    QList<EntityType *> reimplementingEntityTypes() const;

    Property::Type propertyType() const;

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
