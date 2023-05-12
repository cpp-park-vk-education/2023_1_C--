#pragma once

#include <memory>

#include <QtWebApp/httpserver/httprequesthandler.h>
#include "IHttpRequestHandler.hpp"
#include "HttpRequestToIHttpRequestAdapter.hpp"
#include "HttpResponseToIHttpResponseAdapter.hpp"

using namespace stefanfrings;

class RequestMapperAdapter : public stefanfrings::HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(RequestMapperAdapter)

public:
    RequestMapperAdapter(std::unique_ptr<IHttpRequestHandler> requestMapper, QObject* parent) :
        requestMapper(std::move(requestMapper)), stefanfrings::HttpRequestHandler(parent){}

    ~RequestMapperAdapter() override 
    {}

    void service(HttpRequest& request, HttpResponse& response) override;

private:
    std::unique_ptr<IHttpRequestHandler> requestMapper;
};