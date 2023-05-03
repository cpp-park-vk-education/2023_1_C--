#pragma once

#include "HttpRequestHandler.hpp"

class HttpRequestMapper : public HttpRequestHandler
{
public:
    ~HttpRequestMapper();

    void service(IHttpRequest* request, IHttpResponse* response) override;
};