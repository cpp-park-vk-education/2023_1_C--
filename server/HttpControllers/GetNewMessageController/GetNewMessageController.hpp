#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "GetNewMessageService.hpp"

class GetNewMessageController : public IHttpRequestHandler
{
public:
    GetNewMessageController(std::unique_ptr<GetNewMessageService> service) : getMessageService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    void fillJSONMessage(QJsonObject& json, const Message& message);

    std::unique_ptr<GetNewMessageService> getMessageService;
};