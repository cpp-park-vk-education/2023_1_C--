#pragma once
#include <memory>
#include "LoginData.hpp"
#include "SignupData.hpp"

class IAccountNetwork {
public:
    virtual ~IAccountNetwork() {}
    virtual void Login(const LoginData& data) = 0;
    virtual void Signup(const SignupData& data) = 0;
};

using IAccountNetworkSPtr = std::shared_ptr<IAccountNetwork>;
