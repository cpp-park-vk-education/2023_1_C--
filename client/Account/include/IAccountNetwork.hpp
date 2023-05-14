#pragma once
#include "AccountData.hpp"
#include "IAccountNetwork.hpp"
#include <string>
#include <unordered_map>
#include <memory>

class IAccountNetwork {
public:
    virtual ~IAccountNetwork() {}
    virtual void Login(const LoginData& data) = 0;
    virtual void Signup(const SignupData& data) = 0;
    virtual void UserSetting(const UserSettingData& data) = 0;
    virtual void Logout(const LogoutData& data) = 0;
};

using IAccountNetworkSPtr = std::shared_ptr<IAccountNetwork>;
