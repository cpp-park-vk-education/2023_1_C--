#pragma once

#include <QtWebApp/httpserver/httprequest.h>

#include "IHttpRequest.hpp"

using namespace stefanfrings;

class HttpRequestAdapter : public IHttpRequest
{
public:
    HttpRequestAdapter(const HttpRequestAdapter&) = delete;

    HttpRequestAdapter(HttpRequestAdapter&&) = delete;

    HttpRequestAdapter() = delete;

    HttpRequestAdapter(HttpRequest* request) : request(request){}

    HttpMethods getMethod() const override;

    std::string getPath() const override;

    std::string getHeader(const std::string& name) const override;

    std::string getBody() const override;
    
private:
    HttpRequest* request;
};