#pragma once
#include "ISerializer.hpp"

class Serializer : public ISerializer {
public:
    std::vector<char> SerializeLoginData(const LoginData& data) override;
    std::vector<char> SerializeSignupData(const SignupData& data) override;
    std::vector<char> SerializeUserSettingData(const UserSettingData& data) override;
    std::vector<char> SerializeLogoutData(const LogoutData& data) override;
    std::vector<char> SerializeString(const std::string& data) override;
    std::vector<char> SerializeMessage(const Message& data) override;
    std::vector<char> SerializeRoomInfo(const RoomInfo& data) override;
};