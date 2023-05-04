#pragma once
#include <memory>

class IAccountPagesSwitcher {
public:
    ~IAccountPagesSwitcher() {}
    virtual void ShowLoginPage() = 0;
    virtual void ShowSignupPage() = 0;
    virtual void ShowUserSettingPage() = 0;
};

using IAccountPagesSwitcherUPtr = std::unique_ptr<IAccountPagesSwitcher>;
