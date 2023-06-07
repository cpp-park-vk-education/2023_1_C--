#pragma once
#include <QObject>
#include <QTcpSocket>
#include "ITcpConnection.hpp"

class TcpConnection: public QObject,
                     public ITcpConnection {
public:
    TcpConnection();
    void ConnectToHost() override;
    void DisconnectFromHost() override;
    void Write(const std::string& data) override;

    void SetRequestNewMessage(std::function<void(const int)> requestNewMessage) override {
        requestNewMessage_ = requestNewMessage;
    }
    
    void SetConfiguration(const std::string& host, unsigned short port) {
        host_ = "172.17.0.1"; // hard code
        port_ = port;
    }

private slots:
    void HandleReadyRead();

private:
    QString host_;
    qint16 port_;
    QTcpSocket* socket;
    std::function<void(const int)> requestNewMessage_;

};

using ITcpConnectionUPtr = std::unique_ptr<ITcpConnection>;
