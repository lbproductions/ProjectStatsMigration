#include "restserver.h"

#include "contentsservice.h"

#include <QxtWeb/QxtHttpServerConnector>
#include <QxtWeb/QxtHttpSessionManager>
#include <QxtWeb/QxtWebServiceDirectory>

#include <QDebug>

namespace LBDatabase {

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

    m_service = new ContentsService(m_storage, m_session, m_session);

    m_session->setStaticContentService(m_service);

    m_session->start();
}

}
