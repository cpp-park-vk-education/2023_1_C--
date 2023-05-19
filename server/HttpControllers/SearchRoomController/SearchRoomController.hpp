#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "SearchRoomService.hpp"

class SearchRoomController : public IHttpRequestHandler
{
public:
    SearchRoomController(std::unique_ptr<SearchRoomService> service) : searchService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:

    void fillRoomJsonResponse(QJsonObject& json, const QVector<Room>& rooms);
    
    std::unique_ptr<SearchRoomService> searchService;
};