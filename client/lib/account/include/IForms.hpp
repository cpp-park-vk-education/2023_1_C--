#pragma once
#include <memory>
#include "AccountData.hpp"

class ILoginForm {
public:
    virtual ~ILoginForm() {}
    virtual void validate() const = 0;
    virtual LoginData getLoginData() const = 0;
};

class ISignupForm {
public:
    virtual ~ISignupForm() {}
    virtual void validate() const = 0;
    virtual SignupData getSignupData() const = 0;
};

class IUserSettingForm {
public:
    virtual ~IUserSettingForm() {}
    virtual void validate() const = 0;
    virtual UserSettingData getUserSettingData() const = 0;
};

using ILoginFormUPtr = std::unique_ptr<ILoginForm>;
using ISignupFormUPtr = std::unique_ptr<ISignupForm>;
using IUserSettingFormUPtr = std::unique_ptr<IUserSettingForm>;
