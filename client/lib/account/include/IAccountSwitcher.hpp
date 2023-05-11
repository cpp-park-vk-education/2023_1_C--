#pragma once
#include <memory>

class IAccountSwitcher {
public:
    ~IAccountSwitcher() {}
    virtual void ShowLoginPage() = 0;
    virtual void ShowSignupPage() = 0;
    virtual void ShowUserSettingPage() = 0;
};

using IAccountSwitcherUPtr = std::unique_ptr<IAccountSwitcher>;
