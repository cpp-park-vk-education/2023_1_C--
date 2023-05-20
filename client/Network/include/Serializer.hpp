#pragma once
#include "ISerializer.hpp"

class Serializer : public ISerializer {
public:
    std::vector<char> SerializeLoginData(const LoginData& data) override;
    std::vector<char> SerializeSignupData(const SignupData& data) override;
    std::vector<char> SerializeID(const int id) override;
    std::vector<char> SerializeMessage(const Message& data) override;
    std::vector<char> SerializeRoomCreation(std::string&& name,
                                            std::vector<std::string>&& members) override;
    std::vector<char> SerializeJoiningUser(const int roomID,
                                                       const std::string& login) override;
};