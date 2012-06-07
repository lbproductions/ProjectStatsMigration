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

    bool init();

    // MetaData
    QList<ContextMetaData> contexts() const;
    QList<EntityTypeMetaData> entityTypes() const;
    QList<AttributeMetaData> attributes() const;
    QList<FunctionMetaData> functions() const;
    QList<RelationMetaData> relations() const;

    QList<EnumAttributeMetaData> enumValues() const;
    QList<FunctionReimplementationMetaData> functionReimplementations() const;
    QList<RelationReimplementationMetaData> relationReimplementations() const;

    // Attributes
    QVariant attributeValue(const AttributeValue *value) const;
    void setAttributeValue(const AttributeValue *value, const QVariant &data);

    AttributeMetaData addAttribute(int entityTypeId);
    void removeAttribute(int attributeId);

    void setAttributeDisplayName(int id, const QString &displayName);
    void setAttributeIdentifier(int id, const QString &identifier);
    void setAttributeType(int id, Attribute::Type type);
    void setAttributeEditable(int id, bool editable);
    void setAttributeCalculated(int id, bool calculated);
    void setAttributeCached(int id, bool cached);

    // Relations
    QList<RelationValueData> relatedEntities(Relation *relation) const;
    int addRelatedEntity(RelationValueBase *value, const RelationValueData &data);

    // Functions
    QList<FunctionValueData> functionValues(Function *function) const;
    void setFunctionValue(FunctionValue *value, const FunctionValueData &data);

    // Entities
    QList<EntityMetaData> entities(Context *context) const;
    EntityMetaData createEntity(EntityType *type);

private:
    QScopedPointer<LocalStorageDriverPrivate> d_ptr;
    Q_DECLARE_PRIVATE(LocalStorageDriver)
    Q_DISABLE_COPY(LocalStorageDriver)
};

} // namespace LBDatabase

#endif // LBDATABASE_LOCALSTORAGEDRIVER_H
