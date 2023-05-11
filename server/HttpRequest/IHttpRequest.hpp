#pragma once

#include <string>
#include <map>


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

    virtual HttpMethods getMethod() const = 0;

    virtual std::string getPath() const = 0;

    virtual std::string getHeader() const = 0;

    virtual std::string getBody() const = 0;
};