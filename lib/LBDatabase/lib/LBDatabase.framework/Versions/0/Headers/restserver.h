#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <QObject>

class QxtHttpServerConnector;
class QxtHttpSessionManager;

namespace LBDatabase {

class ContentsService;
class Storage;

class RestServer : public QObject
{
    Q_OBJECT
public:
    RestServer(Storage *storage);

    ~RestServer();

    void start();

private:
    QxtHttpServerConnector *m_connector;
    QxtHttpSessionManager *m_session;
    ContentsService *m_service;
    Storage *m_storage;
};

}

#endif // RESTSERVER_H
