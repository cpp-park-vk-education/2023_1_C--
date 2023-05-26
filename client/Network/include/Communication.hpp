#pragma once
#include <QNetworkReply>
#include "ICommunication.hpp"

class Response : public IResponse {
public:
    Response() {}

    Response(bool status, std::vector<char>&& body) 
        : status_(status), body_(body) {}

    Response(bool status, std::string&& description) 
        : status_(status), description_(description) {}

    ~Response() {}

    bool GetStatus() override { return status_; }

    std::string GetDescreption() override { return description_; };
    
    std::vector<char> GetBody() override { return body_; }
    
private:
    bool status_;
    std::string description_;
    std::vector<char> body_;
};

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

Request createRequest(const std::string& url, Headers headers = {{"Content-Type", "JSON"}});