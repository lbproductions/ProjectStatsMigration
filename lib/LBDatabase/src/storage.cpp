#include "storage.h"

#include "attribute.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "enumattribute.h"
#include "function.h"
#include "propertyvalue.h"
#include "relation.h"
#include "relationvalue.h"
#include "storagedriver.h"

#include <QFile>
#include <QMutex>
#include <QFileInfo>
#include <QMetaMethod>

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** StoragePrivate
*/
namespace {
const QString NameColumn("name");
const QString SourcePathColumn("cpppath");
}

class StoragePrivate {
    static QHash<QString, Storage*> instances;

    StoragePrivate() : driver(0) {}

    void init();
    bool open();
    Context *addContext(const QString &name, const QString &baseEntityTypeName);

    Context *createContextInstance(const ContextMetaData &metaData);

    void initDependency(DependencyMetaData metaData);
    Property *property(Property::Type type, int id);

    StorageDriver *driver;

    QString name;
    QString sourcePath;

    QHash<int, Context *> contexts;
    QHash<QString, int> contextIds;
    QHash<int, EntityType *> entityTypes;
    QHash<int, Attribute *> attributes;
    QHash<int, Relation *> relations;
    QHash<int, Function *> functions;
    QList<Property *> properties;

    QHash<QString, QMetaObject> contextMetaObjects;

    Storage * q_ptr;
    Q_DECLARE_PUBLIC(Storage)
};

QHash<QString, Storage*> StoragePrivate::instances = QHash<QString, Storage*>();

void StoragePrivate::init()
{
    qRegisterMetaType<ContextMetaData>();
}

bool sortContextByName(const Context *c1, const Context *c2)
{
    return c1->identifier() < c2->identifier();
}

bool StoragePrivate::open()
{
    Q_Q(Storage);

    if(!driver)
        return false;

    if(!driver->init())
        return false;

    QList<ContextMetaData> contextMetaDatas = driver->contexts();
    QList<EntityTypeMetaData> entityTypeMetaDatas = driver->entityTypes();
    QList<AttributeMetaData> attributeMetaDatas = driver->attributes();
    QList<FunctionMetaData> functionMetaDatas = driver->functions();
    QList<RelationMetaData> relationMetaDatas = driver->relations();

    contexts.reserve(contextMetaDatas.size());
    entityTypes.reserve(entityTypeMetaDatas.size());
    attributes.reserve(attributeMetaDatas.size());
    properties.reserve(attributeMetaDatas.size() + functionMetaDatas.size() + relationMetaDatas.size());

    foreach(ContextMetaData metaData, contextMetaDatas) {
        Context *context = createContextInstance(metaData);
        contexts.insert(metaData.id, context);
        contextIds.insert(metaData.identifier, metaData.id);
    }

    foreach(EntityTypeMetaData metaData, entityTypeMetaDatas) {
        q->insertEntityType(new EntityType(metaData, q));
    }

    foreach(AttributeMetaData metaData, attributeMetaDatas) {
        if(metaData.type == Attribute::Enum) {
            q->insertAttribute(new EnumAttribute(metaData, q));
        }
        else {
            q->insertAttribute(new Attribute(metaData, q));
        }
    }

    foreach(EnumAttributeMetaData metaData, driver->enumValues()) {
        EnumAttribute *attribute = static_cast<EnumAttribute *>(attributes.value(metaData.attributeId));
        attribute->addEnumValue(metaData.identifier,
                                metaData.value);
    }

    foreach(RelationMetaData metaData, relationMetaDatas) {
        q->insertRelation(new Relation(metaData, q));
    }

    foreach(FunctionMetaData metaData, functionMetaDatas) {
        q->insertFunction(new Function(metaData, q));
    }

    foreach(FunctionReimplementationMetaData metaData, driver->functionReimplementations()) {
        Function *function = functions.value(metaData.reimplementedFunctionId);
        EntityType *type = entityTypes.value(metaData.reimplementingEntityTypeId);
        function->addReimplementingEntityType(type);
    }

    foreach(RelationReimplementationMetaData metaData, driver->relationReimplementations()) {
        Relation *relation = relations.value(metaData.reimplementedRelationId);
        EntityType *type = entityTypes.value(metaData.reimplementingEntityTypeId);
        relation->addReimplementingEntityType(type);
    }

    foreach(Context *context, contexts.values()) {
        context->initializeEntityHierarchy();
        context->loadEntities();
    }

    foreach(Property *property, properties) {
        property->addPropertyValueToEntities();
    }
    foreach(Property *property, properties) {
        property->fetchValues();
    }
    foreach(Relation *relation, relations) {
        relation->calculateValues();
    }


    foreach(DependencyMetaData metaData, driver->dependencies()) {
        initDependency(metaData);
    }

    return true;
}

Context *StoragePrivate::createContextInstance(const ContextMetaData &metaData)
{
    Q_Q(Storage);
    const QString contextName = metaData.identifier;

    if(!contextMetaObjects.contains(contextName))
        return new Context(metaData, q);

    QObject *object = contextMetaObjects.value(contextName).newInstance(Q_ARG(const::LBDatabase::ContextMetaData&,metaData), Q_ARG(::LBDatabase::Storage*, q));
    return static_cast<Context *>(object);
}

void StoragePrivate::initDependency(DependencyMetaData metaData)
{
    Property *dependend = property(metaData.dependendPropertyType, metaData.dependendPropertyId);
    Property *dependency = property(metaData.dependencyPropertyType, metaData.dependencyPropertyId);

    if(metaData.entityRelation == -1) {
        foreach(Entity *entity, dependend->entityType()->entities()) {
            PropertyValue *dependendProperty = entity->propertyValue(dependend);
            PropertyValue *dependencyProperty = entity->propertyValue(dependency);
            QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
        }
    }
    else if(metaData.entityRelation == 0) {
        foreach(PropertyValue *dependencyProperty, dependend->propertyValues()) {
            foreach(PropertyValue *dependendProperty, dependency->propertyValues()) {
                QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
            }
        }
    }
    else if(metaData.entityRelation > 0) {
        Relation *relation = relations.value(metaData.entityRelation);
        foreach(Entity *entity, dependend->entityType()->entities()) {
            PropertyValue *dependendProperty = entity->propertyValue(dependend);
            RelationValue<Entity> *relationValue = entity->relation<Entity>(relation->identifier());
            foreach(Entity *relatedEntity, relationValue->entities()) {
                PropertyValue *dependencyProperty = relatedEntity->propertyValue(dependency);
                QObject::connect(dependencyProperty, SIGNAL(changed()), dependendProperty, SLOT(recalculateAfterDependencyChange()));
            }
        }
    }
}

Property *StoragePrivate::property(Property::Type type, int id)
{
    switch(type) {
    case Property::Attribute:
    case Property::EnumAttribute:
        return attributes.value(id);
        break;
    case Property::Function:
        return functions.value(id);
        break;
    case Property::Relation:
        return relations.value(id);
        break;
    }
    return 0;
}

/******************************************************************************
** Storage
*/
/*!
  \class Storage
  \brief The Storage class represents a high level storage for entities.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var Storage::d_ptr
  \internal
  */

/*!
  \fn Storage::nameChanged()

  This signal is emitted when the name of this storage changes.

  */

//void Storage::convertSqlliteDatabaseToStorage(const QString &sqliteDatabaseFileName, const QString &storageFileName)
//{
//    QFile file(sqliteDatabaseFileName);
//    file.open(QFile::ReadOnly);
//    file.copy(storageFileName);
//    file.close();


////    Database *database = Database::instance(storageFileName);
////    database->open();
////    QList<Table *> tables = database->tables();

////    database->createTable(MetaDataTableName);
////    database->createTable(ContextsTableName);
////    database->createTable(EntitiesTableName);
////    database->createTable(AttributesTableName);
////    database->createTable(RelationsTableName);
////    Table *metaDataTable = database->table(MetaDataTableName);
////    Table *contextsTable = database->table(ContextsTableName);
////    Table *entityTypesTable = database->table(EntitiesTableName);
////    Table *attributesTable = database->table(AttributesTableName);
////    Table *relationsTable = database->table(RelationsTableName);

////    metaDataTable->addColumn(NameColumn,QLatin1String("TEXT"));
////    metaDataTable->appendRow();

////    contextsTable->addColumn(Context::IdentifierColumn,QLatin1String("TEXT"));

////    entityTypesTable->addColumn(EntityType::ContextColumn,QLatin1String("INTERGER"));
////    entityTypesTable->addColumn(EntityType::IdentifierColumn,QLatin1String("TEXT"));
////    entityTypesTable->addColumn(EntityType::ParentEntityTypeColumn,QLatin1String("INTERGER"));

////    attributesTable->addColumn(Attribute::IdentifierColumn,QLatin1String("TEXT"));
////    attributesTable->addColumn(Attribute::DisplayNameColumn,QLatin1String("TEXT"));
////    attributesTable->addColumn(Attribute::EntityTypeIdColumn,QLatin1String("INTERGER"));

//////    relationsTable->addColumn(Relation::NameColumn,QLatin1String("TEXT"));
//////    relationsTable->addColumn(Relation::DisplayNameLeftColumn,QLatin1String("TEXT"));
//////    relationsTable->addColumn(Relation::DisplayNameRightColumn,QLatin1String("TEXT"));
//////    relationsTable->addColumn(Relation::EntityTypeLeftColumn,QLatin1String("INTERGER"));
//////    relationsTable->addColumn(Relation::EntityTypeRightColumn,QLatin1String("INTERGER"));
//////    relationsTable->addColumn(Relation::CardinalityColumn,QLatin1String("INTERGER"));

////    Storage *storage = Storage::instance(storageFileName);
////    storage->open();
////    storage->setName(QFileInfo(storageFileName).fileName());

////    foreach(Table *table, tables) {
////        Context *context = storage->addContext(table->name(), table->name().remove(table->name().size() - 1, 1));
////        EntityType *base = context->baseEntityType();

////        table->addColumn(Entity::EntityTypeIdColumn, QLatin1String("INTEGER"), QVariant(base->id()));

////        foreach(Column *column, table->columns()) {
////            if(column->name().compare("ID", Qt::CaseInsensitive) != 0) {
////                base->addAttribute(column->name(),Attribute::Unkown);
////            }
////        }
////    }
//}

/*!
  Closes the storage.
  */
Storage::~Storage()
{
}

void Storage::setDriver(StorageDriver *driver)
{
    Q_D(Storage);
    d->driver = driver;
}

/*!
  Returns the name of the storage.
  */
QString Storage::name() const
{
    Q_D(const Storage);
    return d->name;
}

/*!
  Creates a storage, which uses the database \a fileName.
  */
Storage::Storage(QObject *parent) :
    QObject(parent),
    d_ptr(new StoragePrivate)
{
    Q_D(Storage);
    d->q_ptr = this;
    d->init();
}

/*!
  Returns the EntityType with the ID \a id.
  */
EntityType *Storage::entityType(int id) const
{
    Q_D(const Storage);
    return d->entityTypes.value(id, 0);
}

/*!
  Returns the EntityType with the ID \a id.
  */
Context *Storage::context(int id) const
{
    Q_D(const Storage);
    return d->contexts.value(id, 0);
}

Context *Storage::context(const QString name) const
{
    Q_D(const Storage);
    return d->contexts.value(d->contextIds.value(name));
}

/*!
  Returns a list of all contexts in this storage.
  */
QList<Context *> Storage::contexts() const
{
    Q_D(const Storage);
    QList<Context *> contexts = d->contexts.values();
    qSort(contexts.begin(), contexts.end(), sortContextByName);
    return contexts;
}

/*!
  Returns the Attribute with the ID \a id.
  */
Attribute *Storage::attribute(int id) const
{
    Q_D(const Storage);
    return d->attributes.value(id, 0);
}

StorageDriver *Storage::driver() const
{
    Q_D(const Storage);
    return d->driver;
}

/*!
  \internal

  Inserts the entity type \a type into the storage-global list of types.
  */
void Storage::insertEntityType(EntityType *type)
{
    Q_D(Storage);
    if(d->entityTypes.contains(type->id()))
        return;

    d->entityTypes.insert(type->id(), type);
}

/*!
  \internal

  Inserts the attribute \a attribute into the storage-global list of attributes.
  */
void Storage::insertAttribute(Attribute *attribute)
{
    Q_D(Storage);
    if(d->attributes.contains(attribute->id()))
        return;

    d->attributes.insert(attribute->id(), attribute);
    d->properties.append(attribute);
}

void Storage::removeAttribute(Attribute *attribute)
{
    Q_D(Storage);
    if(!d->attributes.contains(attribute->id()))
        return;

    d->attributes.remove(attribute->id());
    d->properties.removeAll(attribute);
}

/*!
  \internal

  Inserts the relation \a relation into the storage-global list of relations.
  */
void Storage::insertRelation(Relation *relation)
{
    Q_D(Storage);
    if(d->relations.contains(relation->id()))
        return;

    d->relations.insert(relation->id(), relation);
    d->properties.append(relation);
}

/*!
  \internal

  Inserts the function \a function into the storage-global list of functions.
  */
void Storage::insertFunction(Function *function)
{
    Q_D(Storage);
    if(d->functions.contains(function->id()))
        return;

    d->functions.insert(function->id(), function);
    d->properties.append(function);
}

QList<Relation *> Storage::relations() const
{
    Q_D(const Storage);
    return d->relations.values();
}

void Storage::registerContextType(const QString &contextName, QMetaObject metaObject)
{
    Q_D(Storage);
    if(d->contextMetaObjects.contains(contextName))
        return;

    d->contextMetaObjects.insert(contextName, metaObject);
}

/*!
  Opens the storage.
  Returns true upon success and false if something goes wrong (e.g. the file is
  no correct storage).
  */
bool Storage::open()
{
    Q_D(Storage);
    return d->open();
}

/*!
  Returns a list of all entity types, that this storage may contain.
  */
QList<EntityType *> Storage::entityTypes() const
{
    Q_D(const Storage);
    return d->entityTypes.values();
}

} // namespace LBDatabase
