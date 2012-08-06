#include "contentsservice.h"

#include "jsonexporter.h"

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

#define COMMA ,

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
        }
        else {
            postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 400, QByteArray("Invalid URL.")));
        }
    }
}

void ContentsService::respondRoot(QxtWebRequestEvent *event)
{
    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, JsonExporter::metaDataToJson(storage).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::respondContext(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');

    Context *context = contextFromUrl(path);

    if(!context) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("Invalid Url").toUtf8()));
        return;
    }

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, JsonExporter::contextToJson(context).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void ContentsService::respondEntity(QxtWebRequestEvent *event)
{
    QStringList path = event->url.path().split('/');

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
}

} // namespace LBDatabase
