#pragma once
#include "IRequest.hpp"

class Request : public IRequest {
public:
    void SetHeader(const std::string& key, const std::string& value) override {
        headers_.insert({key, value});    
    }

    void SetUrl(const std::string& url) override {
        url_ = url;
    }

    void SetBody(std::vector<char>&& body) override {
        body_ = body;
    }
    
    Headers GetHeaders() override { return headers_; }
    
    std::string GetUrl() override { return url_; }
    
    std::vector<char> GetBody() override { return body_; }

private:
    std::string url_;
    Headers headers_;
    std::vector<char> body_;
};  
