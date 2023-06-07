#pragma once

#include <memory>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "JoinRoomService.hpp"

class JoinRoomController : public IHttpRequestHandler
{
public:
    JoinRoomController(std::unique_ptr<JoinRoomService> service) : joinService(std::move(service)){}

    void service(IHttpRequest* request, IHttpResponse* response) override;
private:
    std::unique_ptr<JoinRoomService> joinService;
};