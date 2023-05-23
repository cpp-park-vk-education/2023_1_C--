#include <QHostAddress>
#include "TcpConnection.hpp"

TcpConnection::TcpConnection() {
    socket = new QTcpSocket;

    connect(socket, &QTcpSocket::stateChanged, this, [this](){
        qDebug() << socket->state();
    });
}

TcpConnection::~TcpConnection() {
    delete socket;
}

void TcpConnection::ConnectToHost(const int roomID, const std::string& login,
                            std::function<void(const int)> requestNewMessage) 
{
    socket->connectToHost(QHostAddress("127.0.0.1"), 1337, QIODevice::ReadWrite);

    auto data = roomID + " " + login;
    socket->write(data.c_str());

    connect(socket, &QTcpSocket::readyRead, this, [requestNewMessage, roomID](){
        requestNewMessage(roomID);
    });
}

void TcpConnection::DisconnectFromHost() {
    socket->disconnectFromHost();
    disconnect(socket, 0, 0, 0);
}
