#pragma once
#include "AccountData.hpp"
#include <memory>

class IAccountReplyHandler {
public:
    virtual ~IAccountReplyHandler() {}
    virtual void OnLoginResponse(const int statusCode, UserData&& userData) = 0;
    virtual void OnSignupResponse(const int statusCode, UserData&& userData) = 0;
    virtual void OnUserSettingResponse(const int statusCode, UserData&& userData) = 0;
    virtual void OnLogoutResponse(const int statusCode) = 0;
};

using IAccountReplyHandlerSPtr = std::shared_ptr<IAccountReplyHandler>;
