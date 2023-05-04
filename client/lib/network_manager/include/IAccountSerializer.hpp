#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "UserData.hpp"
#include "AccountData.hpp"

class IAccountRequestSerializer {
public:
    virtual ~IAccountRequestSerializer() {}
    virtual std::vector<char> SerializeLoginData(const LoginData& data) = 0;
    virtual std::vector<char> SerializeSignupData(const SignupData& data) = 0;
    virtual std::vector<char> SerializeUserSettingData(const UserSettingData& data) = 0;
    virtual std::vector<char> SerializeLogoutData(const LogoutData& data) = 0;
    virtual LoginData DeserializeLoginData(const std::vector<char>& data) = 0;
    virtual SignupData DeserializeSignupData(const std::vector<char>& data) = 0;
    virtual UserSettingData DeserializeUserSettingData(const std::vector<char>& data) = 0;
    virtual LogoutData DeserializeLogoutData(const std::vector<char>& data) = 0;
};

class IAccountResponseSerializer {
public:
    virtual ~IAccountResponseSerializer() {}
    virtual std::vector<char> SerializeResponse(IUserDataUPtr data) = 0;
    virtual IUserDataUPtr DeserializeResponse(const std::vector<char>& data) = 0;
};

using IAccountRequestSerializerUPtr = std::unique_ptr<IAccountRequestSerializer>;
using IAccountResponseSerializerUPtr = std::unique_ptr<IAccountResponseSerializer>;
