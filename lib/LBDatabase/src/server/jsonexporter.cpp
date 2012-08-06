#include "jsonexporter.h"

#include "../attributevalue.h"
#include "../context.h"
#include "../entity.h"
#include "../enumattribute.h"
#include "../function.h"
#include "../functionvalue.h"
#include "../propertyvalue.h"
#include "../relationvalue.h"

#include <QxtCore/QxtJSON>

#include <QStringList>

namespace LBDatabase {

JsonExporter::JsonExporter()
{
}

QString JsonExporter::metaDataToJson(Storage *storage)
{
    QVariantHash hash;

    //Contexts
    QVariantList contexts;
    contexts.reserve(storage->contexts().size());
    foreach(Context *context, storage->contexts()) {
        QVariantHash contextMetaData;
        contextMetaData.insert("id", context->id());
        contextMetaData.insert(LBMeta::ContextColumns::Identifier, context->identifier());
        contextMetaData.insert(LBMeta::ContextColumns::DisplayName, context->displayName());
        contextMetaData.insert(LBMeta::ContextColumns::TableName, context->tableName());
        contexts.append(contextMetaData);
    }
    hash.insert(LBMeta::ContextsTableName, contexts);

    //EntityTypes
    QVariantList entityTypes;
    foreach(EntityType *type, storage->entityTypes()) {
        QVariantHash typeMetaData;
        typeMetaData.insert("id", type->id());
        typeMetaData.insert(LBMeta::EntityTypeColumns::Identifier, type->identifier());
        typeMetaData.insert(LBMeta::EntityTypeColumns::DisplayName, type->displayName());
        typeMetaData.insert(LBMeta::EntityTypeColumns::DisplayNamePlural, type->displayNamePlural());
        typeMetaData.insert(LBMeta::EntityTypeColumns::Context, type->context()->id());
        if(type->parentEntityType())
            typeMetaData.insert(LBMeta::EntityTypeColumns::ParentEntityType, type->parentEntityType()->id());
        else
            typeMetaData.insert(LBMeta::EntityTypeColumns::ParentEntityType, -1);
        entityTypes.append(typeMetaData);
    }
    hash.insert(LBMeta::EntitiesTableName, entityTypes);

    //Attributes
    QVariantList attributes;
    foreach(Attribute *attribute, storage->attributes()) {
        QVariantHash metaData;
        metaData.insert("id", attribute->id());
        metaData.insert(LBMeta::AttributeColumns::Identifier, attribute->identifier());
        metaData.insert(LBMeta::AttributeColumns::DisplayName, attribute->displayName());
        metaData.insert(LBMeta::AttributeColumns::CacheData, attribute->isCached());
        metaData.insert(LBMeta::AttributeColumns::Calculated, attribute->isCalculated());
        metaData.insert(LBMeta::AttributeColumns::Editable, attribute->isEditable());
        metaData.insert(LBMeta::AttributeColumns::EntityTypeId, attribute->entityType()->id());
        metaData.insert(LBMeta::AttributeColumns::Type, attribute->type());
        if(attribute->returnEntityType())
            metaData.insert(LBMeta::AttributeColumns::ReturnEntityType, attribute->returnEntityType()->id());
        else
            metaData.insert(LBMeta::AttributeColumns::ReturnEntityType, -1);
        metaData.insert(LBMeta::AttributeColumns::DefaultValue, attribute->defaultValue());
        attributes.append(metaData);
    }
    hash.insert(LBMeta::AttributesTableName, attributes);

    //Relations
    QVariantList relations;
    foreach(Relation *relation, storage->relations()) {
        if(!relation->isTranspose()) {
            QVariantHash metaData;
            metaData.insert("id", relation->id());
            metaData.insert(LBMeta::RelationColumns::Identifier, relation->identifier());
            metaData.insert(LBMeta::RelationColumns::IdentifierRight, relation->identifierRight());
            metaData.insert(LBMeta::RelationColumns::DisplayNameLeft, relation->displayName());
            metaData.insert(LBMeta::RelationColumns::DisplayNameRight, relation->displayNameRight());
            metaData.insert(LBMeta::RelationColumns::Cardinality, relation->cardinality());
            metaData.insert(LBMeta::RelationColumns::Direction, relation->direction());
            metaData.insert(LBMeta::RelationColumns::Editable, relation->isEditable());
            metaData.insert(LBMeta::RelationColumns::EditableTranspose, relation->isEditableTranspose());
            metaData.insert(LBMeta::RelationColumns::Calculated, relation->isCalculated());
            metaData.insert(LBMeta::RelationColumns::EntityTypeLeft, relation->entityType()->id());
            metaData.insert(LBMeta::RelationColumns::EntityTypeRight, relation->entityTypeOther()->id());
            metaData.insert(LBMeta::RelationColumns::ColumnName, relation->leftEntityIdColumnName());
            metaData.insert(LBMeta::RelationColumns::ColumnNameRight, relation->rightEntityIdColumnName());
            metaData.insert(LBMeta::RelationColumns::TableName, relation->tableName());
            relations.append(metaData);
        }
    }
    hash.insert(LBMeta::RelationsTableName, relations);

    //Functions
    QVariantList functions;
    foreach(Function *function, storage->functions()) {
        QVariantHash metaData;
        metaData.insert("id", function->id());
        metaData.insert(LBMeta::FunctionColumns::Identifier, function->identifier());
        metaData.insert(LBMeta::FunctionColumns::CacheData, function->isCached());
        metaData.insert(LBMeta::FunctionColumns::Calculated, function->isCalculated());
        metaData.insert(LBMeta::FunctionColumns::DisplayName, function->displayName());
        metaData.insert(LBMeta::FunctionColumns::Editable, function->isEditable());
        metaData.insert(LBMeta::FunctionColumns::EntityColumnName, function->entityColumnName());
        metaData.insert(LBMeta::FunctionColumns::EntityType, function->entityType()->id());
        metaData.insert(LBMeta::FunctionColumns::KeyEntityColumnName, function->keyEntityColumnName());
        metaData.insert(LBMeta::FunctionColumns::KeyEntityType, function->keyEntityType()->id());
        metaData.insert(LBMeta::FunctionColumns::TableName, function->tableName());
        metaData.insert(LBMeta::FunctionColumns::Type, function->type());
        if(function->returnEntityType())
            metaData.insert(LBMeta::FunctionColumns::ReturnEntityType, function->returnEntityType()->id());
        else
            metaData.insert(LBMeta::FunctionColumns::ReturnEntityType, -1);
        metaData.insert(LBMeta::FunctionColumns::ValueColumnName, function->valueColumnName());
        functions.append(metaData);
    }
    hash.insert(LBMeta::FunctionsTableName, functions);

    //Enum values
    QVariantList enumValues;
    foreach(EnumAttributeMetaData enumData, storage->driver()->enumValues()) {
        QVariantHash metaData;
        metaData.insert(LBMeta::EnumAttributeColumns::Identifier, enumData.identifier);
        metaData.insert(LBMeta::EnumAttributeColumns::Attribute, enumData.attributeId);
        metaData.insert(LBMeta::EnumAttributeColumns::Value, enumData.value);
        enumValues.append(metaData);
    }
    hash.insert(EnumAttribute::EnumsTable, enumValues);

    //FunctionReimplementations
    QVariantList functionReimplementations;
    foreach(FunctionReimplementationMetaData data, storage->driver()->functionReimplementations()) {
        QVariantHash metaData;
        metaData.insert(LBMeta::FunctionReimplementationsColumns::ReimplementedFunction, data.reimplementedFunctionId);
        metaData.insert(LBMeta::FunctionReimplementationsColumns::ReimplementingEntityType, data.reimplementingEntityTypeId);
        functionReimplementations.append(metaData);
    }
    hash.insert(LBMeta::FunctionReimplementationsTable, functionReimplementations);

    //RelationReimplementations
    QVariantList relationReimplementations;
    foreach(RelationReimplementationMetaData data, storage->driver()->relationReimplementations()) {
        QVariantHash metaData;
        metaData.insert(LBMeta::RelationReimplementationsColumns::ReimplementedRelation, data.reimplementedRelationId);
        metaData.insert(LBMeta::RelationReimplementationsColumns::ReimplementingEntityType, data.reimplementingEntityTypeId);
        relationReimplementations.append(metaData);
    }
    hash.insert(LBMeta::RelationReimplementationsTable, relationReimplementations);

    //Dependencies
    QVariantList dependencies;
    foreach(DependencyMetaData data, storage->driver()->dependencies()) {
        QVariantHash metaData;
        metaData.insert("id", data.id);
        metaData.insert(LBMeta::DependenciesColumns::DependendPropertyId, data.dependendPropertyId);
        metaData.insert(LBMeta::DependenciesColumns::DependencyPropertyId, data.dependencyPropertyId);
        metaData.insert(LBMeta::DependenciesColumns::DependendPropertyType, data.dependendPropertyType);
        metaData.insert(LBMeta::DependenciesColumns::DependencyPropertyType, data.dependencyPropertyType);
        metaData.insert(LBMeta::DependenciesColumns::EntityRelation, data.entityRelation);
        dependencies.append(metaData);
    }
    hash.insert(LBMeta::DependenciesTable, dependencies);
    return QxtJSON::stringify(hash);
}

QString JsonExporter::entityToJson(Entity *entity)
{
    QVariantHash hash;

    //General
    hash.insert(QLatin1String("id"), entity->id());
    hash.insert(QLatin1String("entityTypeId"), entity->entityType()->id());
    hash.insert(QLatin1String("displayName"), entity->displayName());
    hash.insert(QLatin1String("context"), entity->context()->identifier());

    //Attributes
    QVariantHash attributes;
    foreach(Attribute* attribute, entity->entityType()->attributes()) {
        QVariant value = entity->attribute(attribute->identifier())->value();
        attributes.insert(attribute->identifier(), value);
    }
    hash.insert(QLatin1String("attributes"), attributes);

    //Functions
    QVariantHash functions;
    foreach(Function* function, entity->entityType()->functions()) {
        QVariantHash functionData;
        functionData.insert(QLatin1String("keyEntityTypeContext"), function->keyEntityType()->context()->identifier());

        FunctionValue *functionValue = entity->function(function->identifier());

        QVariantHash values;
        QHashIterator<const Entity*, QVariant> i(functionValue->values());

        while (i.hasNext()) {
            i.next();
            values.insert(QString::number(i.key()->id()), i.value());
        }
        functionData.insert(QLatin1String("values"), values);

        functions.insert(function->identifier(), functionData);
    }
    hash.insert(QLatin1String("functions"), functions);

    //Relations
    QVariantHash relations;
    foreach(Relation *relation, entity->entityType()->relations()) {
        RelationValue<Entity> *value = entity->relation<Entity>(relation->identifier());
        relations.insert(relation->identifier(), relationValueToJson(value));
    }
    hash.insert(QLatin1String("relations"), relations);

    return QxtJSON::stringify(hash);
}

QString JsonExporter::contextToJson(Context *context)
{
    QVariantHash hash;

    hash.insert("id", context->identifier());
    hash.insert(LBMeta::ContextColumns::Identifier, context->identifier());
    hash.insert(LBMeta::ContextColumns::DisplayName, context->displayName());
    hash.insert(LBMeta::ContextColumns::TableName, context->tableName());

    QStringList entities;
    foreach(Entity *entity, context->entities()) {
        entities.append(QString::number(entity->id()));
    }
    hash.insert(QLatin1String("entities"), entities);

    return QxtJSON::stringify(hash);
}

QVariantHash JsonExporter::relationValueToJson(RelationValue<Entity> *value)
{
    QVariantHash relationData;
    relationData.insert(QLatin1String("entitiesContext"), value->relation()->entityTypeOther()->context()->identifier());

    QVariantList relatedEntities;
    relatedEntities.reserve(value->entities().size());
    foreach(Entity *relatedEntity, value->entities()) {
        relatedEntities.append(relatedEntity->id());
    }
    relationData.insert(QLatin1String("relatedEntities"), relatedEntities);

    return relationData;
}

} // namespace LBDatabase
