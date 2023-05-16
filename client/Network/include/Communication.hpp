#pragma once
#include "ICommunication.hpp"
#include <QNetworkReply>

class Response : public IResponse {
public:

    Response(const int status, std::vector<char> body)
        : status_(status) {
        body_ = std::move(body);
    }

    const int GetStatus() override { return status_; }

    std::vector<char> GetBody() override { return body_; }

public:
    int status_;
    std::vector<char> body_;
};

QNetworkRequest CreateRequest(const std::string& url,
                              const std::string& contentType = "Json");
