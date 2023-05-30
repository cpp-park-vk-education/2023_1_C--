#include <QHostAddress>
#include "TcpConnection.hpp"

#include <QDebug>

TcpConnection::TcpConnection() {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::stateChanged, this, [this](){
        qDebug() << socket->state();
    });
}

void TcpConnection::ConnectToHost(const int roomID, const std::string& login,
                                  std::function<void(const int)> requestNewMessage) 
{
    qDebug() << "ConnectToHost";
    socket->connectToHost(QHostAddress("127.0.0.1"), 1337, QIODevice::ReadWrite);

    auto data = std::to_string(roomID) + " " + login;
    qDebug() << QString::fromStdString(data);
    socket->write(data.c_str());

    connect(socket, &QTcpSocket::readyRead, this, [requestNewMessage, roomID](){
        requestNewMessage(roomID);
    });
}

void TcpConnection::DisconnectFromHost() {
    qDebug() << "DisconnectFromHost";
    socket->disconnectFromHost();
    disconnect(socket, &QTcpSocket::readyRead, 0, 0);
}
