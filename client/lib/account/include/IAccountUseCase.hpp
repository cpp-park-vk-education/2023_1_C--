#pragma once
#include "Forms.hpp"

class IAccountUseCase {
public:
    virtual ~IAccountUseCase() {}
    virtual void Login(IFormUPtr form) = 0;
    virtual void Signup(IFormUPtr form) = 0;
    virtual void UserSetting(IFormUPtr form) = 0;
    virtual void Logout() = 0;
};

using IAccountUseCaseUPtr = std::unique_ptr<IAccountUseCase>;