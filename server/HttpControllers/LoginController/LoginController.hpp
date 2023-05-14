#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "LoginService.hpp"

class LoginController : public IHttpRequestHandler
{
public:
    LoginController(std::unique_ptr<LoginService> service) : loginService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:

    void fillJsonClient(QJsonObject& json,const Client& client);

    void fillJsonRooms(QJsonObject& json,const QVector<Room>& rooms);
    
    std::unique_ptr<LoginService> loginService;
};