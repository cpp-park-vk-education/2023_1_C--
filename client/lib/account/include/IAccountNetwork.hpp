#pragma once
#include <string>
#include <unordered_map>
#include <memory>

using TextData = std::unordered_map<std::string, std::string>;

class IAccountNetwork {
public:
    virtual ~IAccountNetwork() {}
    virtual void Login(const TextData& textData) = 0;
    virtual void Signup(const TextData& textData) = 0;
    virtual void UserSetting(const TextData& textData) = 0;
    virtual void Logout() = 0;
};

using IAccountNetworkUPtr = std::unique_ptr<IAccountNetwork>;
