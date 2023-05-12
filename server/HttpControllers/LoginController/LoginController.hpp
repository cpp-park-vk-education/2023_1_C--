#pragma once

#include <memory>
#include <QJsonObject>
#include <QJsonDocument>

#include "IHttpRequestHandler.hpp"
#include "LoginService.hpp"

class LoginController : public IHttpRequestHandler
{
public:
    LoginController(std::unique_ptr<LoginService> service) : loginService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    std::unique_ptr<LoginService> loginService;
};