#ifndef LBDATABASE_STORAGEDRIVER_H
#define LBDATABASE_STORAGEDRIVER_H

#include <QObject>

#include <QPair>

#include "attribute.h"
#include "relation.h"

namespace LBDatabase {

namespace LBMeta {
const QString MetaDataTableName("lbmeta");
const QString ContextsTableName("lbmeta_contexts");
const QString EntitiesTableName("lbmeta_entitytypes");
const QString AttributesTableName("lbmeta_attributes");
const QString RelationsTableName("lbmeta_relations");
const QString FunctionsTableName("lbmeta_functions");
const QString FunctionReimplementationsTable("lbmeta_functionreimplementations");
const QString RelationReimplementationsTable("lbmeta_relationreimplementations");
const QString DependenciesTable("lbmeta_dependencies");

namespace ContextColumns {
const QString Identifier("identifier");
const QString DisplayName("displayName");
const QString TableName("tableName");
}
namespace EntityTypeColumns {
const QString Context("context");
const QString Identifier("identifier");
const QString ParentEntityType("parentEntityType");
const QString DisplayName("displayName");
const QString DisplayNamePlural("displayNamePlural");
}
namespace EntityColumns {
const QString Id("id");
const QString EntityType("entityTypeId");
}
namespace AttributeColumns {
const QString Identifier("identifier");
const QString DisplayName("displayName");
const QString EntityTypeId("entityTypeId");
const QString Calculated("calculated");
const QString CacheData("cacheData");
const QString Type("type");
const QString ReturnEntityType("returnEntityType");
const QString Editable("editable");
const QString DefaultValue("defaultValue");
}
namespace FunctionColumns {
const QString Identifier("identifier");
const QString TableName("tableName");
const QString EntityColumnName("entityColumnName");
const QString KeyEntityColumnName("keyEntityColumnName");
const QString ValueColumnName("valueColumnName");
const QString DisplayName("displayName");
const QString EntityType("entityType");
const QString KeyEntityType("keyEntityType");
const QString Calculated("calculated");
const QString CacheData("cacheData");
const QString Type("type");
const QString ReturnEntityType("returnEntityType");
const QString Editable("editable");
}
namespace FunctionReimplementationsColumns {
const QString ReimplementedFunction("function");
const QString ReimplementingEntityType("reimplementingEntityType");
}
namespace RelationColumns {
const QString Identifier("identifier");
const QString IdentifierRight("identifierRight");
const QString DisplayNameLeft("displayName");
const QString DisplayNameRight("displayNameRight");
const QString EntityTypeLeft("entitytypeleft");
const QString EntityTypeRight("entitytyperight");
const QString Cardinality("cardinality");
const QString TableName("tableName");
const QString ColumnName("columnName");
const QString ColumnNameRight("columnNameRight");
const QString Editable("editable");
const QString EditableTranspose("editableTranspose");
const QString Calculated("calculated");
const QString Direction("direction");
}
namespace RelationReimplementationsColumns {
const QString ReimplementedRelation("relation");
const QString ReimplementingEntityType("reimplementingEntityType");
}
namespace EnumAttributeColumns {
const QString Attribute("attribute");
const QString Identifier("name");
const QString Value("value");
}
namespace DependenciesColumns {
const QString DependendPropertyId("dependendPropertyId");
const QString DependencyPropertyId("dependencyPropertyId");
const QString DependendPropertyType("dependendPropertyType");
const QString DependencyPropertyType("dependencyPropertyType");
const QString EntityRelation("entityRelation");
}
}

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
class DependencyMetaData;

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
    virtual QList<DependencyMetaData> dependencies() const = 0;

    virtual void addDependency(DependencyMetaData &metaData) = 0;

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

    virtual void addRelation(EntityType *entityType, RelationMetaData &metaData) = 0;

    virtual void setRelationIdentifier(int id, const QString &identifier) = 0;
    virtual void setRelationIdentifierRight(int id, const QString &identifierRight) = 0;
    virtual void setRelationDisplayName(int id, const QString &displayName) = 0;
    virtual void setRelationDisplayNameRight(int id, const QString &displayNameRight) = 0;
    virtual void setRelationCardinality(int id, Relation::Cardinality cardinality) = 0;
    virtual void setRelationDirection(int id, Relation::Direction direction) = 0;
    virtual void setRelationEntityTypeRight(int id, EntityType *entityType) = 0;
    virtual void setRelationEditable(int id, bool editable) = 0;
    virtual void setRelationCalculated(int id, bool calculated) = 0;

    // Functions
    virtual QList<FunctionValueData> functionValues(Function *function) const = 0;
    virtual void setFunctionValue(FunctionValue *value, const FunctionValueData &data) = 0;

    virtual void addFunction(EntityType *entityType, FunctionMetaData &metaData) = 0;

    virtual void setFunctionDisplayName(int id, const QString &displayName) = 0;
    virtual void setFunctionIdentifier(int id, const QString &identifier) = 0;
    virtual void setFunctionType(int id, Attribute::Type type) = 0;
    virtual void setFunctionEditable(int id, bool editable) = 0;
    virtual void setFunctionKeyEntityType(int id, EntityType *entityType) = 0;
    
    // Entities
    virtual QList<EntityMetaData> entities(Context *context) const = 0;
    virtual EntityMetaData createEntity(EntityType *type) = 0;
};

} // namespace LBDatabase

#endif // LBDATABASE_STORAGEDRIVER_H
