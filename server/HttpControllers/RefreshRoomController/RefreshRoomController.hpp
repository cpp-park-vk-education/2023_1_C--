#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>
#include <QCryptographicHash>

#include "IHttpRequestHandler.hpp"
#include "RefreshRoomService.hpp"

class RefreshRoomController : public IHttpRequestHandler
{
public:
    RefreshRoomController(std::unique_ptr<RefreshRoomService> service) : refreshService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:

    void fillJsonClient(QJsonObject& json,const Client& client);

    void fillJsonRooms(QJsonObject& json,const QVector<Room>& rooms);
    
    std::unique_ptr<RefreshRoomService> refreshService;
};