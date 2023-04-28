#pragma once

#include <string>

class IHttpResponse
{
public:

    virtual void setStatus(const int code) = 0;

    virtual void setHeader(const std::string& name, const std::string& value) = 0;

    virtual void setBody(const std::string& data) = 0;
};