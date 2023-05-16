#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "GetRoomHistoryService.hpp"

class GetRoomHistoryController : public IHttpRequestHandler
{
public:
    GetRoomHistoryController(std::unique_ptr<GetRoomHistoryService> service) : historyService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    void fillJSONMessage(QJsonObject& json, const QVector<Message>& messages);
    std::unique_ptr<GetRoomHistoryService> historyService;
};