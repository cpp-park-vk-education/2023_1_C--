#pragma once
#include <string>
#include <memory>
#include <functional>

class ITcpConnection {
public:
    virtual ~ITcpConnection() {}
    virtual void ConnectToHost() = 0;
    virtual void DisconnectFromHost() = 0;
    virtual void Write(const std::string& data) = 0;
    virtual void SetRequestNewMessage(std::function<void(const int)> requestNewMessage) = 0;
};

using ITcpConnectionUPtr = std::unique_ptr<ITcpConnection>;
