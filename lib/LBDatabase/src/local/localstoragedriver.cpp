#include "localstoragedriver.h"

#include "column.h"
#include "database.h"
#include "row.h"
#include "table.h"

#include "../attributevalue.h"
#include "../context.h"
#include "../enumattribute.h"
#include "../entity.h"
#include "../function.h"
#include "../functionvalue.h"
#include "../relationvalue.h"
#include "../relation.h"

#include <QFile>
#include <QVariant>
#include <QDebug>

namespace {
const QString MetaDataTableName("lbmeta");
const QString ContextsTableName("lbmeta_contexts");
const QString EntitiesTableName("lbmeta_entitytypes");
const QString AttributesTableName("lbmeta_attributes");
const QString RelationsTableName("lbmeta_relations");
const QString FunctionsTableName("lbmeta_functions");
const QString FunctionReimplementationsTable("lbmeta_functionreimplementations");
const QString RelationReimplementationsTable("lbmeta_relationreimplementations");

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
const QString KeyEntityTypeRight("keyEntityType");
const QString Calculated("calculated");
const QString CacheData("cacheData");
const QString Type("type");
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
}

namespace LBDatabase {

class LocalStorageDriverPrivate
{
    LocalStorageDriverPrivate()
    {}

    bool init();

    Database *database;

    Table *attributesTable;
    Table *contextsTable;
    Table *entityTypesTable;
    Table *metaDataTable;
    Table *relationsTable;
    Table *functionsTable;

    QString fileName;

    LocalStorageDriver * q_ptr;
    Q_DECLARE_PUBLIC(LocalStorageDriver)
};

bool LocalStorageDriverPrivate::init()
{
    database = Database::instance(fileName);

    if(!database)
        return false;

    QFile file(fileName);
    if(!file.exists()) {
        return false;
    }

    if(!database->open())
        return false;

    metaDataTable = database->table(MetaDataTableName);
    if(!metaDataTable)
        return false;

    contextsTable = database->table(ContextsTableName);
    if(!contextsTable)
        return false;

    entityTypesTable = database->table(EntitiesTableName);
    if(!entityTypesTable)
        return false;

    attributesTable = database->table(AttributesTableName);
    if(!attributesTable)
        return false;

    relationsTable = database->table(RelationsTableName);
    if(!relationsTable)
        return false;

    functionsTable = database->table(FunctionsTableName);
    if(!functionsTable)
        return false;

    return true;
}

LocalStorageDriver::LocalStorageDriver(const QString &fileName, QObject *parent) :
    StorageDriver(parent),
    d_ptr(new LocalStorageDriverPrivate)
{
    Q_D(LocalStorageDriver);
    d->fileName = fileName;
    d->q_ptr = this;
}

LocalStorageDriver::~LocalStorageDriver()
{
}

bool LocalStorageDriver::init()
{
    Q_D(LocalStorageDriver);
    return d->init();
}

QList<ContextMetaData> LocalStorageDriver::contexts() const
{
    Q_D(const LocalStorageDriver);
    QList<ContextMetaData> metaDatas;
    metaDatas.reserve(d->contextsTable->rows().count());
    foreach(Row *row, d->contextsTable->rows()) {
        ContextMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(ContextColumns::Identifier).toString();
        metaData.displayName = row->data(ContextColumns::DisplayName).toString();
        metaData.tableName = row->data(ContextColumns::TableName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<EntityTypeMetaData> LocalStorageDriver::entityTypes() const
{
    Q_D(const LocalStorageDriver);
    QList<EntityTypeMetaData> metaDatas;
    metaDatas.reserve(d->entityTypesTable->rows().count());
    foreach(Row *row, d->entityTypesTable->rows()) {
        EntityTypeMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(EntityTypeColumns::Identifier).toString();
        metaData.displayName = row->data(EntityTypeColumns::DisplayName).toString();
        metaData.displayNamePlural = row->data(EntityTypeColumns::DisplayNamePlural).toString();
        metaData.contextId = row->data(EntityTypeColumns::Context).toInt();
        metaData.parentEntityTypeId = row->data(EntityTypeColumns::ParentEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<AttributeMetaData> LocalStorageDriver::attributes() const
{
    Q_D(const LocalStorageDriver);
    QList<AttributeMetaData> metaDatas;
    metaDatas.reserve(d->attributesTable->rows().count());
    foreach(Row *row, d->attributesTable->rows()) {
        AttributeMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(AttributeColumns::Identifier).toString();
        metaData.displayName = row->data(AttributeColumns::DisplayName).toString();
        metaData.cached = row->data(AttributeColumns::CacheData).toBool();
        metaData.calculated = row->data(AttributeColumns::Calculated).toBool();
        metaData.editable = row->data(AttributeColumns::Editable).toBool();
        metaData.entityTypeId = row->data(AttributeColumns::EntityTypeId).toInt();
        metaData.type = static_cast<Attribute::Type>(row->data(AttributeColumns::Type).toInt());
        metaData.defaultValue = row->data(AttributeColumns::DefaultValue);
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<FunctionMetaData> LocalStorageDriver::functions() const
{
    Q_D(const LocalStorageDriver);
    QList<FunctionMetaData> metaDatas;
    metaDatas.reserve(d->functionsTable->rows().count());
    foreach(Row *row, d->functionsTable->rows()) {
        FunctionMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(FunctionColumns::Identifier).toString();
        metaData.cacheData = row->data(FunctionColumns::CacheData).toBool();
        metaData.calculated = row->data(FunctionColumns::Calculated).toBool();
        metaData.displayName = row->data(FunctionColumns::DisplayName).toString();
        metaData.editable = row->data(FunctionColumns::Editable).toBool();
        metaData.entityColumnName = row->data(FunctionColumns::EntityColumnName).toString();
        metaData.entityTypeId = row->data(FunctionColumns::EntityType).toInt();
        metaData.keyEntityColumnName = row->data(FunctionColumns::KeyEntityColumnName).toString();
        metaData.keyEntityTypeId = row->data(FunctionColumns::KeyEntityTypeRight).toInt();
        metaData.tableName = row->data(FunctionColumns::TableName).toString();
        metaData.type = static_cast<Attribute::Type>(row->data(FunctionColumns::Type).toInt());
        metaData.valueColumnName = row->data(FunctionColumns::ValueColumnName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationMetaData> LocalStorageDriver::relations() const
{
    Q_D(const LocalStorageDriver);
    QList<RelationMetaData> metaDatas;
    metaDatas.reserve(d->relationsTable->rows().count());
    foreach(Row *row, d->relationsTable->rows()) {
        RelationMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(RelationColumns::Identifier).toString();
        metaData.identifierRight = row->data(RelationColumns::IdentifierRight).toString();
        metaData.displayName = row->data(RelationColumns::DisplayNameLeft).toString();
        metaData.displayNameRight = row->data(RelationColumns::DisplayNameRight).toString();
        metaData.cardinality = static_cast<Relation::Cardinality>(row->data(RelationColumns::Cardinality).toInt());
        metaData.direction = static_cast<Relation::Direction>(row->data(RelationColumns::Direction).toInt());
        metaData.editable = row->data(RelationColumns::Editable).toBool();
        metaData.calculated = row->data(RelationColumns::Calculated).toBool();
        metaData.entityTypeId = row->data(RelationColumns::EntityTypeLeft).toInt();
        metaData.entityTypeOtherId = row->data(RelationColumns::EntityTypeRight).toInt();
        metaData.leftEntityIdColumnName = row->data(RelationColumns::ColumnName).toString();
        metaData.rightEntityIdColumnName = row->data(RelationColumns::ColumnNameRight).toString();
        metaData.tableName = row->data(RelationColumns::TableName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<EnumAttributeMetaData> LocalStorageDriver::enumValues() const
{
    Q_D(const LocalStorageDriver);
    QList<EnumAttributeMetaData> metaDatas;
    metaDatas.reserve(d->database->table(EnumAttribute::EnumsTable)->rows().count());
    foreach(Row *row, d->database->table(EnumAttribute::EnumsTable)->rows()) {
        EnumAttributeMetaData metaData;
        metaData.identifier = row->data(EnumAttributeColumns::Identifier).toString();
        metaData.attributeId = row->data(EnumAttributeColumns::Attribute).toInt();
        metaData.value = row->data(EnumAttributeColumns::Value).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<FunctionReimplementationMetaData> LocalStorageDriver::functionReimplementations() const
{
    Q_D(const LocalStorageDriver);
    QList<FunctionReimplementationMetaData> metaDatas;
    metaDatas.reserve(d->database->table(FunctionReimplementationsTable)->rows().count());
    foreach(Row *row, d->database->table(FunctionReimplementationsTable)->rows()) {
        FunctionReimplementationMetaData metaData;
        metaData.reimplementedFunctionId = row->data(FunctionReimplementationsColumns::ReimplementedFunction).toInt();
        metaData.reimplementingEntityTypeId = row->data(FunctionReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationReimplementationMetaData> LocalStorageDriver::relationReimplementations() const
{
    Q_D(const LocalStorageDriver);
    QList<RelationReimplementationMetaData> metaDatas;
    metaDatas.reserve(d->database->table(RelationReimplementationsTable)->rows().count());
    foreach(Row *row, d->database->table(RelationReimplementationsTable)->rows()) {
        RelationReimplementationMetaData metaData;
        metaData.reimplementedRelationId = row->data(RelationReimplementationsColumns::ReimplementedRelation).toInt();
        metaData.reimplementingEntityTypeId = row->data(RelationReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QVariant LocalStorageDriver::attributeValue(const AttributeValue *value) const
{
    Q_D(const LocalStorageDriver);
    Table *contextTable = d->database->table(value->entity()->context()->tableName());
    Row *row = contextTable->row(value->entity()->id());
    return row->data(value->attribute()->identifier());
}

void LocalStorageDriver::setAttributeValue(const AttributeValue *attribute, const QVariant &data)
{
    Q_D(LocalStorageDriver);
    Table *contextTable = d->database->table(attribute->entity()->context()->tableName());
    Row *row = contextTable->row(attribute->entity()->id());
    row->setData(attribute->attribute()->identifier(), data);
}

void LocalStorageDriver::addAttribute(EntityType *entityType, AttributeMetaData &metaData)
{
    Q_D(LocalStorageDriver);
    Table *contextTable = d->database->table(entityType->context()->tableName());
    contextTable->addColumn(metaData.identifier, Attribute::typeToName(metaData.type));

    Row *row = d->attributesTable->appendRow();
    row->setData(AttributeColumns::Identifier, metaData.identifier);
    row->setData(AttributeColumns::DisplayName, metaData.displayName);
    row->setData(AttributeColumns::CacheData, metaData.cached);
    row->setData(AttributeColumns::Calculated, metaData.calculated);
    row->setData(AttributeColumns::Editable, metaData.editable);
    row->setData(AttributeColumns::EntityTypeId, QVariant(metaData.entityTypeId));
    row->setData(AttributeColumns::Type, QVariant(static_cast<int>(metaData.type)));
    row->setData(AttributeColumns::DefaultValue, metaData.defaultValue);

    metaData.id = row->id();
}

void LocalStorageDriver::removeAttribute(int attributeId)
{
    Q_D(LocalStorageDriver);
    d->attributesTable->deleteRow(attributeId);

    //TODO: delete the column of the attribute.
}

void LocalStorageDriver::setAttributeDisplayName(int id, const QString &displayName)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::DisplayName, displayName);
}

void LocalStorageDriver::setAttributeIdentifier(int id, const QString &identifier)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::Identifier, identifier);
}

void LocalStorageDriver::setAttributeType(int id, Attribute::Type type)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::Type, static_cast<int>(type));
}

void LocalStorageDriver::setAttributeEditable(int id, bool editable)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::Editable, QVariant(editable));
}

void LocalStorageDriver::setAttributeCalculated(int id, bool calculated)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::Calculated, QVariant(calculated));
}

void LocalStorageDriver::setAttributeCached(int id, bool cached)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::CacheData, QVariant(cached));
}

void LocalStorageDriver::setAttributeDefaultValue(int id, QVariant defaultValue)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(AttributesTableName)->row(id);
    row->setData(AttributeColumns::DefaultValue, defaultValue);
}

QList<RelationValueData> LocalStorageDriver::relatedEntities(Relation *relation) const
{
    Q_D(const LocalStorageDriver);
    QList<RelationValueData> entities;

    Table *relationTable = d->database->table(relation->tableName());
    int columnLeft = relationTable->column(relation->leftEntityIdColumnName())->index();
    int columnRight = relationTable->column(relation->rightEntityIdColumnName())->index();

    foreach(Row *row, relationTable->rows()) {
        RelationValueData data;
        data.rowId = row->id();
        data.leftId = row->data(columnLeft).toInt();
        data.rightId = row->data(columnRight).toInt();
        entities.append(data);
    }

    return entities;
}

int LocalStorageDriver::addRelatedEntity(RelationValueBase *value, const RelationValueData &data)
{
    Q_D(LocalStorageDriver);
    Relation *relation = value->relation();
    Table *table = d->database->table(relation->tableName());
    int columnLeft = table->column(relation->leftEntityIdColumnName())->index();
    int columnRight = table->column(relation->rightEntityIdColumnName())->index();

    Row *row = 0;

    if(relation->cardinality() == Relation::OneToMany)
        row = table->row(data.rightId);

    //TODO: OneToOne relations beachten.

    if(!row)
        row = table->appendRow();

    row->setData(columnLeft, data.leftId);
    row->setData(columnRight, data.rightId);

    return row->id();
}

QList<FunctionValueData> LocalStorageDriver::functionValues(Function *function) const
{
    Q_D(const LocalStorageDriver);
    QList<FunctionValueData> values;

    Table *table = d->database->table(function->tableName());
    int columnType = table->column(function->entityColumnName())->index();
    int columnKey = table->column(function->keyEntityColumnName())->index();
    int columnValue = table->column(function->valueColumnName())->index();

    foreach(Row *row, table->rows()) {
        FunctionValueData data;
        data.rowId = row->id();
        data.entityId = row->data(columnType).toInt();
        data.keyEntityId = row->data(columnKey).toInt();
        data.value = row->data(columnValue);
        values.append(data);
    }

    return values;
}

void LocalStorageDriver::setFunctionValue(FunctionValue *functionValue, const FunctionValueData &data)
{
    Q_D(const LocalStorageDriver);

    Function *function = functionValue->function();
    Table *table = d->database->table(function->tableName());
    Row *row = table->row(data.rowId);
    if(!row)
        row = table->appendRow();

    int columnType = table->column(function->entityColumnName())->index();
    int columnKey = table->column(function->keyEntityColumnName())->index();
    int columnValue = table->column(function->valueColumnName())->index();
    row->setData(columnType, QVariant(data.entityId));
    row->setData(columnKey, QVariant(data.keyEntityId));
    row->setData(columnValue, QVariant(data.value));
}

QList<EntityMetaData> LocalStorageDriver::entities(Context *context) const
{
    Q_D(const LocalStorageDriver);
    QList<EntityMetaData> entities;
    Table *contextTable = d->database->table(context->tableName());
    entities.reserve(contextTable->rows().size());

    foreach(Row *row, contextTable->rows()) {
        EntityMetaData metaData;
        metaData.id = row->data(EntityColumns::Id).toInt();
        metaData.entityTypeId = row->data(EntityColumns::EntityType).toInt();
        entities.append(metaData);
    }

    return entities;
}

EntityMetaData LocalStorageDriver::createEntity(EntityType *type)
{
    Q_D(LocalStorageDriver);
    Table *table = d->database->table(type->context()->tableName());
    Row *row = table->appendRow();
    row->setData(EntityColumns::EntityType, QVariant(type->id()));

    EntityMetaData metaData;
    metaData.entityTypeId = type->id();
    metaData.id = row->id();
    return metaData;
}

} // namespace LBDatabase
