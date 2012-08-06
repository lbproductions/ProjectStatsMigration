#include "contentsservice.h"

<<<<<<< HEAD
=======
#include "jsonexporter.h"

>>>>>>> refs/heads/uncommited
#include "../attributevalue.h"
#include "../context.h"
#include "../entity.h"
#include "../enumattribute.h"
#include "../function.h"
#include "../functionvalue.h"
#include "../propertyvalue.h"
#include "../relationvalue.h"
#include "../storage.h"
#include "../storagedriver.h"

#include <QxtWeb/QxtWebPageEvent>
#include <QxtWeb/QxtWebRequestEvent>
#include <QxtCore/QxtJSON>

<<<<<<< HEAD
=======
#define COMMA ,

>>>>>>> refs/heads/uncommited
namespace LBDatabase {

ContentsService::ContentsService(Storage *storage, QxtAbstractWebSessionManager *sm, QObject *parent) :
    QxtAbstractWebService(sm,parent),
    storage(storage)
{
}

ContentsService::~ContentsService()
{
}

void ContentsService::pageRequestedEvent(QxtWebRequestEvent *event)
{
<<<<<<< HEAD
    if(event->url == QUrl("/") ||
            event->url.isEmpty() ||
            event->url.path().size() == 0 ||
            event->url.path().size() == 1) {
        respondRoot(event);
    }
    else {
        QStringList path = event->url.path().split('/');
        if(path.length() == 2 ||
                (path.length() == 3 && path.at(2).isEmpty())) {
            respondContext(event);
        }
        else if(path.length() == 3) {
            respondEntity(event);
=======
    if(event->method == QLatin1String("GET")) {
        if(event->url == QUrl("/") ||
                event->url.isEmpty() ||
                event->url.path().size() == 0 ||
                event->url.path().size() == 1) {
            respondRoot(event);
        }
        else {
            QStringList path = event->url.path().split('/');
            if(path.length() == 2 ||
                    (path.length() == 3 && path.at(2).isEmpty())) {
                respondContext(event);
            }
            else if(path.length() == 3) {
                respondEntity(event);
            }
            else if(path.length() == 4) {
                respondRelation(event);
            }
            else {
                postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 400, QByteArray("Invalid URL.")));
            }
        }
    }
    else if(event->method == QLatin1String("PATCH")) {
        QStringList path = event->url.path().split('/');

        if(path.length() == 3) {
            patchEntity(event);
        }
        else {
            postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 400, QByteArray("Invalid URL.")));
        }
    }
    else if(event->method == QLatin1String("POST")) {
        QStringList path = event->url.path().split('/');

        if(path.length() == 2) {
            postContext(event);
        }
        else if(path.length() == 3) {
            postFunction(event);
        }
        else if(path.length() == 4) {
            postRelation(event);
>>>>>>> refs/heads/uncommited
        }
        else {
            postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 400, QByteArray("Invalid URL.")));
        }
    }
}

void ContentsService::respondRoot(QxtWebRequestEvent *event)
{
<<<<<<< HEAD
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

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, QxtJSON::stringify(hash).toUtf8());
=======
    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, JsonExporter::metaDataToJson(storage).toUtf8());
>>>>>>> refs/heads/uncommited
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::respondContext(QxtWebRequestEvent *event)
{
<<<<<<< HEAD
    QString contextIdentifier = event->url.path().split('/').at(1);

    Context *context = storage->context(contextIdentifier);

    if(!context) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("No such context in this storage: ").append(contextIdentifier).toUtf8()));
        return;
    }
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
    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, QxtJSON::stringify(hash).toUtf8());
=======
    QStringList path = event->url.path().split('/');

    Context *context = contextFromUrl(path);

    if(!context) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, JsonExporter::contextToJson(context).toUtf8());
>>>>>>> refs/heads/uncommited
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::respondEntity(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');

<<<<<<< HEAD
    if(path.length() != 3) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QByteArray("Cannot find an entity for this URL:")));
        return;
    }

    QString contextIdentifier = path.at(1);

    Context *context = storage->context(contextIdentifier);

    if(!context) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("No such context in this storage: ").append(contextIdentifier).toUtf8()));
        return;
    }

    int entityId = path.at(2).toInt();

    Entity *entity = context->entity(entityId);

    if(!entity) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("No such entity in this context: ").append(QString::number(entityId)).toUtf8()));
        return;
    }

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
        QVariantHash relationData;
        relationData.insert(QLatin1String("entitiesContext"), relation->entityTypeOther()->context()->identifier());

        RelationValue<Entity> *value = entity->relation<Entity>(relation->identifier());

        QVariantList relatedEntities;
        relatedEntities.reserve(value->entities().size());
        foreach(Entity *relatedEntity, value->entities()) {
            relatedEntities.append(relatedEntity->id());
        }
        relationData.insert(QLatin1String("relatedEntities"), relatedEntities);
        relations.insert(relation->identifier(), relationData);
    }
    hash.insert(QLatin1String("relations"), relations);

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, QxtJSON::stringify(hash).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
=======
    Entity *entity = entityFromUrl(path);

    if(!entity) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, JsonExporter::entityToJson(entity).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::respondRelation(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');

    RelationValue<Entity> *value = relationValueFromUrl(path);

    if(!value) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, QxtJSON::stringify(JsonExporter::relationValueToJson(value)).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::patchEntity(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');
    Entity *entity = entityFromUrl(path);
    if(!entity) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    foreach(QPair<QString COMMA QString> queryItem, event->url.queryItems()) {
        patchEntity(entity, queryItem);
    }

    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, QByteArray()));
}

void ContentsService::patchEntity(Entity *entity, const QPair<QString, QString> &queryItem)
{
    AttributeValue *value = entity->attribute(queryItem.first);
    if(!value)
        return;

    value->setData(QVariant(queryItem.second));
}

void ContentsService::postRelation(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');
    RelationValue<Entity> *value = relationValueFromUrl(path);
    if(!value) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    foreach(QPair<QString COMMA QString> queryItem, event->url.queryItems()) {
        postRelation(value, queryItem);
    }

    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, QByteArray()));
}

void ContentsService::postRelation(RelationValue<Entity> *relation, const QPair<QString, QString> &queryItems)
{
    Entity *entity = relation->relation()->entityTypeOther()->context()->entity(queryItems.second.toInt());
    if(!entity)
        return;

    relation->addEntity(entity);
}

void ContentsService::postContext(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');
    Context *context = contextFromUrl(path);
    if(!context || event->url.queryItems().size() != 1) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    EntityType *type = storage->entityType(event->url.queryItems().at(0).second.toInt());
    Entity *entity = context->insertEntity(type);

    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, QByteArray(QString::number(entity->id()).toUtf8())));
}

void ContentsService::postFunction(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');
    Entity *entity = entityFromUrl(path);
    if(!entity) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    QString functionIdentifier;
    int keyId;
    QVariant value;

    foreach(QPair<QString COMMA QString> queryItem, event->url.queryItems()) {
        if(queryItem.first == QLatin1String("functionIdentifier")) {
            functionIdentifier = queryItem.second;
        }
        else if(queryItem.first == QLatin1String("keyId")) {
            keyId = queryItem.second.toInt();
        }
        else if(queryItem.first == QLatin1String("value")) {
            value = QVariant(queryItem.second);
        }
    }

    FunctionValue *functionValue = entity->function(functionIdentifier);
    Entity *keyEntity = functionValue->function()->keyEntityType()->context()->entity(keyId);
    functionValue->setValue(keyEntity, value);

    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, QByteArray()));
}

Context *ContentsService::contextFromUrl(const QStringList &path) const
{
    if(path.length() < 2)
        return 0;

    return storage->context(path.at(1));
}

Entity *ContentsService::entityFromUrl(const QStringList &path) const
{
    if(path.length() < 3)
        return 0;

    Context *context = contextFromUrl(path);

    if(!context)
        return 0;

    return context->entity(path.at(2).toInt());
}

RelationValue<Entity> *ContentsService::relationValueFromUrl(const QStringList &path) const
{
    if(path.length() < 4)
        return 0;

    Entity *entity = entityFromUrl(path);

    if(!entity)
        return 0;

    return entity->relation<Entity>(path.at(3));
>>>>>>> refs/heads/uncommited
}

} // namespace LBDatabase
