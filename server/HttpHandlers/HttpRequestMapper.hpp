#pragma once

#include <QObject>
#include <map>
#include <memory>

#include "IHttpRequestHandler.hpp"

class HttpRequestMapper : public QObject, public IHttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(HttpRequestMapper)
public:
    HttpRequestMapper(QObject* parent = nullptr) : QObject(parent){}

    ~HttpRequestMapper(){};

    void service(IHttpRequest* request, IHttpResponse* response) override;

private:
    std::map<std::string, std::unique_ptr<IHttpRequestHandler>> controllerMap;
};