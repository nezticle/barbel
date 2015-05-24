#include "clientconnection.h"
#include "scene.h"

#include <QtNetwork/QTcpSocket>
#include <QtCore/QDataSTream>
#include <QtCore/QTimer>

#include <QtCore/QDebug>

Barbel::Server::ClientConnection::ClientConnection(qintptr socketDescriptor, Barbel::Server::Scene *scene)
    : QObject(0)
    , m_socketDescriptor(socketDescriptor)
    , m_scene(scene)
    , m_socket(Q_NULLPTR)
    , m_pingTimer(Q_NULLPTR)
{

}

void Barbel::Server::ClientConnection::initialize()
{
    //Actually setup the connection here
    //as this gets called whenever we live in our own thread
    if (m_socket != Q_NULLPTR) {
        delete m_socket;
    }

    m_socket = new QTcpSocket(this);
    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        qDebug() << "Connection failed!";
        return;
    }

    //And if everything went well the connection is live
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));

    if (m_pingTimer != Q_NULLPTR)
        delete m_pingTimer;

    m_pingTimer = new QTimer();
    connect(m_pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));

    m_pingTimer->start(1000);
}

void Barbel::Server::ClientConnection::handleDisconnected()
{
    qDebug() << Q_FUNC_INFO;
    if (m_pingTimer != Q_NULLPTR)
        m_pingTimer->stop();
}

void Barbel::Server::ClientConnection::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug() << Q_FUNC_INFO;
}

void Barbel::Server::ClientConnection::handleReadyRead()
{
    qDebug() << Q_FUNC_INFO;
}

void Barbel::Server::ClientConnection::handleBytesWritten(qint64 bytes)
{
    Q_UNUSED(bytes)
    qDebug() << Q_FUNC_INFO;
}

void Barbel::Server::ClientConnection::sendPing()
{
    QByteArray block;

    QDataStream outStream(&block, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_5_5);
    outStream << (quint16)0;
    outStream << QString("ping");
    outStream.device()->seek(0);
    outStream << (quint16)(block.size() - sizeof(quint16));

    m_socket->write(block);
}
