#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtCore/QMap>

namespace Barbel {

namespace Server {
    class Scene;
    class ClientConnection;
}

class ServerManager : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerManager(QObject *parent = 0);
    ~ServerManager();

signals:

public slots:

private slots:
    void handleThreadFinished();

protected:
    void incomingConnection(qintptr handle);

private:
    void initServer();

    Barbel::Server::Scene *m_scene;
    QMap<QThread*,Barbel::Server::ClientConnection*> m_clients;
};

}

#endif // SERVER_H
