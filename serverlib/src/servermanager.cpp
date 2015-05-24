#include "servermanager.h"
#include "scene.h"

#include "clientconnection.h"

#include <QtCore/QThread>

Barbel::ServerManager::ServerManager(QObject *parent)
    : QTcpServer(parent)
    , m_scene(Q_NULLPTR)
{
    initServer();
}

Barbel::ServerManager::~ServerManager()
{
    foreach (QThread *thread, m_clients.keys()) {
        Barbel::Server::ClientConnection *client = m_clients.value(thread, Q_NULLPTR);
        client->deleteLater();
        thread->quit();
        thread->wait();
    }
    m_clients.empty();
}

void Barbel::ServerManager::handleThreadFinished()
{
    QThread *thread = qobject_cast<QThread*>(sender());
    Barbel::Server::ClientConnection *client = m_clients.value(thread, Q_NULLPTR);
    m_clients.remove(thread);
    if (client != Q_NULLPTR)
        client->deleteLater();
    thread->deleteLater();
}


void Barbel::ServerManager::incomingConnection(qintptr handle)
{
    Barbel::Server::ClientConnection *client = new Barbel::Server::ClientConnection(handle, m_scene);
    QThread *clientThread = new QThread(this);
    client->moveToThread(clientThread);
    connect(clientThread, SIGNAL(finished()), this, SLOT(handleThreadFinished()));
    clientThread->start();
    QMetaObject::invokeMethod(client, "initialize", Qt::QueuedConnection);
    m_clients.insert(clientThread, client);
}

void Barbel::ServerManager::initServer()
{
    m_scene = new Barbel::Server::Scene(this);
}
