#ifndef LBDATABASE_CONTENTSSERVICE_H
#define LBDATABASE_CONTENTSSERVICE_H

#include <QxtWeb/QxtAbstractWebService>

class QUrl;
template<class First, class Second>
struct QPair;

namespace LBDatabase {

class Storage;
class Context;
class Entity;
template<class EntityClass>
class RelationValue;

class ContentsService : public QxtAbstractWebService
{
public:
    ContentsService(Storage *storage, QxtAbstractWebSessionManager * sm, QObject * parent = 0 );
    ~ContentsService();
    void pageRequestedEvent ( QxtWebRequestEvent * event );

private:
    void respondRoot(QxtWebRequestEvent *event);
    void respondContext(QxtWebRequestEvent *event);
    void respondEntity(QxtWebRequestEvent *event);
    void respondRelation(QxtWebRequestEvent *event);

    void patchEntity(QxtWebRequestEvent *event);
    void patchEntity(Entity *entity, const QPair<QString, QString> &queryItems);

    void postRelation(QxtWebRequestEvent *event);
    void postRelation(RelationValue<Entity> *relation, const QPair<QString, QString> &queryItems);

    void postContext(QxtWebRequestEvent *event);

    void postFunction(QxtWebRequestEvent *event);

    Context *contextFromUrl(const QStringList &path) const;
    Entity *entityFromUrl(const QStringList &path) const;
    RelationValue<Entity> *relationValueFromUrl(const QStringList &path) const;

    Storage *storage;
};

} // namespace LBDatabase

#endif // LBDATABASE_CONTENTSSERVICE_H
