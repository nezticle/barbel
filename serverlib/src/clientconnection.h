#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>

class QTimer;

namespace Barbel {
namespace Server {

class Scene;

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    enum MessageType {
        PingType,
        PongType,
        CommandType,
        UpdateType
    };
    Q_ENUM(MessageType)


    explicit ClientConnection(qintptr socketDescriptor, Scene *scene);

signals:

public slots:
    void initialize();

private slots:
    void handleDisconnected();
    void handleError(QAbstractSocket::SocketError socketError);
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);

    void sendPing();

private:
    qintptr m_socketDescriptor;
    Scene *m_scene;

    QTcpSocket *m_socket;
    QTimer *m_pingTimer;
};

}
}

#endif // CLIENTCONNECTION_H
