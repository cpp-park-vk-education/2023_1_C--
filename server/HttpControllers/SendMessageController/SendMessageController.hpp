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

#include "IHttpRequestHandler.hpp"
#include "SendMessageService.hpp"


class SendMessageController : public IHttpRequestHandler
{
public:
    SendMessageController(std::unique_ptr<SendMessageService> service)
    : sendService(std::move(service))
    {
        socket = std::make_unique<QTcpSocket>();

        socket->connectToHost("172.17.0.1", 1337);
    }

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    std::unique_ptr<SendMessageService> sendService;

    std::unique_ptr<QTcpSocket> socket;

    std::mutex m;
};