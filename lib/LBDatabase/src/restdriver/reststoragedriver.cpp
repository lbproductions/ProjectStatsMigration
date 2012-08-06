#include "reststoragedriver.h"

#include "../attributevalue.h"
#include "../context.h"
#include "../enumattribute.h"
#include "../entity.h"
#include "../function.h"
#include "../functionvalue.h"
#include "../relationvalue.h"
#include "../relation.h"

#include <QxtCore/QxtJSON>

#include <QDebug>
<<<<<<< HEAD
=======
#include <QEventLoop>
>>>>>>> refs/heads/uncommited

namespace LBDatabase {

RestStorageDriver::RestStorageDriver(const QUrl &server, QObject *parent) :
    StorageDriver(parent),
    m_initialized(false),
    m_serverUrl(server),
    m_totalRequests(0),
    m_requestsDone(0)
{
}

RestStorageDriver::~RestStorageDriver()
{
}

bool RestStorageDriver::init()
{
    if(m_totalRequests > 0)
        return true;

    m_nam = new QNetworkAccessManager(this);

    QNetworkReply *reply = m_nam->get(QNetworkRequest(m_serverUrl));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(metaDataReplyFinished()));
    return true;
}

QList<ContextMetaData> RestStorageDriver::contexts() const
{
    QList<ContextMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::ContextsTableName).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        ContextMetaData metaData;
        metaData.id = data.value("id").toInt();
        metaData.identifier =  data.value(LBMeta::ContextColumns::Identifier).toString();
        metaData.displayName =  data.value(LBMeta::ContextColumns::DisplayName).toString();
        metaData.tableName =  data.value(LBMeta::ContextColumns::TableName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<EntityTypeMetaData> RestStorageDriver::entityTypes() const
{
    QList<EntityTypeMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::EntitiesTableName).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        EntityTypeMetaData metaData;
        metaData.id =  data.value("id").toInt();
        metaData.identifier = data.value(LBMeta::EntityTypeColumns::Identifier).toString();
        metaData.displayName = data.value(LBMeta::EntityTypeColumns::DisplayName).toString();
        metaData.displayNamePlural = data.value(LBMeta::EntityTypeColumns::DisplayNamePlural).toString();
        metaData.contextId = data.value(LBMeta::EntityTypeColumns::Context).toInt();
        metaData.parentEntityTypeId = data.value(LBMeta::EntityTypeColumns::ParentEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<AttributeMetaData> RestStorageDriver::attributes() const
{
    QList<AttributeMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::AttributesTableName).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        AttributeMetaData metaData;
        metaData.id = data.value("id").toInt();
        metaData.identifier = data.value(LBMeta::AttributeColumns::Identifier).toString();
        metaData.displayName = data.value(LBMeta::AttributeColumns::DisplayName).toString();
        metaData.cached = data.value(LBMeta::AttributeColumns::CacheData).toBool();
        metaData.calculated = data.value(LBMeta::AttributeColumns::Calculated).toBool();
        metaData.editable = data.value(LBMeta::AttributeColumns::Editable).toBool();
        metaData.entityTypeId = data.value(LBMeta::AttributeColumns::EntityTypeId).toInt();
        metaData.type = static_cast<Attribute::Type>(data.value(LBMeta::AttributeColumns::Type).toInt());
        metaData.returnEntityTypeId = data.value(LBMeta::AttributeColumns::ReturnEntityType).toInt();
        metaData.defaultValue = data.value(LBMeta::AttributeColumns::DefaultValue);
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<FunctionMetaData> RestStorageDriver::functions() const
{
    QList<FunctionMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::FunctionsTableName).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        FunctionMetaData metaData;
        metaData.id = data.value("id").toInt();
        metaData.identifier = data.value(LBMeta::FunctionColumns::Identifier).toString();
        metaData.cached = data.value(LBMeta::FunctionColumns::CacheData).toBool();
        metaData.calculated = data.value(LBMeta::FunctionColumns::Calculated).toBool();
        metaData.displayName = data.value(LBMeta::FunctionColumns::DisplayName).toString();
        metaData.editable = data.value(LBMeta::FunctionColumns::Editable).toBool();
        metaData.entityColumnName = data.value(LBMeta::FunctionColumns::EntityColumnName).toString();
        metaData.entityTypeId = data.value(LBMeta::FunctionColumns::EntityType).toInt();
        metaData.keyEntityColumnName = data.value(LBMeta::FunctionColumns::KeyEntityColumnName).toString();
        metaData.keyEntityTypeId = data.value(LBMeta::FunctionColumns::KeyEntityType).toInt();
        metaData.tableName = data.value(LBMeta::FunctionColumns::TableName).toString();
        metaData.type = static_cast<Attribute::Type>(data.value(LBMeta::FunctionColumns::Type).toInt());
        metaData.returnEntityTypeId = data.value(LBMeta::FunctionColumns::ReturnEntityType).toInt();
        metaData.valueColumnName = data.value(LBMeta::FunctionColumns::ValueColumnName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationMetaData> RestStorageDriver::relations() const
{
    QList<RelationMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::RelationsTableName).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        RelationMetaData metaData;
        metaData.id = data.value("id").toInt();
        metaData.identifier = data.value(LBMeta::RelationColumns::Identifier).toString();
        metaData.identifierRight = data.value(LBMeta::RelationColumns::IdentifierRight).toString();
        metaData.displayName = data.value(LBMeta::RelationColumns::DisplayNameLeft).toString();
        metaData.displayNameRight = data.value(LBMeta::RelationColumns::DisplayNameRight).toString();
        metaData.cardinality = static_cast<Relation::Cardinality>(data.value(LBMeta::RelationColumns::Cardinality).toInt());
        metaData.direction = static_cast<Relation::Direction>(data.value(LBMeta::RelationColumns::Direction).toInt());
        metaData.editable = data.value(LBMeta::RelationColumns::Editable).toBool();
        metaData.editableTranspose = data.value(LBMeta::RelationColumns::EditableTranspose).toBool();
        metaData.calculated = data.value(LBMeta::RelationColumns::Calculated).toBool();
        metaData.entityTypeId = data.value(LBMeta::RelationColumns::EntityTypeLeft).toInt();
        metaData.entityTypeOtherId = data.value(LBMeta::RelationColumns::EntityTypeRight).toInt();
        metaData.leftEntityIdColumnName = data.value(LBMeta::RelationColumns::ColumnName).toString();
        metaData.rightEntityIdColumnName = data.value(LBMeta::RelationColumns::ColumnNameRight).toString();
        metaData.tableName = data.value(LBMeta::RelationColumns::TableName).toString();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<EnumAttributeMetaData> RestStorageDriver::enumValues() const
{
    QList<EnumAttributeMetaData> metaDatas;
    QVariantList list = m_metaData.value(EnumAttribute::EnumsTable).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        EnumAttributeMetaData metaData;
        metaData.identifier = data.value(LBMeta::EnumAttributeColumns::Identifier).toString();
        metaData.attributeId = data.value(LBMeta::EnumAttributeColumns::Attribute).toInt();
        metaData.value = data.value(LBMeta::EnumAttributeColumns::Value).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<FunctionReimplementationMetaData> RestStorageDriver::functionReimplementations() const
{
    QList<FunctionReimplementationMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::FunctionReimplementationsTable).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        FunctionReimplementationMetaData metaData;
        metaData.reimplementedFunctionId = data.value(LBMeta::FunctionReimplementationsColumns::ReimplementedFunction).toInt();
        metaData.reimplementingEntityTypeId = data.value(LBMeta::FunctionReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<RelationReimplementationMetaData> RestStorageDriver::relationReimplementations() const
{
    QList<RelationReimplementationMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::RelationReimplementationsTable).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        RelationReimplementationMetaData metaData;
        metaData.reimplementedRelationId = data.value(LBMeta::RelationReimplementationsColumns::ReimplementedRelation).toInt();
        metaData.reimplementingEntityTypeId = data.value(LBMeta::RelationReimplementationsColumns::ReimplementingEntityType).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}

QList<DependencyMetaData> RestStorageDriver::dependencies() const
{
    QList<DependencyMetaData> metaDatas;
    QVariantList list = m_metaData.value(LBMeta::DependenciesTable).toList();
    metaDatas.reserve(list.size());
    foreach(QVariant v, list) {
        QVariantMap data = v.toMap();
        DependencyMetaData metaData;
        metaData.id = data.value("id").toInt();
        metaData.dependendPropertyId = data.value(LBMeta::DependenciesColumns::DependendPropertyId).toInt();
        metaData.dependencyPropertyId = data.value(LBMeta::DependenciesColumns::DependencyPropertyId).toInt();
        metaData.dependendPropertyType =
                static_cast<Property::Type>(data.value(LBMeta::DependenciesColumns::DependendPropertyType).toInt());
        metaData.dependencyPropertyType =
                static_cast<Property::Type>(data.value(LBMeta::DependenciesColumns::DependencyPropertyType).toInt());
        metaData.entityRelation = data.value(LBMeta::DependenciesColumns::EntityRelation).toInt();
        metaDatas.append(metaData);
    }
    return metaDatas;
}
void RestStorageDriver::addDependency(DependencyMetaData &metaData)
{
    Q_UNUSED(metaData)
}

QVariant RestStorageDriver::attributeValue(const AttributeValue *value) const
{
    return m_entities.value(value->entity()->context()->identifier())
            .value(value->entity()->id()).value("attributes").toMap().value(value->attribute()->identifier());
}

void RestStorageDriver::setAttributeValue(const AttributeValue *value, const QVariant &data)
{
<<<<<<< HEAD
    Q_UNUSED(value)
    Q_UNUSED(data)
=======
    QList<QPair<QString, QString> > queryItems;
    queryItems.append(QPair<QString, QString>(value->attribute()->identifier(), data.toString()));

    QUrl url(entityUrl(value->entity()));
    url.setQueryItems(queryItems);
    QNetworkReply* reply = m_nam->sendCustomRequest(QNetworkRequest(url), QByteArray("PATCH"));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
>>>>>>> refs/heads/uncommited
}

void RestStorageDriver::addAttribute(EntityType *entityType, AttributeMetaData &metaData)
{
    Q_UNUSED(entityType)
    Q_UNUSED(metaData)
}

void RestStorageDriver::removeAttribute(int attributeId)
{
    Q_UNUSED(attributeId)
}

void RestStorageDriver::setAttributeDisplayName(int id, const QString &displayName)
{
    Q_UNUSED(id)
    Q_UNUSED(displayName)
}

void RestStorageDriver::setAttributeIdentifier(int id, const QString &identifier)
{
    Q_UNUSED(id)
    Q_UNUSED(identifier)
}

void RestStorageDriver::setAttributeType(int id, Attribute::Type type)
{
    Q_UNUSED(id)
    Q_UNUSED(type)
}

void RestStorageDriver::setAttributeEditable(int id, bool editable)
{
    Q_UNUSED(id)
    Q_UNUSED(editable)
}

void RestStorageDriver::setAttributeCalculated(int id, bool calculated)
{
    Q_UNUSED(id)
    Q_UNUSED(calculated)
}

void RestStorageDriver::setAttributeCached(int id, bool cached)
{
    Q_UNUSED(id)
    Q_UNUSED(cached)
}

void RestStorageDriver::setAttributeDefaultValue(int id, QVariant defaultValue)
{
    Q_UNUSED(id)
    Q_UNUSED(defaultValue)
}

QList<RelationValueData> RestStorageDriver::relatedEntities(Relation *relation) const
{
    QList<RelationValueData> entities;
    QHashIterator<int, QVariantMap> it2(m_entities.value(relation->entityType()->context()->identifier()));
    while(it2.hasNext()) {
        it2.next();
        QVariantList relatedEntities = it2.value().value("relations").toMap().value(relation->identifier()).toMap().value("relatedEntities").toList();
        foreach(QVariant v, relatedEntities) {
            RelationValueData data;
            data.leftId = it2.key();
            data.rightId = v.toInt();
            data.rowId = 0;
            entities.append(data);
        }
    }
    return entities;
}

int RestStorageDriver::addRelatedEntity(RelationValueBase *value, const RelationValueData &data)
{
<<<<<<< HEAD
    Q_UNUSED(value)
    Q_UNUSED(data)
=======
    QList<QPair<QString, QString> > queryItems;
    queryItems.append(QPair<QString, QString>(QLatin1String("entity"), QString::number(data.rightId)));

    QUrl url(relationValueUrl(value));
    url.setQueryItems(queryItems);
    QNetworkReply* reply = m_nam->post(QNetworkRequest(url), QByteArray());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

>>>>>>> refs/heads/uncommited
    return 0;
}

void RestStorageDriver::addRelation(EntityType *entityType, RelationMetaData &metaData)
{
    Q_UNUSED(entityType)
    Q_UNUSED(metaData)
}

void RestStorageDriver::setRelationIdentifier(int id, const QString &identifier)
{
    Q_UNUSED(id)
    Q_UNUSED(identifier)
}

void RestStorageDriver::setRelationIdentifierRight(int id, const QString &identifierRight)
{
    Q_UNUSED(id)
    Q_UNUSED(identifierRight)
}

void RestStorageDriver::setRelationDisplayName(int id, const QString &displayName)
{
    Q_UNUSED(id)
    Q_UNUSED(displayName)
}

void RestStorageDriver::setRelationDisplayNameRight(int id, const QString &displayNameRight)
{
    Q_UNUSED(id)
    Q_UNUSED(displayNameRight)
}

void RestStorageDriver::setRelationCardinality(int id, Relation::Cardinality cardinality)
{
    Q_UNUSED(id)
    Q_UNUSED(cardinality)
}

void RestStorageDriver::setRelationDirection(int id, Relation::Direction direction)
{
    Q_UNUSED(id)
    Q_UNUSED(direction)
}

void RestStorageDriver::setRelationEntityTypeRight(int id, EntityType *entityType)
{
    Q_UNUSED(id)
    Q_UNUSED(entityType)
}

void RestStorageDriver::setRelationEditable(int id, bool editable)
{
    Q_UNUSED(id)
    Q_UNUSED(editable)
}

void RestStorageDriver::setRelationCalculated(int id, bool calculated)
{
    Q_UNUSED(id)
    Q_UNUSED(calculated)
}

QList<FunctionValueData> RestStorageDriver::functionValues(Function *function) const
{
    QList<FunctionValueData> functionValueDatas;

    QHashIterator<int, QVariantMap> it2(m_entities.value(function->entityType()->context()->identifier()));
        while(it2.hasNext()) {
            it2.next();
            QVariantMap values = it2.value().value("functions").toMap().value(function->identifier()).toMap().value("values").toMap();
            QMapIterator<QString, QVariant> valueIt(values);
            while(valueIt.hasNext()) {
                valueIt.next();
                FunctionValueData data;
                data.entityId = it2.key();
                data.keyEntityId = valueIt.key().toInt();
                data.value = valueIt.value();
                data.rowId = 0;
                functionValueDatas.append(data);
            }
        }

    return functionValueDatas;
}

void RestStorageDriver::setFunctionValue(FunctionValue *value, const FunctionValueData &data)
{
<<<<<<< HEAD
    Q_UNUSED(value)
    Q_UNUSED(data)
=======
    QList<QPair<QString, QString> > queryItems;
    queryItems.append(QPair<QString, QString>(QLatin1String("functionIdentifier"), value->function()->identifier()));
    queryItems.append(QPair<QString, QString>(QLatin1String("keyId"), QString::number(data.keyEntityId)));
    queryItems.append(QPair<QString, QString>(QLatin1String("value"), data.value.toString()));

    QUrl url(entityUrl(value->entity()));
    url.setQueryItems(queryItems);
    QNetworkReply* reply = m_nam->post(QNetworkRequest(url), QByteArray());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
>>>>>>> refs/heads/uncommited
}

void RestStorageDriver::addFunction(EntityType *entityType, FunctionMetaData &metaData)
{
    Q_UNUSED(entityType)
    Q_UNUSED(metaData)
}

void RestStorageDriver::setFunctionDisplayName(int id, const QString &displayName)
{
    Q_UNUSED(id)
    Q_UNUSED(displayName)
}

void RestStorageDriver::setFunctionIdentifier(int id, const QString &identifier)
{
    Q_UNUSED(id)
    Q_UNUSED(identifier)
}

void RestStorageDriver::setFunctionType(int id, Attribute::Type type)
{
    Q_UNUSED(id)
    Q_UNUSED(type)
}

void RestStorageDriver::setFunctionEditable(int id, bool editable)
{
    Q_UNUSED(id)
    Q_UNUSED(editable)
}

void RestStorageDriver::setFunctionKeyEntityType(int id, EntityType *entityType)
{
    Q_UNUSED(id)
    Q_UNUSED(entityType)
}

QList<EntityMetaData> RestStorageDriver::entities(Context *context) const
{
    QList<EntityMetaData> entities;

    QHashIterator<int, QVariantMap> it2(m_entities.value(context->identifier()));
    while(it2.hasNext()) {
        it2.next();
        EntityMetaData data;
        data.entityTypeId = it2.value().value("entityTypeId").toInt();
        data.id = it2.value().value("id").toInt();
        entities.append(data);
    }

    return entities;
}

EntityMetaData RestStorageDriver::createEntity(EntityType *type)
{
<<<<<<< HEAD
    Q_UNUSED(type)
    return EntityMetaData();
=======
    QList<QPair<QString, QString> > queryItems;
    queryItems.append(QPair<QString, QString>(QLatin1String("entityType"), QString::number(type->id())));

    QUrl url(contextUrl(type->context()));
    url.setQueryItems(queryItems);
    QNetworkReply* reply = m_nam->sendCustomRequest(QNetworkRequest(url), QByteArray("POST"));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    EntityMetaData data;
    data.id  = QString::fromUtf8(reply->readAll().data()).toInt();
    data.entityTypeId = type->id();
    return data;
>>>>>>> refs/heads/uncommited
}

int RestStorageDriver::totalRequests() const
{
    return m_totalRequests;
}

int RestStorageDriver::requestsDone() const
{
    return m_requestsDone;
}

void RestStorageDriver::metaDataReplyFinished()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
<<<<<<< HEAD
    m_metaData = QxtJSON::parse(QString(reply->readAll())).toMap();
=======
    m_metaData = QxtJSON::parse(QString::fromUtf8(reply->readAll().data())).toMap();
>>>>>>> refs/heads/uncommited

    foreach(QVariant contextData, m_metaData.value(LBMeta::ContextsTableName).toList()) {
        ++m_totalRequests;
        QVariantMap metaData = contextData.toMap();
        QUrl contextUrl(m_serverUrl.toString() +'/'+ metaData.value(LBMeta::ContextColumns::Identifier).toString());
        QNetworkReply *contextContentsReply = m_nam->get(QNetworkRequest(contextUrl));
        connect(contextContentsReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
<<<<<<< HEAD
        connect(contextContentsReply, SIGNAL(finished()), this, SLOT(contextContentsReplyFinished()));
    }
=======
        connect(contextContentsReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        connect(contextContentsReply, SIGNAL(finished()), this, SLOT(contextContentsReplyFinished()));
    }
    reply->deleteLater();
>>>>>>> refs/heads/uncommited
}

void RestStorageDriver::contextContentsReplyFinished()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
<<<<<<< HEAD
    QVariantMap data = QxtJSON::parse(QString(reply->readAll())).toMap();
=======
    QVariantMap data = QxtJSON::parse(QString::fromUtf8(reply->readAll().data())).toMap();
>>>>>>> refs/heads/uncommited

    foreach(QVariant v, data.value("entities").toList()) {
        ++m_totalRequests;
        QUrl entitiyUrl(m_serverUrl.toString() +'/'+
                        data.value(LBMeta::ContextColumns::Identifier).toString() +'/'+
                        QString::number(v.toInt()));
<<<<<<< HEAD
        QNetworkReply *entityUrl = m_nam->get(QNetworkRequest(entitiyUrl));
        connect(entityUrl, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
        connect(entityUrl, SIGNAL(finished()), this, SLOT(entityReplyFinished()));
    }
    ++m_requestsDone;
=======
        QNetworkReply *entityReply = m_nam->get(QNetworkRequest(entitiyUrl));
        connect(entityReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
        connect(entityReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        connect(entityReply, SIGNAL(finished()), this, SLOT(entityReplyFinished()));
    }
    ++m_requestsDone;
    reply->deleteLater();
>>>>>>> refs/heads/uncommited
}

void RestStorageDriver::entityReplyFinished()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
<<<<<<< HEAD
    QVariantMap data = QxtJSON::parse(QString(reply->readAll())).toMap();
=======
    QVariantMap data = QxtJSON::parse(QString::fromUtf8(reply->readAll().data())).toMap();
>>>>>>> refs/heads/uncommited
    QString contextIdentifier = data.value("context").toString();
    QHash<int, QVariantMap> entities(m_entities.value(contextIdentifier));
    entities.insert(data.value("id").toInt(), data);
    m_entities.insert(contextIdentifier, entities);
    ++m_requestsDone;
<<<<<<< HEAD
=======
    reply->deleteLater();
>>>>>>> refs/heads/uncommited

    if(m_requestsDone == m_totalRequests) {
        emit progress(m_requestsDone);
        emit finished();
    }
    else
        emit progress(m_requestsDone);
}

<<<<<<< HEAD
=======
void RestStorageDriver::onError(QNetworkReply::NetworkError error)
{
    qWarning() << error;
}

QUrl RestStorageDriver::contextUrl(Context *context) const
{
    return QUrl(m_serverUrl.toString() +'/'+
                    context->identifier());
}

QUrl RestStorageDriver::entityUrl(Entity *entity) const
{
    return QUrl(contextUrl(entity->context()).toString() +'/'+
                QString::number(entity->id()));
}

QUrl RestStorageDriver::relationValueUrl(RelationValueBase *value) const
{
    return QUrl(entityUrl(value->entity()).toString() +'/'+
                    value->relation()->identifier());
}

>>>>>>> refs/heads/uncommited
} // namespace LBDatabase
