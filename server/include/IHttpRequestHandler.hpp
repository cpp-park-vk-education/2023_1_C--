#pragma once

#include <memory>

#include "IHttpRequest.hpp"
#include "IHttpResponse.hpp"

template <typename T>
using Shared = std::shared_ptr<T>;

class IHttpRequestHandler
{
public:
    virtual void service(IHttpRequest* request, IHttpResponse* response) = 0;
};