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
};

class IAccountResponseDeserializer {
public:
    virtual ~IAccountResponseDeserializer() {}
    virtual IUserDataUPtr DeserializeResponse(const std::vector<char>& data) = 0;
};

using IAccountRequestSerializerSPtr = std::shared_ptr<IAccountRequestSerializer>;
using IAccountResponseDeserializerSPtr = std::shared_ptr<IAccountResponseDeserializer>;
