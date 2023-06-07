#pragma once

#include <memory>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>
#include <QJsonValue>

#include "IHttpRequestHandler.hpp"
#include "RegisterService.hpp"

class RegisterController : public IHttpRequestHandler
{
public:
    RegisterController(std::unique_ptr<RegisterService> service) : registerService(std::move(service)){}

    void service(IHttpRequest*, IHttpResponse*) override;

private:
    
    template<typename... Args>
    bool checkArgs(const Args&... args)
    {
        if (((args.isEmpty()), ...))
            return false;

        return true;
    }

    std::unique_ptr<RegisterService> registerService;
};