#pragma once
#include <string>
#include <memory>
#include "Request.hpp"

using QueryString = std::unordered_map<std::string, std::string>;

class IHttpRequestCreator {
public:
    virtual ~IHttpRequestCreator() {}
    virtual Request CreateRequest(const std::string& urlPath) = 0;
    virtual Request CreateRequest(const std::string& urlPath, const Headers headers) = 0;
    virtual void AddQueryString(Request& request, const QueryString& queryString) = 0;
};

using IHttpRequestCreatorSPtr = std::shared_ptr<IHttpRequestCreator>;
