#pragma once

#include <QtWebApp/httpserver/httpresponse.h>
#include "IHttpResponse.hpp"


using namespace stefanfrings;

class HttpResponseAdapter : public IHttpResponse
{
public:
    HttpResponseAdapter(const HttpResponseAdapter&) = delete;

    HttpResponseAdapter(HttpResponseAdapter&&) = delete;

    HttpResponseAdapter() = delete;

    HttpResponseAdapter(HttpResponse* response) : response(response){}

    void setStatus(const int code, const std::string description = "") override;

    void setHeader(const std::string& name, const std::string& value) override;

    void setBody(const std::string& data, bool last = false) override;
private:
    HttpResponse* response;
};