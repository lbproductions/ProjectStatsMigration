#ifndef LBDATABASE_STORAGEDRIVER_H
#define LBDATABASE_STORAGEDRIVER_H

#include <QObject>

#include <QPair>

#include "attribute.h"

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
class RelationReimplementationMetaData;

class StorageDriver : public QObject
{
    Q_OBJECT
public:
    explicit StorageDriver(QObject *parent = 0);

    virtual bool init() = 0;

    // MetaData
    virtual QList<ContextMetaData> contexts() const = 0;
    virtual QList<EntityTypeMetaData> entityTypes() const = 0;
    virtual QList<AttributeMetaData> attributes() const = 0;
    virtual QList<FunctionMetaData> functions() const = 0;
    virtual QList<RelationMetaData> relations() const = 0;

    virtual QList<EnumAttributeMetaData> enumValues() const = 0;
    virtual QList<FunctionReimplementationMetaData> functionReimplementations() const = 0;
    virtual QList<RelationReimplementationMetaData> relationReimplementations() const = 0;

    // Attributes
    virtual QVariant attributeValue(const AttributeValue *value) const = 0;
    virtual void setAttributeValue(const AttributeValue *value, const QVariant &data) = 0;

    virtual void addAttribute(EntityType *entityType, AttributeMetaData &metaData) = 0;
    virtual void removeAttribute(int attributeId) = 0;

    virtual void setAttributeDisplayName(int id, const QString &displayName) = 0;
    virtual void setAttributeIdentifier(int id, const QString &identifier) = 0;
    virtual void setAttributeType(int id, Attribute::Type type) = 0;
    virtual void setAttributeEditable(int id, bool editable) = 0;
    virtual void setAttributeCalculated(int id, bool calculated) = 0;
    virtual void setAttributeCached(int id, bool cached) = 0;
    virtual void setAttributeDefaultValue(int id, QVariant defaultValue) = 0;

    // Relations
    virtual QList<RelationValueData> relatedEntities(Relation *relation) const = 0;
    virtual int addRelatedEntity(RelationValueBase *value, const RelationValueData &data) = 0;

    // Functions
    virtual QList<FunctionValueData> functionValues(Function *function) const = 0;
    virtual void setFunctionValue(FunctionValue *value, const FunctionValueData &data) = 0;
    
    // Entities
    virtual QList<EntityMetaData> entities(Context *context) const = 0;
    virtual EntityMetaData createEntity(EntityType *type) = 0;
};

} // namespace LBDatabase

#endif // LBDATABASE_STORAGEDRIVER_H
