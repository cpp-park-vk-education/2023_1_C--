#include "HttpRequestToIHttpRequestAdapter.hpp"

HttpMethods HttpRequestAdapter::getMethod() const
{
    auto method = request->getMethod().toStdString();

    if (method == "GET")
        return HttpMethods::GET;
    else if (method == "POST")
        return HttpMethods::POST;
    else if (method == "PUT")
        return HttpMethods::PUT;
    else if (method == "DELETE")
        return HttpMethods::DELETE;
    
    return HttpMethods::UNK;
}

std::map<std::string, std::string> HttpRequestAdapter::getParameters() const
{
    std::map<std::string, std::string> parameters;
    auto parameterMap = request->getParameterMap();
    for (const auto& param : parameterMap.toStdMap())
        parameters.insert({param.first.toStdString(), param.second.toStdString()});
    return parameters;
}

std::string HttpRequestAdapter::getPath() const
{
    return request->getPath().toStdString();
}

std::string HttpRequestAdapter::getHeader(const std::string& name) const
{
    return request->getHeader(QByteArray::fromStdString(name)).toStdString();
}

std::string HttpRequestAdapter::getBody() const
{
    return request->getBody().toStdString();
}