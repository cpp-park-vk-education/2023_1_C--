#pragma once
#include "IHttpRequestCreator.hpp"

class HttpRequestCreator : public IHttpRequestCreator {
public:
    Request CreateRequest(const std::string& urlPath) override {
        Request request;
        request.SetUrl("http://" + host_ + ":" + std::to_string(port_) + urlPath);
        request.SetHeader("Content-Type", "Json");
        return request;
    }

    Request CreateRequest(const std::string& urlPath, const Headers headers) override {
        Request request;
        request.SetUrl("http://" + host_ + ":" + std::to_string(port_) + urlPath);
        for (auto it = headers.begin(); it != headers.end(); ++it)
            request.SetHeader(it->first, it->second);
        return request;
    }

    void AddQueryString(Request& request, const QueryString& queryString) override {
        if (queryString.empty())
            return;
        auto url = request.GetUrl() + '?';
        for (auto it = queryString.begin(); it != queryString.end(); ++it)
            url += it->first + '=' + it->second;
        request.SetUrl(url);
    }


    void SetConfiguration(const std::string& host, unsigned short port) {
        host_ = host;
        port_ = port;
    }

private:
    std::string host_;
    unsigned short port_;
};
