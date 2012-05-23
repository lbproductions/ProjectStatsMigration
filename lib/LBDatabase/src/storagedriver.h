#ifndef LBDATABASE_STORAGEDRIVER_H
#define LBDATABASE_STORAGEDRIVER_H

#include <QObject>

#include <QPair>

namespace LBDatabase {

class AttributeValue;
class Context;
class Entity;
class EntityMetaData;
class EntityType;
class Function;
class FunctionValue;
class FunctionValueData;
class Relation;
class ContextMetaData;
class EntityTypeMetaData;
class AttributeMetaData;
class FunctionMetaData;
class RelationMetaData;
class RelationValueBase;

class EnumAttributeMetaData;
class FunctionReimplementationMetaData;
class RelationValueData;

class StorageDriverPrivate;
class StorageDriver : public QObject
{
    Q_OBJECT
public:
    explicit StorageDriver(QObject *parent = 0);
    ~StorageDriver();

    virtual void init() = 0;

    virtual QList<ContextMetaData> contexts() const = 0;
    virtual QList<EntityTypeMetaData> entityTypes() const = 0;
    virtual QList<AttributeMetaData> attributes() const = 0;
    virtual QList<FunctionMetaData> functions() const = 0;
    virtual QList<RelationMetaData> relations() const = 0;

    virtual QList<EnumAttributeMetaData> enumValues() const = 0;
    virtual QList<FunctionReimplementationMetaData> functionReimplementations() const = 0;

    virtual QVariant attributeValue(const AttributeValue *value) const = 0;
    virtual void setAttributeValue(const AttributeValue *value, const QVariant &value) = 0;

    virtual QList<RelationValueData> relatedEntities(Relation *relation) const = 0;
    virtual int addRelatedEntity(RelationValueBase *value, const RelationValueData &data) = 0;

    virtual QList<FunctionValueData> functionValues(Function *function) const = 0;
    virtual void setFunctionValue(FunctionValue *value, const FunctionValueData &data) = 0;
    
    virtual QList<EntityMetaData> entities(Context *context) const = 0;

    virtual EntityMetaData createEntity(EntityType *type) = 0;

private:
    QScopedPointer<StorageDriverPrivate> d_ptr;
    Q_DECLARE_PRIVATE(StorageDriver)
    Q_DISABLE_COPY(StorageDriver)
};

} // namespace LBDatabase

#endif // LBDATABASE_STORAGEDRIVER_H
