#pragma once

#include <string>

enum class HttpMethods
{
    GET = 0,
    POST,
    PUT,
    DELETE
};

class IHttpRequest
{
public:

    virtual int getStatus() const = 0;

    virtual HttpMethods getMethod() const = 0;

    virtual std::string getPath() const = 0;

    virtual std::string getHeader() const = 0;

    virtual std::string getBody() const = 0;
};