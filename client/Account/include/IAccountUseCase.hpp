#pragma once
#include "Forms.hpp"

class IAccountUseCase {
public:
    virtual ~IAccountUseCase() {}
    virtual void Login(ILoginFormUPtr form) = 0;
    virtual void Signup(ISignupFormUPtr form) = 0;
};

using IAccountUseCaseSPtr = std::shared_ptr<IAccountUseCase>;