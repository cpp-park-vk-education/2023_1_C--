#pragma once

#include <gmock/gmock.h>

#include "IHttpRequestHandler.hpp"
#include "IHttpRequest.hpp"
#include "IHttpResponse.hpp"

class HttpRequestHandlerMock : public IHttpRequestHandler
{
public:
    MOCK_METHOD(void, service, (IHttpRequest*, IHttpResponse*));
};