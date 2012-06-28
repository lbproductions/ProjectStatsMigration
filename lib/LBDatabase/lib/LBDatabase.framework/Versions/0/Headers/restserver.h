#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <QObject>

class QxtHttpServerConnector;
class QxtHttpSessionManager;

namespace LBDatabase {

class MyService;
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
    MyService *m_service;
    Storage *m_storage;
};

}

#endif // RESTSERVER_H
