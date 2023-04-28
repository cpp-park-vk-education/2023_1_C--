#pragma once

#include "IHttpResponse.hpp"

#include <gmock/gmock.h>

class HttpResponseMock : public IHttpResponse
{
public:
    MOCK_METHOD(void, setStatus, (const int), (override));

    MOCK_METHOD(void, setHeader, (const std::string&, const std::string&), (override));

    MOCK_METHOD(void, setBody, (const std::string& ), (override));
};