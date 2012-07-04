#ifndef LBDATABASE_CONTENTSSERVICE_H
#define LBDATABASE_CONTENTSSERVICE_H

#include <QxtWeb/QxtAbstractWebService>

namespace LBDatabase {

class Storage;

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

    Storage *storage;
};

} // namespace LBDatabase

#endif // LBDATABASE_CONTENTSSERVICE_H
