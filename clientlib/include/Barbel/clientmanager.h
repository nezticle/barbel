#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

class QTcpSocket;

namespace Barbel {

class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager(QObject *parent = 0);

    void connectToHost(const QHostAddress &address, quint16 port);

signals:

private slots:

    void handleConnected();
    void handleDisconnected();
    void handleError(QAbstractSocket::SocketError socketError);
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);

private:
    QTcpSocket *m_tcpSocket;
    quint16 m_blocksize;
};
}

#endif // CLIENTMANAGER_H
