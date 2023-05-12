#pragma once
#include "ICommunication.hpp"
#include <unordered_map>
#include <string>

using Headers = std::unordered_map<std::string, std::string>;

class Request : public IRequest {
public:
    void SetHeader(const std::string& key, const std::string& value) override {
        headers_.insert({key, value});
    }
    void SetURL(const std::string& url) override { url_ = url; }
    void SetBody(std::vector<char> body) override {
        body = std::move(body_);
    }

private:
    std::string url_;
    std::unordered_map<std::string, std::string> headers_;
    std::vector<char> body_;
};

inline Request CreateRequest(const std::string& url, const Headers& headers) {
    Request request;
    for (auto it = headers.begin(); it != headers.end(); it++) {
        request.SetHeader(it->first, it->second);
    }
    request.SetURL(url);
    return request;
}
