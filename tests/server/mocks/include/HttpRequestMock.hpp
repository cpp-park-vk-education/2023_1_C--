#pragma once

#include "IHttpRequest.hpp"

#include <gmock/gmock.h>

class HttpRequestMock : public IHttpRequest
{
public:
    MOCK_METHOD(int, getStatus, (), (const, override));

    MOCK_METHOD(HttpMethods, getMethod, (), (const, override));

    MOCK_METHOD(std::string, getPath, (), (const, override));

    MOCK_METHOD(std::string, getHeader, (), (const, override));

    MOCK_METHOD(std::string, getBody, (), (const, override));
};