#include "clientmanager.h"

#include <QtNetwork/QTcpSocket>
#include <QtCore/QDataStream>
#include <QtCore/QByteArray>

#include <QtCore/QDebug>

Barbel::ClientManager::ClientManager(QObject *parent)
    : QObject(parent)
    , m_tcpSocket(new QTcpSocket(this))
    , m_blocksize(0)
    , m_connectionState(ClientManager::InitializedState)
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
    m_connectionState = ClientManager::ConnectingState;
    emit connectionStateChanged(m_connectionState);
}

Barbel::ClientManager::ConnectionState Barbel::ClientManager::connectionState() const
{
    return m_connectionState;
}

QString Barbel::ClientManager::errorString() const
{
    return m_errorString;
}

void Barbel::ClientManager::handleConnected()
{
    m_connectionState = ClientManager::ConnectedState;
    emit connectionStateChanged(m_connectionState);
}

void Barbel::ClientManager::handleDisconnected()
{
    m_connectionState = ClientManager::DisconnectedState;
    emit connectionStateChanged(m_connectionState);
}

void Barbel::ClientManager::handleError(QAbstractSocket::SocketError socketError)
{
    m_connectionState = ClientManager::ErrorState;
    emit connectionStateChanged(m_connectionState);

    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        m_errorString = "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        m_errorString = "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::HostNotFoundError:
        m_errorString =	"The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        m_errorString = "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        m_errorString = "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        m_errorString = "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        m_errorString = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        m_errorString = "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
    case QAbstractSocket::AddressInUseError:
        m_errorString = "The address specified to QAbstractSocket::bind() is already in use and was set to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        m_errorString = "The address specified to QAbstractSocket::bind() does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        m_errorString = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        m_errorString = "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        m_errorString = "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        m_errorString = "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        m_errorString = "Could not contact the proxy server because the connection to that server was denied";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        m_errorString = "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        m_errorString = "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        m_errorString = "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        m_errorString = "The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood.";
        break;
    case QAbstractSocket::OperationError:
        m_errorString = "An operation was attempted while the socket was in a state that did not permit it.";
        break;
    case QAbstractSocket::SslInternalError:
        m_errorString = "The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library.";
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        m_errorString = "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library.";
        break;
    case QAbstractSocket::TemporaryError:
        m_errorString = "A temporary error occurred (e.g., operation would block and socket is non-blocking).";
        break;
    default:
        m_errorString = "Unknown Socket Error";
        break;
    }
    emit errorStringChanged(m_errorString);
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
