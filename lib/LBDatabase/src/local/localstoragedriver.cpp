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
const QString Direction("direction");
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

    void init();

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

void LocalStorageDriverPrivate::init()
{
    database = Database::instance(fileName);

    if(!database)
        return;

    QFile file(fileName);
    if(!file.exists()) {
        file.open(QFile::ReadOnly);
        file.close();
    }

    if(!database->open())
        return;

    metaDataTable = database->table(MetaDataTableName);
    if(!metaDataTable)
        return;

    contextsTable = database->table(ContextsTableName);
    if(!contextsTable)
        return;

    entityTypesTable = database->table(EntitiesTableName);
    if(!entityTypesTable)
        return;

    attributesTable = database->table(AttributesTableName);
    if(!attributesTable)
        return;

    relationsTable = database->table(RelationsTableName);
    if(!relationsTable)
        return;

    functionsTable = database->table(FunctionsTableName);
    if(!functionsTable)
        return;
}

LocalStorageDriver::LocalStorageDriver(const QString &fileName, QObject *parent) :
    StorageDriver(parent),
    d_ptr(new LocalStorageDriverPrivate)
{
    Q_D(LocalStorageDriver);
    d->fileName = fileName;
    d->q_ptr = this;
    d->init();
}

LocalStorageDriver::~LocalStorageDriver()
{
}

void LocalStorageDriver::init()
{
    Q_D(LocalStorageDriver);
    d->init();
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
        metaData.cacheData = row->data(AttributeColumns::CacheData).toBool();
        metaData.calculated = row->data(AttributeColumns::Calculated).toBool();
        metaData.editable = row->data(AttributeColumns::Editable).toBool();
        metaData.entityTypeId = row->data(AttributeColumns::EntityTypeId).toInt();
        metaData.type = static_cast<Attribute::Type>(row->data(AttributeColumns::Type).toInt());
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

QVariant LocalStorageDriver::attributeValue(const AttributeValue *value) const
{
    Q_D(const LocalStorageDriver);
    if(!value->attribute()->isCalculated()) {
        Table *contextTable = d->database->table(value->entity()->context()->tableName());
        Row *row = contextTable->row(value->entity()->id());
        return row->data(value->attribute()->identifier());
    }

    return const_cast<AttributeValue*>(value)->calculate();
}

void LocalStorageDriver::setAttributeValue(const AttributeValue *attribute, const QVariant &data)
{
    Q_D(LocalStorageDriver);
    Table *contextTable = d->database->table(attribute->entity()->context()->tableName());
    Row *row = contextTable->row(attribute->entity()->id());
    row->setData(attribute->attribute()->identifier(), data);
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
