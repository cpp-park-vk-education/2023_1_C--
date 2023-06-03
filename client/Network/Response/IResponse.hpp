#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

class IResponse {
public:
    virtual ~IResponse() {}
    virtual bool GetStatus() = 0;
    virtual std::string GetDescreption() = 0;
    virtual std::vector<char> GetBody() = 0;
};

using IResponseUPtr =  std::unique_ptr<IResponse>;
using Callback = std::function<void(IResponseUPtr)>;
