#pragma once
#include <string>
#include <memory>
#include <functional>

class ITcpConnection {
public:
    virtual ~ITcpConnection() {}
    virtual void ConnectToHost(const int roomID, const std::string& login, 
                         std::function<void(const int)> requestNewMessage) = 0;
    virtual void DisconnectFromHost() = 0;
};

using ITcpConnectionUPtr = std::unique_ptr<ITcpConnection>;
