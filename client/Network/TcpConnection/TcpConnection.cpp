#include <QHostAddress>
#include "TcpConnection.hpp"
#include <QDebug>

TcpConnection::TcpConnection() {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::stateChanged, this, [this](){
        qDebug() << socket->state();
    });
}

void TcpConnection::ConnectToHost() {
    qDebug() << "ConnectToHost(" + host_ + ", " + QString::number(port_) + ")";
    socket->connectToHost(host_, port_, QIODevice::ReadWrite);
}

void TcpConnection::Write(const std::string& data) {
    socket->write(data.c_str());
    connect(socket, &QTcpSocket::readyRead, this, &TcpConnection::HandleReadyRead);
    qDebug() << QString::fromStdString("Write(" +  data + ")");
}

void TcpConnection::HandleReadyRead() {
    auto data = socket->readAll();
    qDebug() << "Read(" + QString(data) + ")";
    requestNewMessage_(data.toInt());
}

void TcpConnection::DisconnectFromHost() {
    socket->disconnectFromHost();
    disconnect(socket, &QTcpSocket::readyRead, 0, 0);
    qDebug() << "DisconnectFromHost()\n";
}
