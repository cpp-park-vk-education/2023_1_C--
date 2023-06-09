#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>
#include <vector>

#include "IHttpRequestHandler.hpp"
#include "CreateRoomService.hpp"

class CreateRoomController : public IHttpRequestHandler
{
public:
    CreateRoomController(std::unique_ptr<CreateRoomService> service) : createService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:

    void fillJsonClients(QJsonObject& json, const std::vector<Client>& clients);
    
    std::unique_ptr<CreateRoomService> createService;
};