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
#include <QSqlQuery>
#include <QSqlError>

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
    Table *dependenciesTable;

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

    metaDataTable = database->table(LBMeta::MetaDataTableName);
    if(!metaDataTable)
        return false;

    contextsTable = database->table(LBMeta::ContextsTableName);
    if(!contextsTable)
        return false;

    entityTypesTable = database->table(LBMeta::EntitiesTableName);
    if(!entityTypesTable)
        return false;

    attributesTable = database->table(LBMeta::AttributesTableName);
    if(!attributesTable)
        return false;

    relationsTable = database->table(LBMeta::RelationsTableName);
    if(!relationsTable)
        return false;

    functionsTable = database->table(LBMeta::FunctionsTableName);
    if(!functionsTable)
        return false;

    dependenciesTable = database->table(LBMeta::DependenciesTable);
    if(!dependenciesTable)
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
        metaData.identifier = row->data(LBMeta::ContextColumns::Identifier).toString();
        metaData.displayName = row->data(LBMeta::ContextColumns::DisplayName).toString();
        metaData.tableName = row->data(LBMeta::ContextColumns::TableName).toString();
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
        metaData.identifier = row->data(LBMeta::EntityTypeColumns::Identifier).toString();
        metaData.displayName = row->data(LBMeta::EntityTypeColumns::DisplayName).toString();
        metaData.displayNamePlural = row->data(LBMeta::EntityTypeColumns::DisplayNamePlural).toString();
        metaData.contextId = row->data(LBMeta::EntityTypeColumns::Context).toInt();
        metaData.parentEntityTypeId = row->data(LBMeta::EntityTypeColumns::ParentEntityType).toInt();
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
        metaData.identifier = row->data(LBMeta::AttributeColumns::Identifier).toString();
        metaData.displayName = row->data(LBMeta::AttributeColumns::DisplayName).toString();
        metaData.cached = row->data(LBMeta::AttributeColumns::CacheData).toBool();
        metaData.calculated = row->data(LBMeta::AttributeColumns::Calculated).toBool();
        metaData.editable = row->data(LBMeta::AttributeColumns::Editable).toBool();
        metaData.entityTypeId = row->data(LBMeta::AttributeColumns::EntityTypeId).toInt();
        metaData.type = static_cast<Attribute::Type>(row->data(LBMeta::AttributeColumns::Type).toInt());
        metaData.returnEntityTypeId = row->data(LBMeta::AttributeColumns::ReturnEntityType).toInt();
        metaData.defaultValue = row->data(LBMeta::AttributeColumns::DefaultValue);
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
        metaData.identifier = row->data(LBMeta::FunctionColumns::Identifier).toString();
        metaData.cached = row->data(LBMeta::FunctionColumns::CacheData).toBool();
        metaData.calculated = row->data(LBMeta::FunctionColumns::Calculated).toBool();
        metaData.displayName = row->data(LBMeta::FunctionColumns::DisplayName).toString();
        metaData.editable = row->data(LBMeta::FunctionColumns::Editable).toBool();
        metaData.entityColumnName = row->data(LBMeta::FunctionColumns::EntityColumnName).toString();
        metaData.entityTypeId = row->data(LBMeta::FunctionColumns::EntityType).toInt();
        metaData.keyEntityColumnName = row->data(LBMeta::FunctionColumns::KeyEntityColumnName).toString();
        metaData.keyEntityTypeId = row->data(LBMeta::FunctionColumns::KeyEntityType).toInt();
        metaData.tableName = row->data(LBMeta::FunctionColumns::TableName).toString();
        metaData.type = static_cast<Attribute::Type>(row->data(LBMeta::FunctionColumns::Type).toInt());
        metaData.returnEntityTypeId = row->data(LBMeta::FunctionColumns::ReturnEntityType).toInt();
        metaData.valueColumnName = row->data(LBMeta::FunctionColumns::ValueColumnName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationMetaData> LocalStorageDriver::relations() const
{
    Q_D(const LocalStorageDriver);
    QList<RelationMetaData> metaDatas;
    foreach(Row *row, d->relationsTable->rows()) {
        RelationMetaData metaData;
        metaData.id = row->id();
        metaData.identifier = row->data(LBMeta::RelationColumns::Identifier).toString();
        metaData.identifierRight = row->data(LBMeta::RelationColumns::IdentifierRight).toString();
        metaData.displayName = row->data(LBMeta::RelationColumns::DisplayNameLeft).toString();
        metaData.displayNameRight = row->data(LBMeta::RelationColumns::DisplayNameRight).toString();
        metaData.cardinality = static_cast<Relation::Cardinality>(row->data(LBMeta::RelationColumns::Cardinality).toInt());
        metaData.direction = static_cast<Relation::Direction>(row->data(LBMeta::RelationColumns::Direction).toInt());
        metaData.editable = row->data(LBMeta::RelationColumns::Editable).toBool();
        metaData.editableTranspose = row->data(LBMeta::RelationColumns::EditableTranspose).toBool();
        metaData.calculated = row->data(LBMeta::RelationColumns::Calculated).toBool();
        metaData.entityTypeId = row->data(LBMeta::RelationColumns::EntityTypeLeft).toInt();
        metaData.entityTypeOtherId = row->data(LBMeta::RelationColumns::EntityTypeRight).toInt();
        metaData.leftEntityIdColumnName = row->data(LBMeta::RelationColumns::ColumnName).toString();
        metaData.rightEntityIdColumnName = row->data(LBMeta::RelationColumns::ColumnNameRight).toString();
        metaData.tableName = row->data(LBMeta::RelationColumns::TableName).toString();
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
        metaData.identifier = row->data(LBMeta::EnumAttributeColumns::Identifier).toString();
        metaData.attributeId = row->data(LBMeta::EnumAttributeColumns::Attribute).toInt();
        metaData.value = row->data(LBMeta::EnumAttributeColumns::Value).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<FunctionReimplementationMetaData> LocalStorageDriver::functionReimplementations() const
{
    Q_D(const LocalStorageDriver);
    QList<FunctionReimplementationMetaData> metaDatas;
    metaDatas.reserve(d->database->table(LBMeta::FunctionReimplementationsTable)->rows().count());
    foreach(Row *row, d->database->table(LBMeta::FunctionReimplementationsTable)->rows()) {
        FunctionReimplementationMetaData metaData;
        metaData.reimplementedFunctionId = row->data(LBMeta::FunctionReimplementationsColumns::ReimplementedFunction).toInt();
        metaData.reimplementingEntityTypeId = row->data(LBMeta::FunctionReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationReimplementationMetaData> LocalStorageDriver::relationReimplementations() const
{
    Q_D(const LocalStorageDriver);
    QList<RelationReimplementationMetaData> metaDatas;
    metaDatas.reserve(d->database->table(LBMeta::RelationReimplementationsTable)->rows().count());
    foreach(Row *row, d->database->table(LBMeta::RelationReimplementationsTable)->rows()) {
        RelationReimplementationMetaData metaData;
        metaData.reimplementedRelationId = row->data(LBMeta::RelationReimplementationsColumns::ReimplementedRelation).toInt();
        metaData.reimplementingEntityTypeId = row->data(LBMeta::RelationReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<DependencyMetaData> LocalStorageDriver::dependencies() const
{
    Q_D(const LocalStorageDriver);
    QList<DependencyMetaData> metaDatas;
    metaDatas.reserve(d->dependenciesTable->rows().count());
    foreach(Row *row, d->dependenciesTable->rows()) {
        DependencyMetaData metaData;
        metaData.id = row->id();
        metaData.dependendPropertyId = row->data(LBMeta::DependenciesColumns::DependendPropertyId).toInt();
        metaData.dependencyPropertyId = row->data(LBMeta::DependenciesColumns::DependencyPropertyId).toInt();
        metaData.dependendPropertyType =
                static_cast<Property::Type>(row->data(LBMeta::DependenciesColumns::DependendPropertyType).toInt());
        metaData.dependencyPropertyType =
                static_cast<Property::Type>(row->data(LBMeta::DependenciesColumns::DependencyPropertyType).toInt());
        metaData.entityRelation = row->data(LBMeta::DependenciesColumns::EntityRelation).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

void LocalStorageDriver::addDependency(DependencyMetaData &metaData)
{
    Q_D(LocalStorageDriver);
    Row *row = d->dependenciesTable->appendRow();
    metaData.id = row->id();

    row->setData(LBMeta::DependenciesColumns::DependendPropertyId, metaData.dependendPropertyId);
    row->setData(LBMeta::DependenciesColumns::DependencyPropertyId, metaData.dependencyPropertyId);
    row->setData(LBMeta::DependenciesColumns::DependendPropertyType, metaData.dependendPropertyType);
    row->setData(LBMeta::DependenciesColumns::DependencyPropertyType, metaData.dependencyPropertyType);
    row->setData(LBMeta::DependenciesColumns::EntityRelation, metaData.entityRelation);
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
    if(!metaData.calculated) {
        Table *contextTable = d->database->table(entityType->context()->tableName());
        Column *column = contextTable->column(metaData.identifier);
        if(!column)
            column = contextTable->addColumn(metaData.identifier, Attribute::typeToName(metaData.type));
    }

    Row *row = d->attributesTable->appendRow();
    row->setData(LBMeta::AttributeColumns::Identifier, metaData.identifier);
    row->setData(LBMeta::AttributeColumns::DisplayName, metaData.displayName);
    row->setData(LBMeta::AttributeColumns::CacheData, metaData.cached);
    row->setData(LBMeta::AttributeColumns::Calculated, metaData.calculated);
    row->setData(LBMeta::AttributeColumns::Editable, metaData.editable);
    row->setData(LBMeta::AttributeColumns::EntityTypeId, QVariant(metaData.entityTypeId));
    row->setData(LBMeta::AttributeColumns::Type, QVariant(static_cast<int>(metaData.type)));
    row->setData(LBMeta::AttributeColumns::DefaultValue, metaData.defaultValue);

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
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::DisplayName, displayName);
}

void LocalStorageDriver::setAttributeIdentifier(int id, const QString &identifier)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::Identifier, identifier);
}

void LocalStorageDriver::setAttributeType(int id, Attribute::Type type)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::Type, static_cast<int>(type));
}

void LocalStorageDriver::setAttributeEditable(int id, bool editable)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::Editable, QVariant(editable));
}

void LocalStorageDriver::setAttributeCalculated(int id, bool calculated)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::Calculated, QVariant(calculated));
}

void LocalStorageDriver::setAttributeCached(int id, bool cached)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::CacheData, QVariant(cached));
}

void LocalStorageDriver::setAttributeDefaultValue(int id, QVariant defaultValue)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::AttributesTableName)->row(id);
    row->setData(LBMeta::AttributeColumns::DefaultValue, defaultValue);
}

QList<RelationValueData> LocalStorageDriver::relatedEntities(Relation *relation) const
{
    Q_D(const LocalStorageDriver);
    QList<RelationValueData> entities;

    QSqlQuery query(d->database->sqlDatabase());
    query.setForwardOnly(true);
    query.exec("SELECT id, "+
               relation->leftEntityIdColumnName()+","+
               relation->rightEntityIdColumnName()+
               " FROM "+relation->tableName());

    while (query.next()) {
        RelationValueData data;
        data.rowId = query.value(0).toInt();
        data.leftId = query.value(1).toInt();
        data.rightId = query.value(2).toInt();
        entities.append(data);
    }
    query.finish();

    //This is slow (by slow I mean 400ms vs 60ms for our ProjectStats.lbstorage):
//    Table *relationTable = d->database->table(relation->tableName());
//    int columnLeft = relationTable->column(relation->leftEntityIdColumnName())->index();
//    int columnRight = relationTable->column(relation->rightEntityIdColumnName())->index();
//    foreach(Row *row, relationTable->rows()) {
//        RelationValueData data;
//        data.rowId = row->id();
//        data.leftId = row->data(columnLeft).toInt();
//        data.rightId = row->data(columnRight).toInt();
//        entities.append(data);
//    }

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

    if(!row) {
        if(relation->cardinality() != Relation::OneToOne)
            row = table->appendRow();
        else
            return -1;
    }

    row->setData(columnLeft, data.leftId);
    row->setData(columnRight, data.rightId);

    return row->id();
}

void LocalStorageDriver::addRelation(EntityType *entityType, RelationMetaData &metaData)
{
    Q_UNUSED(entityType)
    Q_D(LocalStorageDriver);
    if(!metaData.calculated) {
        Table *table = d->database->table(metaData.tableName);
        if(!table)
            table = d->database->createTable(metaData.tableName);

        Column *idColumn = table->column("id");
        if(!idColumn)
            idColumn = table->addColumn("id", Attribute::typeToName(Attribute::Integer));

        Column *entityIdColumn = table->column(metaData.leftEntityIdColumnName);
        if(!entityIdColumn)
            entityIdColumn = table->addColumn(metaData.leftEntityIdColumnName, Attribute::typeToName(Attribute::Integer));

        Column *relatedEntityColumn = table->column(metaData.rightEntityIdColumnName);
        if(!relatedEntityColumn)
            relatedEntityColumn = table->addColumn(metaData.rightEntityIdColumnName, Attribute::typeToName(Attribute::Integer));
    }

    Row *row = d->relationsTable->appendRow();
    metaData.id = row->id();

    row->setData(LBMeta::RelationColumns::Identifier, metaData.identifier);
    row->setData(LBMeta::RelationColumns::IdentifierRight, metaData.identifierRight);
    row->setData(LBMeta::RelationColumns::DisplayNameLeft, metaData.displayName);
    row->setData(LBMeta::RelationColumns::DisplayNameRight, metaData.displayNameRight);
    row->setData(LBMeta::RelationColumns::Cardinality, metaData.cardinality);
    row->setData(LBMeta::RelationColumns::Direction, metaData.direction);
    row->setData(LBMeta::RelationColumns::Editable, metaData.editable);
    row->setData(LBMeta::RelationColumns::Calculated, metaData.calculated);
    row->setData(LBMeta::RelationColumns::EntityTypeLeft, metaData.entityTypeId);
    row->setData(LBMeta::RelationColumns::EntityTypeRight, metaData.entityTypeOtherId);
    row->setData(LBMeta::RelationColumns::ColumnName, metaData.leftEntityIdColumnName);
    row->setData(LBMeta::RelationColumns::ColumnNameRight, metaData.rightEntityIdColumnName);
    row->setData(LBMeta::RelationColumns::TableName, metaData.tableName);
}

void LocalStorageDriver::setRelationIdentifier(int id, const QString &identifier)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::Identifier, identifier);
}

void LocalStorageDriver::setRelationIdentifierRight(int id, const QString &identifierRight)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::IdentifierRight, identifierRight);
}

void LocalStorageDriver::setRelationDisplayName(int id, const QString &displayName)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::DisplayNameLeft, displayName);
}

void LocalStorageDriver::setRelationDisplayNameRight(int id, const QString &displayNameRight)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::DisplayNameRight, displayNameRight);
}

void LocalStorageDriver::setRelationCardinality(int id, Relation::Cardinality cardinality)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::Cardinality, cardinality);
}

void LocalStorageDriver::setRelationDirection(int id, Relation::Direction direction)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::Direction, direction);
}

void LocalStorageDriver::setRelationEntityTypeRight(int id, EntityType *entityType)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::EntityTypeRight, entityType->id());
}

void LocalStorageDriver::setRelationEditable(int id, bool editable)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::Editable, editable);
}

void LocalStorageDriver::setRelationCalculated(int id, bool calculated)
{
    Q_D(LocalStorageDriver);
    Row *row = d->database->table(LBMeta::RelationsTableName)->row(id);
    row->setData(LBMeta::RelationColumns::Calculated, calculated);
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

void LocalStorageDriver::addFunction(EntityType *entityType, FunctionMetaData &metaData)
{
    Q_UNUSED(entityType)
    Q_D(LocalStorageDriver);
    if(!metaData.calculated) {
        Table *table = d->database->table(metaData.tableName);
        if(!table)
            table = d->database->createTable(metaData.tableName);

        Column *idColumn = table->column("id");
        if(!idColumn)
            idColumn = table->addColumn("id", Attribute::typeToName(Attribute::Integer));

        Column *entityColumn = table->column(metaData.entityColumnName);
        if(!entityColumn)
            entityColumn = table->addColumn(metaData.entityColumnName, Attribute::typeToName(Attribute::Integer));

        Column *keyEntityColumn = table->column(metaData.keyEntityColumnName);
        if(!keyEntityColumn)
            keyEntityColumn = table->addColumn(metaData.keyEntityColumnName, Attribute::typeToName(Attribute::Integer));

        Column *valueColumn = table->column(metaData.valueColumnName);
        if(!valueColumn)
            valueColumn = table->addColumn(metaData.valueColumnName, Attribute::typeToName(metaData.type));
    }

    Row *row = d->functionsTable->appendRow();
    row->setData(LBMeta::FunctionColumns::Identifier, metaData.identifier);
    row->setData(LBMeta::FunctionColumns::DisplayName, metaData.displayName);
    row->setData(LBMeta::FunctionColumns::CacheData, metaData.cached);
    row->setData(LBMeta::FunctionColumns::Calculated, metaData.calculated);
    row->setData(LBMeta::FunctionColumns::Editable, metaData.editable);
    row->setData(LBMeta::FunctionColumns::EntityType, QVariant(metaData.entityTypeId));
    row->setData(LBMeta::FunctionColumns::Type, QVariant(static_cast<int>(metaData.type)));
    row->setData(LBMeta::FunctionColumns::KeyEntityType, metaData.keyEntityTypeId);
    row->setData(LBMeta::FunctionColumns::TableName, metaData.tableName);
    row->setData(LBMeta::FunctionColumns::EntityColumnName, metaData.entityColumnName);
    row->setData(LBMeta::FunctionColumns::KeyEntityColumnName, metaData.keyEntityColumnName);
    row->setData(LBMeta::FunctionColumns::ValueColumnName, metaData.valueColumnName);
    metaData.id = row->id();

}

void LocalStorageDriver::setFunctionDisplayName(int id, const QString &displayName)
{
    Q_D(LocalStorageDriver);
    Row *row = d->functionsTable->row(id);
    row->setData(LBMeta::FunctionColumns::DisplayName, displayName);
}

void LocalStorageDriver::setFunctionIdentifier(int id, const QString &identifier)
{
    Q_D(LocalStorageDriver);
    Row *row = d->functionsTable->row(id);
    row->setData(LBMeta::FunctionColumns::Identifier, identifier);
}

void LocalStorageDriver::setFunctionType(int id, Attribute::Type type)
{
    Q_D(LocalStorageDriver);
    Row *row = d->functionsTable->row(id);
    row->setData(LBMeta::FunctionColumns::Type, static_cast<int>(type));
}

void LocalStorageDriver::setFunctionEditable(int id, bool editable)
{
    Q_D(LocalStorageDriver);
    Row *row = d->functionsTable->row(id);
    row->setData(LBMeta::FunctionColumns::Editable, editable);
}

void LocalStorageDriver::setFunctionKeyEntityType(int id, EntityType *entityType)
{
    Q_D(LocalStorageDriver);
    Row *row = d->functionsTable->row(id);
    row->setData(LBMeta::FunctionColumns::KeyEntityType, entityType->id());
}

QList<EntityMetaData> LocalStorageDriver::entities(Context *context) const
{
    Q_D(const LocalStorageDriver);
    QList<EntityMetaData> entities;
    Table *contextTable = d->database->table(context->tableName());
    entities.reserve(contextTable->rows().size());

    foreach(Row *row, contextTable->rows()) {
        EntityMetaData metaData;
        metaData.id = row->data(LBMeta::EntityColumns::Id).toInt();
        metaData.entityTypeId = row->data(LBMeta::EntityColumns::EntityType).toInt();
        entities.append(metaData);
    }

    return entities;
}

EntityMetaData LocalStorageDriver::createEntity(EntityType *type)
{
    Q_D(LocalStorageDriver);
    Table *table = d->database->table(type->context()->tableName());
    Row *row = table->appendRow();
    row->setData(LBMeta::EntityColumns::EntityType, QVariant(type->id()));

    EntityMetaData metaData;
    metaData.entityTypeId = type->id();
    metaData.id = row->id();
    return metaData;
}

} // namespace LBDatabase
