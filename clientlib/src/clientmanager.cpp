#include "clientmanager.h"

#include <QtNetwork/QTcpSocket>
#include <QtCore/QDataStream>
#include <QtCore/QByteArray>

#include <QtCore/QDebug>

Barbel::ClientManager::ClientManager(QObject *parent)
    : QObject(parent)
    , m_tcpSocket(new QTcpSocket(this))
    , m_blocksize(0)
{
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
}

void Barbel::ClientManager::connectToHost(const QHostAddress &address, quint16 port)
{
    m_tcpSocket->abort();
    m_blocksize = 0;
    m_tcpSocket->connectToHost(address, port);
}

void Barbel::ClientManager::handleConnected()
{
    qDebug() << Q_FUNC_INFO;
}

void Barbel::ClientManager::handleDisconnected()
{
    qDebug() << Q_FUNC_INFO;
}

void Barbel::ClientManager::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug() << Q_FUNC_INFO;
}

void Barbel::ClientManager::handleReadyRead()
{
    qDebug() << Q_FUNC_INFO;

    QDataStream inStream(m_tcpSocket);
    inStream.setVersion(QDataStream::Qt_5_5);

    if (m_blocksize == 0) {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
    }

    inStream >> m_blocksize;

    if (m_tcpSocket->bytesAvailable() < m_blocksize)
        return;

    QString type;

    inStream >> type;

    qDebug() << "read message" << type;

}

void Barbel::ClientManager::handleBytesWritten(qint64 bytes)
{
    Q_UNUSED(bytes)
    qDebug() << Q_FUNC_INFO;
}
