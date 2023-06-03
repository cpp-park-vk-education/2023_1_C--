#pragma once
#include <memory>
#include "LoginData.hpp"
#include "SignupData.hpp"

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

using ILoginFormUPtr = std::unique_ptr<ILoginForm>;
using ISignupFormUPtr = std::unique_ptr<ISignupForm>;
