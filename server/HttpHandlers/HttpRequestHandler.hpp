#pragma once

#include <qt5/QtCore/QObject>

#include "IHttpRequestHandler.hpp"

class HttpRequestHandler : public IHttpRequestHandler, public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HttpRequestHandler)

public:
    HttpRequestHandler(QObject *parent = nullptr) : QObject(parent) {}
};