#pragma once
#include <QObject>
#include <QTcpSocket>
#include "ITcpConnection.hpp"

class TcpConnection: public QObject,
                     public ITcpConnection {
public:
    TcpConnection();
    void ConnectToHost(const int roomID, const std::string& login,
                 std::function<void(const int)> requestNewMessage) override;
    void DisconnectFromHost() override;

private:
    QTcpSocket* socket;    
};

using ITcpConnectionUPtr = std::unique_ptr<ITcpConnection>;
