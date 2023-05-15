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

class SendMessageController : public IHttpRequestHandler
{
public:
    SendMessageController(std::unique_ptr<SendMessageService> service) : sendService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    std::unique_ptr<SendMessageService> sendService;
};