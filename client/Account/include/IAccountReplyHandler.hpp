#pragma once
#include "AccountData.hpp"
#include <memory>

class IAccountReplyHandler {
public:
    virtual ~IAccountReplyHandler() {}
    virtual void OnLoginResponse(UserData&& userData) = 0;
    virtual void OnLoginResponse(std::string&& error) = 0;
    virtual void OnSignupResponse(UserData&& userData) = 0;
    virtual void OnSignupResponse(std::string&& error) = 0;
};

using IAccountReplyHandlerSPtr = std::shared_ptr<IAccountReplyHandler>;
