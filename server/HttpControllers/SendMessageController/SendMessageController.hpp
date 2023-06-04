#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>
#include <QTcpSocket>
#include <mutex>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "IHttpRequestHandler.hpp"
#include "SendMessageService.hpp"

class SendMessageController :public IHttpRequestHandler
{
public:
    SendMessageController(std::unique_ptr<SendMessageService> service, QObject* parent = nullptr) :
    sendService(std::move(service))
    {
        socket = std::make_unique<sf::TcpSocket>();

        socket->connect(sf::IpAddress("172.17.0.1"), 1337);
    }

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    std::unique_ptr<SendMessageService> sendService;

    std::unique_ptr<sf::TcpSocket> socket;

    std::mutex m;
};