#ifndef LBDATABASE_LOCALSTORAGEDRIVER_H
#define LBDATABASE_LOCALSTORAGEDRIVER_H

#include "../storagedriver.h"

namespace LBDatabase {

class LocalStorageDriverPrivate;
class LocalStorageDriver : public StorageDriver
{
public:
    LocalStorageDriver(const QString &fileName, QObject *parent);
    ~LocalStorageDriver();

    void init();

    QList<ContextMetaData> contexts() const;
    QList<EntityTypeMetaData> entityTypes() const;
    QList<AttributeMetaData> attributes() const;
    QList<FunctionMetaData> functions() const;
    QList<RelationMetaData> relations() const;

    QList<EnumAttributeMetaData> enumValues() const;
    QList<FunctionReimplementationMetaData> functionReimplementations() const;

    QVariant attributeValue(const AttributeValue *attribute) const;
    void setAttributeValue(const AttributeValue *attribute, const QVariant &value);

    QList<RelationValueData> relatedEntities(Relation *relation) const;
    int addRelatedEntity(RelationValueBase *value, const RelationValueData &data);

    QList<FunctionValueData> functionValues(Function *function) const;
    void setFunctionValue(FunctionValue *function, const FunctionValueData &data);

    QList<EntityMetaData> entities(Context *context) const;

    EntityMetaData createEntity(EntityType *type);

private:
    QScopedPointer<LocalStorageDriverPrivate> d_ptr;
    Q_DECLARE_PRIVATE(LocalStorageDriver)
    Q_DISABLE_COPY(LocalStorageDriver)
};

} // namespace LBDatabase

#endif // LBDATABASE_LOCALSTORAGEDRIVER_H
