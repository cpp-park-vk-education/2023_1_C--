#pragma once

#include <map>
#include <memory>

#include "IHttpRequestHandler.hpp"

class HttpRequestMapper : public IHttpRequestHandler
{
    using UniqueHandler = std::unique_ptr<IHttpRequestHandler>;
public:
    HttpRequestMapper();

    HttpRequestMapper(std::map<std::string, UniqueHandler>&& controllerMap) : controllerMap(std::move(controllerMap)){}

    ~HttpRequestMapper(){}

    void service(IHttpRequest* request, IHttpResponse* response) override;

private:
    std::map<std::string, UniqueHandler> controllerMap;
};