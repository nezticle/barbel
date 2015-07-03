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
    Q_PROPERTY(ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
public:
    enum ConnectionState
    {
        InitializedState,
        ConnectingState,
        ConnectedState,
        DisconnectedState,
        ErrorState
    };
    Q_ENUM(ConnectionState)

    explicit ClientManager(QObject *parent = 0);

    void connectToHost(const QHostAddress &address, quint16 port);

    ConnectionState connectionState() const;
    QString errorString() const;

signals:
    void connectionStateChanged(ConnectionState connectionState);
    void errorStringChanged(QString errorString);

private slots:

    void handleConnected();
    void handleDisconnected();
    void handleError(QAbstractSocket::SocketError socketError);
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);

private:
    QTcpSocket *m_tcpSocket;
    quint16 m_blocksize;
    ConnectionState m_connectionState;
    QString m_errorString;
};
}
Q_DECLARE_METATYPE(Barbel::ClientManager*)

#endif // CLIENTMANAGER_H
