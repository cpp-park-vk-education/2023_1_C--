#include "HttpResponseToIHttpResponseAdapter.hpp"

void HttpResponseAdapter::setStatus(const int code, const std::string description)
{
    response->setStatus(code, QByteArray::fromStdString(description));
}

void HttpResponseAdapter::setHeader(const std::string& name, const std::string& value)
{
    response->setHeader(
        QByteArray::fromStdString(name),
        QByteArray::fromStdString(value)
    );
}

void HttpResponseAdapter::setBody(const std::string& data, bool last)
{
    response->write(QByteArray::fromStdString(data), last);
}