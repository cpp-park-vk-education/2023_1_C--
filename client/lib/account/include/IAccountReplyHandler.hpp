#pragma once
#include "UserData.hpp"
#include <memory>
// #include <optional>

class IAccountReplyHandler {
public:
    virtual ~IAccountReplyHandler() {}
    virtual void OnLoginResponse(unsigned int statusCode, IUserDataUPtr userData) = 0;
    virtual void OnSignupResponse(unsigned int statusCode, IUserDataUPtr userData) = 0;
    virtual void OnUserSettingResponse(unsigned int statusCode, IUserDataUPtr userData) = 0;
    // virtual void OnLogOutResponse() = 0;
};

using IAccountReplyHandlerUPtr = std::unique_ptr<IAccountReplyHandler>;
