#pragma once

#include <memory>

#include "IHttpRequest.hpp"
#include "IHttpResponse.hpp"

class IHttpRequestHandler
{
public:
    virtual void service(IHttpRequest* request, IHttpResponse* response) = 0;
};