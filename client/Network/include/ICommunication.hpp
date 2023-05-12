#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

class IRequest {
public:
    virtual ~IRequest() {}
    virtual void SetHeader(const std::string& key, const std::string& value) = 0;
    virtual void SetURL(const std::string& url) = 0;
    virtual void SetBody(std::vector<char> body) = 0;
};

class IResponse {
public:
    virtual ~IResponse() {}
    virtual unsigned int GetStatus(const std::string& url) = 0;
    virtual std::vector<char> GetBody() = 0;
};

using IResponseUPtr =  std::unique_ptr<IResponse>;
using IRequestUPtr =  std::unique_ptr<IRequest>;
using Callback = std::function<void(IResponseUPtr)>;
