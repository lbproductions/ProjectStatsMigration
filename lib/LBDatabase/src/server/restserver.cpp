#include "restserver.h"

#include "../attributevalue.h"
#include "../context.h"
#include "../entity.h"
#include "../function.h"
#include "../functionvalue.h"
#include "../propertyvalue.h"
#include "../relationvalue.h"
#include "../storage.h"

#include <QxtWeb/QxtHttpServerConnector>
#include <QxtWeb/QxtHttpSessionManager>
#include <QxtWeb/QxtAbstractWebService>
#include <QxtWeb/QxtWebPageEvent>
#include <QxtWeb/QxtWebRequestEvent>

#include <QxtCore/QxtJSON>

#include <QDebug>

namespace LBDatabase {

class MyService : public QxtAbstractWebService
{
public:
    MyService(Storage *storage, QxtAbstractWebSessionManager * sm, QObject * parent = 0 );
    ~MyService();
    void pageRequestedEvent ( QxtWebRequestEvent * event );

private:
    void respondRoot(QxtWebRequestEvent *event);
    void respondContext(QxtWebRequestEvent *event);
    void respondEntity(QxtWebRequestEvent *event);

    Storage *storage;
};

MyService::MyService(Storage *storage, QxtAbstractWebSessionManager *sm, QObject *parent) :
    QxtAbstractWebService(sm,parent),
    storage(storage)
{
}

MyService::~MyService()
{
}

void MyService::pageRequestedEvent(QxtWebRequestEvent *event)
{
    if(event->originalUrl == QUrl("/") ||
            event->originalUrl.isEmpty()) {
        respondRoot(event);
    }
    else {
        QStringList path = event->originalUrl.path().split('/');
        if(path.length() == 2 ||
                (path.length() == 3 && path.at(2).isEmpty())) {
            respondContext(event);
        }
        else if(path.length() == 3) {
            respondEntity(event);
        }
        else {
            postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 400, QByteArray("Invalid URL.")));
        }
    }
}

void MyService::respondRoot(QxtWebRequestEvent *event)
{
    QxtJSON json;

    QStringList contexts;
    contexts.reserve(storage->contexts().size());
    foreach(Context *context, storage->contexts()) {
        contexts.append(context->identifier());
    }


//    QString json = QLatin1String("{\n"
//                                 "\"contexts\": {");

//    foreach(Context *context, storage->contexts()) {
//        json += QLatin1String("\"") + context->identifier() + QLatin1String("\": {\n");
//        json += QLatin1String("\"url\": \"/") + context->identifier() + QLatin1String("\"\n");
//        json += QLatin1String("},\n");
//    }
//    json.remove(json.length()-2,1);
//    json += QLatin1String("}\n}");

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, json.stringify(contexts).toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void MyService::respondContext(QxtWebRequestEvent *event)
{
    QString contextIdentifier = event->originalUrl.path().split('/').at(1);

    Context *context = storage->context(contextIdentifier);

    if(!context) {
        postEvent(new QxtWebErrorEvent (event->sessionID, event->requestID, 404, QString("No such context in this storage: ").append(contextIdentifier).toUtf8()));
        return;
    }

    QString json = QLatin1String("{\n"
                   "\"") + context->identifier() + QLatin1String("\": [\n");

    bool first = true;
    foreach(Entity *entity, context->entities()) {
        if(first)
            first = false;
        else
            json += QLatin1String(",\n");

        json += QString::number(entity->id());
    }

    json += QLatin1String("]\n}");

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, json.toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

void MyService::respondEntity(QxtWebRequestEvent *event)
{
    QStringList path = event->originalUrl.path().split('/');

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


    QString json = QLatin1String("{\n");

        json += QLatin1String("\"") + entity->displayName();
        json += QLatin1String("\": { \n\"url\": \"/") + context->identifier() + QLatin1String("/")+QString::number(entity->id())+QLatin1String("\"");
        json += QLatin1String(",\n\"id\": \"") + QString::number(entity->id()) + QLatin1String("\",\n\"attributes\": {\n");

        bool first = true;
        foreach(Attribute* attribute, entity->entityType()->attributes()) {
            if(first)
                first = false;
            else
                json += QLatin1String(",\n");

            json += QLatin1String("\"");
            json += attribute->identifier();
            json += QLatin1String("\": \"");
//            json += entity->attributeValue(attribute->identifier())->dataForModel().toString().replace("\"","\\\"");
            json += QLatin1String("\"");
        }
        json += QLatin1String("\n},\n\"functions\": {\n");

        first = true;
        foreach(Function* function, entity->entityType()->functions()) {
            if(first)
                first = false;
            else
                json += QLatin1String(",\n");

            json += QLatin1String("\"");
            json += function->identifier();
            json += QLatin1String("\": {\n\"context\": \"");

            json += function->keyEntityType()->context()->identifier()+QLatin1String("\",\n\"values\": {\n");


            FunctionValue *functionValue = static_cast<FunctionValue*>(entity->propertyValue(function));

            QHashIterator<const Entity*, QVariant> i(functionValue->values());

            while (i.hasNext()) {
                if(i.hasPrevious()) {
                    json += QLatin1String(",\n");
                }
                i.next();
                json += QLatin1String("\"")+ QString::number(i.key()->id()) + QLatin1String("\": \"") + i.value().toString().replace("\"","\\\"") + QLatin1String("\"");
            }
            json += QLatin1String("\n}\n}");
        }
        json += QLatin1String("\n},\n\n\"relations\": {\n");

        first = true;
        foreach(Relation *relation, entity->entityType()->relations()) {
            if(first)
                first = false;
            else
                json += QLatin1String(",\n");

            RelationValue<Entity> *value = entity->relation<Entity>(relation->identifier());

            json += QLatin1String("\"");
            json += relation->identifier();
            json += QLatin1String("\": {\n\"context\": \"");

            json += relation->entityTypeOther()->context()->identifier()+QLatin1String("\",\n\"values\": [\n");

            bool first2 = true;
            foreach(Entity *relatedEntity, value->entities()) {
                if(first2)
                    first2 = false;
                else
                    json += QLatin1String(",\n");

                json += QString::number(relatedEntity->id());
            }
            json += QLatin1String("\n]");
            json += QLatin1String("\n}");
        }

        json += QLatin1String("\n}");

    json += QLatin1String("\n}");
    json += QLatin1String("\n}");

    QxtWebPageEvent* respond = new QxtWebPageEvent(event->sessionID, event->requestID, json.toUtf8());
    respond->contentType = QByteArray("application/json");
    postEvent(respond);
}

RestServer::RestServer(Storage *storage) :
    m_storage(storage)
{
}

RestServer::~RestServer()
{
}


void RestServer::start()
{
    m_connector = new QxtHttpServerConnector(this);

    m_session = new QxtHttpSessionManager(this);
    m_session->setPort(8080);
    m_session->setConnector(m_connector);

    m_service = new MyService(m_storage, m_session);
    m_session->setStaticContentService(m_service);

    m_session->start();
}

}
