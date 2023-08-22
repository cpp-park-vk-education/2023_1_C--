#pragma once

#include <map>
#include <memory>

#include "IHttpRequestHandler.hpp"

template<typename T, typename InterfaceType = IHttpRequestHandler>
concept ImplementInterface = requires(T a, InterfaceType* b)
{
    b = &a;
};

class HttpRequestMapper : public IHttpRequestHandler
{
    using UniqueHandler = std::unique_ptr<IHttpRequestHandler>;
public:
    HttpRequestMapper();

    ~HttpRequestMapper(){}

    template<typename Controller, typename Service, typename... DbManager>
    requires ImplementInterface<Controller>
    void addController(const std::string& path, DbManager&... DbManagers);

    void service(IHttpRequest* request, IHttpResponse* response) override;


private:
    std::map<std::string, UniqueHandler> controllerMap;
};

template<typename Controller, typename Service, typename... DbManager>
requires ImplementInterface<Controller>
void HttpRequestMapper::addController(const std::string& path, DbManager&... DbManagers)
{
    controllerMap.insert(
        std::make_pair(path, std::make_unique<Controller>(
            (std::make_unique<Service>(DbManagers...))
        ))
    );
}