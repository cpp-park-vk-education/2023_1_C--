#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "SendMessageService.hpp"
#include "TCPMessageReciver.hpp"

class SendMessageController : public IHttpRequestHandler
{
public:
    SendMessageController(std::unique_ptr<SendMessageService> service)
    : sendService(std::move(service))
    {
        messageRouter = std::make_unique<TcpMessageReciver>();
    }

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    std::unique_ptr<SendMessageService> sendService;

    std::unique_ptr<TcpMessageReciver> messageRouter;
};