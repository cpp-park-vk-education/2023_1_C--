#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using Headers = std::unordered_map<std::string, std::string>;

class IRequest {
public:
    virtual ~IRequest() {}
    virtual void SetHeader(const std::string& key, const std::string& value) = 0;
    virtual void SetUrl(const std::string& url) = 0;
    virtual void SetBody(std::vector<char>&& body) = 0;
    virtual Headers GetHeaders() = 0;
    virtual std::string GetUrl() = 0;
    virtual std::vector<char> GetBody() = 0;
};

using IRequestUPtr =  std::unique_ptr<IRequest>;
