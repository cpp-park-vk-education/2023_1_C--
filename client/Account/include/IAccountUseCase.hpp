#pragma once
#include "Forms.hpp"

class IAccountUseCase {
public:
    virtual ~IAccountUseCase() {}
    virtual void Login(ILoginFormUPtr form) = 0;
    virtual void Signup(ISignupFormUPtr form) = 0;
    virtual void UserSetting(IUserSettingFormUPtr form) = 0;
    virtual void Logout(const std::string& token) = 0;
};

using IAccountUseCaseSPtr = std::shared_ptr<IAccountUseCase>;