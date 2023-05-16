#pragma once
#include "ISerializer.hpp"

class Serializer : public ISerializer {
public:
    std::vector<char> SerializeLoginData(const LoginData& data) override;
    std::vector<char> SerializeSignupData(const SignupData& data) override;
    std::vector<char> SerializeID(const int id) override;
    std::vector<char> SerializeMessage(const Message& data) override;
    std::vector<char> SerializeRoomInfo(const RoomInfo& data) override;
};